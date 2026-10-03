#include "simulation.h"
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "hangar.h"
#include "matching.h"
#include "mission.h"
#include "porco.h"
#include <report.h>
#include <stdio.h>
int main(void)
{
struct Machine machines[] = {
    { "Savoia S.21", 52.0, 0.6108652382 },
    { "Möwe",        45.5, 0.5235987756 },
};
int machine_count = 2;

/* data/missions.txt: target heights 40.0 (S21), 20.0 (M09)
   and 50.0 (X07). X07 targets "Unknown Flyer", which is
   not in the machine roster above, so it can never be
   feasible no matter how demanding it looks on paper. */
struct HangarList *missions = parse_missions("data/missions.txt");

const struct Mission *best = find_best_mission(missions, machines, machine_count);
printf("%s %.2f\n", best->code, best->target_height);
write_mission_report("mission_report.txt", missions, machines, machine_count);

hangar_destroy(missions);
//int write_mission_report(const char *filepath, const struct HangarList *missions,
 //  const struct Machine *machines, int machine_count);

return 0;
}