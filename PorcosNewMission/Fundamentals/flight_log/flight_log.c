#include "flight_log.h"
#include <stdio.h>
/*
struct Mission
{
    char *date;
    char *mission_type;
    double bounty;
};
*/

struct Mission *alloc_missions(size_t n)
{
    struct Mission* arr=malloc(n*sizeof(struct Mission));
    if (arr==NULL)
    {
        printf("Error : Could not allocate memory\n");
        return NULL;
    }
    for(size_t i=0;i<n;i++)
    {
        arr[i].date=NULL;
        arr[i].mission_type=NULL;
        arr[i].bounty=0.0;


    }
    
    return arr ;
}

void init_mission(struct Mission *missions, size_t i, char *date, char *type, double bounty)
{

        if( missions==NULL || date==NULL || type==NULL || bounty<0 )
        {
           printf("Error : Invalid Parameter\n") ;
           return ;
        }
        missions[i].date=date;
        missions[i].mission_type=type;
        missions[i].bounty=bounty;
        
}
void free_missions(struct Mission *missions, size_t n)
{
    if (missions ==NULL)
    {
        printf( "Error : Invalid Parameter\n");
        return ;
    }
    if (n==0)return ;
    for(size_t i=0;i<n;i++)
    {
        free(missions[i].date);
        free(missions[i].mission_type);
    }
    free(missions);
}
double total_bounty(struct Mission *missions, size_t n) 
{   if(missions==NULL)
    {
        printf("Error : Invalid Parameter\n");
        return -1;
    }
    if (n==0)return 0;
    
    double count=0.0;
    for (size_t i=0;i<n;i++)
    {
        count =missions[i].bounty+count;
    }
    return count ;
}
/*
int main(void)
{
    struct Mission *missions = alloc_missions(2);
init_mission(missions, 0, "17/06/1929", "Escort", 4500.00);
init_mission(missions, 1, "22/06/1929", "Recovery", 3700.50);
size_t n = 2;

double total = total_bounty(missions, n);
// total is now 8200.50
printf("totale:%f\n",total);
}
*/
struct Mission *max_bounty(struct Mission *missions, size_t n)
{
    if (missions==NULL)
    {
        printf("Error : Invalid Parameter\n");
        return NULL;
    }
    if (n==0)return NULL;
    struct  Mission* max_box=&missions[0];
    double maxb=missions[0].bounty;
    for(size_t i=1; i<n;i++)
    {
        if (missions[i].bounty>maxb)
        {
            maxb=missions[i].bounty;
            max_box=&missions[i];
        }
    }
    return max_box;

}

/*
int main(void)
{
struct Mission *missions = alloc_missions(2);
init_mission(missions, 0, "17/06/1929", "Escort", 4500.00);
init_mission(missions, 1, "22/06/1929", "Recovery", 3700.50);
size_t n = 2;

struct Mission *best = max_bounty(missions, n);
// best is now &missions[0] (bounty = 4500.00, the highest)
printf("best is now %f\n",best->bounty);
return 0;


}
*/