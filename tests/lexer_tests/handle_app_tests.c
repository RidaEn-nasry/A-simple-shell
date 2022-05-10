/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_app_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:09:07 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/10 16:40:50 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"


// basic test 
START_TEST (test_handle_app_1)
{
    int i = 0;
    t_data *data = NULL;
    data =  init_data(data);
    char *input = ">> outfile";
    handle_app(data, input, &i);
    ck_assert_str_eq(data->files->out[0], "outfile");
    ck_assert_str_eq(data->tokens, APPEND);
    ft_safeFree(input);
    input = ft_strdup(">>outfile");
    handle_app(data, input, &i);
    ck_assert_ptr_nonnull(data->files->out);
    ck_assert_str_eq(data->files->out[0], "outfile");
    ck_assert_str_eq(data->tokens, APPEND);
    ft_safeFree(input);
}

START_TEST (test_handle_app_2)
{
    t_data *data = NULL;
    data = init_data(data);
    char *input = ft_strdup(">> outfile >> outfile >> outfile >> outfile >> outfile >> outfile");
    int i = 0;
    handle_app(data, input, &i);
    ck_assert_ptr_nonnull(data->files->out);
    for (int i = 0 ; i < 6; i++)
    {
        ck_assert_ptr_nonnull(data->files->out[i]);
        ck_assert_str_eq(data->files->out[i], "outfile");
    }
    ck_assert_ptr_null(data->files->out[6]);
    size_t len = ft_doublen((const char **)data->files->out);
    
    ck_assert_int_eq(len, 6);
    char *expected_token = "<ap> <ap> <ap> <ap> <ap> <ap>";
    ck_assert_str_eq(data->tokens, expected_token);
    ft_safeFree(input);
    ft_safeFree(expected_token);
    
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