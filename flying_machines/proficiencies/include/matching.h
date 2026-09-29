#ifndef MATCHING_H
#define MATCHING_H

#include "machine.h"
#include "mission.h"
#include "hangar.h"

/* proficiencies/src/matching.c */
int mission_is_feasible(const struct Mission *mission, const struct Machine *machine);
int mission_compare(const void *a, const void *b);
const struct Mission *find_best_mission(struct HangarList *missions,
                                  const struct Machine *machines, int machine_count);

#endif /* MATCHING_H */
