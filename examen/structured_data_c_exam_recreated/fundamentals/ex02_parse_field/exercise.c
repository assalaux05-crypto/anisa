#define _POSIX_C_SOURCE 200809L
#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *parse_field(char **input)
{
    
   if(!input || !*input)return NULL;
   char* res=*input;
   char* v=strchr(*input,',');
   if(v!=NULL)
   {
    *v='\0';
    *input=*input+1;
   }
   else 
   {
    *input=NULL;
   }
    return res ;


}

