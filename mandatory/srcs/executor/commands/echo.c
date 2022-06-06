/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:48:13 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 02:28:23 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_if(t_shell *shell, int tmp_out)
{
	int	i;

	i = 2;
	while (shell->cmds->args[i])
	{
		ft_putstr_fd(shell->cmds->args[i], tmp_out);
		ft_putchar_fd(' ', tmp_out);
		i++;
	}
	close(tmp_out);
	shell->cmds = shell->cmds->next;
	shell->status = EXIT_SUCCESS;
	return (i);
}

int	ft_echo(t_shell *shell)
{
	int	i;
	int	tmp_out;

	i = 2;
	tmp_out = open(shell->tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_out == -1)
		return (false);
	if (shell->cmds->args[1] && !ft_strncmp(shell->cmds->args[1], "-n", 2))
	{
		i = ft_if(shell, tmp_out);
		return (EXIT_SUCCESS);
	}
	i -= 1;
	while (shell->cmds->args[i])
	{
		ft_putstr_fd(shell->cmds->args[i], tmp_out);
		ft_putchar_fd(' ', tmp_out);
		i++;
	}
	ft_putchar_fd('\n', tmp_out);
	close(tmp_out);
	shell->cmds = shell->cmds->next;
	shell->status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
