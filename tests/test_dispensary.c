#include "../src/dispensary.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <glib.h>

void test_dispensary_new(void)
{
    Dispensary *dispensary = dispensary_new();
    CU_ASSERT(dispensary != NULL);
    CU_ASSERT(dispensary->name == NULL);
    CU_ASSERT(dispensary->place == NULL);
    CU_ASSERT(dispensary->tel == NULL);
    CU_ASSERT(dispensary->next == NULL);
    CU_ASSERT(dispensary->mdc_head == NULL);
    g_free(dispensary);
}

void test_dispensary_new_with_data(void)
{
    Dispensary *dispensary = dispensary_new();
    Dispensary *next = NULL;
    dispensary = dispensary_new_with_data(dispensary, "name", "place",
            "tel");
    next = dispensary->next;
    CU_ASSERT_NOT_EQUAL(next, NULL);
    CU_ASSERT_STRING_EQUAL(next->name->str, "name");
    CU_ASSERT_STRING_EQUAL(next->place->str, "place");
    CU_ASSERT_STRING_EQUAL(next->tel->str, "tel");

    g_string_free(next->name, TRUE);
    g_string_free(next->place, TRUE);
    g_string_free(next->tel, TRUE);

    g_free(next);
    g_free(dispensary);
}

void test_dispensary_append_child(void)
{
    Dispensary *dispensary = dispensary_new();
    Dispensary *child = dispensary_new();
    CU_ASSERT_NOT_EQUAL(dispensary, NULL);
    CU_ASSERT_NOT_EQUAL(child, NULL);
    dispensary = dispensary_append_child(dispensary, child);
    CU_ASSERT_EQUAL(dispensary->next, child);
}

void test_dispensary_get_child_at(void)
{
    Dispensary *dispensary = dispensary_new();
    CU_ASSERT(dispensary);
    Dispensary *child_1 = dispensary_new();
    Dispensary *child_2 = dispensary_new();
    CU_ASSERT(child_1);
    CU_ASSERT(child_2);
    dispensary = dispensary_append_child(dispensary, child_1);
    dispensary = dispensary_append_child(dispensary, child_2);

    CU_ASSERT_EQUAL(dispensary_get_child_at(dispensary, 0), dispensary);
    CU_ASSERT_EQUAL(dispensary_get_child_at(dispensary, 1), child_1);
    CU_ASSERT_EQUAL(dispensary_get_child_at(dispensary, 2), child_2);

    g_free(dispensary);
    g_free(child_1);
    g_free(child_2);
}

void test_dispensary_replace_with(void)
{
    Dispensary *head = dispensary_new();
    Dispensary *child = dispensary_new();
    Dispensary *child_repl = dispensary_new();
    CU_ASSERT(head);
    CU_ASSERT(child);
    CU_ASSERT(child_repl);

    head = dispensary_append_child(head, child);
    CU_ASSERT_EQUAL(head->next, child);

    head = dispensary_replace_with(head, 1, child_repl);
    CU_ASSERT_EQUAL(head->next, child_repl);

    g_free(head);
    g_free(child);
    g_free(child_repl);
}

void test_dispensary_remove(void)
{
    Dispensary *dispensary = dispensary_new();
    Dispensary *child = dispensary_new();
    CU_ASSERT_FALSE_FATAL(dispensary);
    CU_ASSERT_FALSE_FATAL(child);

    dispensary = dispensary_append_child(dispensary, child);
    CU_ASSERT_EQUAL(dispensary->next, child);

    dispensary = dispensary_remove(dispensary, 1);
    CU_ASSERT_EQUAL(dispensary->next, NULL);

    g_free(dispensary);
    g_free(child);
}

void test_dispensary_remove_all(void)
{
    Dispensary *dispensary = dispensary_new();
    Dispensary *child_1 = dispensary_new();
    Dispensary *child_2 = dispensary_new();
    CU_ASSERT_FALSE_FATAL(dispensary);
    CU_ASSERT_FALSE_FATAL(child_1);
    CU_ASSERT_FALSE_FATAL(child_2);

    dispensary = dispensary_append_child(dispensary, child_1);
    dispensary = dispensary_append_child(dispensary, child_2);

    CU_ASSERT_EQUAL(dispensary->next, child_1);
    CU_ASSERT_EQUAL(dispensary->next->next, child_2);

    // because remove_all has free mem, so we don't need
    // to free mem manually.
    dispensary = dispensary_remove_all(dispensary);
    CU_ASSERT_EQUAL(dispensary, NULL);
}

// caution. Id is given by modules, do not modify it in your code.
void test_dispensary_get_child_by_id()
{
    Dispensary *dispensary = dispensary_new();
    Dispensary *child = dispensary_new();
    CU_ASSERT_FALSE_FATAL(dispensary);
    CU_ASSERT_FALSE_FATAL(child);

    child->id = 2;
    CU_ASSERT_EQUAL(child->id, 2);
    dispensary = dispensary_append_child(dispensary, child);
    CU_ASSERT_EQUAL(dispensary->next, child);
    CU_ASSERT_EQUAL(dispensary_get_child_by_id(dispensary, 2), child);
    CU_ASSERT_EQUAL(child->id, 2);

    g_free(child);
    g_free(dispensary);
}

void test_dispensary_remove_by_id(void)
{
    Dispensary *dispensary = dispensary_new();
    Dispensary *child_1 = dispensary_new();
    Dispensary *child_2 = dispensary_new();
    CU_ASSERT_FALSE_FATAL(dispensary);
    CU_ASSERT_FALSE_FATAL(child_1);
    CU_ASSERT_FALSE_FATAL(child_2);

    child_1->id = 1;
    child_2->id = 2;
    dispensary = dispensary_append_child(dispensary, child_1);
    dispensary = dispensary_append_child(dispensary, child_2);
    CU_ASSERT_EQUAL(dispensary->next, child_1);
    CU_ASSERT_EQUAL(child_1->next, child_2);
    
    dispensary = dispensary_remove_by_id(dispensary, 1);
    CU_ASSERT_EQUAL(dispensary->next, child_2);

    // remove function allready free memory of child_1
    g_free(dispensary);
    g_free(child_2);
}

void test_dispensary_append_with_data()
{
    Dispensary *child;
    Dispensary *dispensary = dispensary_new();
    CU_ASSERT_FALSE_FATAL(dispensary);
    
    int child_id = 2;
    dispensary = dispensary_append_with_data(dispensary, 
            "child_name",
            "child_place",
            "child_tel",
            child_id);
    child = dispensary->next;
    CU_ASSERT_EQUAL(child->id, child_id);
    CU_ASSERT_STRING_EQUAL(child->name->str, "child_name");
    CU_ASSERT_STRING_EQUAL(child->place->str, "child_place");
    CU_ASSERT_STRING_EQUAL(child->tel->str, "child_tel");

    g_free(dispensary);
    g_free(child);
}

