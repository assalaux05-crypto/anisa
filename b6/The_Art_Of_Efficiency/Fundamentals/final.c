#include "final.h"









/*

struct grid
{
    size_t width;
    size_t height;
    uint8_t *data;
};

*/
size_t grid_count(const struct grid *grid)
{
    
        size_t cpt=0;
        size_t tot=grid->width * grid->height;
        size_t r=0;
        if(tot%8!=0)
        {
            r=1;
        }
        size_t octet=tot/8+r;
        for(size_t i=0;i<octet;i++)
        {
            size_t limit=tot-i*8;
            if(limit>8)
            {
                limit=8;
            }
            // je prend pas j<8 psq la grill nest pas init a 0 donc il faut limiter 

           for(int j=0;j<limit;j++)
           {
             uint8_t m=1<<j;
            uint8_t res=grid->data[i] & m;
            res=res>>j;
            if((int)res==1)cpt++;
           }
           
        

        }
        return cpt;









}

void grid_invert(struct grid *grid)
{
    if(!grid)return ;
    size_t tot=grid->width *grid->height;
    size_t r=0;
    if(tot%8!=0)
    {
        r=1;
    }
    size_t octet=tot/8+r;
    for(int i=0;i<octet;i++)
    {
        size_t l=tot-i*8;
        if(l>8)l=8;
        for(size_t j=0;j<l;j++)
        {
            uint8_t m=1<<j;
           grid-> data[i] ^=m;// je fait comment pour acceder au bit exacte
        }
    }
    
}

unsigned int grid_count_neighbors(const struct grid *grid, size_t x, size_t y)
{


if (!grid || x >= grid->width || y >= grid->height)
        return 0;

    size_t cpt = 0;

    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            // la case elle meme
            if (dx == 0 && dy == 0)
                continue;

            //voisin
            int nx = (int)x + dx;
            int ny = (int)y + dy;

            // voisi dans grid
            if (nx < 0 || ny < 0 ||
                nx >= (int)grid->width || ny >= (int)grid->height)
                continue;

            // index du bit
           size_t index = (size_t)ny * grid->width + (size_t)nx;
            // Récupérer la valeur du bit
            int value = (grid->data[index / 8] >> (index % 8)) & 1;

            
            if (value == 1)
                cpt++;
        }
    }

    return cpt;
}
/*
#include "final.h"

#include <stdio.h>

int main(void)
{
    // Cells, row by row:
    // 1 0 1
    // 0 1 0
    // 1 0 1
    //
    // In the last byte, only bit 0 represents a cell.
    // The other bits are deliberately set to 1.
    uint8_t data[] = { 0x55, 0xff };
    struct grid grid = {
        .width = 3,
        .height = 3,
        .data = data
    };

    printf("Active cells: %zu\n", grid_count(&grid));
    printf("Center neighbors: %u\n",
           grid_count_neighbors(&grid, 1, 1));
    printf("Corner neighbors: %u\n",
           grid_count_neighbors(&grid, 0, 0));

    grid_invert(&grid);

    printf("After inversion: %zu\n", grid_count(&grid));
    printf("Stored bytes: %02x %02x\n",
           (unsigned int)data[0], (unsigned int)data[1]);

    return 0;
}
*/