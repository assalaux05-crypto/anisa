
#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include "porco.h"
#include <stdio.h>

double total_declared_speed(const char *filepath)
{
    //if(filepath==NULL)return 
    FILE* f=fopen(filepath,"r");
    if(!f)return -1.0;
    char buff[258];
    double tot=0.0;
    while(fgets(buff,sizeof(buff),f)!=NULL)
    {
        if(buff[0]=='\n')
        {
            continue;
        }

        
        char* name=strtok(buff,";");

        if(!name)continue;


        char* vit=strtok(NULL,",");
        if(!vit)continue;
        double speed=atof(vit);
        double res=porco_knots_to_ms(speed);
        tot =tot+res;
    }
    fclose(f);
    return tot;

}

int write_machine_cards(const char *input_path, const char *output_path)
{
    FILE* f=fopen(input_path,"r");
    if(!f)return 1;
    FILE* output=fopen(output_path,"w");
    if(!output)
    {
        fclose(f);
        return 1;
    }
    char line[222];
    while(fgets(line,sizeof(line),f)!=NULL)
    {
        if(line[0]!="\n")
        {
            char* name=strtok(line,";");
            if(!name)
            {
                fclose(f);
                fclose(output);
                return 1;
            }
            char* vit=strtok(NULL,";");
            if(!vit)
            {
                fclose(f);
                fclose(output);
                return 1;
            }
            double speed=atof(vit);
            double res=porco_knots_to_ms(speed);
           // const char *porco_machine_class(double speed_ms);
           const char* class=porco_machine_class(speed);
           //NAME | XX.XX m/s | CLASS
            fprintf(output,"%s | %2f m/s | %s\n",name,res,class);

        }
        else
        {
            continue;
        }

    }
    fclose(f);
    fclose(output);
    return 0;
}
