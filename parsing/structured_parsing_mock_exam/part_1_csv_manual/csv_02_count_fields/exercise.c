#define _POSIX_C_SOURCE 200809L
#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>

/* TODO: implement the function described in README.md. */
size_t csv_count_fields(const char *path)
{
    FILE*f=fopen(path,"r");
    if(!f)return 0;
    size_t cpt=1;
    char *line=NULL;
    size_t size=0;
    
}
