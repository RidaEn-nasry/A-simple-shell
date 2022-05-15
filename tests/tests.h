#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "../mandatory/includes/minishell.h"
#include <check.h>


// #define ck_assert_stdout_eq(expected) ck_assert_str_eq(expected, stdout_get_string())


void CheckMemoryLeaks(int argc, char **argv);


/*
    test with file permission.
    change file permission and store file name in env variable and pass it to env.

*/


// lexing tests
typedef struct s_lexing_suite_coll
{
    char *name;
    Suite *(*suite)();
    struct s_lexing_suite_coll *next;
} t_lexing_suite_coll;
    char *name;


// lexeing handlers test suites
Suite *handle_app_suite(void);
Suite   *handle_env_suite(void);

