#include "simulation.h"
#include <stddef.h>

struct FlightPoint *simulate_flight(struct Machine machine, double dt, int *nb_points)
{
    return NULL;    
}

void free_flight_points(struct FlightPoint *points)
{
    return;
}


struct Wind parse_environment(const char *filepath)
{
    return (struct Wind){0};
}

struct FlightPoint *simulate_flight_with_wind(struct Machine machine, struct Wind wind,
                                        double dt, int *nb_points)
{
    return NULL;
}
