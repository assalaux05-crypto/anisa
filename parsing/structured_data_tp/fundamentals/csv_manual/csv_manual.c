/* TODO: implement the five functions from exercise.h using FILE*. */
#define _POSIX_C_SOURCE 200809L

#include "exercise.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _POSIX_C_SOURCE 200809L

// jai appris comment sauter la premiere ligne
int csv_count_rows(const char *filename)
{

    FILE*f =fopen(filename,"r");
    if(!f)return -1;
    char* line=NULL;
    size_t size=0;
    int cpt=0;
   
    getline(&line,&size,f);
    while(getline(&line,&size,f)!=-1)
    {
        

        
             char* id=strtok(line,",");
            if(!id)continue;
            char* name=strtok(NULL,",");
            if(!name)continue;
            char*grade=strtok(NULL,",");
            if(!grade)continue;
            

        cpt++;
       
    }
    free(line);
    fclose(f);
    return cpt;
}

// utilisation strtol => long val=strtol(char*,NULL,10)
// ne jamais oublie le break
int csv_find_student(const char *filename, int id, char *out, size_t out_size)
{
   FILE* f=fopen(filename,"r");
   if(!f)return -1;
   char* line=NULL;
   size_t size=0;
   int found=0;
   getline(&line,&size,f);
   while( getline(&line,&size,f)!=-1)
   {
    char*idd=strtok(line,",");
    if(!id)continue;
    long i=strtol(idd,NULL,10);
    if (id==i)
    {
        char*name=strtok(NULL,",");
        if(!name)continue;
        // est ce que faut faire ca ou non 
        size_t len=strlen(name)+1;
        if(len<out_size)
        {
            strcpy(out,name);
            found=1;
            break;
        }
    }
   }
   free(line);
   fclose(f);
   if(found)
   {
    return 0;
   }
   return 1;
}
// pour ajouter faut utiliser appen et ne pas oublie \n pour fprintf
int csv_add_student(const char *filename, int id, const char *name, int grade)
{
    // fseek(f, 0, SEEK_END); r+ lire et ecrie sans effacer 
  FILE*f=fopen(filename,"a");
  if(!f)return -1;
  fprintf(f,"%d,%s,%d\n",id,name,grade);
  fclose(f);
  return 0;
}
// pour modi un file tjr pensee fichier tmp creer apres soit rename ou remove
// oublie pas continue quand c important 
int csv_update_grade(const char *filename, int id, int grade)
{
    FILE*f=fopen(filename,"r");
    if(!f)return -1;
    //const char *file = "temp.csv"; sans snprintf

    char file[1024];
    snprintf(file,sizeof(file),"%s.tmp",filename);
    FILE*out=fopen(file,"w");// si il existe ok snn cree le 
    if(!out)
    {
        fclose(f);
        return -1;
        
    }
    char*line=NULL;
    size_t size=0;
    int found=0;

    getline(&line,&size,f);// elle lis \n faire attention ne pas lajouter dans fprintf
    fprintf(out,"%s",line);
    while(getline(&line,&size,f)!=-1)
    {
        char*idd=strtok(line,",");
        if(!idd)continue;

        long val=strtol(idd,NULL,10);
        char*name=strtok(NULL,",");
        if(!name)continue;
        char* g=strtok(NULL,",");// il contient \n
        if(!g)continue;
        
        if(val==id)
        {
            //char* new_g=atoi(grade);
            fprintf(out,"%s,%s,%i\n",idd,name,grade);
            found=1;
            continue;
        }
       
        fprintf(out,"%s,%s,%s",idd,name,g);


    }
    free(line);
    fclose(f);
    fclose(out);
    if(found)
    {
        rename(file,filename); // pour remplacer 
       
        return 0;
    }
    remove(file);// pour supp le temporaire 
    return -1;
}

int csv_delete_student(const char *filename, int id)
{
  FILE*f=fopen(filename,"r");
  if(!f)return -1;
  const char* file="tmp.csv";
  FILE*out=fopen(file,"w");
  if(!out)
  {
    fclose(f);
    return -1;
  }
  char* line=NULL;
  size_t size=0;
  getline(&line,&size,f);
  fprintf(out,"%s",line);
  int found =0;
  while(getline(&line,&size,f)!=-1)
  {

    char*idd=strtok(line,",");
    if(!idd)continue;
    long val=strtol(idd,NULL,10);
    if(id==val)
    {
        found=1;
        continue ;
    }
    char*name=strtok(NULL,",");
    if(!name)continue;
    char* g=strtok(NULL,";");
    if(!g)continue;
    fprintf(out,"%s,%s,%s",idd,name,g);
  }
  free(line);
  fclose(f);
  fclose(out);
  if(found)
  {
    rename(file,filename);
    return  0;
  }
  remove(file);
  return -1;

}