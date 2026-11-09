/* TODO: use cJSON (cJSON.h):
 * cJSON_ParseWithLength, cJSON_GetObjectItemCaseSensitive,
 * cJSON_IsArray/Object/String/Number, cJSON_GetArraySize,
 * cJSON_CreateArray/Object, cJSON_AddItemToArray,
 * cJSON_Print, cJSON_Delete.
 */

 #include "exercise.h"
 #include <cjson/cJSON.h>

 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>



int json_library_count_courses(const char *filename)
{

    FILE*f=fopen(filename,"r");
    if(!f)return -1;
    // lire file 
    fseek(f,0,SEEK_END);
    long size=ftell(f);
    rewind(f);

    if(size<=0)
    {
        fclose(f) ; 
        return -1;
    }

    char* buff=malloc(size+1);
    if(!buff)
    {
        fclose(f);
        return -1;
    }
   if(fread(buff,1,size,f)!= (size_t)size)
   {
    free(buff);
    fclose(f);
    return -1;
   }
    buff[size]='\0';
    fclose(f);
    //================================
    
    // parse file 
    cJSON* root=cJSON_Parse(buff);
    free(buff);
    if(!root)
    {
        
        return -1;
    }
    cJSON* courses=cJSON_GetObjectItemCaseSensitive(root,"courses");
    if(!cJSON_IsArray(courses))
    {
        cJSON_Delete(root);
        
        return -1;
    }
    int count = cJSON_GetArraySize(courses);
    cJSON_Delete(root);
    return count ;


}

/*
    open file
    lire file 
    parse root + free buff (root doit etre delete en cas derreur )
    ce qui est demander 
    delet(root) a la fin 

*/

int json_library_total_students(const char *filename){

    FILE* f=fopen(filename,"r");
    if(!f)return -1;

    fseek(f,0,SEEK_END);
    long size=ftell(f);
    rewind(f);

    char* buff=malloc(size+1);
    if(!buff)
    {
        fclose(f);
        return -1;
    }
    if(fread(buff,1,size,f)!=(size_t)size)
    {
        free(buff);
        fclose(f);
        return -1;
    }
    buff[size]='\0';
    fclose(f);

    cJSON* root=cJSON_Parse(buff);
    // if !root
    free(buff);
    cJSON* courses=cJSON_GetObjectItemCaseSensitive(root,"courses");
    if(!cJSON_IsArray(courses))
    {
        cJSON_Delete(root);
        return -1;
    }
    int nb_c=cJSON_GetArraySize(courses);
    int cpt=0;
    for(int i=0;i<nb_c ;i++)
    {
        cJSON* c=cJSON_GetArrayItem(courses, i);
        if(!cJSON_IsObject(c))continue;
        cJSON* students=cJSON_GetObjectItemCaseSensitive(c,"students");
        if(!cJSON_IsArray(students))
        {
            
            continue;

        }
        int count=cJSON_GetArraySize(students);
        cpt+=count;
    }

    cJSON_Delete(root);
    return cpt;

}


