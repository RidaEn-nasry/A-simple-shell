/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_out_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:30:52 by yelgharo          #+#    #+#             */
/*   Updated: 2022/06/06 14:31:31 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_sec_if(t_shell **shell, t_var *var)
{
	var->end = var->index;
	next(var->line, &var->end);
	(*shell)->files->out = (char **)ft_doubrealloc(\
		(void **)(*shell)->files->out, var->len + 1);
	exit_free_if(!(*shell)->files->out, shell, "allocation failed");
	(*shell)->files->out[var->len] = ft_substr(var->line, var->index, var->end);
	exit_free_if(!(*shell)->files->out[var->len], shell, "allocation failed");
	if (!validate_file(shell, var->len))
		return (NULL);
	(*shell)->tokens = (char *)ft_ternary(var->op_len == 1, \
		ft_strjoin((*shell)->tokens, OUT), \
		ft_strjoin((*shell)->tokens, APPEND));
	(*shell)->tokens = ft_strjoin((*shell)->tokens, " ");
	var->i = var->end;
	return (var->line);
}

char	*ft_first_if(t_shell **shell, t_var *var)
{
	if (var->line[var->index] == '$')
	{
		var->line = handle_env(shell, var->line, var->index);
		if (!var->line)
			return (NULL);
	}
	if (var->line[var->index] == '\'' || var->line[var->index] == '"')
	{
		var->line = get_file_quote(shell, var->line, &var->index, var->len);
		if (!var->line)
			return (NULL);
		var->i = var->index;
		(*shell)->tokens = (char *)ft_ternary(var->op_len == 1, \
			ft_strjoin((*shell)->tokens, OUT), \
			ft_strjoin((*shell)->tokens, APPEND));
		(*shell)->tokens = ft_strjoin((*shell)->tokens, " ");
		return (var->line);
	}
	var->line = ft_sec_if(shell, var);
	return (var->line);
}
