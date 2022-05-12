/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:11:40 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/12 15:12:00 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void    handle_env(t_data *data, char *line, size_t *i)
{
    size_t index;
    size_t len = ft_doublen((const char **)data->files->out);
    index = *i;
    if (line[index] == '$' && line[index + 1] == '?')
    {
       data->tokens = ft_strjoin(data->tokens, EXIT);
       *i = index + 2;
       return;
    }
    next_space(line, &index);
    skip_space(line, &index);
    size_t end = index;
    next_space(line, &end);
    data->env = (char **)ft_doubrealloc((void **)data->env, len + 1);
    exit_free_if(!data->env, data, "allocation failed");
    data->env[len] = ft_substr(line, index + 1, end);
    exit_free_if(!data->env[len], data, "allocation failed");
    data->tokens = ft_strjoin(data->tokens, VAR);
    *i = end;
}
