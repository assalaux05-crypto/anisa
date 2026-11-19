#include "bits.h"
#include <stdio.h>

uint8_t set_bit(uint8_t value, unsigned int pos)
{
    uint8_t n=1<<pos;
    uint8_t res=value | n;
    return res;
}

uint8_t unset_bit(uint8_t value, unsigned int pos)
{
    uint8_t n=1<<pos;

    uint8_t res=value & ~n;

    return res;
}

uint8_t invert_bit(uint8_t value, unsigned int pos)
{
    uint8_t n=1<<pos;

    return value ^ n;
}

/*
recuperer bit=> msk et and avec val + decalage a doite pour avoir exactement le bit que jai besoin
ajouter bit a mon res => mais avant faut lui liberer une place avec un decalage a gauche








*/

uint8_t extract_bits(uint8_t value, unsigned int start, unsigned int count)
{
    uint8_t res=0;;
    
    for(unsigned int i=start;i<count+start;i++)
    {
        uint8_t m=1<<i;
        uint8_t bit= value & m;
        bit=bit >> i;
        res=res << 1 ;
        res=res | bit;
    }
    return res;
}
/*
int main(void)
{
    uint8_t value = 42; // 0b00101010

    printf("%u\n", (unsigned int)extract_bits(value, 2, 5));
    printf("%u\n", (unsigned int)extract_bits(value, 1, 3));

    return 0;
}
*/