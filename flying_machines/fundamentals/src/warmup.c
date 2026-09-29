
#include <stddef.h>
#include "machine.h"
#include "porco.h"

double estimate_speed_ms(double knots)
{
   //double porco_knots_to_ms(double knots);

   double res=porco_knots_to_ms(knots);
   return res;
}

const char *classify_machine_speed(double speed_ms)
{
    //const char *porco_machine_class(double speed_ms);
    const char* res=porco_machine_class(speed_ms);
    return res;

  
}


int decode_machine_code(const char *code)
{
    //int porco_parse_code(const char *code);
    int res =porco_parse_code(code);
    return res;
}

