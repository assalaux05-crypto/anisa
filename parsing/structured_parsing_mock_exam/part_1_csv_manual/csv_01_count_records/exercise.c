#define _POSIX_C_SOURCE 200809L
#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>
size_t csv_count_records(const char *path)
{
    FILE*f=fopen(path,"r");
    if(!f)return 0;
    size_t cpt=0;
    char* line =NULL;
    size_t size=0;
    getline(&line,&size,f);
    if(line[0]=='\n')
    {
        free(line);
        fclose(f);
        return 0;

    }
    while(getline(&line,&size,f)!= -1)
    {
        if(line[0]=='\0')
        {
             continue;
        }
        if(line[0]=='\n')
        {
            continue;
        }
        cpt++;
       
    }
    free(line);
    fclose(f);
    return cpt;
}
