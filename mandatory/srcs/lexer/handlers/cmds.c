/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:27:45 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/14 09:22:51 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	next_cmd(char *s, size_t *index)
{
	size_t	i;

	i = *index;
	while ((s[i]) && !((s[i] == ' ') || (getState(s[i], s[i + 1]) > 2 \
		&& (getState(s[i], s[i + 1]) < 10))))
		i++;
	*index = i;
}

t_cmd	*new_node(t_shell *shell)
{
	t_cmd	*new;

	new = malloc(sizeof(*new));
	exit_free_if(!new, shell, "allocation failed");
	new->cmd = NULL;
	new->next = NULL;
	new->args = NULL;
	return (new);
}

t_cmd	*add_node(t_shell *shell, char *name, char **args)
{
	t_cmd	*tmp;

	tmp = shell->cmds;
	if (!tmp)
	{
		tmp = new_node(shell);
		tmp->cmd = name;
		tmp->args = args;
		return (tmp);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node(shell);
		tmp->next->cmd = name;
		tmp->next->args = args;
		tmp->next->next = NULL;
		return (shell->cmds);
	}
}

char	**get_args(char *s, size_t *index, char *cmd)
{
	int		i;
	size_t	end;
	char	**tmp;

	skip_space(s, index);
	if (!s)
		return (NULL);
	end = *index;
	i = *index;
	if (s[i] && (ft_isalnum(s[i]) || s[i] == '-'))
	{
		tmp = malloc(sizeof(char *) * 3);
		next_cmd(s, &end);
		tmp[0] = cmd;
		tmp[1] = ft_substr(s, i, end);
		tmp[2] = NULL;
		*index = end;
		return (tmp);
	}
	else
		return (NULL);
}



char *cmd_exist(char *cmd, char **env)
{
	char **paths;
    int i;
	char *path;
	char *cmd_path;
	
	i = 0;	
	paths = ft_split(ft_getenv(env, "PATH"), ':');
    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, F_OK) == 0)
            return (cmd);
        else
            return (false);
    } 
    while (paths[i])
    {
        path = paths[i];
        cmd_path = ft_strjoin(path, "/");
        cmd_path = ft_strjoin(cmd_path, cmd);
        if (access(cmd_path, F_OK) == 0)
        {
            return (cmd_path);
        }
		free(path);
		free(cmd_path);
        i++;
    }
    return false;
}

bool	handle_cmd(t_shell *shell, char *line, size_t *i, char **env)
{
	char	*tmp;
	size_t	index;
	size_t	end;
	char	**args;

	index = *i;
	end = index;
	next_cmd(line, &end);
	tmp = ft_substr(line, index, end);
	exit_free_if(!tmp, shell, "allocation failed");
	tmp = cmd_exist(tmp, env);
	if (!tmp)
	{
		free_if(1, shell, "command not found");
		return (false);
	}
	index = end;
	args = get_args(line, &index, ft_substr(tmp, \
		ft_strrchr(tmp, '/') - tmp + 1, ft_strlen(tmp)));
	shell->cmds = add_node(shell, tmp, args);
	shell->tokens = ft_strjoin(shell->tokens, CMD);
	exit_free_if(!shell->tokens, shell, "allocation failed");
	*i = index;
	return (true);
}
