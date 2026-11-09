#include "exercise.h"
#include <stdlib.h>
unsigned parse_unit(char *decimal)
{
    if (decimal == NULL) return 0;
    return (unsigned)atoi(decimal);
}
