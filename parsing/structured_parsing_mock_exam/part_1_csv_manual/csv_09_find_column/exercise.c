#include "exercise.h"

/* TODO: implement the function described in README.md. */
int csv_find_column(const char *path, const char *name, size_t *column_index)
{


FILE*f=fopen(path,"r");
    if(!f)return 0;
    
    char *line=NULL;
    size_t size=0;
   
    if(getline(&line,&size,f)== -1)
    {
        fclose(f);
        free(line);
        return 0;
    }
    int len=strlen(line);
    if(len >0 && line[len-1]='\n')
    {
        line [len-1]='\0';
    }
    char*token=strtok(line,",");
    if(!token)free(line) fclose(f) return 0;
    size_t index=0;
    int i=0;

    while(token)
    {
        if(strcmp(token,name)==0)
        {
            index=i;
            break;
        }
        i++;
        token=strtok(NULL,",");
    }
    *column_index=index;
    return 1;









}






int csv_find_column(const char *path, const char *name, size_t *column_index)
{


FILE*f=fopen(path,"r");
    if(!f)return 0;
    
    char *line=NULL;
    size_t size=0;
   
    if(getline(&line,&size,f)== -1)
    {
        fclose(f);
        free(line);
        return 0;
    }
    int len=strlen(line);
    if(len >0 && line[len-1]=='\n')
    {
        line[len-1]='\0';
    }
    char*token=line;
    size_t i=0;
    while(token)
    {
        char*virgule=strchr(token,",");
        if(virgule!=NULL)
        {
            *virgule='\0';
        }
        if(strcmp(token,name)==0)
        {
            *column_index=i;
            free(line);
            fclose(f);
            return 1;
        }
        if(virgule!=NULL)
        {
            token=virgule+1;
        }
        else 
        {
            token=NULL;
        }
        i++;
    }




}