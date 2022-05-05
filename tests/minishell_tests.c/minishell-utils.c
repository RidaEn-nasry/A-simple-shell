


#include "../tests.h"

START_TEST(test_exit_if_1)
{
    exitIf(1, "test");
}
END_TEST;

Suite *minishell_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("minishell");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_exit_if_1);
    suite_add_tcase(s, tc_core);

    return (s);
}