/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_app_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:09:07 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/15 12:15:44 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"


// basic test 
START_TEST (test_handle_app_1)
{
    size_t i = 0;
    t_shell *shell = NULL;
    shell =  init_data(shell);
    char *input = ">> outfile";
    append_out(shell, input, &i);
    ck_assert_str_eq(shell->files->out[0], "outfile");
    ck_assert_str_eq(shell->tokens, APPEND);
    ft_sfree(input);
    input = ft_strdup(">>outfile");
    append_out(shell, input, &i);
    ck_assert_ptr_nonnull(shell->files->out);
    ck_assert_str_eq(shell->files->out[0], "outfile");
    ck_assert_str_eq(shell->tokens, APPEND);
    ft_sfree(input);
}

START_TEST (test_handle_app_2)
{
    t_shell *shell = NULL;
    shell = init_data(shell);
    char *input = ft_strdup(">> outfile >> outfile >> outfile >> outfile >> outfile >> outfile");
    size_t i = 0;
    append_out(shell, input, &i);
    ck_assert_ptr_nonnull(shell->files->out);
    for (int i = 0 ; i < 6; i++)
    {
        ck_assert_ptr_nonnull(shell->files->out[i]);
        ck_assert_str_eq(shell->files->out[i], "outfile");
    }
    ck_assert_ptr_null(shell->files->out[6]);
    size_t len = ft_doublen((const char **)shell->files->out);
    
    ck_assert_int_eq(len, 6);
    char *expected_token = "<ap> <ap> <ap> <ap> <ap> <ap>";
    ck_assert_str_eq(shell->tokens, expected_token);
    ft_sfree(input);
    ft_sfree(expected_token);
    
}
Suite *handle_app_suite(void)
{
    Suite *s;

    s = suite_create("handle_app");
    TCase *tc_1;
    TCase *tc_2;

    tc_1 = tcase_create("test_handle_app_1");
    tcase_add_test(tc_1, test_handle_app_1);
    suite_add_tcase(s, tc_1);
    
    tc_2 = tcase_create("test_handle_app_2");
    tcase_add_test(tc_2, test_handle_app_2);
    suite_add_tcase(s, tc_2);

    return s;
}