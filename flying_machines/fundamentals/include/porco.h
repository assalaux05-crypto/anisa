#ifndef PORCO_H
#define PORCO_H

#include <stddef.h>

/*
** libporco - small workshop helper library.
** See README.md for the exact contract of each function
** (in particular the sentinel values returned on invalid input).
*/

double porco_knots_to_ms(double knots);
const char *porco_machine_class(double speed_ms);
int porco_parse_code(const char *code);
int porco_write_machine_label(char *buffer, size_t size,
                               const char *name, double speed_ms);

#endif /* PORCO_H */
