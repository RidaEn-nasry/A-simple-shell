/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:53:09 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 16:00:45 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*handle_delim(t_shell **shell, char *line, char *tmp)
{
	int	len;

	if (!(*shell)->delim)
	{
		(*shell)->delim = malloc(sizeof(char *) * 1);
		(*shell)->delim[0] = NULL;
		len = 0;
	}
	else
		len = ft_doublen((const char **)(*shell)->delim);
	(*shell)->delim = (char **)ft_doubrealloc((void **)(*shell)->delim, \
		ft_doublen((const char **)(*shell)->delim) + 1);
	exit_free_if(!(*shell)->delim, shell, "allocation failed");
	(*shell)->delim[len] = ft_strdup(tmp);
	exit_free_if(!(*shell)->delim[len], shell, "allocation failed");
	(*shell)->tokens = ft_strjoin((*shell)->tokens, HEREDOC);
	(*shell)->tokens = ft_strjoin((*shell)->tokens, " ");
	exit_free_if(!(*shell)->tokens, shell, "allocation failed");
	return (line);
}

bool	validate_infile(char *infile)
{
	if (access(infile, F_OK) == -1)
	{
		ft_putstr_fd("minishell:\terror: no such file or directory: ", 2);
		ft_putendl_fd(infile, 2);
		return (false);
	}
	if (access(infile, R_OK) == -1)
	{
		ft_putstr_fd("minishell:\terror: permission denied: ", 2);
		ft_putendl_fd(infile, 2);
		return (false);
	}
	return (true);
}

char	*handle_in(t_shell **shell, char *line, char *tmp)
{
	int			len;
	extern char	**envs;

	if (!(*shell)->files->in)
	{
		(*shell)->files->in = malloc(sizeof(char *) * 1);
		(*shell)->files->in[0] = NULL;
		len = 0;
	}
	else
		len = ft_doublen((const char **)(*shell)->files->in);
	(*shell)->files->in = (char **)ft_doubrealloc((void **)(*shell)->files->in, \
		ft_doublen((const char **)(*shell)->files->in) + 1);
	exit_free_if(!(*shell)->files->in, shell, \
		"minishell:\t:error:\tallocation failed");
	(*shell)->files->in[len] = tmp;
	exit_free_if(!(*shell)->files->in[len], shell, \
		"minishell:\t:error:\tallocation failed");
	if (!validate_infile((*shell)->files->in[len]))
		return (NULL);
	(*shell)->tokens = ft_strjoin((*shell)->tokens, IN);
	(*shell)->tokens = ft_strjoin((*shell)->tokens, " ");
	exit_free_if(!(*shell)->tokens, shell, \
		"minishell:\t:error:\tallocation failed");
	return (line);
}

char	*get_in_delim(t_shell **shell, char *line, size_t *index, int op_len)
{
	char	q;
	size_t	i;
	char	*tmp;

	i = *index + 1;
	q = ft_intternary(line[*index] == '"', '"', '\'');
	if (!ft_strchr(line + i, q))
		return (NULL);
	tmp = ft_substr(line, i, ft_strchr(line + i, q) - line);
	exit_free_if(!tmp, shell, "minishell:\t:error:\tallocation failed");
	if (ft_strchr(tmp, '$'))
	{
		tmp = handle_env(shell, tmp, ft_strchr(tmp, '$') - tmp);
		exit_free_if(!tmp, shell, "minishell:\t:error:\tallocation failed");
	}
	*index = ft_strchr(line + i, q) - line + 1;
	if (op_len == 1)
		if (!validate_infile(tmp))
			return (NULL);
	if (op_len == 1)
		return (handle_in(shell, line, tmp));
	else
		return (handle_delim(shell, line, tmp));
}

char	*ft_delim_if(t_shell *shell, t_var *var, char *tmp)
{
	if (var->line[var->index] == '$')
	{
		var->line = handle_env(&shell, var->line, var->index);
		if (!var->line)
			return (NULL);
	}
	if (var->line[var->index] == '\'' || var->line[var->index] == '"')
	{
		var->line = get_in_delim(&shell, var->line, &var->index, var->op_len);
		if (!var->line)
			return (NULL);
		var->i = var->index;
		return (var->line);
	}
	var->end = var->index;
	next(var->line, &var->end);
	tmp = ft_substr(var->line, var->index, var->end);
	if (var->op_len == 2)
		handle_delim(&shell, var->line, tmp);
	else
		if (!handle_in(&shell, var->line, tmp))
			return (NULL);
	var->i = var->end;
	return (var->line);
}
