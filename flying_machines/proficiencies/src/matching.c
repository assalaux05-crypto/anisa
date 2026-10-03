#include "matching.h"
#include "porco.h"
#include "mission.h"
#include <string.h>
#include <math.h>
/*
struct Machine {
    char name[64];
    double velocity;   
    double angle_rad;  radians 
struct Mission{
    char *code;
    char *machine_name;
    double target_height;
    int has_max_range;
    double max_range;
};

*/
int mission_is_feasible(const struct Mission *mission, const struct Machine *machine)
{
    if(mission ==NULL || machine ==NULL)return 0;
    //int porco_parse_code(const char *code);
    int res=porco_parse_code(mission->code);
    if(res==-1)return 0;

    int n=strcmp(machine->name,mission->machine_name);
    if (n!=0)return 0;
    double v=machine->velocity*machine->velocity;
    double s=sin(machine->angle_rad)*sin(machine->angle_rad);
    double max_h=(v*s)/(2*9.81);
    double range=0.0;
    if(max_h>=mission->target_height)return 0;
    if(mission->has_max_range==1)
    {
         range=(v*sin(2*machine->angle_rad))/9.81;
    
            if(range>mission->max_range  )
            {
                return 0;
            }
    }
return 1;

}
/*
avant -1
apres 1

*/
int mission_compare(const void *a, const void *b)
{
     const struct Mission* c=(const struct Mission*)a;
     const struct Mission* d=(const struct Mission*)b;
    if(c->target_height > d->target_height)
    {
        return -1;
    }
    else if (c->target_height < d->target_height)
    {
        return 1;
    }
    else 
    {
        if(c->has_max_range && d->has_max_range)
        {
            if(c->max_range > d->max_range)return 1;
            if(c->max_range < d->max_range)return -1;
        }
    }
    return 0;
}


const struct Mission *find_best_mission(struct HangarList *missions,
                                  const struct Machine *machines, int machine_count)
{
        if(missions==NULL || machines==NULL || machine_count <=0)return NULL;
        //int hangar_sort(struct HangarList *list, HangarCompareFn compare);
        int res=hangar_sort(missions,mission_compare);
        if(res==-1)return NULL;
        //size_t hangar_size(const struct HangarList *list);
        size_t size=hangar_size(missions);
        if(size==0)return NULL;
        for(size_t i=0;i<size;i++)
        {
            //const void *hangar_at_const(const struct HangarList *list, size_t index);
            const struct Mission* m=hangar_at_const(missions,i);
            if(!m)continue;

            for(int j=0;j<machine_count;j++)
            {
                const struct Machine *avion=&machines[j];
                int k=strcmp(avion->name,m->machine_name);
                if(k==0)
                {
                    if(mission_is_feasible(m, avion)==1)return m;
                    break;
 
                }                 
                
            }

        }
    return NULL;
}
