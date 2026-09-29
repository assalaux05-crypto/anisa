#include "report.h"

int write_trajectory_csv(const char *filepath, const char *machine_name,
                          const struct FlightPoint *points, int nb_points)
{
    return 0;
}

double compute_landing_distance_difference(const struct FlightPoint *points_no_wind,
                                            int n1,
                                            const struct FlightPoint *points_wind,
                                            int n2)
{
    return 0.0;
}

int write_mission_debrief(const char *filepath, const char *machine_name,
                           const struct FlightPoint *points_no_wind, int n1,
                           const struct FlightPoint *points_wind, int n2)
{
    return 0;
}
