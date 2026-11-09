#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "exercise.h"






/*
typedef struct {
    int id;
    char name[64];
    char department[64];
    double grade;
} CsvStudent;







*/

static int fct(char** token,char*buff,size_t size)
{

    char* v=strchr(*token,',');
    size_t len;
    if(v!=NULL)
    {
        len=(size_t)(v-*token);

    }
    else 
    {
        len=strlen(*token);
    }
    if (len >=size)return 0;
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
int csv_find_student(const char *path, int wanted_id, CsvStudent *out)
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
        char* token=line;
        char id[34];
        char name[123];
        char sub[128];
        char grad[64];
        if(!fct(&token,id,sizeof(id)))continue;
        if(!fct(&token,name,sizeof(name)))continue;
        if(!fct(&token,sub,sizeof(sub)))continue;
        if(!fct(&token,grad,sizeof(grad)))continue;
        char id_c[32];
        snprintf(id_c ,sizeof(id_c),"%i",wanted_id);
        if(strcmp(id,id_c)==0)
        {
            out->id=wanted_id;
            strcpy(out->name,name);
            strcpy(out->department,sub);
            double res=atof(grad);
            out->grade=res;
            free(line);
            fclose(f);
            return 1;
        }




    }
    free(line);
    fclose(f);
    return 0;














} 


static int fct(char**token,char*buff,size_t size)
{

    char*v=strchr(*token,',');
    size_t len;
    if(v!=NULL)
    {
        len=(size_t)(v-token);
    }
    else
    {
        len=strlen(token);
    }

    if(len >=size)return 0;
    memcpy(buff,token,len);
    buff[len]='\0';
    if(v)
    {
        token=v+1;
    }
    else
    {
        token=NULL;
    }
    return 1;

}