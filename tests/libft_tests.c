
#include "tests.h"


// START_TEST(ft_realloc_test) {
    
//     char *str = malloc(sizeof(char) * 6);
//     char *new = ft_realloc(str, 10);
//     ck_assert_ptr_ne(new, NULL);
//     ck_assert_str_eq(new, "hello");
//     free(new);
// } END_TEST

START_TEST(ft_substr_test) {
    char *str = "Hello world";
    char *substr = ft_substr(str, 0, 5);
    ck_assert_ptr_ne(substr, NULL);
    ck_assert_str_eq(substr, "Hello");
    free(substr);
} END_TEST

// START_TEST(ft_strtok_test)
// {
//     char *path = getenv("PATH");
//     path = ft_strtok(path, ":");
//     while (path)
//     {
//         printf("%s\n", path);
//         path = ft_strtok(NULL, ":");
//     }

// }
// END_TEST



Suite *libft_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("libft");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, ft_substr_test);
    // tcase_add_test(tc_core, ft_strtok_test);
    suite_add_tcase(s, tc_core);
    return (s);
}

