//#include "machine.h"
//#include "porco.h"
#include <stdio.h>
//#include <parser.h>
#include <physics.h>
#include <math.h>
#include <stdlib.h>
#include "report.h"
int main(){


//rite_machine_cards("data/inventory.txt", "cards.txt");
//printf("%.2f\n", degrees_to_radians(35.0));


//printf("%.2f %.2f\n", calculate_vx(52.0, 0.6108652382),
                       //calculate_vy(52.0, 0.6108652382));

//printf("%.2f\n", calculate_max_height(52.0, 0.6108652382));

//printf("%.2f\n", calculate_range(52.0, 0.6108652382));
//printf("%.2f\n", calculate_time_of_flight(52.0, 0.6108652382));
//printf("%s\n", classify_altitude(19.34));
/*char *summary = generate_flight_summary(52.0, 0.6108652382);
printf ("hellllllllllllll\n");
printf("%s\n", summary);
free(summary);
    return 0;
}
*/
struct Machine machines[] = {
    { "Savoia S.21", 52.0, 0.6108652382 },
    { "Möwe",        45.5, 0.5235987756 },
};
write_flight_report("report.txt", machines, 2, 40.0);
printf("hello\n");

}