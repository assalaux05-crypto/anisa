#ifndef EXERCISE_H
#define EXERCISE_H
/* Return number of course objects; -1 on parse/type error. */
int json_library_count_courses(const char *filename);
/* Return the total number of students in all courses; -1 on error. */
int json_library_total_students(const char *filename);
/* Change the room of the course with the requested id and save the JSON. */
int json_library_update_room(const char *filename, int course_id, const char *room);
/* Export names of students with grade >= minimum to a JSON array file. */
int json_library_export_top(const char *input, const char *output, int minimum);
#endif
