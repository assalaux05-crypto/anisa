#ifndef HANGAR_H
#define HANGAR_H

#include <stddef.h>

/*
** libhangar - opaque dynamic container library.
** See README.md for the exact contract of each function.
*/

struct HangarList;

typedef void (*HangarDestroyFn)(void *element);
typedef int (*HangarCompareFn)(const void *a, const void *b);

struct HangarList *hangar_create(size_t element_size, HangarDestroyFn destroy);
int hangar_push(struct HangarList *list, const void *element);
size_t hangar_size(const struct HangarList *list);
void *hangar_at(struct HangarList *list, size_t index);
const void *hangar_at_const(const struct HangarList *list, size_t index);
int hangar_sort(struct HangarList *list, HangarCompareFn compare);
void hangar_destroy(struct HangarList *list);

#endif /* HANGAR_H */
