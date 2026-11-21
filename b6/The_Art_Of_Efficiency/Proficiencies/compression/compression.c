#include "compression.h"


#include <stdlib.h>


/*

    1 1 1 0 0 1 1 0

    1 | 0|0 | 0|0|1|0|0| 1 ->3fois
    data[0]=1 1 1 0 0 1 1 0






*/
uint8_t *rle_compress(const uint8_t *data, size_t bit_count,
                      size_t *compressed_size)
{


        if(!data || bit_count==0)return NULL;
        uint8_t *box=malloc(bit_count*sizeof(uint8_t));
        if(!box)return NULL;
        *compressed_size=0;
        uint8_t val=data[0]& 1u;// pour recuperer le premier bit 00000001
        size_t len=1;
        size_t idx = 0;
        
        for(size_t i=1;i<bit_count;i++)
        {
            uint8_t m=1u<<(i%8);
            uint8_t res= data[i/8] & m;// faire attention faut div 8 psq je gere des bit et pas des octet
            res=res>>(i%8);
            if(res==val && len <127)
            {
                len++;
                continue;
            }
            // je remplis box
            box[idx]=(val<<7) | len;
            idx++;
            len=1;
            val=res;
            
        }
        box[idx++] = (val << 7) | len;// last sequence 
        *compressed_size = idx;
        return box;
    
}

uint8_t *rle_decompress(const uint8_t *data, size_t size, size_t *bit_count)
{
   


        size_t cpt=0;
        for(size_t i=0;i<size;i++)
        {
            uint8_t len=data[i] & 0x7F;
            cpt+=len;
        }
        *bit_count=cpt;
        size_t r=0;
        if(cpt%8!=0)
        {
            r=1;
        }
        size_t nb_o=cpt/8+r;
        uint8_t*box=calloc(nb_o,sizeof(uint8_t));
        size_t idx=0;
        if(!box)return NULL;
        for(size_t i=0;i<size;i++)
        {
            uint8_t val=data[i]>>7;
            uint8_t len=data[i] & 0x7F ;//01111111
            for(size_t j=0;j<len;j++)
            {
                box[idx/8]=box[idx/8] | val<<(idx%8);
                idx++;

            }
        }

        return box;




}
#include "compression.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Read from bit 0 to bit 7: 1 1 1 0 0 1 1 0.
    uint8_t data[] = { 0x67 };
    size_t compressed_size;

    uint8_t *compressed =
        rle_compress(data, 8, &compressed_size);
    if (compressed == NULL)
    {
        return EXIT_FAILURE;
    }

    printf("Compressed:");
    for (size_t i = 0; i < compressed_size; i++)
    {
        printf(" %02x", (unsigned int)compressed[i]);
    }
    printf("\n");

    size_t bit_count;
    uint8_t *decoded =
        rle_decompress(compressed, compressed_size, &bit_count);
    if (decoded == NULL)
    {
        free(compressed);
        return EXIT_FAILURE;
    }

    printf("Decoded bits: %zu\n", bit_count);
    printf("Decoded byte: %02x\n", (unsigned int)decoded[0]);

    free(decoded);
    free(compressed);

    // 130 consecutive ones require two runs: 127 and 3.
    uint8_t long_run[17];
    for (size_t i = 0; i < sizeof(long_run); i++)
    {
        long_run[i] = 0xff;
    }

    compressed = rle_compress(long_run, 130, &compressed_size);
    if (compressed == NULL)
    {
        return EXIT_FAILURE;
    }

    printf("Long run:");
    for (size_t i = 0; i < compressed_size; i++)
    {
        printf(" %02x", (unsigned int)compressed[i]);
    }
    printf("\n");

    free(compressed);
    return EXIT_SUCCESS;
}
