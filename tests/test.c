#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/list_interface.h"

static void list_create(void **state){
    list *l = l_new();
    assert_int_equal(l_end_idx(l), -1);
    assert_int_equal(l_first_idx(l), 0);
}

void list_fill(void **state){
    list *l = *state;
    assert_int_equal(l_end_idx(l), -1);

    int i = 0;
    for(i; i <= 1000; i++){
        int *k = malloc(sizeof(k));
        *k = i;
        l_insert(l, k, i);
        assert_int_equal(l_end_idx(l), i);
    }
    assert_int_equal(l_first_idx(l), 0);
}

static void list_check_content(void **state){
    list *l = *state;
    for(int i = 0; i<= 1000; i++){
        int a = *(int*)l_retrieve(l, i);
        assert_int_equal(a, i);
    }
}

static void list_delete_last(void **state){
    list *l = *state;
    for(int i = 1000; i>=0; i--){
        assert_int_equal(l_end_idx(l), i);
        l_delete_at(l, i);
    }
}

static void list_delete_first(void **state){
    list *l = *state;
    list_fill(&l);
    list_check_content(&l);
    for(int i = 1000; i>=0; i--){
        assert_int_equal(l_end_idx(l), i);
        l_delete_at(l, 0);
    }
}

static int list_setup(void **state){
    list *l = l_new();
    *state = l;
    return 0;
}

static int list_teardown(void **state){
    free(*state);
    return 0;
}

int main(void){
    const struct CMUnitTest create_destroy[] = {
        cmocka_unit_test(list_fill)
      , cmocka_unit_test(list_check_content)      
      , cmocka_unit_test(list_delete_last)      
      , cmocka_unit_test(list_delete_first)      
    };
    return cmocka_run_group_tests(create_destroy, list_setup, list_teardown);
}
