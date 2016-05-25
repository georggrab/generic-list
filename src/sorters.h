#include "list_interface.h"

//#ifndef SORTERS_STANDALONE
//#endif

void quicksort(list *l);
void insertionsort(list *l, int len);
void mergesort(list *l);
void bubblesort(list *l, int len);

void set_compare_func(int(*func)(void*,void*));
list *randomlist(int length);
double profilesort(void(*sortalg)(list *l));
