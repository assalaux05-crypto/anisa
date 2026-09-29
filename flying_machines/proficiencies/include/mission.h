#ifndef MISSION_H
#define MISSION_H

#include "hangar.h"

struct Mission {
    char *code;
    char *machine_name;
    double target_height;
    int has_max_range;
    double max_range;
};

/* proficiencies/src/mission.c */
struct HangarList *parse_missions(const char *filepath);

#endif /* MISSION_H */
