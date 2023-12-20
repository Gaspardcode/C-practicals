#include <stdlib.h>
#include <string.h>
char* replace(const char* s, const char* from, const char* to)
{
   int c = 0;
   int len = 0;
   int str1 = strlen(to);
   int str2 = strlen(from);
   int * occ = calloc(1,sizeof(int));
   for(int i = 0; s[i] != 0; i++)
   {
        len++;
        int k = str2;
        for(int j = i; from[j-i] != 0 && s[j] == from[j-i];j++,k--);
        if(!k) // k == 0
        {
                c++;
                occ[c-1] = i;
                occ = realloc(occ, (c+1)*sizeof(int));
        }
   }
   char * r = calloc(len + c*(str1 - str2) + 1, 1);
   int pos = 0;
   if(c > 0)
   {
        for(int j = 0; j < occ[0];j++,pos++)
                r[pos] = s[j];
        for(int j = occ[0]; j < occ[0] + str1; j++,pos++)
                r[pos] = to[j - occ[0]];
   }
   for(int i = 1; i < c; i++)
   {
        for(int j = occ[i-1]; j < occ[i];j++,pos++)
                r[pos] = s[j];
        for(int j = occ[i]; j < occ[i] + str1; j++,pos++)
                r[pos] = to[j - occ[i]];
   }
   for(int i = occ[c-1] + str1 - 1; s[i] != 0; i++,pos++)
        r[pos] = s[i];
   free(occ);
   return r;
}
