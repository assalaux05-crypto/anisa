#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H
#include <stddef.h>

#define JSON_TEXT_MAX 128
#define JSON_MAX_STUDENTS 16

typedef struct {
    int id;
    char name[64];
    int active;
} JsonUser;

typedef struct {
    int id;
    char name[64];
    double grade;
} JsonStudent;

typedef struct {
    int id;
    char title[64];
    char teacher_name[64];
    char teacher_room[32];
    JsonStudent students[JSON_MAX_STUDENTS];
    size_t student_count;
} JsonCourse;

typedef struct {
    char theme[32];
    int font_size;
    int notifications;
} JsonSettings;

typedef struct {
    int id;
    char title[64];
    int done;
} JsonTask;

typedef struct {
    size_t objects;
    size_t arrays;
    size_t max_depth;
} JsonStats;

#endif
