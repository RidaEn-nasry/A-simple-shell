/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:53:09 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/13 15:35:53 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void    handle_delim(t_shell *shell, char *line, size_t *start, size_t *end)
{
    int len;
    if (!shell->delim)
    {
        shell->delim = malloc(sizeof(char *) * 2);
        len = 0;
    }
    else 
        len = ft_doublen((const char **)shell->delim);
    shell->delim = (char **)ft_doubrealloc((void **)shell->delim, ft_doublen((const char **)shell->delim) + 2);
    exit_free_if(!shell->delim, shell, "allocation failed");
    shell->delim[len] = ft_substr(line, *start, *end);
    exit_free_if(!shell->delim[len], shell, "allocation failed");
    shell->delim[len + 1] = NULL;
    shell->tokens = ft_strjoin(shell->tokens, HEREDOC);
    exit_free_if(!shell->tokens, shell, "allocation failed");
}


bool    handle_in(t_shell *shell, char *line, size_t *start, size_t *end)
{
    int len;

    if (!shell->files->in)
    {
        shell->files->in = malloc(sizeof(char *) * 2);
        len = 0;
    }
    else
        len = ft_doublen((const char **)shell->files->in);
    shell->files->in = (char **)ft_doubrealloc((void **)shell->files->in, ft_doublen((const char **)shell->files->in) + 2);
    exit_free_if(!shell->files->in, shell, "allocation failed");
    shell->files->in[len] = ft_substr(line, *start, *end);
    exit_free_if(!shell->files->in[len], shell, "allocation failed");
    if (access(shell->files->in[len], F_OK) == -1)
    {
        free_if(1, shell, "file not found");
        return (false);
    }
    if (access(shell->files->in[len], R_OK) == -1)
    {
        free_if(1, shell, "permission denied");
        return (false);
    }
    shell->files->in[len + 1] = NULL;
    shell->tokens = ft_strjoin(shell->tokens, IN);
    exit_free_if(!shell->tokens, shell, "allocation failed");
    return (true);    
}

bool    delim_in(t_shell *shell, char *line, size_t *i)
{
    size_t index;
    size_t  end;
    index = *i;

    int op_len;


    op_len = ft_intternary(line[index] == '<' && line[index + 1] == '<', 2, 1);
    
   
    index += op_len;
   
    skip_space(line, &index);
    end = index;
    next_op(line, &end);
    if (op_len == 2)
        handle_delim(shell, line, &index, &end);
    else 
        if (!handle_in(shell, line, &index, &end))
            return (false);
    *i = end;
    return true;
}


