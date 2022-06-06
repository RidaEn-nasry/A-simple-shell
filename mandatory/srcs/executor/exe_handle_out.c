/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_handle_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:01:04 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 10:07:58 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	exe_handle_out(t_shell *shell)
{
	char	*outfile;
	int		err;

	outfile = ft_strdup(shell->files->out[0]);
	err = ft_filecpy(shell->tmpfile, outfile, O_WRONLY | O_TRUNC | O_CREAT);
	if (err == -1)
	{
		ft_putstr_fd("minishell:\terror: error processing file: ", 2);
		ft_putendl_fd(outfile, 2);
		ft_putchar_fd('\n', 2);
		return (false);
	}
	ft_doubdel(shell->files->out, 0, 1);
	return (true);
}
