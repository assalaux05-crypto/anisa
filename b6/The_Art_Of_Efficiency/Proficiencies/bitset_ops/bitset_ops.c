#include "bitset_ops.h"

#include <stdlib.h>


/*
struct bitset
{
    size_t size;// nb bit et pas octet
    uint8_t *data;
};




*/
struct bitset *bitset_union(const struct bitset *a, const struct bitset *b)
{

    if(!a || !b)return NULL;
    struct bitset*box=malloc(sizeof (struct bitset));
    
    if(!box)return NULL;
    box->size=a->size;
    size_t r=0;
    if(box->size%8!=0)
    {
        r=1;
    }
    size_t nb_o=box->size/8+r;
    box->data=calloc(nb_o,sizeof(uint8_t));
    if(!box->data)
    {
        free(box);

        return NULL;
    }
    for (size_t i=0;i<nb_o;i++)
    {
        box->data[i]=a->data[i] | b->data[i];

    }
    return box;

}

struct bitset *bitset_intersection(const struct bitset *a,
                                   const struct bitset *b)
{
    if(!a || !b)return NULL;
    struct bitset*box=malloc(sizeof (struct bitset));
    
    if(!box)return NULL;
    box->size=a->size;
    size_t r=0;
    if(box->size%8!=0)
    {
        r=1;
    }
    size_t nb_o=box->size/8+r;
    box->data=calloc(nb_o,sizeof(uint8_t));
    if(!box->data)
    {
        free(box);

        return NULL;
    }
    for (size_t i=0;i<nb_o;i++)
    {
        box->data[i]=a->data[i] & b->data[i];

    }
    return box;
}

struct bitset *bitset_difference(const struct bitset *a, const struct bitset *b)
{
    if(!a || !b)return NULL;
    struct bitset*box=malloc(sizeof (struct bitset));
    
    if(!box)return NULL;
    box->size=a->size;
    size_t r=0;
    if(box->size%8!=0)
    {
        r=1;
    }
    size_t nb_o=box->size/8+r;
    box->data=calloc(nb_o,sizeof(uint8_t));
    if(!box->data)
    {
        free(box);

        return NULL;
    }
    for (size_t i=0;i<nb_o;i++)
    {
        box->data[i]=a->data[i] & ~b->data[i];

    }
    return box;
}

struct bitset *bitset_symmetric_difference(const struct bitset *a,
                                           const struct bitset *b)
{
   if(!a || !b)return NULL;
    struct bitset*box=malloc(sizeof (struct bitset));
    
    if(!box)return NULL;
    box->size=a->size;
    size_t r=0;
    if(box->size%8!=0)
    {
        r=1;
    }
    size_t nb_o=box->size/8+r;
    box->data=calloc(nb_o,sizeof(uint8_t));
    if(!box->data)
    {
        free(box);

        return NULL;
    }
    for (size_t i=0;i<nb_o;i++)
    {
        box->data[i]=a->data[i] ^ b->data[i];

    }
    return box;
}

int bitset_is_subset(const struct bitset *a, const struct bitset *b)
{
   if(!a || !b)return 0;
   size_t r=0;
   if(a->size%8!=0)
   {
    r=1;
   }
   size_t nb_o=a->size/8+r;
   for(size_t i=0;i<nb_o;i++)
   {
        uint8_t res=a->data[i] & ~b->data[i];
        if(res!=0)
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
