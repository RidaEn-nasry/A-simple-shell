/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_handle_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 11:45:00 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 10:37:24 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	exe_handle_heredoc(t_shell *shell)
{
	char	*herdoc;
	char	*input;
	int		herdoc_tmp;

	herdoc = ft_strdup(shell->delim[0]);
	herdoc_tmp = open(shell->tmpfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (herdoc_tmp == -1)
		return (false);
	while (1)
	{
		input = readline("herdoc> ");
		if (ft_strncmp(input, herdoc, ft_strlen(input)) == 0)
			break ;
		ft_putendl_fd(input, herdoc_tmp);
	}
	ft_doubdel(shell->delim, 0, 1);
	close(herdoc_tmp);
	return (true);
}
