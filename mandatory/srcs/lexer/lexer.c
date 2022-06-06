/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:38:43 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 10:50:44 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	lexer(t_shell **shell, t_var *var)
{
	var->i = 0;
	while (var->line[var->i])
	{
		var->line = state_1(shell, var);
		if (!var->line)
			return (false);
		var->line = state_2(shell, var);
		if (!var->line)
			return (false);
		var->line = state_3(shell, var);
		if (!var->line)
			return (false);
	}
	return (true);
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n$> ", 1);
		rl_redisplay();
	}
}

bool	loop(t_shell *shell)
{
	t_var	var;

	var.line = ft_strdup("");
	while (1)
	{
		init_shell(&shell);
		var.line = readline("$> ");
		if (!var.line)
		{
			rl_redisplay();
			continue ;
		}
		if (!ft_strlen(var.line) || ft_sisspace(var.line))
			continue ;
		add_history(var.line);
		if (!lexer(&shell, &var))
		{
			free_if(1, &shell, NULL);
			continue ;
		}
		executor(shell);
		free_if(1, &shell, NULL);
	}
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(*shell));
	exit_free_if(!shell, &shell, "minishell:\terror:\tallocation failed");
	shell->env = ft_doubdup(env);
	shell->tmpfile = ft_strdup("/tmp/minishell.tmp");
	signal(SIGQUIT, exit);
	signal(SIGINT, sigint_handler);
	loop(shell);
	return (0);
}
