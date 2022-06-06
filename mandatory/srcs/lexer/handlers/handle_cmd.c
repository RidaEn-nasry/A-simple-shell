/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:27:45 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 08:37:31 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
// #include "../../../includes/minishell.h"

t_cmd	*new_node(t_shell **shell)
{
	t_cmd	*new;

	new = malloc(sizeof(*new));
	exit_free_if(!new, shell, "minsihell:\terror: allocation failed");
	new->cmd = NULL;
	new->next = NULL;
	new->args = NULL;
	return (new);
}

t_cmd	*add_node(t_shell **shell, char *name, char **args)
{
	t_cmd	*tmp;

	tmp = (*shell)->cmds;
	if (!tmp)
	{
		tmp = new_node(shell);
		tmp->cmd = name;
		tmp->args = args;
		return (tmp);
	}
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new_node(shell);
		tmp->next->cmd = name;
		tmp->next->args = args;
		tmp->next->next = NULL;
		tmp->next->prev = tmp;
		return ((*shell)->cmds);
	}
}

char	*check_cmd(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (cmd);
	else
		return (NULL);
}

char	*cmd_exist(char *cmd, char **env)
{
	char	**paths;
	int		i;
	char	*path;
	char	*cmd_path;

	i = 0;
	if (!ft_envexist(env, "PATH"))
		return (NULL);
	paths = ft_split(ft_getenv(env, "PATH"), ':');
	if (ft_strchr(cmd, '/'))
		return (check_cmd(cmd));
	while (paths[i])
	{
		path = paths[i];
		cmd_path = ft_strjoin(path, "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(path);
		free(cmd_path);
		i++;
	}
	free(paths);
	return (false);
}

char	*handle_cmd(t_shell **shell, t_var *var)
{
	char		*tmp;
	size_t		index;
	size_t		end;

	index = var->i;
	end = index;
	next(var->line, &end);
	tmp = ft_substr(var->line, index, end);
	exit_free_if(!tmp, shell, "minshell:\terror\t:allocation failed");
	if (ft_strncmp(tmp, "exit", 4) && ft_strncmp(tmp, "unset", 5) \
		&& ft_strncmp(tmp, "export", 6))
		tmp = cmd_exist(tmp, (*shell)->env);
	if (!tmp)
	{
		ft_putstr_fd("minishell:\terror: command not found\n", 2);
		return (NULL);
	}
	index = end;
	skip_space(var->line, &index);
	var->line = handle_args(shell, var->line, &index, tmp);
	(*shell)->tokens = ft_strjoin((*shell)->tokens, CMD);
	(*shell)->tokens = ft_strjoin((*shell)->tokens, " ");
	if ((*shell)->status)
	{
		(*shell)->tokens = ft_strjoin((*shell)->tokens, EXIT);
		(*shell)->tokens = ft_strjoin((*shell)->tokens, " ");
		(*shell)->status = 0;
	}
	exit_free_if(!(*shell)->tokens, shell, \
		"minishell:\t:error:\tallocation failed");
	var->i = index;
	return (var->line);
}
