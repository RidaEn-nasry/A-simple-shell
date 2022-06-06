/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim_in_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:00:30 by yelgharo          #+#    #+#             */
/*   Updated: 2022/06/06 16:02:57 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*delim_in(t_shell **shell, t_var *var)
{
	char	*tmp;

	tmp = NULL;
	var->index = var->i;
	var->op_len = ft_intternary(var->line[var->index] == '<' && \
		var->line[var->index + 1] == '<', 2, 1);
	var->index += var->op_len;
	skip_space(var->line, &var->index);
	var->line = ft_delim_if(*shell, var, tmp);
	if (!var->line)
		return (NULL);
	return (var->line);
}
