/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_handle_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:42:41 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 09:58:38 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <minishell.h>
#include "../../includes/minishell.h"

static bool	ft_if(t_shell *shell, int tmpfd_in, int tmpfd_out, pid_t pid)
{
	if (pid == 0)
	{
		if (dup2(tmpfd_in, STDIN_FILENO) == -1)
			return (false);
		if (dup2(tmpfd_out, STDOUT_FILENO) == -1)
			return (false);
		if (execve(shell->cmds->cmd, shell->cmds->args, shell->env) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(shell->cmds->cmd, 2);
			ft_putchar_fd('\n', 2);
		}
	}
	else
	{
		wait(&shell->status);
		close(tmpfd_in);
		close(tmpfd_out);
		shell->cmds = shell->cmds->next;
	}
	return (true);
}

bool	exe_handle_cmd(t_shell *shell)
{
	pid_t	pid;
	int		tmpfd_out;
	int		tmpfd_in;
	char	*tmpfile;

	if (is_builtin(shell->cmds->cmd))
		if (handle_builtins(shell))
			return (true);
	tmpfile = ft_strdup("/tmp/minishell_tmpfile");
	ft_filecpy(shell->tmpfile, tmpfile, O_RDWR | O_CREAT | O_TRUNC);
	tmpfd_in = open(tmpfile, O_RDONLY);
	tmpfd_out = open(shell->tmpfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tmpfd_out == -1 || tmpfd_in == -1)
		return (false);
	pid = fork();
	if (!ft_if(shell, tmpfd_in, tmpfd_out, pid))
		return (false);
	return (true);
}
