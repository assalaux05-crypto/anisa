#include "report.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *generate_flight_summary(double velocity, double angle_rad)
{
    
    
    double v=velocity *velocity;
    double s=sin(angle_rad)*sin(angle_rad);
    double height=(v*s)/(2*9.81);
    
     double a=2*angle_rad;
     double range=(v*sin(a))/9.81;
     double time=(2*velocity*sin(angle_rad))/9.81;
     
    double k=sin(angle_rad)*sin(angle_rad);
      double max_height=(velocity*velocity*k)/(2*9.81);
      char* str="\0";
    if (max_height>=60.0)
    {
         str= "HIGH ALTITUDE";
            
    }
    else if (max_height>=20.0&& max_height<60.0)
    {
        str=  "MODERATE ALTITUDE";
    }
    else str= "LOW ALTITUDE";

  int taille=  snprintf(NULL,0,"At %.2f m/s and %.4f rad, the machine reaches a maximum height of %.2f m, covers a range of %.2f m in %.2f s of flight, and is rated: %s.",velocity,angle_rad,height,range,time,str);
  char * summ=malloc(taille *sizeof(char));
  if (!summ)return NULL;
  snprintf(summ,taille+1,"At %.2f m/s and %.4f rad, the machine reaches a maximum height of %.2f m, covers a range of %.2f m in %.2f s of flight, and is rated: %s.",velocity,angle_rad,height,range,time,str);
  return summ;
}

/*
struct Machine {
    char name[64];
    double velocity;   /* m/s */
    double angle_rad;  /* radians *
};

*/
int write_flight_report(const char *filepath, const struct Machine *machines,
                         int count, double threshold)
{
    //name=Savoia S.21 max_height=45.34 range=259.01 verdict=cleared
    FILE *f=fopen(filepath,"w");
    if(!f)return -1;
    for(int i=0;i<count;i++)
    {
      double a=machines[i].angle_rad;
      double sinn=sin(a);
      double s=sinn*sinn;
      double v=(machines[i].velocity)*(machines[i].velocity);
      double max_height=(v*s)/(2*9.81);

      double vv=(machines[i].velocity)*(machines[i].velocity);
      double aa=2*a;
      double ss=sin(aa);

      double range =(vv*ss)/9.81;
      char* verdict="\0";
      if(max_height>threshold)
      {
        verdict="cleared";
      }
      else 
      {
        verdict ="grounded";
      }
      fprintf(f,"name=%s max_height=%2f range=%2f verdict=%s\n",machines[i].name,max_height,range,verdict);


    }
    fclose(f);
    return 0;
}
