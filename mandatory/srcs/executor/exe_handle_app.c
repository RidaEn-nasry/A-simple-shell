/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_handle_app.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:45:21 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 03:31:38 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	exe_handle_app(t_shell *shell)
{
	char	*append_file;
	int		err;

	append_file = ft_strdup(shell->files->out[0]);
	err = ft_filecpy(shell->tmpfile, append_file, \
		O_WRONLY | O_APPEND | O_CREAT);
	if (err == -1)
	{
		ft_putstr_fd("minishell:\terror: error processing file: ", 2);
		ft_putendl_fd(append_file, 2);
		ft_putchar_fd('\n', 2);
		return (false);
	}
	ft_doubdel(shell->files->out, 0, 1);
	return (true);
}
