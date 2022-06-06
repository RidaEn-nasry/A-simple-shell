/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_handle_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:01:32 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 10:07:34 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	exe_handle_in(t_shell *shell)
{
	int		infile_fd;
	int		err;
	char	*infile;

	infile = ft_strdup(shell->files->in[0]);
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
	{
		ft_putstr_fd("minishell:\terror: error processing file: ", 2);
		ft_putendl_fd(infile, 2);
		return (false);
	}
	err = ft_filecpy(infile, shell->tmpfile, O_WRONLY | O_CREAT | O_APPEND);
	if (err == -1)
	{
		ft_putstr_fd("minishell:\terror: error processing file: ", 2);
		ft_putendl_fd(infile, 2);
		return (false);
	}
	ft_doubdel(shell->files->in, 0, 1);
	return (true);
}
