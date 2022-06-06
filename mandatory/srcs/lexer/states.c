/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:47:21 by yelgharo          #+#    #+#             */
/*   Updated: 2022/06/06 14:38:33 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_state_3(t_shell **shell, t_var *var)
{
	(*shell)->tokens = ft_strjoin((*shell)->tokens, PIPE);
	(*shell)->tokens = ft_strjoin((*shell)->tokens, " ");
	exit_free_if(!(*shell)->tokens, shell, \
		"minishell:\terror:\tallocation failed");
	var->i += 1;
}

char	*state_3(t_shell **shell, t_var *var)
{
	if (get_state(var->line[var->i], var->line[var->i + 1]) == 8)
		ft_state_3(shell, var);
	else if (get_state(var->line[var->i], var->line[var->i + 1]) == 9)
	{
		var->line = handle_exe(shell, var);
		if (!var->line)
			return (NULL);
	}	
	else if (get_state(var->line[var->i], var->line[var->i + 1]) == 10)
	{
		(*shell)->tokens = ft_strjoin((*shell)->tokens, EXIT);
		(*shell)->tokens = ft_strjoin((*shell)->tokens, " ");
		exit_free_if(!(*shell)->tokens, shell, \
			"minishell:\terror:\tallocation failed");
		var->i += 2;
	}
	else if (get_state(var->line[var->i], var->line[var->i + 1]) == 11)
	{
		var->line = handle_env(shell, var->line, var->i);
		if (!var->line)
			return (NULL);
	}
	return (var->line);
}

char	*state_2(t_shell **shell, t_var *var)
{
	if (get_state(var->line[var->i], var->line[var->i + 1]) == 4)
	{
		var->line = append_out(shell, var);
		if (!var->line)
			return (NULL);
	}
	else if (get_state(var->line[var->i], var->line[var->i + 1]) == 5)
	{
		var->line = delim_in(shell, var);
		if (!var->line)
			return (NULL);
	}
	else if (get_state(var->line[var->i], var->line[var->i + 1]) == 6)
	{
		var->line = append_out(shell, var);
		if (!var->line)
			return (NULL);
	}
	return (var->line);
}

char	*ft_state_1(t_shell *shell, t_var *var)
{
	if (get_state(var->line[var->i], var->line[var->i + 1]) == 2)
	{
		var->line = handle_quote(&shell, var->line, var->i);
		if (!var->line)
			return (NULL);
	}
	else if (get_state(var->line[var->i], var->line[var->i + 1]) == 3)
	{
		var->line = delim_in(&shell, var);
		if (!var->line)
			return (NULL);
	}
	return (var->line);
}

char	*state_1(t_shell **shell, t_var *var)
{
	if (get_state(var->line[var->i], var->line[var->i + 1]) == 12)
	{
		ft_putstr_fd("minishell:\terror: invalid input\n", 2);
		return (NULL);
	}
	else if (get_state(var->line[var->i], var->line[var->i + 1]) == 0)
		skip_space(var->line, &var->i);
	else if (get_state(var->line[var->i], var->line[var->i + 1]) == 1)
	{
		var->line = handle_cmd(shell, var);
		if (!var->line)
			return (NULL);
	}
	else
	{
		var->line = ft_state_1(*shell, var);
		if (!var->line)
			return (NULL);
	}
	return (var->line);
}
