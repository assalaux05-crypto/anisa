#include "report.h"
#include "matching.h"
#include <stdio.h>
#include <math.h>
#include "hangar.h"
#include "porco.h"
#include "mission.h"
#include <string.h>

/*

struct Machine {
    char name[64];
    double velocity;   /* m/s */
    double angle_rad;  /* radians *



struct Mission {
    char *code;
    char *machine_name;
    double target_height;
    int has_max_range;
    double max_range;
};
*/
//mission est ce que son avion existe dans tab machine?


int write_mission_report(const char *filepath, const struct HangarList *missions,
                          const struct Machine *machines, int machine_count)
{
    if(filepath==NULL || missions==NULL || machines==NULL || machine_count<=0)return -1;

    FILE * f=fopen(filepath,"w");
    if(!f)return -1;
    fprintf(f,"MISSION REPORT\n");
    //## `size_t hangar_size(const HangarList *list);`
    size_t size=hangar_size(missions);
    for(size_t i=0;i<size;i++)
    {
        //const void *hangar_at_const(const HangarList *list, size_t index);`

        const struct Mission* m=hangar_at_const(missions,i);
        if(!m)continue;
        const struct Machine* avion=NULL;
        for(int k=0;k<machine_count;k++)
        {
                int r= strcmp(machines[k].name,m->machine_name);
                if (r==0)
                {
                    avion =&machines[k];
                    break;
                }
       
        }
        char label[128];
        double max_height=0.0;
        double range=0.0;
        int feasible=0;
        if(avion)
        {
            porco_write_machine_label(label, sizeof(label), avion);
            double sin_angle = sin(avion->angle_rad);
            max_height = (avion->velocity * avion->velocity * sin_angle * sin_angle) / (2.0 * 9.81);
            range = (avion->velocity * avion->velocity * sin(2.0 * avion->angle_rad)) / 9.81;
            if (mission_is_feasible(m, avion) == 1)
                feasible = 1;
        }
    
       else{
            strcpy(label, "UNKNOWN MACHINE");
      }
      fprintf(f, "machine=%s code=%s target_height=%.2f max_height=%.2f range=%.2f feasible=%d",
                label, m->code, m->target_height, max_height, range, feasible);

    if (m->has_max_range)
            fprintf(f, "max_range=%.2f\n", m->max_range);
        else
            fprintf(f,"\n");
    }
    fclose(f);
    return 0;

}
