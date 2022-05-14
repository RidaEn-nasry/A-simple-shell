/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:35:00 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/13 15:35:39 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	@description: 
		- handles the operators: > and >>
	@note:
		- because the operator > can be handled on the same way as >>,
			except for it's length, we use the same handler for both.
		- append_in.c is a silly acronym for append and in redirection opperators.
*/

#include <minishell.h>

void	next_op(char *s, size_t *index)
{
	size_t	i;
	int		current_state;

	i = *index;
	current_state = getState(s[i], s[i + 1]);
	while (s[i] && (getState(s[i], s[i + 1]) == 12 \
		|| getState(s[i], s[i + 1]) == current_state))
		i++;
	*index = i;
}

bool	validate_file(char *filename, t_shell *shell)
{
	if ((access(filename, F_OK) == 0))
	{
		if (access(filename, R_OK) != 0)
		{
			free_if(1, shell, "permission denied");
			return (false);
		}
	}
	else
	{
		if (ft_strlen(filename) == 0 || !ft_validfname(filename))
		{
	
			free_if(1, shell, "invalid file name");
			return (false);
		}
	}
	return (true);
}

static void	init(t_shell *shell, size_t *len)
{
	if (!shell->files->out)
	{
		shell->files->out = malloc(sizeof(char) * 1);
		exit_free_if(!shell->files->out, shell, "allocation failed");
		*len = 0;
	}
	else
		*len = ft_doublen((const char **)shell->files->out);
}

bool	append_out(t_shell *shell, char *line, size_t *i)
{
	size_t	index;
	size_t	end;
	size_t	len;
	int		op_len;

	init(shell, &len);
	index = *i;
	op_len = ft_intternary(getState(line[index], line[index + 1]) == 4, 2, 1);
	index += op_len;
	skip_space(line, &index);
	end = index;
	next_op(line, &end);
	shell->files->out = (char **)ft_doubrealloc(\
		(void **)shell->files->out, len + 1);
	exit_free_if(!shell->files->out, shell, "allocation failed");
	shell->files->out[len] = ft_substr(line, index, end);
	exit_free_if(!shell->files->out[len], shell, "allocation failed");
	if (!validate_file(shell->files->out[len], shell))
		return (false);
	shell->tokens = (char *)ft_ternary(op_len == 1, \
		ft_strjoin(shell->tokens, OUT), ft_strjoin(shell->tokens, APPEND));
	*i = end;
	return (true);
}
