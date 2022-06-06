/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:00:17 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 02:30:25 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_env(t_shell *shell)
{
	int	i;
	int	tmpfd_out;

	tmpfd_out = open(shell->tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmpfd_out == -1)
		return (false);
	i = 0;
	if (shell->cmds->args[1])
		return (1);
	while (shell->env[i])
	{
		ft_putstr_fd(shell->env[i], tmpfd_out);
		ft_putchar_fd('\n', tmpfd_out);
		i++;
	}
	shell->status = EXIT_SUCCESS;
	shell->cmds = shell->cmds->next;
	return (0);
}
