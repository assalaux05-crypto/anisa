#ifndef REPORT_H
#define REPORT_H

#include "machine.h"

/* fundamentals/src/report.c */
char *generate_flight_summary(double velocity, double angle_rad);
int write_flight_report(const char *filepath, const struct Machine *machines,
                         int count, double threshold);

#endif /* REPORT_H */
