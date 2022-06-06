/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:28:35 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 02:31:45 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exit(t_shell *shell)
{
	if (shell->cmds->args[1])
		return (1);
	else
	{
		free_if(1, &shell, NULL);
		exit(EXIT_SUCCESS);
	}
}
