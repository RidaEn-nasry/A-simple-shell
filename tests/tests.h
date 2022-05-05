#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "utils/get_next_line/get_next_line.h"
#include "../mandatory/utils/libft/libft.h"
#include "../mandatory/includes/minishell.h"
#include <check.h>



void CheckMemoryLeaks(int argc, char **argv);





// test suites :
Suite *libft_suite(void);
Suite *minishell_suite(void);
