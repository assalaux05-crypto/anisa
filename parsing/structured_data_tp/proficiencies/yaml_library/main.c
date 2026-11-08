#include "exercise.h"
#include <stdio.h>
int main(void)
{
    printf("Tasks: %d\n", yaml_library_count_tasks("tasks.yaml"));
    printf("Done: %d\n", yaml_library_count_status("tasks.yaml", "done"));
    return 0;
}
