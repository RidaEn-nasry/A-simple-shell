/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:39:46 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 02:32:42 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_export(t_shell *shell)
{
	size_t	len;

	len = ft_doublen((const char **)shell->env);
	if (shell->cmds->args[1] && shell->cmds->args[2])
		return (1);
	if (!shell->cmds->args[1])
	{
		ft_env(shell);
		return (0);
	}
	shell->env = (char **)ft_doubrealloc((void **)shell->env, len + 1);
	shell->env[len] = ft_strdup(shell->cmds->args[1]);
	shell->cmds = shell->cmds->next;
	shell->status = 0;
	return (0);
}
