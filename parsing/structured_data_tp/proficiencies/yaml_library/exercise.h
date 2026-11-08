#ifndef EXERCISE_H
#define EXERCISE_H
/* Count items in the top-level "tasks" sequence; -1 on invalid YAML. */
int yaml_library_count_tasks(const char *filename);
/* Count tasks whose status scalar equals status. */
int yaml_library_count_status(const char *filename, const char *status);
/* Change the status of the task with matching id and write a YAML document. */
int yaml_library_update_status(const char *filename, int id, const char *status);
#endif
