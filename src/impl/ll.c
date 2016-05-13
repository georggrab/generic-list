#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

typedef struct node {
    void *item;
    struct node *next;
} node;

typedef struct list {
    node *node;
    node *end;
    int len;
} list;

node *_goto(list *l, int idx){
    int count = 0;
    node *iter = l->node;
    while (count != idx){
        iter = iter->next;
        count++;
    }
    return iter;
}

node *_nnew(void *el){
    node *n = malloc(sizeof(n));
    n->item = el;
    return n;
}

// nicht im list interface, hässlicher spezialfall
void l_prepend(list *l, void *el){
    node *n = _nnew(el);
    n->next = l->node;
    l->node = n;
    if (n->next == NULL) l->end = n;
    (l->len)++;
}

// el als neues element mit neuem index idx
void l_insert(list *l, void *el, int idx){
    if (idx == 0)
        return l_prepend(l, el);

    int count = 0;
    node *iter = l->node;
    while (count != idx - 1){
        iter = iter->next;
        count++;
    }

    node *n = _nnew(el);
    n->next = iter->next;
    iter->next = n;
    l->len++; 
    if (n->next == NULL) l->end = n;
}

// shitty benannt: el als neues item des list entries mit index idx
void l_insert_at(list *l, void *el, int idx){
    node *element = _goto(l, idx);
    element->item = el;
}

void l_delete(list *l, void* el){
    node **n = &l->node;

    // traversieren via short-circuit evaluation
    while (((*n)->item != el) && *(n = &((*n)->next)) != NULL);

    node *nnext = (*n)->next;
    free(*n);
    *n = nnext;
}

void l_find_end(list *l){
    node *n = l->node;
    while (n->next != NULL)
        n = n->next;

    l->end = n;
}

void l_delete_at(list *l, int idx){
    node **n = &l->node;

    // Einelementige Liste
    if (l->node->next == NULL){
        free(l->node->item);
        free(l->node);
        l->len--;
        return;
    }

    int cnt = 0;
    while ((cnt++ != idx) && (*(n = &(*n)->next) != NULL));

    node *nnext = (*n)->next;
    if ((*n)->item)
        free((**n).item);
    free(*n);
    *n = nnext;

    l->len--;
    if (nnext == NULL) return l_find_end(l);
    if (nnext->next == NULL) l->end = nnext;
}

// Print upto max location saved in list struct
void l_print_as_ints(list *l){
    node *iter = l->node;
    int c = 0;
    do {
        printf("list[%d] = %d\n", c, *(int*)iter->item);
        c++;
    } while((iter = iter->next) != NULL);
    printf("len=%d; end_val=%d\n", l->len, *(int*)l->end->item);
}

void* l_locate(list *l, void *el){
    node *n = l->node;
    do {
        if (n->item == el) return el;     
    } while ((n = n->next) != NULL);
    return NULL;
}

list *l_new(void){
    list *l;
    l = malloc(sizeof(list));
    l->len = 0;
    return l;
}

// Fill with ptr to random int upto location
void populate_random_ints(list *l, int howmuch){
    for (int i = 0; i < howmuch ; i++){
       int *number = malloc(sizeof(number));
       *number = i;
       l_insert(l, number, 0);
    } 
}
void* l_retrieve(list *l, int idx){
    assert(idx < l->len && idx >= 0);

    node *n = _goto(l, idx);
    return n->item;
}
void* l_first(list *l){
    return l->node;
}
int l_first_idx(list *l){
    return 0;
}
void* l_end(list *l){
    return l->end;
}
int l_end_idx(list *l){
    return l->len - 1;
}
void* l_next(list *l, int pos){
assert((pos + 1) <= l->len);
    return _goto(l, pos + 1);
}
int l_next_idx(list *l, int pos){
    assert((pos + 1) <= l->len);
    return pos + 1;
}
void* l_prev(list *l, int pos){
    assert((pos - 1) >= 0);
    return _goto(l, pos - 1);
}
int l_prev_idx(list *l, int pos){
    assert((pos - 1) >= 0);
    return pos - 1;
}

/*int main(){
    list* l = l_new();
    int x = 42;
    int y = 24;
    l_insert(l, (void*)&y, 0);
    populate_random_ints(l, 10);
    l_insert(l, (void*)&x, 0);
    l_print_as_ints(l);
    printf("\n");
    l_delete_at(l, 3);
    l_print_as_ints(l);
}*/

