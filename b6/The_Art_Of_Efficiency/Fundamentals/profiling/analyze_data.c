#include "analyze_data.h"

#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 5000

int main(void)
{
    unsigned int *data = malloc(DATA_SIZE * sizeof(*data));
    if (data == NULL)
        return EXIT_FAILURE;

    for (size_t i = 0; i < DATA_SIZE; i++)
        data[i] = (i * 14 + 58) % 1722;

    unsigned int checksum = compute_checksum(data, DATA_SIZE);
    unsigned long result = analyze_data(data, DATA_SIZE);

    printf("Checksum: %u\n", checksum);
    printf("Result: %lu\n", result);

    free(data);
    return EXIT_SUCCESS;
}

unsigned int compute_checksum(const unsigned int *data, size_t n)
{
    unsigned int checksum = 0;

    for (size_t i = 0; i < n; i++)
        checksum ^= data[i];

    return checksum;
}

unsigned int compute_threshold(const unsigned int *data, size_t n)
{
    if (n == 0)
        return 0;

    unsigned long sum = 0;

    for (size_t i = 0; i < n; i++)
        sum += data[i];

    return sum / n;
}
/*
unsigned int compute_score(const unsigned int *data, size_t n, size_t index)
{
    unsigned int threshold = compute_threshold(data, n);
    unsigned int value = data[index];

    return value > threshold ? value - threshold : 0;
}
*/

unsigned long analyze_data(const unsigned int *data, size_t n)
{
    unsigned long result = 0;
    unsigned int threshold = compute_threshold(data, n);

    for (size_t i = 0; i < n; i++)
        result += data[i] > threshold ? data[i] - threshold : 0;

    return result;
}
