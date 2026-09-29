#ifndef REPORT_H
#define REPORT_H

#include "machine.h"
#include "mission.h"
#include "simulation.h"
#include "hangar.h"

/* proficiencies/src/debrief.c */
int write_trajectory_csv(const char *filepath, const char *machine_name,
                          const struct FlightPoint *points, int nb_points);
double compute_landing_distance_difference(const struct FlightPoint *points_no_wind,
                                            int n1,
                                            const struct FlightPoint *points_wind,
                                            int n2);
int write_mission_debrief(const char *filepath, const char *machine_name,
                           const struct FlightPoint *points_no_wind, int n1,
                           const struct FlightPoint *points_wind, int n2);

/* proficiencies/src/mission_report.c */
int write_mission_report(const char *filepath, const struct HangarList *missions,
                          const struct Machine *machines, int machine_count);

#endif /* REPORT_H */
