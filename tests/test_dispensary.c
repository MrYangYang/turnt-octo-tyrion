#include "../src/dispensary.h"
#include <glib.h>
#include <check.h>
#include "dsp_test.h"

static Dispensary *head;
static Dispensary *child_1;
static Dispensary *child_2;

static void setup(void)
{
    ck_assert_ptr_eq(head, NULL);
    ck_assert_ptr_eq(child_1, NULL);
    ck_assert_ptr_eq(child_2, NULL);

    head = dispensary_new();
    child_1 = dispensary_new();
    child_2 = dispensary_new();

    ck_assert_ptr_ne(head, NULL);
    ck_assert_ptr_ne(child_1, NULL);
    ck_assert_ptr_ne(child_2, NULL);
}

static void teardown(void)
{
    if (head) {
        g_free(head);
        head = NULL;
    }

    if (child_1) {
        g_free(child_1);
        child_1 = NULL;
    }

    if (child_2) {
        g_free(child_2);
        child_2 = NULL;
    }
}

START_TEST (test_dispensary_new)
{
    ck_assert_ptr_ne(head, NULL);
    ck_assert_ptr_eq(head->name, NULL);
    ck_assert_ptr_eq(head->place, NULL);
    ck_assert_ptr_eq(head->tel, NULL);
    ck_assert_ptr_eq(head->next, NULL);
    ck_assert_ptr_eq(head->mdc_head, NULL);
}
END_TEST

START_TEST (test_dispensary_new_with_data)
{
    Dispensary *dispensary = dispensary_new();
    Dispensary *next = NULL;
    head = dispensary_new_with_data(head, "name", "place",
            "tel");
    next = head->next;
    ck_assert_ptr_ne(next, NULL);
    ck_assert_str_eq(next->name->str, "name");
    ck_assert_str_eq(next->place->str, "place");
    ck_assert_str_eq(next->tel->str, "tel");

    g_string_free(next->name, TRUE);
    g_string_free(next->place, TRUE);
    g_string_free(next->tel, TRUE);

    g_free(dispensary);
}
END_TEST

START_TEST (test_dispensary_append_child)
{
    head = dispensary_append_child(head, child_1);
    head = dispensary_append_child(head, child_2);
    ck_assert_ptr_eq(head->next, child_1);
    ck_assert_ptr_eq(head->next->next, child_2);
}
END_TEST

START_TEST (test_dispensary_get_child_at)
{
    head = dispensary_append_child(head, child_1);
    head = dispensary_append_child(head, child_2);

    ck_assert_ptr_eq(dispensary_get_child_at(head, 0), head);
    ck_assert_ptr_eq(dispensary_get_child_at(head, 1), child_1);
    ck_assert_ptr_eq(dispensary_get_child_at(head, 2), child_2);
}
END_TEST

START_TEST (test_dispensary_replace_with)
{
    head = dispensary_append_child(head, child_1);
    ck_assert_ptr_eq(head->next, child_1);

    head = dispensary_replace_with(head, 1, child_2);
    ck_assert_ptr_eq(head->next, child_2);
}
END_TEST

START_TEST (test_dispensary_remove)
{
    head = dispensary_append_child(head, child_1);
    ck_assert_ptr_eq(head->next, child_1);
    head = dispensary_remove(head, 1);
    ck_assert_ptr_ne(head, NULL);
    ck_assert_ptr_eq(head->next, NULL);
}
END_TEST


START_TEST (test_dispensary_remove_all)
{
    head = dispensary_append_child(head, child_1);
    head = dispensary_append_child(head, child_2);

    ck_assert_ptr_ne(head, NULL);
    ck_assert_ptr_ne(head->next, NULL);
    ck_assert_ptr_eq(head->next, child_1);
    ck_assert_ptr_ne(head->next->next, NULL);
    ck_assert_ptr_eq(head->next->next, child_2);

    head = dispensary_remove_all(head);
    ck_assert_ptr_eq(head, NULL);
}
END_TEST

START_TEST (test_dispensary_get_child_by_id)
{
    child_1->id = 1;
    child_2->id = 2;
    ck_assert_int_eq(child_1->id, 1);
    ck_assert_int_eq(child_2->id, 2);
    head = dispensary_append_child(head, child_1);
    head = dispensary_append_child(head, child_2);
    ck_assert_ptr_eq(head->next, child_1);
    ck_assert_ptr_eq(dispensary_get_child_by_id(head, 1), child_1);
    ck_assert_ptr_eq(dispensary_get_child_by_id(head, 2), child_2);
    ck_assert_int_eq(child_1->id, 1);
    ck_assert_int_eq(child_2->id, 2);
}
END_TEST

START_TEST (test_dispensary_remove_by_id)
{
    child_1->id = 1;
    child_2->id = 2;
    head = dispensary_append_child(head, child_1);
    head = dispensary_append_child(head, child_2);
    ck_assert_ptr_eq(head->next, child_1);
    ck_assert_ptr_eq(child_1->next, child_2);
    
    head = dispensary_remove_by_id(head, 1);
    ck_assert_ptr_eq(head->next, child_2);
}
END_TEST

START_TEST (test_dispensary_append_with_data)
{
    Dispensary *child;
    int child_id = 2;
    head = dispensary_append_with_data(head, 
            "child_name",
            "child_place",
            "child_tel",
            child_id);
    child = head->next;
    ck_assert_ptr_ne(child, NULL);
    ck_assert_int_eq(child->id, child_id);
    ck_assert_str_eq(child->name->str, "child_name");
    ck_assert_str_eq(child->place->str, "child_place");
    ck_assert_str_eq(child->tel->str, "child_tel");
    
    g_string_free(child->name, TRUE);
    g_string_free(child->place, TRUE);
    g_string_free(child->tel, TRUE);
    g_free(child);
}
END_TEST

Suite *dispensary_suite(void)
{
    Suite *s = suite_create("Dispensary");
    TCase *tc = tcase_create("methods");
    tcase_add_checked_fixture(tc, setup, teardown);
    
    /* add tests */
    tcase_add_test(tc, test_dispensary_new);
    tcase_add_test(tc, test_dispensary_new_with_data);
    tcase_add_test(tc, test_dispensary_append_child);
    tcase_add_test(tc, test_dispensary_get_child_at);
    tcase_add_test(tc, test_dispensary_replace_with);
    tcase_add_test(tc, test_dispensary_remove);
    tcase_add_test(tc, test_dispensary_remove_all);
    tcase_add_test(tc, test_dispensary_get_child_by_id);
    tcase_add_test(tc, test_dispensary_remove_by_id);
    tcase_add_test(tc, test_dispensary_append_with_data);

    /* add test case to suite */
    suite_add_tcase(s, tc);
    return s;
}


