#define _POSIX_C_SOURCE 200809L
#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* TODO: implement the function described in README.md. */
int csv_parse_long(const char *text, long *value)
{
    if(isspace((unsigned char)*text))
    {
        text++;

    }
    char*end;
    long v= strtol(text,&end,10);
    if(text==end )return 0;
    while(isspace((unsigned char)*end))end++;
    if( *end!='\0')return 0;
    *value=v;
    return 1;
}
