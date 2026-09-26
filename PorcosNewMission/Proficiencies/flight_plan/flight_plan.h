#ifndef FLIGHT_PLAN_HEADER
#define FLIGHT_PLAN_HEADER

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "squadron.h"

struct squadron *read_flight_plan(const char *filename, int *err_out);

#endif // FLIGHT_PLAN_HEADER