int json_library_update_room(const char *filename, int course_id, const char *room)
{

    FILE*f=fopen(filename,"r");
    if(!f)return  -1;

    fseek(f,0,SEEK_END);
    long size=ftell(f);
    rewind(f);

    char* buff=malloc(size+1);
    if(!buff)
    {
        fclose(f);
        return -1;
    }
    if(fread(buff,1,size,f)!=(size_t)size)
    {
        free(buff);
        fclose(f);
        return -1;
    }
    buff[size]='\0';
    fclose(f);



    cJSON* root=cJSON_Parse(buff);
    free(buff);
    if(!root)
    {
        return -1;
    }
    cJSON* courses=cJSON_GetObjectItemCaseSensitive(root,"courses");
    if(!cJSON_IsArray(courses))
    {
        cJSON_Delete(root);
        return -1;
    }
    int cpt =cJSON_GetArraySize(courses);

    int found=0;
    const char*file="tmp.json";
    for(int i=0;i<cpt;i++)
    {
        cJSON*c=cJSON_GetArrayItem(courses,i);
        if(!cJSON_IsObject(c))
        {
            continue;
        }
        cJSON*id=cJSON_GetObjectItemCaseSensitive(c,"id");
        if(!cJSON_IsNumber(id))
        {
            continue;
        }
        int val=cJSON_GetNumberValue(id);

        if(val==course_id)
        {
            cJSON*r=cJSON_GetObjectItemCaseSensitive(c,"room");
            if(!cJSON_IsString(r))
            {
                break;
            }
            cJSON_SetValuestring(r, room);
            found=1;
            break;

        }
    }

    if(found)
    {
        
            FILE*out=fopen(file,"w");
            if(!f)
            {
                cJSON_Delete(root);
                return -1;
            }
            char* res=cJSON_Print(root);

            fprintf(out,"%s",res);
            fclose(out);
            found=1;
            free(res);
            rename(file,filename);
            cJSON_Delete(root);
            return 0;
            
        
    }
    


    cJSON_Delete(root);
    return -1;












}

int json_library_export_top(const char *input, const char *output, int minimum)
{




    FILE*f=fopen(input,"r");
    if(!f)return -1;

    fseek(f,0,SEEK_END);
    long size=ftell(f);
    if(size<=0)
    {
        fclose(f);
        return -1;
    }
    rewind(f);

    char* buff=malloc(size+1);
    if(!buff)
    {
        fclose(f);
        return -1;
    }
   if(fread(buff,1,size,f)!= (size_t)size)
   {
    free(buff);
    fclose(f);
    return -1;
   }
   buff[size]='\0';
   fclose(f);


   cJSON* root=cJSON_Parse(buff);
   free(buff);
   if(!root)
   {
        return -1;
   }
   cJSON* courses=cJSON_GetObjectItemCaseSensitive(root,"courses");
   if(!cJSON_IsArray(courses))
   {
    cJSON_Delete(root);
    return -1;
   }
   int nb_c=cJSON_GetArraySize(courses);
    cJSON*arr=cJSON_CreateArray();

   for(int i=0;i<nb_c;i++)
   {
        cJSON*c=cJSON_GetArrayItem(courses,i);
        if(!cJSON_IsObject(c))
        {
            continue;
        }
        cJSON* students=cJSON_GetObjectItemCaseSensitive(c,"students");
        if(!cJSON_IsArray(students))
        {
            continue;
        }
        int s=cJSON_GetArraySize(students);
        cJSON*obj;
        for(int j=0;j<s;j++)
        {
            cJSON* st=cJSON_GetArrayItem(students,j);
            if(!cJSON_IsObject(st))
            {
                continue;
            }
            cJSON*name=cJSON_GetObjectItemCaseSensitive(st,"name");
            if(!cJSON_IsString(name))continue;
            char* n=cJSON_GetStringValue(name);
            cJSON*grade=cJSON_GetObjectItemCaseSensitive(st,"grade");
            if(!cJSON_IsNumber(grade))continue;
            int g=cJSON_GetNumberValue(grade);
            if(g>=minimum)
            {
              obj=  cJSON_CreateObject();
              cJSON*nom=cJSON_CreateString(n);
              cJSON*gr=cJSON_CreateNumber(g);

              cJSON_AddItemToObject(obj,"name",nom);
              cJSON_AddItemToObject(obj,"grade",gr);
                cJSON_AddItemToArray(arr,obj);

            }
            

        }
            
  



   }
   char*res=cJSON_Print(arr);
   FILE*out=fopen(output,"w");
   if(!out)
   {
    free(res);
    cJSON_Delete(root);
    cJSON_Delete(arr);
   return -1;

   }
   fprintf(out,"%s",res);
   free(res);
   fclose(out);
   cJSON_Delete(arr);
   cJSON_Delete(root);
   return 0;













}
