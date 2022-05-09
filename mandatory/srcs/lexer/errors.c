/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:59:49 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/09 15:20:38 by ren-nasr         ###   ########.fr       */
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
        if (tmp->args)
            while (tmp->args[i])
            {
                ft_safeFree(tmp->args[i]);
                i++;
            }
        ft_safeFree(tmp->args);
        free(tmp);
    }
    ft_safeFree(data->tokens);
    while (data->files->out[i])
    {
        ft_safeFree(data->files->out[i]);
        i++;
    }
    
    free(data);
    printf("%s\n", msg);
    perror(msg);
    exit(EXIT_FAILURE);
    }
}

