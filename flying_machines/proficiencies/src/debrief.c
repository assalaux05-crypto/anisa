#include "report.h"
#include <stdio.h>
#include <simulation.h>

int write_trajectory_csv(const char *filepath, const char *machine_name,
                          const struct FlightPoint *points, int nb_points)
{
    FILE* f=fopen(filepath,"w");
    if(!f)return -1;
    fprintf(f,"machine,t,x,y\n");
    for (int i=0; i<nb_points;i++)
    {
        fprintf(f,"%s,%.2f,%.2f,%.2f\n",machine_name,points[i].t,points[i].x,points[i].y);

    }
    fclose(f);
    return 0;

}

double compute_landing_distance_difference(const struct FlightPoint *points_no_wind,
                                            int n1,
                                            const struct FlightPoint *points_wind,
                                            int n2)
{
    if(points_no_wind == NULL || points_wind == NULL || n1<=0 || n2<=0)return 0.0;
    double x1=points_no_wind[n1-1].x;
    double x2=points_wind[n2-1].x;
    double res=x2-x1;
    return res;
}

int write_mission_debrief(const char *filepath, const char *machine_name,
                           const struct FlightPoint *points_no_wind, int n1,
                           const struct FlightPoint *points_wind, int n2)
{
    FILE* f=fopen(filepath,"w");
    if(!f)return -1;
    double diff=compute_landing_distance_difference(points_no_wind,n1,points_wind,n2);
    //if(diff==0.0)return -1;
    

                fprintf(f,"machine=%s landing_distance_difference=%.2f\n",machine_name,diff);
                fprintf(f,"TRAJECTORY_NO_WIND\n");
                for(int i=0;i<n1;i++)
                {
                    fprintf(f,"t=%.2f x=%.2f y=%.2f\n",points_no_wind[i].t,points_no_wind[i].x,points_no_wind[i].y);
                }
                fprintf(f,"TRAJECTORY_WITH_WIND\n");
                for(int i=0;i<n2;i++)
                {
                    fprintf(f,"t=%.2f x=%.2f y=%.2f\n",points_wind[i].t,points_wind[i].x,points_wind[i].y);
                }


            
            fclose(f);
            return 0;





}
