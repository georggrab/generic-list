#ifndef LINK_DYNAMIC
#include "list_interface.h"
#endif
#include <stdlib.h>
#include "list_generics.h"

int default_equal(void* v1, void* v2){
    return v1 == v2;
}

int default_less_than(void* v1, void* v2){
    return v1 < v2;
}

extern int (*compare_equal)(void*, void*) = &default_equal;
extern int (*compare_less_than)(void*, void*) = &default_less_than;

void set_compare_less_than(int (*func)(void*, void*)){
    compare_less_than = func;
}

void set_compare_equal(int (*func)(void*, void*)){
    compare_equal = func;
}

int l_sorted(list *lst, int upto){
    for (int i = 0; i<=upto; i++){
        if (!compare_less_than(l_retrieve(lst, i), l_retrieve(lst, i+1))){
            if (!compare_equal(l_retrieve(lst, i), l_retrieve(lst, i+1))){
                return 0;
            }
        }
    }
    return 1;
}

void l_swap(list *l, int el1, int el2){
    void *el1val = l_retrieve(l, el1);
    l_insert_at(l, l_retrieve(l, el2), el1);
    l_insert_at(l, el1val, el2);
}

void l_purge(list *l){
    int p,q;
    p = l_first_idx(l);
    while (p != l_end_idx(l)){
        q = l_next_idx(l, p);
        while (q != l_end_idx(l)){
            if(compare_equal(l_retrieve(l,p), l_retrieve(l,q))){
                l_delete_at(l, q);
            } else {
                q = l_next_idx(l, q);
            }
        }
        p = l_next_idx(l, p);
    }
}

void l_destroy(list *l){
    int p;
    p = l_end_idx(l);
    while(p != l_first_idx(l)){
        l_delete_at(l, p); 
        p = l_prev_idx(l, p);
    } 
    free(l);
}
