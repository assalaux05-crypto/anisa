#include "exercise.h"
#include <stdio.h>
int main(void)
{
    char title[64];
    if (xml_get_text("course.xml", "title", title, sizeof(title)) == 0)
        printf("Title: %s\n", title);
    printf("Students: %d\n", xml_count_students("course.xml"));
    return 0;
}
