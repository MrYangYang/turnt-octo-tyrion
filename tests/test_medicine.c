#include "dsp_test.h"
#include "../src/medicine.h"
#include <check.h>
#include <glib.h>


static Medicine *head;
static Medicine *child1;
static Medicine *child2;

static void setup(void)
{
    ck_assert_ptr_eq(head, NULL);
    ck_assert_ptr_eq(child1, NULL);
    ck_assert_ptr_eq(child2, NULL);

    head = medicine_new();
    child1 = medicine_new();
    child2 = medicine_new();

    ck_assert_ptr_ne(head, NULL);
    ck_assert_ptr_ne(child1, NULL);
    ck_assert_ptr_ne(child2, NULL);
}

static void teardown(void)
{
    if (head) {
        g_free(head);
        head = NULL;
    }

    if (child1) {
        g_free(child1);
        child1 = NULL;
    }

    if (child2) {
        g_free(child2);
        child2 = NULL;
    }
}

START_TEST (test_medicine_new)
{
    ck_assert_ptr_ne(head, NULL);
    ck_assert_ptr_eq(head->name, NULL);
    ck_assert_int_eq(head->quantity, 0);
    ck_assert_ptr_eq(head->unit, NULL);
    ck_assert_ptr_eq(head->specification, NULL);
    ck_assert_ptr_eq(head->allow_key, NULL);
    ck_assert_ptr_eq(head->identify_key, NULL);
    ck_assert_ptr_eq(head->producer, NULL);
}
END_TEST

START_TEST (test_medicine_append_with_data)
{
    Medicine *tmp = NULL;
    int quantity = 2;
    medicine_append_with_data(head, 
            "name", 
            "unit", 
            quantity,
            "specification",
            "allow_key",
            "identify_key",
            "producer");
    tmp = head->next;
    ck_assert_ptr_ne(head->next, NULL);
    ck_assert_str_eq(tmp->name->str, "name");
    ck_assert_str_eq(tmp->unit->str, "unit");
    ck_assert_str_eq(tmp->specification->str, "specification");
    ck_assert_str_eq(tmp->allow_key->str, "allow_key");
    ck_assert_str_eq(tmp->identify_key->str, "identify_key");
    ck_assert_str_eq(tmp->producer->str, "producer");

    ck_assert_ptr_eq(tmp->hist_head, NULL);
    ck_assert_ptr_eq(tmp->next, NULL);

    g_string_free(tmp->name, TRUE);
    g_string_free(tmp->unit, TRUE);
    g_string_free(tmp->specification, TRUE);
    g_string_free(tmp->allow_key, TRUE);
    g_string_free(tmp->identify_key, TRUE);
    g_string_free(tmp->producer, TRUE);

    g_free(tmp);
}
END_TEST

START_TEST (test_medicine_append_child)
{
    head = medicine_append_child(head, child1);
    head = medicine_append_child(head, child2);

    ck_assert_ptr_ne(head->next, NULL);
    ck_assert_ptr_eq(head->next, child1);
    ck_assert_ptr_ne(head->next->next, NULL);
    ck_assert_ptr_eq(head->next->next, child2);
}
END_TEST

START_TEST (test_medicine_get_child_at)
{
    head->next = child1;
    child1->next = child2;
    ck_assert_ptr_eq(medicine_get_child_at(head, 0), head);
    ck_assert_ptr_eq(medicine_get_child_at(head, 1), child1);
    ck_assert_ptr_eq(medicine_get_child_at(head, 2), child2);
}
END_TEST

START_TEST (test_medicine_remove)
{
    head->next = child1;
    child1->next = child2;
    head = medicine_remove(head, 0);
    ck_assert_ptr_eq(head, child1);
    ck_assert_ptr_eq(head->next, child2);
    head = medicine_remove(head, 1);
    ck_assert_ptr_eq(head, child1);
    ck_assert_ptr_eq(head->next, NULL);
    
    head = NULL;
    child2 = NULL;
}
END_TEST

START_TEST (test_medicine_remove_all)
{
    head->next = child1;
    child1->next = child2;
    head = medicine_remove_all(head);
    ck_assert_ptr_eq(head, NULL);
    child1 = NULL;
    child2 = NULL;
}
END_TEST

START_TEST (test_medicine_remove_by_identify_key)
{
    head->next = child1;
    child1->next = child2;
    child1->identify_key = g_string_new("identify_key");
    head = medicine_remove_by_identify_key(head, "identify_key");
    ck_assert_ptr_eq(head->next, child2);
    ck_assert_ptr_eq(child2->next, NULL);
}
END_TEST

START_TEST (test_medicine_get_child_by_identify_key)
{
    Medicine *temp;
    head->next = child1;
    child1->next = child2;
    head->identify_key = g_string_new("identify_key0");
    child1->identify_key = g_string_new("identify_key1");
    child2->identify_key = g_string_new("identify_key2");

    temp = medicine_get_child_by_identify_key(head, "identify_key0");
    ck_assert_ptr_eq(temp, head);
    temp = medicine_get_child_by_identify_key(head, "identify_key1");
    ck_assert_ptr_eq(temp, child1);
    temp = medicine_get_child_by_identify_key(head, "identify_key2");
    ck_assert_ptr_eq(temp, child2);

    g_string_free(head->identify_key, TRUE);
    g_string_free(child1->identify_key, TRUE);
    g_string_free(child2->identify_key, TRUE);
}
END_TEST

Suite *medicine_suite(void)
{
    Suite *s = suite_create("Medicine");
    TCase *tc = tcase_create("core");
    tcase_add_checked_fixture(tc, setup, teardown);

    /* add tests */
    tcase_add_test(tc, test_medicine_new);
    tcase_add_test(tc, test_medicine_append_with_data);
    tcase_add_test(tc, test_medicine_append_child);
    tcase_add_test(tc, test_medicine_get_child_at);
    tcase_add_test(tc, test_medicine_remove);
    tcase_add_test(tc, test_medicine_remove_all);
    tcase_add_test(tc, test_medicine_remove_by_identify_key);
    tcase_add_test(tc, test_medicine_get_child_by_identify_key);

    suite_add_tcase(s, tc);
    return s;
}

