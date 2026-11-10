#define _POSIX_C_SOURCE 200809L
#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




static int fct(char**token,char*buff,size_t size)
{
    if(*token==NULL)return 0;
    char*v=strchr(*token,',');
    size_t len;

    if(v)
    {
        len=(size_t)(v-*token);
    }
    else
    {
        len=strcspn(*token ,"\r\n");
    }
    if(len>=size)return 0;
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
struct author *parse_author_row(char *row)
{
    if(!row)return NULL;
    struct author*box=malloc(sizeof(struct author));
    if(!box)return NULL;
    char idd[64];
    char name [64];
    if(!fct(&row,idd,sizeof(idd)))
    {
        free(box);
        return NULL;
    }
    if(!fct(&row,name,sizeof(name)))
    {
        free(box);
        return NULL;

    }
    int len=strlen(name);
    box->name=malloc(len+1);
    if(!box->name)return NULL;// free box
    strcpy(box->name,name);
    long val=strtol(idd,NULL,10);
    box->id=(int)val;

    return box;

}

void print_all_books_written_by(char *author_lastname)
{

    const char*file="authors.csv";
    FILE*f=fopen(file,"r");

    if(!f)return ;
    const char*out="books.csv";
    FILE*g=fopen(out,"r");
    if(!g)
            {
                fclose(f);
               
                return ;

            }
    char* line=NULL;
    size_t size=0;
    char* linee=NULL;
    size_t sizee=0;
    char* id;
    if(getline(&line,&size,f)==-1)
    {
        free(line);
        fclose(f);
        fclose(g);
        return ;
    }
    while(getline(&line,&size,f)!=-1)
    {

        if(line[0]=='\n')continue;
        id=line;
        char* v=strchr(id,',');
        *v='\0';
        if(v==NULL)continue;
        char*name=v+1;

        int len=strlen(name);
        if(len >0 && name[len-1]=='\n')
        {
            name[len-1]='\0';
        }
        if(strcmp(name,author_lastname)==0)
        {
            break;
        }   
    }
    fclose(f);
    if(getline(&linee,&sizee,g)==-1)
            {
                free(line);
                free(linee);
                
                fclose(g);
                return;
                
            }
            while(getline(&linee,&sizee,g)!=-1)
            {
                char*i=linee;
                char*v=strchr(i,',');
                if(v==NULL)continue;
                *v='\0';
                char*book=v+1;
                v=strchr(book,',');
                if(v==NULL)continue;
                *v='\0';
                char*au_id=v+1;
                if(!au_id)continue;
                int len=strlen(au_id);
                if(len >0 && au_id[len-1]=='\n')
                {
                    au_id[len-1]='\0';
                }
                int l_b=strlen(book);
                if(l_b >0 && book[l_b-1]=='\n')
                {
                    book[l_b-1]='\0';
                }
                if(strcmp(id,au_id)==0)
                {
                    printf("%s\n",book);
                }








    }






        free(line);
        free(linee);
        fclose(g);
        return  ;






}

void free_author(struct author *value)
{
    if(value==NULL)return ;
    free(value->name);
    free(value);
}
