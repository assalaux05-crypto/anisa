#ifndef MACHINE_H
#define MACHINE_H

struct Machine {
    char name[64];
    double velocity;   /* m/s */
    double angle_rad;  /* radians */
};

#endif /* MACHINE_H */
