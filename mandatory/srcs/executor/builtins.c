/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:05:37 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 03:29:37 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_builtin(char *cmd)
{
	if (ft_strrchr(cmd, '/'))
		cmd = ft_strrchr(cmd, '/') + 1;
	if (!ft_strncmp(cmd, "cd", 3))
		return (true);
	if (!ft_strncmp(cmd, "echo", 4))
		return (true);
	if (!ft_strncmp(cmd, "env", 3))
		return (true);
	if (!ft_strncmp(cmd, "exit", 4))
		return (true);
	if (!ft_strncmp(cmd, "export", 6))
		return (true);
	if (!ft_strncmp(cmd, "unset", 5))
		return (true);
	if (!ft_strncmp(cmd, "pwd", 3))
		return (true);
	return (false);
}

bool	handle_builtins(t_shell *shell)
{
	if (ft_strrchr(shell->cmds->cmd, '/'))
		shell->cmds->cmd = ft_strrchr(shell->cmds->cmd, '/') + 1;
	if (!ft_strncmp(shell->cmds->cmd, "cd", 2))
		if (!ft_cd(shell))
			return (true);
	if (!ft_strncmp(shell->cmds->cmd, "echo", 4))
		if (!ft_echo(shell))
			return (true);
	if (!ft_strncmp(shell->cmds->cmd, "env", 3))
		if (!ft_env(shell))
			return (true);
	if (!ft_strncmp(shell->cmds->cmd, "exit", 4))
		if (!ft_exit(shell))
			return (true);
	if (!ft_strncmp(shell->cmds->cmd, "export", 6))
		if (!ft_export(shell))
			return (true);
	if (!ft_strncmp(shell->cmds->cmd, "unset", 5))
		if (!ft_unset(shell))
			return (true);
	if (!ft_strncmp(shell->cmds->cmd, "pwd", 3))
		if (!ft_pwd(shell))
			return (true);
	return (false);
}
