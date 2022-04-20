/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:25:49 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/20 17:49:13 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// diplay prompt
void prompt(void)
{
    char *user;
    char *host;
    char *cwd;

    user = getenv("USER");
    host = getenv("HOSTNAME");
    cwd = getcwd(NULL, 0);
    if (user == NULL || host == NULL || cwd == NULL)
        return ;
    ft_putstr("\033[1;32m");
    ft_putstr(user);
    ft_putstr("\033[0m@");
    ft_putstr("\033[1;32m");
    ft_putstr(host);
    ft_putstr("\033[0m:");
    ft_putstr("\033[1;32m");
    ft_putstr(cwd);
    ft_putstr("\033[0m$ ");
}