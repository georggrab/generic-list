#include <stdio.h>
#include <stdlib.h>

// Das file mit den generics, bspw. purge
#ifndef LINK_DYNAMIC
#include "src/list_generics.h"
#include "src/list_interface.h"
#else
#include "src/dynamics_list_interface.h"
#include "src/list_generics.c"
#endif

// Benutzer der generics library muss um die
// purge funktion nutzen zu können den equality
// check selbst implementieren, hier bspw. für ints.
//int l_equal(void* l1, void* l2){
//    return *(int*)l1 == *(int*)l2;
//}

int main(void){
    
// LINK_DYNAMIC wird vom Makefile gesetzt,
// falls nicht statisch gegen eine implementierung
// gelinkt, sondern die implementierung
// dynamisch eingeladen werden soll.
#ifdef LINK_DYNAMIC
#include <dirent.h>
#include <string.h>
#include <dlfcn.h>
#include "src/dynamics.c"
#endif
    
    printf("Yoa, paar Tests here:\n");
    list *list_t = l_new();
    int *ins = malloc(sizeof(ins));
    *ins = 999;

    int el_num_populate = 400;

    printf("populate_random_ints\n");
    populate_random_ints(list_t, el_num_populate);
    l_print_as_ints(list_t);

    printf("delete_at\n");
    l_delete_at(list_t, 5);
    l_print_as_ints(list_t);

    printf("insert\n");
    l_insert(list_t, ins, 5);
    l_print_as_ints(list_t);

    printf("purge\n");
    l_purge(list_t);
    l_print_as_ints(list_t);
    
    l_destroy(list_t);

}
