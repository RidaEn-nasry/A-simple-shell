/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:19:42 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 02:36:53 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_unset(t_shell *shell)
{
	size_t	i;
	char	*name;

	i = 0;
	if (shell->cmds->args[1] && shell->cmds->args[2])
		return (1);
	name = shell->cmds->args[1];
	if (!ft_envexist(shell->env, name))
		return (1);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], name, ft_strlen(name)))
		{
			shell->env = ft_doubdel(shell->env, i, i + 1);
			shell->cmds = shell->cmds->next;
			shell->status = 0;
			return (0);
		}
		i++;
	}
	shell->cmds = shell->cmds->next;
	shell->status = 0;
	return (0);
}
