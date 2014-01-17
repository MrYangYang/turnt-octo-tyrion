#include <stdio.h>
#include <glib.h>
#include <check.h>

#include "dsp_test.h"


int main(int argc, char **argv)
{
    int num_failed = 0;
    Suite *suite = dispensary_suite();
    SRunner *sr = srunner_create(suite);
    suite = medicine_suite();
    srunner_add_suite(sr, suite);
    suite = history_suite();
    srunner_add_suite(sr, suite);
    srunner_run_all (sr, CK_VERBOSE);
    num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (num_failed == 0) ? 0 : 1;
}


