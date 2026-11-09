#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *skip(const char *p)
{
    // Cas 1 : La valeur est une chaîne de caractères ("...")
    if (*p == '"') {
        p++; // On dépasse le guillemet ouvrant
        while (*p && *p != '"') {
            if (*p == '\\' && *(p + 1)) {
                p += 2; // On saute les caractères échappés comme \"
            } else {
                p++;
            }
        }
        if (*p == '"') p++; // On dépasse le guillemet fermant
        return p;
    }

    // Cas 2 : La valeur est un objet {...} ou un tableau [...]
    if (*p == '{' || *p == '[') {
        int depth = 0;
        while (*p) {
            if (*p == '{' || *p == '[') {
                depth++;
            } else if (*p == '}' || *p == ']') {
                depth--;
                if (depth == 0) {
                    p++; // On dépasse la fermeture finale
                    break;
                }
            } else if (*p == '"') {
                // Sauter les chaînes à l'intérieur pour ignorer leurs accolades/crochets
                p++;
                while (*p && *p != '"') {
                    if (*p == '\\' && *(p + 1)) p += 2;
                    else p++;
                }
            }
            if (*p) p++;
        }
        return p;
    }

    // Cas 3 : Nombre, booléen (true/false) ou null
    // On avance jusqu'au prochain séparateur (',', '}', ']' ou fin de ligne)
    while (*p && *p != ',' && *p != '}' && *p != ']' && 
           *p != ' ' && *p != '\t' && *p != '\n' && *p != '\r') {
        p++;
    }

    return p;
}
const char* space(const char*p)
{
    while(*p==' ' || *p=='\t' || *p=='\n' || *p=='\r')
    {
        p++;
    }
    return p;
}





// {\n  "course": "Structured Data",\n  "year": 2026,\n  "semester": 1,\n  "students": [\n    {"id": 1, "name": "Ada"},\n    {"id": 2, "name": "Bob"},\n    {"id": 3, "name": "Chihiro"}\n  ]\n}\0

int json_get_string(const char *filename, const char *key, char *out, size_t out_size)
{
   FILE*f=fopen(filename,"r");
   if(!f)return -1;
   fseek(f,0,SEEK_END);
   long size=ftell(f);
   rewind(f);
   if(size<=0)
   {
    fclose(f);
    return -1;
   }
   char* buff=malloc(size+1);
   if(!buff)
   {
    fclose(f);
    return -1;
   }
   fread(buff,1,size,f);
   buff[size]='\0';
   fclose(f);
   //===========================================================================
   const char* p=space(buff);
   
   if(*p!='{')
   {
    free(buff);
    return -1;
   }
   p++;
   while(*p!='\0')
   {
    p=space(p);
    if(*p=='}')
    {
        free(buff);
        return -1;
    }
    if(*p!='"')
    {
        free(buff);
        return -1;
    }
    p++;
    const char* start=p;
    while(*p && *p!='"')p++;
    if(*p!='"')
    {
        free(buff);
        return -1;
    }
    size_t len=p-start;
    int match=0;
    if(strlen(key)==len && strncmp(start,key,len)==0)
    {
        match=1;
    }
    p++;
    p=space(p);
    if(*p!=':'){free(buff); return -1;}
    p++;
    p=space(p);
    if(match)
    {   

    
    if(*p!='"'){free(buff); return -1;}
    p++;
    size_t i=0;
    while(*p && *p!='"')
    {
        if(i+1 >=out_size){free(buff); return -1;}
        out[i]=*p;
        i++;
        p++;
    }
    out[i]='\0';
    free(buff);
    return 0;
    }
    p=skip(p);
    p=space(p);
    if(*p==',')p++;

   }
   free(buff);
   return -1;




}

int json_get_int(const char *filename, const char *key, int *out)
{
    FILE*f =fopen(filename,"r");
    if (!f)return -1;
    fseek(f,0,SEEK_END);
    long size=ftell(f);
    rewind(f);
    if(size<=0){fclose(f);return -1;}
    char*buff=malloc(size+1);
    if(!buff){fclose(f);return -1;}
    fread(buff,1,size,f);
    buff[size]='\0';
    fclose(f);
    //===================================
    const char*p=buff;
    p=space(p);
    if(*p!='{'){free(buff); return -1;}
    p++;
    while(*p!='\0')
    {

    
   
    p=space(p);
    if(*p!='"'){free(buff); return -1;}
    p++;
    const char*start=p;
    while(*p && *p!='"')
    {
        p++;
    }
    if(*p!='"'){free(buff); return -1;}
    size_t len =p-start;
    int match=0;
    if(strlen(key)==len && strncmp(start,key,len)==0)
    {
        match=1;
    }
    p++;
    p=space(p);
    if(*p && *p!=':'){free(buff); return -1;}
    p++;
    p=space(p);
    
    if(match==1)
    {
        
    if ((*p < '0' || *p > '9') && *p != '-')
    {
        free(buff);
        return -1;
    }

    char *endptr;
    long val = strtol(p, &endptr, 10);
    if (endptr == p)
    {
        free(buff);
        return -1;
    }

    *out = (int)val;
    free(buff);
    return 0;

    }
    
    p=skip(p);
    p=space(p);
    if(*p && *p!=','){free(buff); return -1;}
    p++;
}
free(buff);
return -1;

}

