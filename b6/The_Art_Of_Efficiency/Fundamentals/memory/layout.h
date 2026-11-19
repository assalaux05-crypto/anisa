#ifndef LAYOUT_H
#define LAYOUT_H

#include <stdint.h>

struct record
{
    char status;
    uint64_t timestamp;
    uint8_t priority;
    uint32_t id;
    uint16_t value;
    char *category;
};

#endif /* ! LAYOUT_H */
