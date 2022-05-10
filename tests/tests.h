#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "../mandatory/includes/minishell.h"
#include <check.h>



void CheckMemoryLeaks(int argc, char **argv);





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

