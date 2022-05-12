/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:59:49 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/12 16:23:37 by ren-nasr         ###   ########.fr       */
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
void     free_if(int condition, t_data * data,  char *msg)
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
    ft_sfree(data->tokens);
    if (data->files->out)
        while (data->files->out[i])
        {
            ft_sfree(data->files->out[i]);
            i++;
    }
    ft_sfree(data->files);
    free(data);
    if (msg)
        ft_putendl_fd(msg, 2);
    }
}

void    exit_free_if(int condition, t_data * data,  char *msg)
{  
    if (condition)
    {
        free_if(condition, data, msg);
        exit(EXIT_FAILURE);
    }

}

