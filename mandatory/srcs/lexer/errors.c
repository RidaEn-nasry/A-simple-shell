/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:59:49 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/13 15:36:11 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void freeAST(t_AST *ast)
{
    if (ast->left)
        freeAST(ast->left);
    if (ast->right)
        freeAST(ast->right);
    free(ast->token);
    free(ast);
}
 
 
// should be reacreated.
void     free_if(int condition, t_shell * shell,  char *msg)
{
    t_cmd *tmp;
    int i;

    i = 0;
    if (condition)
    {
        tmp = shell->cmds;
        while (shell->cmds)
        {
        tmp = shell->cmds->next;
        tmp = shell->cmds;
        shell->cmds = shell->cmds->next;
        ft_sfree(tmp->cmd);
        if (tmp->args && tmp->args[0])
            while (tmp->args[i])
            {
                ft_sfree(tmp->args[i]);
                i++;
            } 
        ft_sfree(tmp->args);
        free(tmp);
    }
    ft_sfree(shell->tokens);
    if (shell->delim)
        while (shell->delim[i])
        {
            ft_sfree(shell->delim[i]);
            i++;
        }
    if (shell->files->in)
        while (shell->files->in[i])
        {
            ft_sfree(shell->files->in[i]);
            i++;
        }
    ft_sfree(shell->files->in);
    if (shell->files->out)
        while (shell->files->out[i])
        {
            ft_sfree(shell->files->out[i]);
            i++;
    }
    ft_sfree(shell->files);
    free(shell);
    if (msg)
        ft_putendl_fd(msg, 2);
    }
}

void    exit_free_if(int condition, t_shell * shell,  char *msg)
{  
    if (condition)
    {
        free_if(condition, shell, msg);
        exit(EXIT_FAILURE);
    }

}

