#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "exercise.h"

/* TODO: implement the function described in README.md. */
int csv_average_column(const char *path, const char *header, double *average, size_t *used_rows)
{
   FILE*f=fopen(path,"r");
    if(!f)return 0;
    
    char *line=NULL;
    size_t size=0;
    
    double avrg=0.0;
    if(getline(&line,&size,f)== -1)
    {
        fclose(f);
        free(line);
        return 0;
    }
    
    size_t cl=0;
    size_t i=0;
    size_t cpt=0;
    size_t len=strlen(line);
    if(len >0  && line[len-1]=='\n')
    {
        line[len-1]='\0';
    }
    char*token=strtok(line,",");
    if(!token)
    {
        fclose(f);
        free(line);
        return 0;

    }
    while(token)
    {
    
        if(strcmp(token,header)==0)
        {
            cl=i;

        }
        i++;
        token=strtok(NULL,",");
    }
    printf("%zu\n",cl);


    while(getline(&line,&size,f)!=-1)
    {
        int j=0;
        if(line[j]=='\n')
        {
            continue;
        }
        cpt++;
        size_t i=0;
        char* t=line;
        while(t && i<cl )
        {
            char*v=strchr(t,',');
            if(v)
            {
                t=v+1;

            }
            else 
            {
                t=NULL;
            }
            i++;
        }
        if(t==NULL)
        {
        
            break;
        }

        char* n=strchr(t,',');
        size_t len;
        if(n)
        {
            len=(size_t)(n-t);

        }
        else 
        {
           len= strlen(t);
        }

        char dest[345];
        memcpy(dest,t,len);
        dest[len]='\0';

        double res=atof(dest);
        avrg+=res;
        printf("%f\n",avrg);


    }

    if(cpt==0)
    {
        fclose(f);
        free(line);
        return 0;
    }
    *used_rows=cpt;
    *average=avrg/cpt;
    
    
    
    
    free(line);
    fclose(f);
    
    
    return 1;
} 


