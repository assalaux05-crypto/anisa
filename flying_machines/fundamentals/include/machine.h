#ifndef MACHINE_H
#define MACHINE_H

struct Machine {
    char name[64];
    double velocity;   /* m/s */
    double angle_rad;  /* radians */
};

/* fundamentals/src/warmup.c */
double estimate_speed_ms(double knots);
const char *classify_machine_speed(double speed_ms);
int decode_machine_code(const char *code);

#endif /* MACHINE_H */
