/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:15:07 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 02:33:31 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_shell *shell)
{
	char	*pwd;
	int		tmpfd_out;

	if (shell->cmds->args[1])
		return (1);
	tmpfd_out = open(shell->tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmpfd_out == -1)
		return (false);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	ft_putstr_fd(pwd, tmpfd_out);
	ft_putchar_fd('\n', tmpfd_out);
	free(pwd);
	close(tmpfd_out);
	shell->cmds = shell->cmds->next;
	shell->status = EXIT_SUCCESS;
	return (0);
}
