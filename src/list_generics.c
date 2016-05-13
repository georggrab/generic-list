#ifndef LINK_DYNAMIC
#include "list_interface.h"
#endif
#include <stdlib.h>

void l_purge(list *l){
    int p,q;
    p = l_first_idx(l);
    while (p != l_end_idx(l)){
        q = l_next_idx(l, p);
        while (q != l_end_idx(l)){
            if(l_equal(l_retrieve(l,p), l_retrieve(l,q))){
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