int json_count_students(const char *filename)
{
    FILE*f=fopen(filename,"r");
    if(!f)return -1;

    fseek(f,0,SEEK_END);
    long size=ftell(f);
    rewind(f);
    if(size<=0){fclose(f); return -1;}

    char* buff=malloc(size+1);
    if(!buff){fclose(f); return -1;}
    buff[size]='\0';
    fread(buff,1,size,f);
    fclose(f);


    //========================
    const char*p=space(buff);

    if(*p && *p!='{'){free(buff); return -1;}
    p++;
    while(*p!='\0')
    {
        p=space(p);
        if(*p && *p!='"'){free(buff); return -1;}
        p++;
        const char * start=p;
        while(*p && *p!='"')p++;
        if(*p!='"'){free(buff); return -1;}
        size_t len=p-start;
        int match=0;
        if(strlen("students")== len && strncmp(start,"students",len)==0)
        {
            match=1;
        }
        p++;
        p=space(p);
        if(*p && *p!=':'){free(buff); return -1;}
        p++;
        p=space(p);
        int cpt=0;
        if(match)
        {
           if(*p!='[')
           {
            free(buff);
            return-1;
           }
           p++;
           p=space(p);
           while(*p && *p!=']')
           {
            if(*p=='{')
            {
                cpt++;
                p=skip(p);

            }
            p=space(p);
            if(*p==',')
            {
                p++;
                p=space(p);

            }
           }
           free(buff);
           return cpt;
        }
        
        p=skip(p);
        p=space(p);
        if(*p && *p==',')
        {
            p++;
        }

    }
    free(buff);
    return -1;

}

int json_update_semester(const char *filename, int semester)
{
   

    FILE*f=fopen(filename,"r");
    if(!f)return -1;

    fseek(f,0,SEEK_END);
    long size=ftell(f);
    rewind(f);

    if(size<=0){fclose(f); return -1;}

    char* buff=malloc(size+1);
    if(!buff){fclose(f); return -1;}
    

    fread(buff,1,size,f);
    buff[size]='\0';
    fclose(f);


    const char* p=space(buff);
    if(*p && *p!='{'){free(buff); return -1;}
    p++;
    while(*p!='\0')
    {
        p=space(p);
        if(*p=='}')break;// pour sortie de la boucle 
        if(*p && *p!='"'){free(buff); return -1;}
        p++;
        const char*start=p;
        while(*p && *p!='"')
        {
            p++;
        }
        if(*p!='"'){free(buff); return -1;}
        size_t len=p-start;
        int match=0;
        if(strlen("semester")==len && strncmp(start,"semester",len)==0)
        {
            match=1;
        }
        p++;
        p=space(p);
        if (*p!=':'){free(buff); return -1;}
        p++;
        p=space(p);
        if(match)
        {
            if((*p<'0' || *p>'9') && *p!='-'){free(buff); return -1;}
            const char*val_start=p;
            char*end;
            strtol(p,&end,10);
        
            if(p==end){free(buff); return -1;}
            const char*val_fin=end;
            char new_val[32];
            int size=snprintf(new_val,sizeof(new_val),"%d",semester);
            if(size<=0){free(buff); return -1;}

            size_t pref=val_start-buff;
            size_t suff=strlen(val_fin);
            size_t m=strlen(new_val);

            size_t total=pref+suff+m;
            char* new_buff=malloc(total+1);
            if (!new_buff){free(buff); return -1;}

            memcpy(new_buff,buff,pref);
            memcpy(new_buff+pref,new_val,m);
            memcpy(new_buff+pref+m,val_fin,suff);

            new_buff[total]='\0';
            

            const char*file="tmp.json";
            FILE*out=fopen(file,"w");
            if(!out){free(buff);  free(new_buff); return -1;}
            fprintf(out,"%s",new_buff);
            fclose(out);// avant rename 
            if(rename(file,filename)!=0)
            {
                remove(file);
                free(buff);
                free(new_buff);
                return -1;
            }
            
            free(buff);
            free(new_buff);
            return 0;

        }
        p=skip(p);
        p=space(p);
        if(*p==',')
        {
            p++;
        }

    }
    
free(buff);
return -1;


}