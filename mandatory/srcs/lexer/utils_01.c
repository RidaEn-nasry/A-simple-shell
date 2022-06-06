/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:55:28 by yelgharo          #+#    #+#             */
/*   Updated: 2022/06/06 11:56:48 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_space(char *s, size_t *index)
{
	size_t	i;

	i = *index;
	while (s[i] && s[i] == ' ')
		i++;
	*index = i;
}

void	next_space(char *s, size_t *index)
{
	size_t	i;

	i = *index;
	while (s[i] && s[i] != ' ')
		i++;
	*index = i;
}

size_t	ll_len(t_cmd *cmd)
{
	size_t	i;
	t_cmd	*head;

	head = cmd;
	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

void	init_shell(t_shell **shell)
{
	(*shell)->cmds = NULL;
	(*shell)->tokens = ft_strdup("");
	(*shell)->files = malloc(sizeof(t_files));
	(*shell)->files->out = NULL;
	(*shell)->files->in = NULL;
	(*shell)->delim = NULL;
	(*shell)->status = 0;
	exit_if(!(*shell)->tokens \
		|| !(*shell)->files, "minishell:\terror:\tallocation failed");
}
