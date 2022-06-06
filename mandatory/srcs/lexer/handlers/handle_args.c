/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 08:49:37 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 17:41:55 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_squote(t_shell **shell, char *s, size_t *index, char **tmp)
{
	if (!ft_strchr(&s[*index + 1], '\''))
		return (NULL);
	*tmp = ft_substr(s, *index + 1, ft_strchr(&s[*index + 1], '\'') - s);
	exit_free_if(!*tmp, shell, "allocation failed");
	*index = ft_strchr(&s[*index + 1], '\'') - s + 1;
	skip_space(s, index);
	return (s);
}

static char	*get_dquote(t_shell **shell, char *s, size_t *index, char **tmp)
{
	if (!ft_strchr(&s[*index + 1], '"'))
		return (NULL);
	*tmp = ft_substr(s, *index + 1, ft_strchr(&s[*index + 1], '"') - s);
	if (ft_strchr(*tmp, '$'))
		*tmp = handle_env(shell, *tmp, ft_strchr(*tmp, '$') - *tmp);
	if (!*tmp)
		return (NULL);
	*index = ft_strchr(&s[*index + 1], '"') - s + 1;
	skip_space(s, index);
	return (s);
}

static char	*check_args(t_shell **shell, char *s, size_t *index, char **tmp)
{
	size_t	i;

	i = *index;
	if (s[i] == '$')
	{
		s = handle_env(shell, s, i);
		if (!s)
			return (NULL);
		next(s, index);
		*tmp = ft_substr(s, i, *index);
		return (s);
	}
	if (s[i] == '\'')
		s = get_squote(shell, s, &i, tmp);
	else if (s[i] == '"')
		s = get_dquote(shell, s, &i, tmp);
	if (!s)
		return (NULL);
	*index = i;
	return (s);
}

static char	**init_args(char *s, size_t *index, char *cmd, size_t *j)
{
	char	**tmp;

	skip_space(s, index);
	tmp = malloc(sizeof(char *) * 2);
	tmp[0] = ft_substr(cmd, ft_strrchr(cmd, '/') - cmd + 1, ft_strlen(cmd));
	tmp[1] = NULL;
	*j = 1;
	return (tmp);
}

char	*ft_arg_loop(t_shell **shell, t_arg *arg,char *s)
{
	arg->tmp = (char **)ft_doubrealloc((void **)arg->tmp, arg->j + 1);
		exit_free_if(!arg->tmp, shell, "minishell:\terror:\tallocation failed");
		if (s[arg->i] == '$' && s[arg->i + 1] && s[arg->i + 1] == '?')
		{
			(*shell)->status = 1;
			arg->i += 2;
		}
		if (s[arg->i] == '$' || s[arg->i] == '\'' || s[arg->i] == '"')
		{
			s = check_args(shell, s, &arg->i, &arg->tmp[arg->j]);
			if (!s)
				return (NULL);
			arg->j++;
		}
		else
		{
			arg->end = arg->i;
			next(s, &arg->i);
			arg->tmp[arg->j] = ft_substr(s, arg->end, arg->i);
			exit_free_if(!arg->tmp[arg->j], shell, "minishell:\terror:\tallocation failed");
			arg->j++;
		}
		if (ft_isspace(s[arg->i]))
			skip_space(s, &arg->i);
		arg->end = arg->i;
		return (s);
}

char	*handle_args(t_shell **shell, char *s, size_t *index, char *cmd)
{
	t_arg	arg;

	arg.tmp = init_args(s, index, cmd, &arg.j);
	arg.end = *index;
	arg.i = *index;
	while (s[arg.i] && !(s[arg.i] == '|' || s[arg.i] == '<' \
				|| s[arg.i] == '>' || s[arg.i] == '&'))
	{
		s = ft_arg_loop(shell, &arg, s);
		if (!s)
			return (NULL);
	}
	*index = arg.i;
	(*shell)->cmds = add_node(shell, cmd, arg.tmp);
	return (s);
}
