/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:11:40 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 08:32:16 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

size_t	next_env(char *line, size_t *i)
{
	size_t	index;

	index = *i;
	while (line[index] && (ft_isalnum(line[index]) || line[index] == '_'))
		index++;
	return (index);
}

char	*get_env_name(t_shell **shell, char *line, size_t i)
{
	char	*env_name;
	size_t	index;

	index = i;
	index += 1;
	index = next_env(line, &index);
	env_name = ft_substr(line, i + 1, index);
	exit_free_if(!env_name, shell, "minishell: error: allocation failed");
	return (env_name);
}

char	*handle_env(t_shell **shell, char *line, size_t i)
{
	char		*env_name;
	char		*env_value;
	char		*new_line;

	env_name = get_env_name(shell, line, i);
	env_value = ft_envexp((*shell)->env, env_name);
	if (env_value)
	{
		new_line = ft_lineinsert(line, env_value, i, \
									i + ft_strlen(env_name) + 1);
		exit_free_if(!new_line, shell, "minishell:\terror:\tallocation failed");
		return (new_line);
	}
	else
	{
		ft_putstr_fd("minishell: error: env variable not found: ", 2);
		ft_putendl_fd(env_name, 2);
		return (NULL);
	}
}
