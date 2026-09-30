#include "mission.h"
#include <string.h>
#include "porco.h"
#include <stdlib.h>
#include <stdio.h>
#include "hangar.h"

/*


struct Mission{
    char *code;
    char *machine_name;
    double target_height;
    int has_max_range;
    double max_range;
};

S21|Savoia S.21|40.0|300.0



*/
void destroy_mission(void *element)
{
    if (element == NULL)
        return;

    struct Mission *mission = (struct Mission *)element;
    free(mission->machine_name);
    free(mission->code);
}

struct HangarList *parse_missions(const char *filepath)
{
    FILE *f=fopen(filepath,"r");
    if(!f)return NULL;
    //struct HangarList *hangar_create(size_t element_size, HangarDestroyFn destroy);
    
    struct HangarList* lst=hangar_create(sizeof(struct Mission),destroy_mission);
    if(!lst)
    {
        fclose(f);
        return NULL;
    }
    char buff[222];
   while(fgets(buff,sizeof(buff),f)!=NULL)
   {
    struct Mission mission;

    if(buff[0]=='\n')continue;
    char* code=strtok(buff,"|");
    if(!code)continue;
    char*nom=strtok(NULL,"|");
    if(!nom)continue;
    char* hauteur=strtok(NULL,"|");
    if(!hauteur)continue;
    char* porte=strtok(NULL,"|");
    if(!porte)continue;
    int res =porco_parse_code(code);
    if(!res)continue;
    int len_name=strlen(nom)+1;
    char* name=malloc(len_name*sizeof(char));
    if(!name)
    {
        fclose(f);
        
        continue;
    }
    int len_code=strlen(code)+1;
    char* codee=malloc(len_code*sizeof(char));
    if(!codee)
    {
        fclose(f);
        free(name);
        continue;
    }

    strcpy(name,nom);
    mission.machine_name=name;
    strcpy(codee,code);
    mission.code=codee;
    mission.target_height=atof(hauteur);
    mission.max_range=atof(porte);
    if(porte[0]=='-')
    {
            mission.has_max_range=0;

    }
    else{
            mission.has_max_range=1;

    }
    //int hangar_push(struct HangarList *list, const void *element);
    int r=hangar_push(lst,&mission);
    if(r==-1)
    {
        free(mission.code);
        free(mission.machine_name);
        continue;
    }
  

   }

     fclose(f);
    return lst;
}
