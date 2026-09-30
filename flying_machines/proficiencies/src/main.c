#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hangar.h"
#include "matching.h"
#include "mission.h"
#include "porco.h"

int main(void)
{

    struct Machine machines[] = {
        { "Savoia S.21", 52.0, 0.6108652382 }
    };
    int machine_count = 1;
    struct HangarList *missions = hangar_create(sizeof(struct Mission), NULL);
    if (!missions)
        return 1;

    struct Mission m1 = { "S21", "Savoia S.21", 40.0, 0, 0.0 };
    struct Mission m2 = { "S21", "Savoia S.21", 20.0, 0, 0.0 };
    struct Mission m3 = { "S21", "Savoia S.21", 50.0, 0, 0.0 };

    hangar_push(missions, &m1);
    hangar_push(missions, &m2);
    hangar_push(missions, &m3);

  
    const struct Mission *best = find_best_mission(missions, machines, machine_count);

    if (best != NULL)
        printf("%.2f\n", best->target_height);
  
    hangar_destroy(missions);

    return 0;
}