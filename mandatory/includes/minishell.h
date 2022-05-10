/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:25:58 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/10 14:45:32 by ren-nasr         ###   ########.fr       */
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
#define PIPE "<pp> " // |
#define OUT "<out> "  // >
#define IN "<in> "   // <
#define HEREDOC "<hd> " // << 
#define APPEND "<ap> " // >>
#define VAR "<var> " // $
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
} t_AST;


typedef struct s_cmd
{
    char *cmd;
    char **args;
    int fd[2];
    struct s_cmd *next;
} t_cmd;


typedef struct s_env {
    char **env;
    int index;
} t_env;


typedef struct s_files {
    char *in;
    char **out;
} t_files;

typedef struct s_data {
    t_cmd *cmds;
    char *tokens;
    t_files *files;
    char *delim;
    t_env *env;
    void (*free)(int, struct s_data *, char *);
} t_data;



// we will tokinze the string like this: 

t_cmd *add_node(t_cmd *cmds, char *cmd, char **args);


int    skip_space(char *s, int *i);

char *cmd_exist(char *cmd);

// Error handling :
int     exitIF(int , char *);
void    exitFreeIF(int condition, t_data *data, char *msg);



/* 
** lexer 
*/
// state machine
int getState(char c, char c1);

// lexer handlers
void    handle_delim(t_data *data, char *line, int *i);
void    handle_cmd(t_data *data, char *line, int *i);
void    handle_app(t_data *data, char *line, int *i);


// data initialization
t_data *init_data(t_data *data);

#endif  