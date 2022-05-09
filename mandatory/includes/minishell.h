/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:25:58 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/09 11:02:50 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#define PIPE "<pp>" // |
#define OUT "<out>"  // >
#define IN "<in>"   // <
#define HEREDOC "<hd>" // << 
#define APPEND "<ap>" // >>
#define VAR "<var>" // $
#define DQUOTE "<dq>" // "
#define SQUOTE "<sq>" // '
#define BQUOTE "<bq>" // `
#define SEMICOLON "<sc>" // ;
#define AND "<and>" // &&
#define OR "<or>" // ||




typedef struct s_ast {
    char *token;
    struct s_ast *left;
    struct s_ast *right;
} t_ast;


typedef struct s_cmd
{
    char *cmd;
    char **args;
    int fd[2];
    struct s_cmd *next;
} t_cmd;

typedef struct s_data{
    t_cmd *cmds;
    char *tokens;
    char **out;
    char *in;
	void (*free)(int cond, t_data *, char *msg);
	char *delim;
} t_data;



// we will tokinze the string like this: 

t_cmd *add_node(t_cmd *cmds, char *cmd, char **args);


int exitIF(int , char *);

