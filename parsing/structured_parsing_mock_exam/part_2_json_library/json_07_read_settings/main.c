#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 07: read settings\n");
    JsonSettings settings = {0};
    int ok = json_read_settings(path, &settings);
    printf("Success: %d, theme: %s, font: %d, notifications: %d\n", ok, settings.theme, settings.font_size, settings.notifications);
    return 0;
}
