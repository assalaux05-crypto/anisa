#include "average.h"










/*
struct measurement
{
    double temperature;
    double humidity;
    uint64_t timestamp;
    uint32_t sensor_id;
    aos
};



*/
double average_aos(const struct measurement *data, size_t size,
                   uint32_t sensor_id)
{
   
    if(!data)return 0.0;
    size_t cpt=0;
    double res=0.0;
    for (size_t i=0; i<size;i++)
    {
        if(data[i].sensor_id==sensor_id)
        {
            cpt++;
            res+=data[i].temperature;
        }

    }
    if(cpt!=0)
    {
        return res/cpt;
    }
    return res;


}
/*

struct measurements
{
    size_t size;
    double *temperatures;
    double *humidities;
    uint64_t *timestamps;
    uint32_t *sensor_ids;
};




*/

double average_soa(const struct measurements *data, uint32_t sensor_id)
{
    

    if(!data)return 0.0;
    size_t cpt=0;
    double res=0.0;
    for (size_t i=0; i<data->size;i++)
    {
        if(data->sensor_ids[i]==sensor_id)
        {
            cpt++;
            res+=data->temperatures[i];
        }

    }
    if(cpt!=0)
    {
        return res/cpt;
    }
    return res;







}
/*

#include <stdio.h>

int main(void)
{
    struct measurement aos[] = {
        { .temperature = 18.0, .sensor_id = 7 },
        { .temperature = 30.0, .sensor_id = 2 },
        { .temperature = 22.0, .sensor_id = 7 }
    };

    double temperatures[] = { 18.0, 30.0, 22.0 };
    double humidities[] = { 0.0, 0.0, 0.0 };
    uint64_t timestamps[] = { 0, 0, 0 };
    uint32_t sensor_ids[] = { 7, 2, 7 };

    struct measurements soa = {
        .size = 3,
        .temperatures = temperatures,
        .humidities = humidities,
        .timestamps = timestamps,
        .sensor_ids = sensor_ids
    };

    printf("AoS, sensor 7: %.1f\n", average_aos(aos, 3, 7));
    printf("SoA, sensor 7: %.1f\n", average_soa(&soa, 7));
    printf("AoS, sensor 9: %.1f\n", average_aos(aos, 3, 9));
    printf("SoA, sensor 9: %.1f\n", average_soa(&soa, 9));

    return 0;
}

#include "average.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    size_t size = 5e6;
    struct measurement *aos = calloc(size, sizeof(*aos));
    struct measurements soa = {
        .size = size,
        .temperatures = calloc(size, sizeof(double)),
        .humidities = calloc(size, sizeof(double)),
        .timestamps = calloc(size, sizeof(uint64_t)),
        .sensor_ids = calloc(size, sizeof(uint32_t))
    };

    if (!aos || !soa.temperatures || !soa.humidities
        || !soa.timestamps || !soa.sensor_ids)
    {
        free(aos);
        free(soa.temperatures);
        free(soa.humidities);
        free(soa.timestamps);
        free(soa.sensor_ids);
        return 1;
    }

    for (size_t i = 0; i < size; i++)
    {
        aos[i].temperature = soa.temperatures[i] = i % 100;
        aos[i].sensor_id = soa.sensor_ids[i] = i % 16;
    }

    clock_t start = clock();
    double result_aos = average_aos(aos, size, 7);
    double seconds_aos = (double)(clock() - start) / CLOCKS_PER_SEC;

    start = clock();
    double result_soa = average_soa(&soa, 7);
    double seconds_soa = (double)(clock() - start) / CLOCKS_PER_SEC;

    printf("AoS: %.2f, CPU time: %.6f s\n", result_aos, seconds_aos);
    printf("SoA: %.2f, CPU time: %.6f s\n", result_soa, seconds_soa);

    free(aos);
    free(soa.temperatures);
    free(soa.humidities);
    free(soa.timestamps);
    free(soa.sensor_ids);
    return 0;
}
*/