#ifndef ANALYZE_DATA_H
#define ANALYZE_DATA_H

#include <stddef.h>

unsigned int compute_checksum(const unsigned int *data, size_t n);
unsigned long analyze_data(const unsigned int *data, size_t n);

#endif /* ! ANALYZE_DATA_H */
