/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:39:13 by yelgharo          #+#    #+#             */
/*   Updated: 2022/06/06 14:18:55 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	next_ope(char *s, size_t *index)
{
	size_t	i;

	i = 0;
	while ((s[i]) && (!((s[i] == ' ') || !(get_state(s[i], s[i + 1]) > 2 \
		&& (get_state(s[i], s[i + 1]) < 9))) || ft_isalnum(s[i])))
		i++;
	*index = i;
}

bool	is_special(char c)
{
	if (c == '\\' || c == '{' || c == '}' || c == '[' || c == ']' \
		|| c == '#' || c == '=' || c == '!' || c == ';' || c == ')' \
		|| c == '(' || c == '~' || c == '&')
		return (true);
	return (false);
}

bool	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (true);
	return (false);
}

int	get_state(char c, char c1)
{
	if (ft_isspace(c))
		return (0);
	else if (c == '\'' || c == '"')
		return (2);
	else if (c == '<' && c1 == '<')
		return (3);
	else if (c == '>' && c1 == '>')
		return (4);
	else if (c == '<')
		return (5);
	else if (c == '>')
		return (6);
	if (c == '.' && c1 == '/')
		return (9);
	else if (c == '|')
		return (8);
	else if (c == '&' && c1 == '&')
		return (9);
	else if (c == '$' && c1 == '?')
		return (10);
	else if (c == '$')
		return (11);
	if (!is_special(c))
		return (1);
	return (12);
}

void	next(char *s, size_t *index)
{
	size_t	i;

	i = *index;
	while ((s[i]) && !(ft_isspace(s[i]) || is_operator(s[i])))
		i++;
	*index = i;
}
