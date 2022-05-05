
// start from here 
// #include "tests.h"

#include "tests.h"








// int minishell_utils_test_init()
// {
//     int number_failed;
//     Suite *s;
//     SRunner *sr;

//     s = minishell_suite();
//     sr = srunner_create(s);

//     srunner_run_all(sr, CK_NORMAL);
//     number_failed = srunner_ntests_failed(sr);
//     srunner_free(sr);
//     return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
// }




// libft functions tests 


// each seperate test ;
int libft_test_init()
{
    int number_failed;
    Suite *s;
    SRunner *sr;
    s = libft_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int main(void)
{
    // minishell_utils_test_init();
    int test_res = libft_test_init();
    return (test_res);
}
