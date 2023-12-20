#include <stdio.h>
#include "htab.h"
#include "htab.c"

void print_pair(struct pair * h)
{
	struct pair * tp = h;
	while(tp)
	{
		printf("(0x%x,%s,%s,%d) -> ",tp->hkey,tp->key,tp->value,
				tp->next);
		tp = tp->next;
	}
}
void print_tab(struct htab * ht)
{
	printf("(%d,%d,%d%)\n", ht->capacity,ht->size,
			(100*ht->size)/ht->capacity);
	for(size_t i = 0; i < ht->capacity; i++)
	{
		printf("%d ",i);
		print_pair(&(ht->data[i]));
		printf("\n");
	}
}
void is_there(struct htab * ht,char * value)
{
	struct pair * p = htab_get(ht,value);
	if(p == NULL)
		printf("Not here\n");
	else
		printf("Here : (0x%x,%s,%s)\n",p->hkey,p->key,p->value);
}
void tab_remove(struct htab * ht, char * value)
{
	htab_remove(ht,value);
	printf("removed %s\n",value);
}
int main(int argc, char **argv)
{
/*
	struct pair * tp = malloc(sizeof(struct pair));
	printf("%s\n",argv[1]);
	printf("0x%x\n",hash(argv[1]));
*/

	struct htab * ht = htab_new();
	htab_insert(ht,"France","Paris");
	htab_insert(ht,"Spain","Madrid");
	htab_insert(ht,"Irland","Dublin");
	htab_insert(ht,"Russia","Moscow");
	htab_insert(ht,"Irland","Dublin");
	htab_insert(ht,"China","Pekin");
	htab_insert(ht,"Japan","Tokyo");
	htab_insert(ht,"India","New Delhi");
	htab_insert(ht,"Saudi Arabia","Riyadh");
	htab_insert(ht,"Liban","Beirut");
	htab_insert(ht,"Morocco","Rabat");
	htab_insert(ht,"Canada","Ottawa");
	htab_insert(ht,"U.S","Washington");
	htab_insert(ht,"Germany","Berlin");
	htab_insert(ht,"Israel","Jerusalem");
	htab_insert(ht,"Iran","Tehran");
	htab_insert(ht,"Irak","Baghdad");
	htab_insert(ht,"Libya","Tripoli");
	htab_insert(ht,"Egypt","Cairo");
	htab_insert(ht,"Sweeden","Stockholm");
	htab_insert(ht,"Norway","Oslo");
	htab_insert(ht,"Turkey","Ankara");
	htab_insert(ht,"Syria","Damascus");
	htab_insert(ht,"Afghanistan","Kabul");
	htab_insert(ht,"Nepal","Kathmandu");

	print_tab(ht);
	is_there(ht,"France");
	is_there(ht,"China");

	tab_remove(ht,"France");
	tab_remove(ht,"Russia");

	print_tab(ht);

	htab_clear(ht);

	print_tab(ht);

	htab_insert(ht,"France","Paris");
	htab_insert(ht,"Spain","Madrid");
	htab_insert(ht,"Irland","Dublin");
	htab_insert(ht,"Russia","Moscow");
	htab_insert(ht,"Irland","Dublin");
	htab_insert(ht,"China","Pekin");

	print_tab(ht);

	htab_clear(ht);
	htab_free(ht);
	return 0;
}
