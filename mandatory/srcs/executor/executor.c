/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:00:51 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 12:04:33 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	flush_tmpfile(char *tmpfile)
{
	int		fd;
	char	*rd;

	fd = open(tmpfile, O_RDWR);
	if (fd == -1)
		return (false);
	rd = get_next_line(fd);
	while (rd)
	{
		ft_putstr_fd(rd, STDOUT_FILENO);
		rd = get_next_line(fd);
	}
	close(fd);
	return (true);
}

static void	ft_if(t_shell *shell, char **tokens, size_t *i)
{
	if (!ft_strncmp(tokens[*i], IN, 4))
		exe_handle_in(shell);
	else if (!ft_strncmp(tokens[*i], CMD, 5))
	{
		if (tokens[*i + 1] && !ft_strncmp(tokens[*i + 1], PIPE, 3))
		{
			exe_handle_cmd(shell);
			exe_handle_cmd(shell);
			*i += 2;
		}
		else if (tokens[*i + 1] && !ft_strncmp(tokens[*i + 1], EXIT, 5))
		{
			shell->cmds->args = ft_doubadd(shell->cmds->args, \
				ft_itoa(shell->status));
			exe_handle_cmd(shell);
			*i += 1;
		}
		else
			exe_handle_cmd(shell);
	}
}

bool	executor(t_shell *shell)
{
	size_t	i;
	char	**tokens;

	i = 0;
	tokens = ft_split(shell->tokens, ' ');
	while (tokens[i])
	{
		ft_if(shell, tokens, &i);
		if (!ft_strncmp(tokens[i], OUT, 5))
			exe_handle_out(shell);
		else if (!ft_strncmp(tokens[i], APPEND, 4))
			exe_handle_app(shell);
		else if (!ft_strncmp(tokens[i], HEREDOC, 4))
			exe_handle_heredoc(shell);
		i++;
	}
	if (ft_strncmp(tokens[i - 1], OUT, 5) \
		&& ft_strncmp(tokens[i - 1], APPEND, 4))
		flush_tmpfile(shell->tmpfile);
	return (true);
}
