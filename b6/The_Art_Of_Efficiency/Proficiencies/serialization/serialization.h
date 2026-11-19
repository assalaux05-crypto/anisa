#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <stddef.h>
#include <stdint.h>

struct node
{
    uint16_t value;
    struct node *left;
    struct node *right;
};

uint8_t *tree_serialize(const struct node *root, size_t *byte_count);
struct node *tree_deserialize(const uint8_t *data, size_t byte_count);

#endif /* ! SERIALIZATION_H */
