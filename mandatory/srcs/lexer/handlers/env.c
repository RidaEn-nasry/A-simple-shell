/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:11:40 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/13 15:34:32 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
    @description:
       - this handler is used to handle env variables and $?.

*/

#include <minishell.h>

void    handle_env(t_shell *shell, char *line, size_t *i)
{
    size_t index;
    size_t end;
    size_t  len;

    if (!shell->env)
    {
        shell->env = malloc(sizeof(char *) * 2);
        len = 0;
    }
    else
        len = ft_doublen((const char **)shell->env);
    index = *i;
    if (line[index] == '$' && line[index + 1] == '?')
    {
       shell->tokens = ft_strjoin(shell->tokens, EXIT);
       *i = index + 2;
       return;
    }
    index += 1;
    end = index;
    next_op(line, &end);
    shell->env = (char **)ft_doubrealloc((void **)shell->env, ft_doublen((const char **)shell->env) + 2);
    shell->env[len] = ft_substr(line, index, end);
    exit_free_if(!shell->env[len], shell, "allocation failed");
    shell->env[len + 1] = NULL;
    shell->tokens = ft_strjoin(shell->tokens, VAR);
    exit_free_if(!shell->tokens, shell, "allocation failed");
    *i = end;
}