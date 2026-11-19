#include "bitset.h"

#include <stdlib.h>



/*

struct bitset
{
    size_t size; // Number of bits stored in the bitset
    uint8_t *data; // Pointer to the allocated buffer
};

*/
struct bitset *bitset_create(size_t size)
{
    struct bitset*box=malloc(sizeof(struct bitset));
    if(!box)return NULL;
    box->size=size;
    if(size==0)
    {
        box->data=NULL;
        return box;
    }
    //faire tres attention qd jai des bit moi il me faut combien octe et faut gerer le cas quand ya le rest
    // size=10 10/8=1octet mais il reste 2bit il leur faut un octe
    size_t reste=0;
    if(size%8!=0)
    {
        reste=1;
    }
    size_t n=size/8+reste;//nb octet 
    box->data=calloc(n,sizeof(uint8_t));
    if(!box->data)
    {
        free(box);
        return NULL;
    }
    return box;
}

void bitset_destroy(struct bitset *bs)
{
    if(!bs)return;
    free(bs->data);
    free(bs);
}


/*
    index/8 =>octet
    index%8 le bit de loctet


*/

void bitset_set(struct bitset *bs, size_t index, int value)
{
    if(!bs || index>=bs->size)return ;
    if(value==0)
    {
        //bs->data[index]
        uint8_t m=1<<(index%8);
        bs->data[index/8]=bs->data[index/8] & ~m;

    }
    else 
    {
        uint8_t n=1<<(index%8);
        bs->data[index/8]=bs->data[index/8] | n;

    }
}

int bitset_get(const struct bitset *bs, size_t index)
{
    if(!bs || bs->size<=index)return -1;
    uint8_t m=1<<(index%8);
    uint8_t res=bs->data[index/8] & m;
    res=res>>(index%8);
    return (int)res;
}
/*
#include <stdio.h>
int main(void)
{
    struct bitset *b = bitset_create(12);

    bitset_set(b, 3, 1);
    printf("%d\n", bitset_get(b, 0));
    printf("%d\n", bitset_get(b, 1));
    printf("%d\n", bitset_get(b, 3));
    printf("%d\n", bitset_get(b, 4));

    bitset_destroy(b);
    return 0;
}
*/