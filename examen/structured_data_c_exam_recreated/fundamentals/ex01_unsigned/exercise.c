#define _POSIX_C_SOURCE 200809L
#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned int  parse_unit(char *decimal)
{
   const char*filename="units.csv";
   FILE*f=fopen(filename,"r");
   if(!f)return 0;
   char*line=NULL;
   size_t size=0;
   if(getline(&line,&size,f)==-1)
   {
        free(line);
        fclose(f);
        return 0;

   }
   char* token=strtok(line,",");
   int i=0;
   
   int cl=0;
   while(token)
   {
        int len=strlen(token);
        if(len >0 && token[len-1]=='\n')
        {
            token[len-1]='\0';

        }
        if(strcmp(token,decimal)==0)
        {
            cl=i;
            break;
        }
        token=strtok(NULL,",");
        i++;

   }
  
        char*t=decimal;
        int j=0;

        while(t && j<cl)
        {

            char*v=strchr(t,',');
            if(v!=NULL)
            {
                t=v+1;
            }
            else 
            {
                t=NULL;
            }
            j++;
        }
        if(t==NULL)return 0;
        char* n=strchr(t,',');
        size_t len;
        if(n!=NULL)
        {
            len=(size_t)(n-t);

        }
        else
        {
            len=strcspn(t,"\r\n");
        }
        char buff[234];
        memcpy(buff,t,len);
        buff[len]='\0';
       
            unsigned int res=atoi(buff);
            return res;
       
        
   
   free(line);
   fclose(f);
   return -1;
   
}
