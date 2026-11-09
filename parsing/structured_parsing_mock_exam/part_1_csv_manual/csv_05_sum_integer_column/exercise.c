#define _POSIX_C_SOURCE 200809L
#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TODO: implement the function described in README.md. */
int csv_sum_integer_column(const char *path, size_t column, long *sum)
{


    FILE*f=fopen(path,"r");
    if(!f)return 0;
    char*line=NULL;
    size_t size=0;
    if(getline(&line,&size,f)==-1)
    {
        free(line);
        fclose(f);
        return 0;
    }
    while(getline(&line,&size,f)!=-1)
    {
        size_t i=0;
        char * token=line;

        while(token!=NULL && i<column)
        {

       
                char*v=strchr(token,',');
                if(v!=NULL)
                {
                    token=v+1;
                }
                else 
                {
                    token=NULL;
                }

                i++;
         }
         if(token==NULL)return 0;

    
        char*n=strchr(token,',');
        size_t len;
        if(n!=NULL)
        {
            len=(size_t)(n-token);
        }
        else 
        {
            len=strlen(token);
        }
        char dest[123];
        memcpy(dest,token,len);
        dest[len]='\0';
        char* end=NULL;
        long val=strtol(dest,&end,10);
        if(dest==end)continue;
        *sum+=val;


    }


    free(line);
    fclose(f);
    return 1;





}
