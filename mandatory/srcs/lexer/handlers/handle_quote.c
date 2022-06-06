/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:42:16 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 08:30:44 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	next_q(char *s, size_t *index, char q)
{
	size_t	i;

	i = *index;
	while (s[i] && (s[i] != q))
		i++;
	*index = i;
}

char	*handle_dquote(t_shell **shell, char *line, size_t start, size_t end)
{
	char	*content;
	char	*new_line;
	char	*expan;

	content = ft_substr(line, start + 1, end);
	exit_free_if(!content, shell, "minishell:\terror:\tallocation failed");
	if (ft_strchr(content, '$'))
	{
		expan = handle_env(shell, content, ft_strchr(content, '$') - content);
		if (!expan)
			return (NULL);
		new_line = ft_lineinsert(line, expan, start, end + 1);
		exit_free_if(!new_line, shell, "minishell:\terror:\tallocation failed");
		return (new_line);
	}
	if (ft_strlen(content) == 0)
	{
		new_line = ft_lindetach(line, start, end + 1);
		exit_free_if(!new_line, shell, "minishell:\terror:\tallocation failed");
		return (new_line);
	}
	new_line = ft_lineinsert(line, content, start, end + 1);
	exit_free_if(!new_line, shell, "minishell:\terror:\tallocation failed");
	return (new_line);
}

char	*handle_squote(t_shell **shell, char *line, size_t start, size_t end)
{
	char	*new_line;
	char	*content;

	new_line = NULL;
	content = ft_substr(line, start + 1, end);
	exit_free_if(!content, shell, "minishell:\terror:\tallocation failed");
	new_line = ft_lineinsert(line, content, start, end + 1);
	exit_free_if(!new_line, shell, "minishell:\terror:\tallocation failed");
	return (new_line);
}

char	*handle_quote(t_shell **shell, char *line, size_t i)
{
	char	quote;
	size_t	index;
	size_t	end;

	quote = line[i];
	index = i;
	end = index + 1;
	next_q(line, &end, quote);
	if (end == ft_strlen(line) && line[end] != quote)
	{
		ft_putstr_fd("minishell:\terror:\tmissing closing quote\n", 2);
		return (NULL);
	}
	if (quote == '\'')
		return (handle_squote(shell, line, index, end));
	else
		return (handle_dquote(shell, line, index, end));
}
