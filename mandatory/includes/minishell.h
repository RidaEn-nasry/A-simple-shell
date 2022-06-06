/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:25:58 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/06 17:23:51 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/get_next_line/get_next_line.h"
# include "../utils/libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/resource.h>
# include <readline/history.h>
# include <readline/readline.h>

# define CMD "<cmd>"
# define PIPE "<p>"
# define OUT "<out>"
# define IN "<in>"
# define HEREDOC "<hd>"
# define APPEND "<ap>"
# define VAR "<var>"
# define EXIT "<ex>"
# define DQUOTE "<dq>"
# define SQUOTE "<sq>"
# define AND "<and>"
# define OR "<or>"

# define WRITE_END 1
# define READ_END 0

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_files {
	char	**in;
	char	**out;
}	t_files;

typedef struct s_shell {
	t_cmd	*cmds;
	char	*tokens;
	t_files	*files;
	char	**delim;
	char	**env;
	char	*tmpfile;
	int		status;
}	t_shell;

typedef struct s_var {
	char	*line;
	size_t		i;
	size_t	index;
	size_t	end;
	size_t	len;
	int		op_len;
}	t_var;

typedef struct s_arg {
	size_t	i;
	size_t	end;
	char	**tmp;
	size_t	j;
}	t_arg;

t_cmd	*add_node(t_shell **shell, char *name, char **args);
char	*ft_delim_if(t_shell *shell, t_var *var, char *tmp);
void	skip_space(char *s, size_t *index);
char	*cmd_exist(char *cmd, char **env);

// Error handling :
int		exit_if(int cond, char *msg);
void	exit_free_if(int cond, t_shell **shell, char *msg);
void	free_if(int cond, t_shell **shell, char *msg);

// state machine
int		get_state(char c, char c1);
char	*state_1(t_shell **shell, t_var *var);
char	*state_2(t_shell **shell, t_var *var);
char	*state_3(t_shell **shell, t_var *var);
bool	validate_file(t_shell **shell, size_t len);
char	*get_file_quote(t_shell **shell, char *line, size_t *index, size_t len);

// lexer handlers
char	*delim_in(t_shell **shell, t_var *var);
char	*handle_cmd(t_shell **shell, t_var *var);
char	*append_out(t_shell **shell, t_var *var);
char	*ft_first_if(t_shell **shell, t_var *var);
char	*ft_sec_if(t_shell **shell, t_var *var);
char	*handle_env(t_shell **shell, char *line, size_t i);
char	*handle_quote(t_shell **shell, char *line, size_t i);
char	*handle_args(t_shell **shell, char *s, size_t *index, char *cmd);
char	*handle_exe(t_shell **shell, t_var *var);

// shell initialization
void	init_shell(t_shell **shell);
void	next_space(char *s, size_t *index);
void	next_cmd(char *s, size_t *index);
void	next_op(char *s, size_t *index);
char	*expand_env(t_shell *shell, char *line, size_t *i);
bool	is_operator(char c);
bool	is_special(char c);
char	*check_env_file(t_shell *shell, int len);
void	next(char *s, size_t *index);

// parser errors detectors
bool	check_invalid_start(char *tokens);
bool	check_conse_and_or(char *tokens);
bool	check_pipe_andor(char *tokens);

// execution
bool	executor(t_shell *shell);
bool	handle_builtins(t_shell *shell);
bool	is_builtin(char *cmd);

// exucution handlers
bool	exe_handle_cmd(t_shell *shell);
bool	exe_handle_out(t_shell *shell);
bool	exe_handle_app(t_shell *shell);
bool	exe_handle_in(t_shell *shell);
bool	exe_handle_heredoc(t_shell *shell);

// commands:
int		ft_echo(t_shell *shell);
int		ft_cd(t_shell *shell);
int		ft_env(t_shell *shell);
int		ft_exit(t_shell *shell);
int		ft_export(t_shell *shell);
int		ft_pwd(t_shell *shell);
int		ft_unset(t_shell *shell);

#endif  