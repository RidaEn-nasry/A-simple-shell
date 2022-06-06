/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:24:24 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 10:02:57 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	add_env(t_shell *shell, char *env_name, char *env_value)
{
	size_t	len;

	len = ft_doublen((const char **)shell->env);
	shell->env = (char **)ft_doubrealloc((void **)shell->env, len + 1);
	shell->env[len] = ft_strdup(env_name);
	shell->env[len] = ft_strjoin(shell->env[len], "=");
	shell->env[len] = ft_strjoin(shell->env[len], env_value);
	return (true);
}

void	ft_else_if(char *path, t_shell *shell)
{
	path = ft_strdup(ft_getenv(shell->env, "OLD_PWD"));
	if (!path)
		path = getcwd(NULL, 0);
}

int	ft_cd(t_shell *shell)
{
	char	*path;

	path = NULL;
	if (!shell->cmds->args[1])
		path = ft_strdup(getenv("HOME"));
	else if (shell->cmds->args[1][0] == '~')
		path = ft_strjoin(getenv("HOME"), &shell->cmds->args[1][1]);
	else if (!ft_strncmp(shell->cmds->args[1], "-", \
		ft_strlen(shell->cmds->args[1]) - 1))
		ft_else_if(path, shell);
	else
	{
		if (shell->cmds->args[1] == NULL)
			path = getenv("HOME");
		else
			path = shell->cmds->args[1];
	}
	add_env(shell, "OLD_PWD", getcwd(NULL, 0));
	if (chdir(path) != 0)
		return (1);
	shell->cmds = shell->cmds->next;
	shell->status = 0;
	return (0);
}
