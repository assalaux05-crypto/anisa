#include "exercise.h"
#include <stdio.h>
int main(void)
{
    char room[64];
    if (yaml_get("course.yaml", "room", room, sizeof(room)) == 0)
        printf("Room: %s\n", room);
    printf("Modules: %d\n", yaml_count_modules("course.yaml"));
    return 0;
}
