#ifndef PHYSICS_H
#define PHYSICS_H

/* fundamentals/src/physics.c */
double degrees_to_radians(double degrees);
double calculate_vx(double velocity, double angle_rad);
double calculate_vy(double velocity, double angle_rad);
double calculate_max_height(double velocity, double angle_rad);
double calculate_range(double velocity, double angle_rad);
double calculate_time_of_flight(double velocity, double angle_rad);
const char *classify_altitude(double max_height);

#endif /* PHYSICS_H */
