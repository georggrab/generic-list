#include <stdio.h>
#include "sorters.h"
#include "list_generics.h"


#ifdef SORTERS_STANDALONE
// Mah Testing shit for equality
int __compare_equal(void *l1, void *l2){
    return *(int*)l1 == *(int*)l2;
}

int __compare_less_than(void *l1, void *l2){
    return *(int*)l1 < *(int*)l2;
}
#endif

int partition(list *lst, int left, int right){
    int i = left;
    for(int j = left; j < right; j++){
        if(compare_less_than(
                    l_retrieve(lst, j),
                    l_retrieve(lst, right)
                    )){
            l_swap(lst, i, j);
            i++;
        } 
    }
    l_swap(lst, i, right);
    return i;
}

void qs(list *l, int left, int right){
    if (left < right){
        int part = partition(l, left, right);
        qs(l, left, part-1);
        qs(l, part+1, right);
    }
}

void quicksort_recursive(list *l, int len){
    qs(l,0,len-1);
}
void quicksort_iterative(list *l, int len){
    
}
void insertionsort(list *l, int len){
    int sortedidx = 0;
    int cpy;
    while (sortedidx != len - 1){
        cpy = sortedidx;
        int targetelm = sortedidx + 1;
        while (cpy >= 0){
            if (compare_less_than(
                            l_retrieve(l, targetelm),
                            l_retrieve(l, cpy)
                        )){
                l_swap(l, targetelm, cpy); 
                targetelm = cpy;
            }
            cpy--;
        }
        sortedidx++;
    }
}

void bubblesort(list *l, int len){
    int check_upto = len - 1;
    int check_idx  = 0;
    while (!l_sorted(l, check_upto)){
        if (compare_less_than(l_retrieve(l, check_idx+1), l_retrieve(l, check_idx))){
            l_swap(l, check_idx, check_idx + 1);
        }
        check_idx++;
        if (check_idx == len -1) {
            check_idx = 0;
            check_upto--;
        }
    }
}

#ifdef SORTERS_STANDALONE
int main(void){
    // TODO TEST MAIN
    set_compare_less_than(__compare_less_than);
    set_compare_equal(__compare_equal);

    list* l = l_new();
    populate_random_ints(l, 15);

    for(int i = 0; i<15; i++){
        printf("%d ", *(int*)l_retrieve(l, i));
    }
    printf("\n");

    //quicksort_recursive(l, 5000);
    bubblesort(l,15);

    for(int i = 0; i<15; i++){
        printf("%d ", *(int*)l_retrieve(l, i));
    }
    printf("\n");
}
#endif
