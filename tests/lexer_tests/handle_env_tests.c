/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 11:59:43 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/15 14:45:41 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"



START_TEST(handle_env_test1)
{
    size_t i;
    i = 5;
    char *line = ft_strdup("echo $HOME");
    // char **envs = environ;
    t_shell *shell = NULL;
    shell = init_data(shell);
    char *expected = "echo /Users/wa5ina";
    char *actual = handle_env(shell, line, i);
    ck_assert_ptr_nonnull(actual);
    ck_assert_str_eq(expected, actual);
} END_TEST;


START_TEST(handle_env_test2)
{
    char *line = ft_strdup("ls -la > $HOME/outfile");
    size_t i = ft_strchr(line, '$') - line;
    // printf("%zu\n", i);
    t_shell *shell = NULL;
    shell = init_data(shell);
    char *expected = "ls -la > /Users/wa5ina/outfile";
    char *actual = handle_env(shell, line, i);
    ck_assert_ptr_nonnull(actual);
    ck_assert_str_eq(expected, actual);
} END_TEST;

START_TEST(handle_env_test3)
{
    char *line = ft_strdup("grep -i $INVALID_ENV_VARIABLE");
    size_t i = ft_strchr(line, '$') - line;
    t_shell *shell = NULL;
    shell = init_data(shell);
    char *actual = handle_env(shell, line, i);
    ck_assert_ptr_null(actual);
} END_TEST;



START_TEST(handle_env_test4)
{
    char *line = ft_strdup("\t\t\v\f\r\r\r\r\t$USER\t\t\t\t");
    size_t i = ft_strchr(line, '$') - line;
    t_shell *shell = NULL;
    shell = init_data(shell);
    char *expected = "\t\t\v\f\r\r\r\r\twa5ina\t\t\t\t";
    char *actual = handle_env(shell, line, i);
    ck_assert_ptr_nonnull(actual);
    ck_assert_str_eq(expected, actual);
} END_TEST;



START_TEST(handle_env_test5)
{
    char *line = ft_strdup("\"'''''\"$LOGNAME\"''''\"");
    size_t i = ft_strchr(line, '$') - line;
    t_shell *shell = NULL;
    shell = init_data(shell);
    char *expected = "\"'''''\"wa5ina\"''''\"";
    char *actual = handle_env(shell, line, i);
    ck_assert_ptr_nonnull(actual);
    ck_assert_str_eq(expected, actual);
} END_TEST;


Suite   *handle_env_suite(void)
{
    Suite   *s;
    TCase   *tc_core;
    TCase  *tc_1;
    TCase *tc_2;
    TCase *tc_3;
    TCase *tc_4;
    
    s = suite_create("handle_env");
    tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, handle_env_test1);
    suite_add_tcase(s, tc_core);
    
    tc_1 = tcase_create("handle_env_test2");
    tcase_add_test(tc_1, handle_env_test2);
    suite_add_tcase(s, tc_1);
    
    tc_2 = tcase_create("handle_env_test3");
    tcase_add_test(tc_2, handle_env_test3);
    suite_add_tcase(s, tc_2);

    tc_3 = tcase_create("handle_env_test4");
    tcase_add_test(tc_3, handle_env_test4);
    suite_add_tcase(s, tc_3);
    
    tc_4 = tcase_create("handle_env_test5");
    tcase_add_test(tc_4, handle_env_test5);
    suite_add_tcase(s, tc_4);
    return (s);
}