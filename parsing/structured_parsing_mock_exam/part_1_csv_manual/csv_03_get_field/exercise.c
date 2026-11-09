#define _POSIX_C_SOURCE 200809L
#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TODO: implement the function described in README.md. */
int csv_get_field(const char *line, size_t index, char *out, size_t out_size)
{
  
   const char* token=line;
   size_t i=0;
   while(token!=NULL && i<index)
    {
       
            const char*virgule=strchr(token,',');
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
    if(token==NULL)return 0;
    const char*next=strchr(token,',');
    size_t len;
    if(next!=NULL)
    {
        len=(size_t)(next-token);

    }
    else
    {
        len=strlen(token);
    }
    
    if(len+1 >out_size)
    {
        return 0;
    }
    memcpy(out,token,len);
    out[len]='\0';
    return 1;
}
