#include "physics.h"
#include <complex.h>
#include <stddef.h>
#include <math.h>

double degrees_to_radians(double degrees)
{
    //adians = degrees × (π / 180)
    double radians=degrees*(M_PI/180.0);
    return radians;
}

double calculate_vx(double velocity, double angle_rad)
{
    //vx = velocity × cos(angle_rad)
    double res=velocity*cos(angle_rad);
    return res;
}

double calculate_vy(double velocity, double angle_rad)
{
    //vy = velocity × sin(angle_rad)
    double res=velocity*sin(angle_rad);
    return res;
}

double calculate_max_height(double velocity, double angle_rad)
{
    //max_height = (velocity² × sin(angle_rad)²) / (2 × g)
    double sinn=sin(angle_rad);
    double s=sinn*sinn;
    double max_height=(velocity*velocity*s)/(2*9.81);
    return max_height;
}

double calculate_range(double velocity, double angle_rad)
{
    double v=velocity * velocity;
    double a=2*angle_rad;
    double s=sin(a);
    double range =(v*s)/9.81;
    return range ;
    
}

double calculate_time_of_flight(double velocity, double angle_rad)
{
    double t=(2*velocity*sin(angle_rad))/9.81;
    return t;
}

const char *classify_altitude(double max_height)
{
if (max_height>=60.0)
    {
         return "HIGH ALTITUDE";
            
    }
else if (max_height>=20.0&& max_height<60.0)
{
    return  "MODERATE ALTITUDE";
}
else return "LOW ALTITUDE";

}
