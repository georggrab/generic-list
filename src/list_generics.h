#ifndef LDYNAMIC
typedef struct list list;
#endif

void set_compare_equal(int(*)(void*,void*)); 
void set_compare_less_than(int(*)(void*,void*));

extern int (*compare_equal)(void*, void*);
extern int (*compare_less_than)(void*, void*);

void l_purge(list*);
void l_destroy(list*);
void l_swap(list*, int index0, int index1);
int l_sorted(list*, int upto);

