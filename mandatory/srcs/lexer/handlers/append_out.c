/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:35:00 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 14:38:47 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	validate_file(t_shell **shell, size_t len)
{
	if ((access((*shell)->files->out[len], F_OK) == 0))
	{
		if (access((*shell)->files->out[len], R_OK) != 0)
		{
			ft_putstr_fd("minishell:\terror:\tpermission denied: ", 2);
			ft_putendl_fd((*shell)->files->out[len], 2);
			return (false);
		}
	}
	else
	{
		if (ft_strlen((*shell)->files->out[len]) == 0 \
			|| !ft_validfname((*shell)->files->out[len]))
		{
			ft_putstr_fd("minishell:\terror:\tinvalid file name: ", 2);
			ft_putendl_fd((*shell)->files->out[len], 2);
			return (false);
		}
	}
	return (true);
}

char	*get_file_quote(t_shell **shell, char *line, size_t *index, size_t len)
{
	size_t	i;
	char	*tmp;
	char	q;

	q = ft_intternary(line[*index] == '"', '"', '\'');
	i = *index + 1;
	if (!ft_strchr(&line[i], q))
	{
		ft_putstr_fd("minishell:\terror:\tunmatched quote: ", 2);
		return (NULL);
	}
	tmp = ft_substr(line, i, ft_strchr(&line[i], q) - line);
	if (ft_strchr(tmp, '$'))
		tmp = handle_env(shell, tmp, ft_strchr(tmp, '$') - tmp);
	if (!tmp)
		return (NULL);
	(*shell)->files->out = (char **)ft_doubrealloc(\
		(void **)(*shell)->files->out, len + 1);
	exit_free_if(!(*shell)->files->out, shell, \
		"minisell:\terror:\tallocation failed");
	(*shell)->files->out[len] = tmp;
	if (!validate_file(shell, len))
		return (NULL);
	*index = ft_strchr(&line[i], q) - line + 1;
	return (line);
}

static void	init(t_shell **shell, size_t *len)
{
	if (!(*shell)->files->out)
	{
		(*shell)->files->out = malloc(sizeof(char) * 1);
		(*shell)->files->out[0] = NULL;
		exit_free_if(!(*shell)->files->out, shell, "allocation failed");
		*len = 0;
	}
	else
		*len = ft_doublen((const char **)(*shell)->files->out);
}

char	*append_out(t_shell **shell, t_var *var)
{
	init(shell, &var->len);
	var->index = var->i;
	var->op_len = ft_intternary(get_state(var->line[var->index], \
		var->line[var->index + 1]) == 4, 2, 1);
	var->index += var->op_len;
	skip_space(var->line, &var->index);
	var->line = ft_first_if(shell, var);
	if (!var->line)
		return (NULL);
	return (var->line);
}
