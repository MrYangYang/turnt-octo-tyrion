#include "../src/history.h"
#include "dsp_test.h"
#include <check.h>
#include <glib.h>

static History *head;
static History *child1;
static History *child2;

static void setup(void)
{
    ck_assert_ptr_eq(head, NULL);
    ck_assert_ptr_eq(child1, NULL);
    ck_assert_ptr_eq(child2, NULL);

    head = history_new();
    child1 = history_new();
    child2 = history_new();

    ck_assert_ptr_ne(head, NULL);
    ck_assert_ptr_ne(head, NULL);
    ck_assert_ptr_ne(head, NULL);
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

START_TEST (test_history_new)
{
    ck_assert_ptr_ne(head, NULL);
    ck_assert_ptr_ne(child1, NULL);
    ck_assert_ptr_ne(child2, NULL);
}
END_TEST

START_TEST (test_history_new_with_data)
{
    History *hist = NULL;
    head = history_new_with_data(head,
            TRUE,
            100);
    hist = head->next;
    ck_assert_int_eq(hist->flag, TRUE);
    ck_assert_int_eq(hist->amount, 100);

    g_string_free(hist->date, TRUE);
    g_free(hist);
}
END_TEST

START_TEST (test_history_append_with_data)
{
    History *hist;
    head = history_append_with_data(head,
            TRUE,
            20,
            "time now");
    hist = head->next;
    ck_assert_ptr_ne(hist, NULL);
    ck_assert_str_eq(hist->date->str, "time now");
    ck_assert_int_eq(hist->amount, 20);
    ck_assert_int_eq(hist->flag, TRUE);

    g_string_free(hist->date, TRUE);
    g_free(hist);
}
END_TEST

START_TEST (test_history_append_child)
{
    head = history_append_child(head, child1);
    head = history_append_child(head, child2);

    ck_assert_ptr_eq(head->next, child1);
    ck_assert_ptr_eq(head->next->next, child2);
}
END_TEST

START_TEST (test_history_get_child_at)
{
    History *temp = NULL;
    head->next = child1;
    child1->next = child2;
    
    temp = history_get_child_at(head, 0);
    ck_assert_ptr_eq(temp, head);
    temp = history_get_child_at(head, 1);
    ck_assert_ptr_eq(temp, child1);
    temp = history_get_child_at(head, 2);
    ck_assert_ptr_eq(temp, child2);

}
END_TEST

START_TEST (test_history_remove)
{
    head->next = child1;
    child1->next = child2;

    head = history_remove(head, 0);
    ck_assert_ptr_eq(head, child1);
    head = history_remove(head, 1);
    ck_assert_ptr_eq(head, child1);
    head = NULL;
    child2 = NULL;
}
END_TEST

START_TEST (test_history_remove_all)
{
    head->next = child1;
    child1->next = child2;

    head = history_remove_all(head);
    ck_assert_ptr_eq(head, NULL);
}
END_TEST

Suite *history_suite(void)
{
    Suite *s = suite_create("History");
    TCase *tc = tcase_create("core");
    tcase_add_checked_fixture(tc, setup, teardown);

    tcase_add_test(tc, test_history_new);
    tcase_add_test(tc, test_history_new_with_data);
    tcase_add_test(tc, test_history_append_with_data);
    tcase_add_test(tc, test_history_append_child);
    tcase_add_test(tc, test_history_get_child_at);
    tcase_add_test(tc, test_history_remove);
    tcase_add_test(tc, test_history_remove_all);

    suite_add_tcase(s, tc);
    return s;
}



