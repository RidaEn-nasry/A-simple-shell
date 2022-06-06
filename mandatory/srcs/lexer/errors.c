/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:59:49 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 10:41:45 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_if(int condition, t_shell **shell, char *msg)
{
	t_cmd	*tmp;
	int		i;

	i = -1;
	if (condition)
	{
		while ((*shell)->cmds)
		{
			tmp = (*shell)->cmds;
			ft_sfree(tmp->cmd);
			if (tmp->args && tmp->args[0])
			{
				while (tmp->args[++i])
					ft_sfree(tmp->args[i]);
			}
			ft_sfree(tmp->args);
			(*shell)->cmds = (*shell)->cmds->next;
			ft_sfree(tmp);
		}
		unlink((*shell)->tmpfile);
		if (msg)
			ft_putendl_fd(msg, 2);
	}
}

void	exit_free_if(int condition, t_shell **shell, char *msg)
{
	if (condition)
	{
		free_if(condition, shell, msg);
		exit(EXIT_FAILURE);
	}
}
