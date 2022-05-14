/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:25:58 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/13 15:34:47 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../utils/get_next_line/get_next_line.h"
#include "../utils/libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>


// lexer will create tokens of given strings and handle errors on the fly.
// parser will create an AST from the tokens.
// interpreter will execute the AST.
// 

// we will do our error handling in the lexer

// command table structure
/*
--------------------------------------------------
    cmd1    |  flags    | 
    cmd2    |  flags    | 
    INPUT   |  OUTPUT   | ERR 
------------------------------------------------
*/


// These are special operators and their corresponding token

#define CMD "<cmd> "
#define PIPE "<p> " // |
#define OUT "<out> "  // >
#define IN "<in> "   // <
#define HEREDOC "<hd> " // << 
#define APPEND "<ap> " // >>
#define VAR "<var> " // $
#define EXIT "<ex> " // $?
#define DQUOTE "<dq> " // "
#define SQUOTE "<sq> " // '
#define BQUOTE "<bq> " // `
#define SEMICOLON "<sc> " // ;
#define AND "<and> " // &&
#define OR "<or> " // ||


typedef struct s_AST {
    char *token;
    struct s_AST *left;
    struct s_AST *right;
}   t_AST;

typedef struct s_cmd
{
    char *cmd;
    char **args;
    int fd[2];
    struct s_cmd *next;
} t_cmd;

typedef struct s_files {
    char **in;
    char **out;
} t_files;

typedef struct s_shell {
    t_cmd *cmds;
    char *tokens;
    t_files *files;
    char **delim;
    char **env;
    int last_exit;
} t_shell;

// we will tokinze the string like this: 

// t_cmd *add_node(t_shell *data, char *cmd_name);


void    skip_space(char *s, size_t *index);

char *cmd_exist(char *cmd, char **env);

// Error handling :
int     exitIF(int , char *);
void    exit_free_if(int , t_shell *, char *);
void    free_if(int , t_shell *, char *);



/* 
** lexer 
*/
// state machine
int getState(char c, char c1);

// lexer handlers
bool    delim_in(t_shell *data, char *line, size_t *i);
bool    handle_cmd(t_shell *data, char *line, size_t *i, char **env);
bool    append_out(t_shell *data, char *line, size_t *i);
void    handle_env(t_shell *data, char *line, size_t *i);

// data initialization
t_shell *init_data(t_shell *data);
void next_space(char *s, size_t *index);
void    next_cmd(char *s, size_t *index);
void	next_op(char *s, size_t *index);

#endif  