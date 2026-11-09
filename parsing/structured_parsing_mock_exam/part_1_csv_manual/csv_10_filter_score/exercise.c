#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "exercise.h"

/* TODO: implement the function described in README.md. */



static int fct(char**token , char* buff , size_t size)
{

   if(*token ==NULL)return 0;
   char* v=strchr(*token,',');
   
   size_t len;
   if(v)
   {
      len =(size_t)(v-*token);

   }
   else 
   {
      len=strcspn(*token, "\r\n");
   }
   if (len >=size)
   {
      return 0;
   }
   
   memcpy(buff,*token,len);
   buff[len]='\0';
   if(v)
   {
      *token=v+1;
   }
   else 
   {
      *token=NULL;
   }
   return 1;





}

int csv_filter_score(const char *input, const char *output, double min_score)
{
   FILE*f=fopen(input,"r");
   if(!f)return 0;
   FILE*out=fopen(output,"w");
   if(!out)
   {
      fclose(f);
      return 0;
   }
   char* line=NULL;
   size_t size=0;
   if(getline(&line,&size,f)== -1)
   {
      free(line);
      fclose(f);
      fclose(out);
      return 0;
   }
   fputs(line,out);
   while(getline(&line,&size,f)!=-1)
   {
      char*token=line;
      char id[34];
      char name[64];
      char score[322];


      if(!fct(&token,id,sizeof(id)))continue;
      if(!fct(&token,name,sizeof(name)))continue;
      if(!fct(&token , score,sizeof(score)))continue;
      double res=atof(score);
      if (res >=min_score)
      {
         fputs(line,out);
      }



   }
   free(line);
   fclose(f);
   fclose(out);
   return 1;
   
}
