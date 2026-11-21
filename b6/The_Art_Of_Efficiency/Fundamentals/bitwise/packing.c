#include "packing.h"
#include <stdio.h>
#include <stdlib.h>
// == Record packing ==
/*

struct record
{
    char id[2]; // 2-character identifier
    uint8_t type; // Type of the record (4 bits)
    uint8_t priority; // Priority of the record (2 bits)
    uint16_t value; // Numerical value associated with the record (10 bits)
};
*/
uint32_t pack_record(const struct record *record)
{
    uint32_t res=0;
    uint32_t a=(uint8_t)record->id[0];
    res=res|a;

    uint32_t b=(uint8_t)record->id[1];
    b=b<<8;
    res=res | b;
    uint32_t type=record->type & 0x0F; // 0000 1111
    type=type<<16;
    res=res | type;
    uint32_t p=record->priority & 0x03; // 0000 0011
    p=p<<20;
    res=res | p;
    uint32_t v=record->value & 0x03FF; // 0000 0000 0000 0011 1111 1111
    v=v <<22;
    res =res | v;
    return res;





}

struct record *unpack_record(uint32_t packed)
{
    struct record*box=malloc(sizeof(struct record));
    if(!box)return NULL;
    //box->id=malloc(sizeof(char)); non c pas id* pas un ptr
    box->id[0]=0;
    for(int i=7;i>-1;i--)
    {
        uint8_t m=1u <<i;
        uint8_t b=packed & m;
        b=b>>i;
        box->id[0]=box->id[0]<<1;
        box->id[0]=box->id[0] | b;

    }
    box->id[1]=0;
    for(int i=15;i>7;i--)
    {
        uint32_t m=1u <<i;
        uint32_t b=packed & m;
        b=b>>i;
        box->id[1]=box->id[1] <<1;
        box->id[1]=box->id[1] | b;
    }
    box->type=0;
    for(int i=19 ; i>15;i--)
    {
        uint32_t m=1u <<i;
        uint32_t b=packed & m;
        b=b>>i;
        box->type=box->type<<1;
        box->type=box->type | b;
    }
    box->priority=0;
    for(int i=21 ; i>19;i--)
    {
        uint32_t m=1u <<i;
        uint32_t b=packed & m;
        b=b>>i;
        box->priority=box->priority<<1;
        box->priority=box->priority | b;

    }
    box->value=0;
    for(int i=31; i>21;i--)
    {
        uint32_t m=1u <<i;
        uint32_t b=packed & m;
        b=b>>i;
        box->value=box->value<<1;
        box->value=box->value | b;

    }
    return box;
}

// == Firefly packing ==
/*

enum firefly_type
{
    FT_NO_LIGHT = 0,
    FT_BARELY = 1,
    FT_DIM = 2,
    FT_LOW = 3,
    FT_HIGH = 4,
    FT_BRIGHT = 5,
    FT_SUN = 6,
    FT_SUPERNOVA = 7,
    FT_UNIMAGINABLE = 8,
    FT_IDK_ANYMORE_TOO_BRIGHT = 9
};

struct firefly
{
    char *name;
    enum firefly_type light_type;
    unsigne char leg_count;
};

*/
int strlenn(char*str)
{
    int len=0;
    while(str[len]!='\0')
    {
        len++;
    }
    return len;
}
void pack_firefly(const struct firefly *firefly, uint8_t *packed)
{
    if(!packed || ! firefly)return;
    int len =strlenn(firefly->name);
    packed[0]=len;
    for(int i=0;i<len;i++)
    {
        packed[i+1]=firefly->name[i];
    }
    uint8_t res=0;
    uint8_t a=firefly->light_type;
    // je veux que les 4 bits
    // je peux faire un masque qui contient 1 dans la partie que je veux recuperer et apres un and
    for (int i=3;i>-1;i--)
    {
        uint8_t m=1<<i;
        uint8_t b=firefly->leg_count & m;
        b=b>>i;
        res=res<<1;
        res=res | b;
    }


    uint8_t c=res<<4;

    packed[len+1]=a|c;


}

void unpack_firefly(const uint8_t *packed, struct firefly *firefly)
{
        if(!packed || ! firefly)return;

        int len=packed[0];
        for (int i=0;i<len;i++)
        {
            firefly->name[i]=packed[i+1];
        }
        firefly->name[len]='\0';

        uint8_t m=0x0F;//0000 1111
        firefly->light_type=packed[len+1] & m;
        uint8_t mm=0xF0;
        firefly->leg_count=packed[len+1] & mm >> 4;
}

/*
int main(void)
{
    struct record record = {
        .id = { 'A', 'B' },
        .type = 3,
        .priority = 2,
        .value = 42
    };

    uint32_t packed = pack_record(&record);
    printf("Packed: 0x%08lx\n", (unsigned long)packed);

    struct record *decoded = unpack_record(packed);
    if (decoded == NULL)
    {
        return EXIT_FAILURE;
    }

    printf("ID: %c%c\n", decoded->id[0], decoded->id[1]);
    printf("Type: %u\n", (unsigned int)decoded->type);
    printf("Priority: %u\n", (unsigned int)decoded->priority);
    printf("Value: %u\n", (unsigned int)decoded->value);

    free(decoded);
    return EXIT_SUCCESS;
}
*/



int main(void)
{
    struct firefly firefly = {
        .name = "Jiro",
        .light_type = FT_BRIGHT,
        .leg_count = 6
    };
    uint8_t packed[6];

    pack_firefly(&firefly, packed);

    for (size_t i = 0; i < sizeof(packed); i++)
    {
        printf("%02x%s", (unsigned int)packed[i],
               i + 1 == sizeof(packed) ? "\n" : " ");
    }

    char name[5];
    struct firefly decoded = { .name = name };

    unpack_firefly(packed, &decoded);

    printf("Name: %s\n", decoded.name);
    printf("Light type: %u\n", (unsigned int)decoded.light_type);
    printf("Leg count: %u\n", (unsigned int)decoded.leg_count);

    return 0;
}

