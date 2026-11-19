#ifndef AVERAGE_H
#define AVERAGE_H

#include <stddef.h>
#include <stdint.h>

struct measurement
{
    double temperature;
    double humidity;
    uint64_t timestamp;
    uint32_t sensor_id;
};

struct measurements
{
    size_t size;
    double *temperatures;
    double *humidities;
    uint64_t *timestamps;
    uint32_t *sensor_ids;
};

double average_aos(const struct measurement *data, size_t size,
                   uint32_t sensor_id);
double average_soa(const struct measurements *data, uint32_t sensor_id);

#endif /* ! AVERAGE_H */
