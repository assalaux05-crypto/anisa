#ifndef SIMULATION_H
#define SIMULATION_H

#include "machine.h"

struct FlightPoint {
    double t;
    double x;
    double y;
};

enum WindDirection {
    WIND_HEADWIND,
    WIND_TAILWIND
};

struct Wind {
    double speed;
    enum WindDirection direction;
};

/* proficiencies/src/simulation.c */
struct FlightPoint *simulate_flight(struct Machine machine, double dt, int *nb_points);
void free_flight_points(struct FlightPoint *points);
struct Wind parse_environment(const char *filepath);
struct FlightPoint *simulate_flight_with_wind(struct Machine machine, struct Wind wind,
                                        double dt, int *nb_points);

#endif /* SIMULATION_H */
