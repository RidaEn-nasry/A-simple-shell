
#include "tests.h"



t_lexing_suite_coll  *start_lexer(char *name)
{
    t_lexing_suite_coll   *coll;

    coll = malloc(sizeof(*coll));
    exitIF(!coll, "allocation failed");
    coll->name = name;
    coll->suite = handle_app_suite;
    coll->next = NULL;
    return (coll);
}

Suite *getSuite(char *name)
{
    if (strcmp(name, "append") == 0)
        return handle_app_suite();
    if (strcmp(name, "env") == 0)
        return handle_env_suite();

    else 
    {
        printf(" %s: suite Not found\n", name);
        exit(EXIT_FAILURE);
    }

}


int main(int argc, char **argv)
{
    (void)argc;
    Suite *suite;
    if (!strcmp(argv[1], "-u"))
    {
        exitIF(!argv[2], "Usage: ./check [options: -u || -s ] < suite || suite collections > \n");
        Suite *s = getSuite(argv[2]);
        SRunner *sr = srunner_create(s);
        srunner_run_all(sr, CK_NORMAL);
        int number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    else if (!strcmp(argv[1], "-s"))
    {
        exitIF(!argv[2], "Usage: ./check [options: -u || -s ] < suite || suite collections > \n");
        int number_failed = 0;
        t_lexing_suite_coll   *coll = start_lexer(argv[2]);
        while (coll)
        {
            suite = coll->suite();
            SRunner *sr = srunner_create(suite);
            srunner_run_all(sr, CK_NORMAL);
            number_failed = srunner_ntests_failed(sr);
            srunner_free(sr);
            coll = coll->next;
        }
        return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
        
    }
}
