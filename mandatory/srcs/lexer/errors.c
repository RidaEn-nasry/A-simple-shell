/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:59:49 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/09 10:06:54 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    exitFreeIF(int condition, t_data * data,  char *msg)
{
    t_cmd *tmp;
    int i;

    i = 0;
    if (condition)
    {
        tmp = data->cmds;
        while (data->cmds)
        {
            tmp = data->cmds->next;
        tmp = data->cmds;
        data->cmds = data->cmds->next;
        ft_safeFree(tmp->cmd);
        while (tmp->args[i])
        {
            ft_safeFree(tmp->args[i]);
            i++;
        }
        ft_safeFree(tmp->args);
        free(tmp);
    }
    ft_safeFree(data->tokens);
    ft_safeFree(data->in);
    ft_safeFree(data->out);
    free(data);
    perror(msg);
    exit(EXIT_FAILURE);
    }
}

