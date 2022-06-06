/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:31:44 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 08:37:11 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*handle_exe(t_shell **shell, t_var *var)
{
	char	*exe;
	char	**args;
	size_t	end;

	end = var->i;
	var->i += 2;
	next(var->line, &end);
	exe = ft_substr(var->line, var->i, end);
	args = malloc(sizeof(char *) * 2);
	args[0] = exe;
	args[1] = NULL;
	if (access(exe, F_OK) == 0)
	{
		(*shell)->cmds = add_node(shell, exe, args);
		var->i = end;
		(*shell)->tokens = ft_strjoin((*shell)->tokens, CMD);
		return (exe);
	}
	ft_putstr_fd("minishell: error: command not found: ", 2);
	ft_putendl_fd(exe, 2);
	var->i = end;
	return (NULL);
}
