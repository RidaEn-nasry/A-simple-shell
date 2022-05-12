/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:27:45 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/12 14:45:24 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	next_cmd(char *s, size_t *index)
{
	size_t	i;

	i = *index;
	while ((s[i]) && !((s[i] == ' ') || (getState(s[i], s[i + 1]) > 2 \
		&& (getState(s[i], s[i + 1]) < 9))))
		i++;
	*index = i;
}

t_cmd	*new_node(t_data *data)
{
	t_cmd	*new;

	new = malloc(sizeof(*new));
	exit_free_if(!new, data, "allocation failed");
	new->cmd = NULL;
	new->next = NULL;
	new->args = NULL;
	return (new);
}

t_cmd	*add_node(t_data *data, char *name, char *args)
{
	t_cmd	*tmp;

	tmp = data->cmds;
	if (!tmp)
	{
		tmp = new_node(data);
		tmp->cmd = name;
		tmp->args = args;
		return (tmp);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node(data);
		tmp->next->cmd = name;
		tmp->next->args = args;
		tmp->next->next = NULL;
		return (data->cmds);
	}
}

char	*get_args(char *s, size_t *index)
{
	int		i;
	size_t	end;
	char	*tmp;

	skip_space(s, index);
	if (!s)
		return (NULL);
	end = *index;
	i = *index;
	if (s[i] && (ft_isalnum(s[i]) || s[i] == '-'))
	{
		next_cmd(s, &end);
		tmp = ft_substr(s, i, end);
		*index = end;
		return (tmp);
	}
	else
		return (NULL);
}

bool	handle_cmd(t_data *data, char *line, size_t *i)
{
	char	*tmp;
	size_t	index;
	size_t	end;
	char	*args;

	index = *i;
	end = index;
	next_cmd(line, &end);
	tmp = ft_substr(line, index, end);
	exit_free_if(!tmp, data, "allocation failed");
	tmp = cmd_exist(tmp);
	if (!tmp)
	{
		free_if(1, data, "command not found");
		return (false);
	}
	index = end;
	args = get_args(line, &index);
	data->cmds = add_node(data, tmp, args);
	data->tokens = ft_strjoin(data->tokens, CMD);
	exit_free_if(!data->tokens, data, "allocation failed");
	*i = index;
	return (true);
}
