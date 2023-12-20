#include <err.h>
#include <string.h>

#include "htab.h"
#include "stdint.h"
#include "stdlib.h"

uint32_t hash(char *key)
{
	size_t i = 0;
	uint32_t hash = 0;
	while(key[i] != 0)
	{
		hash += key[i++];
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return hash;
}

struct htab *htab_new()
{
	struct htab * tab = malloc(sizeof(struct htab));
	tab->capacity = 4;
	tab->size = 0;
	tab->data = malloc(4 * sizeof(struct pair));
	for(size_t i = 0; i < 4; i++)
	{
		tab->data[i].hkey = 0;
		tab->data[i].key = 0;
		tab->data[i].value = 0;
		tab->data[i].next = NULL;
	}
	return tab;
}

void htab_clear(struct htab *ht)
{
	ht->size = 0;
	for(size_t i = 0;i < ht->capacity > 0; i++)
	{
		struct pair * tp = &(ht->data[i]);
		tp = tp->next;
		struct pair * prev;
		while(tp)
		{
			prev = tp->next;
			free(tp);
			tp = prev;
		}
		ht->data[i].next = NULL;
	}
}

void htab_free(struct htab *ht)
{
    free(ht->data);
    free(ht);
}

struct pair *htab_get(struct htab *ht, char *key)
{
	uint32_t h = hash(key);
	struct pair * tp = &(ht->data[h%(ht->capacity)]);
	while(tp && tp->key != key)
		tp = tp->next;
	return tp;
}

int htab_insert(struct htab *ht, char *key, void *value)
{
    if(htab_get(ht,key) != NULL)
	    return 0;
    else
    {
	uint32_t h = hash(key);
	struct pair * tp = &(ht->data[h%(ht->capacity)]);
	while(tp->next)
		tp = tp->next;
	tp->next = malloc(sizeof(struct pair));
	tp->next->hkey = h;
	tp->next->key = key;
	tp->next->value = value;
	tp->next->next = NULL;
	(ht->size)++;
	if((double)ht->size/(double)ht->capacity > 0.75)
	{
		ht->capacity*=2;
		ht->data = realloc(ht->data,ht->capacity*sizeof(struct pair));
		size_t i;
		for(i = ht->capacity /2; i < ht->capacity; i++)
		{
			ht->data[i].hkey = 0;
			ht->data[i].key = 0;
			ht->data[i].value = 0;
			ht->data[i].next = NULL;
		}
		struct pair * pairs = malloc(sizeof(struct pair));
		int len = 0;
		for(i = 0; i < ht->capacity/2;i++)
		{
			struct pair * tp = &(ht->data[i]);
			tp = tp->next;
			struct pair * prev;

			while(tp)
			{
				prev = tp->next;
				len++;
				pairs = realloc(pairs,len*sizeof(struct pair));
				pairs[len-1] = *tp;
				tp = prev;
			}
		}
		htab_clear(ht);
		for(i=0; i < len; i++)
			htab_insert(ht, pairs[i].key,pairs[i].value);
		free(pairs);
	}
	return EXIT_SUCCESS;
    }
}

void htab_remove(struct htab *ht, char *key)
{
	uint32_t h = hash(key);
	struct pair * tp = &(ht->data[h%(ht->capacity)]);
	struct pair * prev = NULL;
	while(tp && tp->key != key)
	{
		prev = tp;
		tp = tp->next;
	}
	if(tp)
	{
		prev->next = tp->next;
		free(tp);
		(ht->size)--;
	}
}
