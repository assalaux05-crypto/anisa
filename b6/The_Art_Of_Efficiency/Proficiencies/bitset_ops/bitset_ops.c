#include "bitset_ops.h"

#include <stdlib.h>


/*
struct bitset
{
    size_t size;// nb bit et pas octet
    uint8_t *data;
};




*/

#include "bitset_ops.h"

#include <stdlib.h>

static size_t cnt_byte(size_t size)
{
    size_t r = 0;

    if (size % 8 != 0)
    {
        r = 1;
    }

    return size / 8 + r;
}

static uint8_t getB(const struct bitset *bs, size_t i)
{
    size_t nb = cnt_byte(bs->size);

    if (i >= nb)
    {
        return 0;
    }

    uint8_t value = bs->data[i];

    if (i == nb - 1 && bs->size % 8 != 0)
    {
        uint8_t mask = (1 << (bs->size % 8)) - 1; 
        value = value & mask;
    }

    return value;
}

static struct bitset *create_result(size_t size)
{
    struct bitset *box = malloc(sizeof(struct bitset));

    if (!box)
    {
        return NULL;
    }

    box->size = size;

    size_t nb_o = cnt_byte(size);
    box->data = NULL;

    if (nb_o != 0)
    {
        box->data = calloc(nb_o, sizeof(uint8_t));

        if (!box->data)
        {
            free(box);
            return NULL;
        }
    }

    return box;
}

struct bitset *bitset_union(const struct bitset *a,
                            const struct bitset *b)
{
    if (!a || !b)
    {
        return NULL;
    }

    size_t size = a->size;

    if (b->size > size)
    {
        size = b->size;
    }

    struct bitset *box = create_result(size);

    if (!box)
    {
        return NULL;
    }

    size_t nb_o = cnt_byte(size);

    for (size_t i = 0; i < nb_o; i++)
    {
        uint8_t av = getB(a, i);
        uint8_t bv = getB(b, i);

        box->data[i] = av | bv;
    }

    return box;
}

struct bitset *bitset_intersection(const struct bitset *a,
                                   const struct bitset *b)
{
    if (!a || !b)
    {
        return NULL;
    }
    size_t size = a->size;
    if (b->size > size)
    {
        size = b->size;
    }
    struct bitset *box = create_result(size);
    if (!box)
    {
        return NULL;
    }
    size_t nb_o = cnt_byte(size);
    for (size_t i = 0; i < nb_o; i++)
    {
        uint8_t av = getB(a, i);
        uint8_t bv = getB(b, i);
        box->data[i] = av & bv;
    }
    return box;
}

struct bitset *bitset_difference(const struct bitset *a,
                                 const struct bitset *b)
{
    if (!a || !b)
    {
        return NULL;
    }
    struct bitset *box = create_result(a->size);
    if (!box)
    {
        return NULL;
    }
    size_t nb_o = cnt_byte(a->size);
    for (size_t i = 0; i < nb_o; i++)
    {
        uint8_t av = getB(a, i);
        uint8_t bv = getB(b, i);
        box->data[i] = av & ~bv;
    }
    return box;
}

struct bitset *bitset_symmetric_difference(const struct bitset *a,
                                           const struct bitset *b)
{
    if (!a || !b)
    {
        return NULL;
    }
    size_t size = a->size;
    if (b->size > size)
    {
        size = b->size;
    }
    struct bitset *box = create_result(size);
    if (!box)
    {
        return NULL;
    }
    size_t nb_o = cnt_byte(size);
    for (size_t i = 0; i < nb_o; i++)
    {
        uint8_t av = getB(a, i);
        uint8_t bv = getB(b, i);
        box->data[i] = av ^ bv;
    }
    return box;
}

int bitset_is_subset(const struct bitset *a,
                     const struct bitset *b)
{
    if (!a || !b)
    {
        return 0;
    }
    size_t nb_o = cnt_byte(a->size);
    for (size_t i = 0; i < nb_o; i++)
    {
        uint8_t av = getB(a, i);
        uint8_t bv = getB(b, i);
        uint8_t res = av & ~bv;
        if (res != 0)
        {
            return 0;
        }
    }
    return 1;
}

/*
#include "bitset_ops.h"

#include <stdio.h>

int main(void)
{
    // a = { 2, 4 }, b = { 0, 2, 4 }
    uint8_t a_data[] = { 0x14 };
    uint8_t b_data[] = { 0x15 };
    uint8_t empty_data[] = { 0x00 };

    struct bitset a = { .size = 5, .data = a_data };
    struct bitset b = { .size = 5, .data = b_data };

    // Same size, but no elements belong to this set.
    struct bitset empty = { .size = 5, .data = empty_data };

    printf("a subset of b: %d\n", bitset_is_subset(&a, &b));
    printf("b subset of a: %d\n", bitset_is_subset(&b, &a));
    printf("Empty subset of a: %d\n",
           bitset_is_subset(&empty, &a));

    return 0;
}
*/
#include "bitset_ops.h"

#include <stdio.h>

int main(void)
{
    // a = { 2, 4 }, b = { 0, 2, 4 }
    uint8_t a_data[] = { 0x14 };
    uint8_t b_data[] = { 0x15 };
    uint8_t empty_data[] = { 0x00 };

    struct bitset a = { .size = 5, .data = a_data };
    struct bitset b = { .size = 5, .data = b_data };

    // Same size, but no elements belong to this set.
    struct bitset empty = { .size = 5, .data = empty_data };

    printf("a subset of b: %d\n", bitset_is_subset(&a, &b));
    printf("b subset of a: %d\n", bitset_is_subset(&b, &a));
    printf("Empty subset of a: %d\n",
           bitset_is_subset(&empty, &a));

    return 0;
}
