#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#define max_list 10000

typedef struct list {
    int max_used_idx;
    void *items[max_list];
    void *last;
} list;

// Add new Element at location
void l_insert(list *l, void *el, int idx){
    //assert(idx <= l->max_used_idx);
    for(int i = l->max_used_idx; i > idx; i--){
        l->items[i] = l->items[i-1]; 
    }
    l->items[idx] = el;
    l->max_used_idx++;
    l->last = l->items[l->max_used_idx];
}

// Change Element at location (beware shitty naming)
void l_insert_at(list *l, void *el, int idx){
    l->items[idx] = el;
    l->last = el;
    if (idx > l->max_used_idx) 
        l->max_used_idx = idx;
}

void l_delete_at(list *l, int idx){
    assert(idx <= l->max_used_idx);
    
    void *el = l->items[idx];
    for(int i = idx + 1; i <= l->max_used_idx; i++){
        l->items[i - 1] = l->items[i];
    }
    l->max_used_idx--;
    l->last = l->items[l->max_used_idx];
    free(el);
    
}

void l_delete(list *l, void* el){
    for(int i=0; i<= l->max_used_idx; i++){
        if(l->items[i] == el)
            return l_delete_at(l, i);
    }
}


// Print upto specific location
void l_print_as_ints_(list *l, int upto){
    for (int i = 0; i<=upto; i++){
        printf("list[%3d] = %d\n", i, *(int*)l->items[i]);
    }
    printf("len=%d, end_val=%d\n", l->max_used_idx, *(int*)l->last);
}

// Print upto max location saved in list struct
void l_print_as_ints(list *l){
    l_print_as_ints_(l, l->max_used_idx);
}
void* l_locate(list *l, void *el){
    for(int i = 0; i<=l->max_used_idx;i++){
        if(l->items[i] == el) return el;
    }
    return NULL;
}

list *l_new(void){
    list *l_ptr = malloc(sizeof(list));
    l_ptr->max_used_idx = -1;
    return l_ptr;
}

// Fill with ptr to random int upto location
void populate_random_ints(list *l, int howmuch){
    for (int i = 0; i<howmuch; i++){
        int *r_int = malloc(sizeof(r_int));
        *r_int = rand() % 101;
        l_insert_at(l, (void*)r_int, i);
    }
}
void* l_retrieve(list *l, int idx){
    assert(idx <= l->max_used_idx);
    return l->items[idx];
}
void* l_first(list *l){
    return l->items[0];
}
int l_first_idx(list *l){
    return 0;
}
void* l_end(list *l){
    return l->items[l->max_used_idx];
}
int l_end_idx(list *l){
    return l->max_used_idx;
}
void* l_next(list *l, int pos){
    assert((pos + 1) <= l->max_used_idx);
    return l->items[pos + 1];
}
int l_next_idx(list *l, int pos){
    assert((pos + 1) <= l->max_used_idx);
    return pos + 1;
}
void* l_prev(list *l, int pos){
    assert((pos - 1) >= 0);
    return l->items[pos - 1];
}
int l_prev_idx(list *l, int pos){
    assert((pos - 1) >= 0);
    return pos - 1;
}
