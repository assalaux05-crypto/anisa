#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int on_string(void *ctx, const unsigned char *value, size_t len)
{
    (void)value; (void)len;
    ((JsonStats *)ctx)->strings++;
    return 1;
}
static int on_integer(void *ctx, long long value)
{
    (void)value;
    ((JsonStats *)ctx)->integers++;
    return 1;
}
static int on_array(void *ctx)
{
    ((JsonStats *)ctx)->arrays++;
    return 1;
}
static int on_object(void *ctx)
{
    ((JsonStats *)ctx)->objects++;
    return 1;
}
static const yajl_callbacks callbacks = {
    .yajl_string = on_string,
    .yajl_integer = on_integer,
    .yajl_start_array = on_array,
    .yajl_start_map = on_object
};
int json_count_events(const char *path, JsonStats *out)
{
    (void)path; (void)out;
    /* TODO: read file and use yajl_alloc(&callbacks, NULL, out). */
    return -1;
}
