#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 12: add task\n");
    JsonTask task = {2, "Finish TP", 0};
    int ok = json_add_task(path, "with_task.json", &task);
    printf("Append: %d\n", ok);
    return 0;
}
