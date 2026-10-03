#include "simulation.h"
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/*


struct FlightPoint{
    double t;
    double x;
    double y;
};

enum WindDirection{
    WIND_HEADWIND,
    WIND_TAILWIND
};



struct Machine {
    char name[64];
    double velocity;  
    double angle_rad;  radians 
};
je c pas combien de pt je vais stocke 
*/
struct FlightPoint *simulate_flight(struct Machine machine, double dt, int *nb_points)
{

    double vx=machine.velocity*cos(machine.angle_rad);
    double vy=machine.velocity*sin(machine.angle_rad);
    double t=0.0;
    double x=0.0;
    double y=0.0;
    int c=16;
    int nb=0;
    struct FlightPoint* points=malloc(c*sizeof(struct FlightPoint));
    if(!points)return NULL;
    points[0].t=0.0;
    //printf("hello\n");

    points[0].x=0.0;
    points[0].y=0.0;
    for(int i=1;i<c;i++)
    {
        if(c==nb)
        {
            c*=2;
            points=realloc(points,c*sizeof(struct FlightPoint));
     
        }
        x=x+vx*dt;
        y=y+vy*dt;
        vy=vy-9.81*dt;
        t=t+dt;
        points[i].t=t;
        points[i].x=x;
        points[i].y=y;
        nb++;
        if(points[i].y<=0)
        {
            break;
        }
    }
    nb_points=&nb;// calcul pas bon 
    return points;
}

void free_flight_points(struct FlightPoint *points)
{
    free(points);
}


struct Wind parse_environment(const char *filepath)
{
    FILE* f=fopen(filepath,"r");
    if(!f)return NULL;
    /*parse_environment must return a Wind with speed 0.0 and a safe default direction*/
    struct Wind box=NULL;
    char buff[128];
    while(fgets(buff,sizeof(buff),f)!=NULL)
    {
        /*
            struct Wind{
    double speed;
    enum WindDirection direction;
};
        */
        char* info=strtok(buff,"=");
        if(!info)
        
            {
                fclose(f);
                return NULL;
            }
        
        if(strcmp(info,"wind_speed")==0)
        {
            char* speed=strtok(NULL,"=");
            if(!speed)
            {
                fclose(f);
                return NULL;
            }
            box.speed=atof(speed);

        }
        if(strcmp(info,"wind_direction")==0)
        {
            char* dr=strtok(NULL,"=");
            if(!dr)
            {
                fclose(f);
                return NULL;

            }
            /*
            
                enum WindDirection{
                    WIND_HEADWIND,
                    WIND_TAILWIND
                };

            */
            if(strcmp(d,"headwind"))
            {
                box.direction=WIND_HEADWIND;

            }
            else{
                box.direction= WIND_TAILWIND;
            }

        }
    }
    fclose(f);
    return box;
}

struct FlightPoint *simulate_flight_with_wind(struct Machine machine, struct Wind wind,
                                        double dt, int *nb_points)
{
    double vx = machine.velocity * cos(machine.angle_rad);
    if (wind.direction == WIND_HEADWIND)
        vx -= wind.speed;
    else if (wind.direction == WIND_TAILWIND)
        vx += wind.speed;
    double vy=machine.velocity*sin(machine.angle_rad);
    double t=0.0;
    double x=0.0;
    double y=0.0;
    int c=16;
    int nb=0;

    struct FlightPoint *points = malloc(capacity * sizeof(*points));
    if (points == NULL)
    {
        *nb_points = 0;
        return NULL;
    }
    points[0].t=0.0;
    //printf("hello\n");

    points[0].x=0.0;
    points[0].y=0.0;
    for(int i=1;i<c;i++)
    {
        if(c==nb)
        {
            c*=2;
            points=realloc(points,c*sizeof(struct FlightPoint));
     
        }
        x=x+vx*dt;
        y=y+vy*dt;
        vy=vy-9.81*dt;
        t=t+dt;
        points[i].t=t;
        points[i].x=x;
        points[i].y=y;
        nb++;
        if(points[i].y<=0)
        {
            break;
        }
    }
    nb_points=&nb;// calcul pas bon 
    return points;
}






