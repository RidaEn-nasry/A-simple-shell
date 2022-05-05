/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:38:43 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/05 12:42:59 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <readline/history.h>
#include <readline/readline.h>
// state machine for lexer
// - state 0:
//     - if char is a space, go to state 0 

/* Backus Naur Form of shell grammar

    cmd [arg]* [ | cmd [arg]*]* 
        [[>filename][<filename][>&filename][>>filename][>>&filename]]*[&]

    cmd:
        [a-zA-Z0-9_]+ 
    arg:
        [a-zA-Z0-9_]+
    filename:
        [a-zA-Z0-9_]+
    &:
        &
    >:
        >
    <:
        <
    >>:
        >>
    >>&:
        >>&
    [:
        [
    ]:
        ]
        
*/


// lex and tokenize a string 
// return a list of tokens

// state machine :
// - cmd state 
// - 
// ======= pseudo code for lexer =======
    

// the lexer will take the given string and create tokens out if it.
// the lexer will also handle errors on the fly.
// the lexer will return a list of tokens.


// the values and their tokens are: 
// -> cmd: <cmd cmd flags>

// get the part after <cmd and before >


// <
// <in> <cmd ls -al> <pipe> <cmd cat> <pipe> <cmd wc -la> <out> 


    // state machine :
    
        // printable is not an operator.
                //  handle which operator.
        // printable is a space.
                // 
        // printable is a letter.
    

        // - if char is a '>', go to state 0
        // - if char is a '<', go to state 1
        // - if char is a '|', go to state 2
        // - if char is a quote go to state 3
        // - if char is a '$', go to state 4
        // - else char * is a cmd to state 5
        



#include "../../includes/minishell.h"

/* 
    -> analyzing the problem : 
        - the lexer will take the given string and create tokens out of it.
        - the lexer will also handle errors on the fly.
        - the lexer will return a list of tokens.
        

    -> simple solution using state machine :
        - if we're in state 0 :
            - store next char * in infile 
                - if infile exist :
                    - tokonize the in redirection.
        - if we're in state 1:
            - store next char * in outfile    
            - tokonize the out redirection.
        - if we're in state 2:
            - tokonize the pipe.     
        - if we're in state 3:
            - tokinze the quote.
        - else :
            - we're in state 5.
                - if cmd is valid : 
                    - tokenize the cmd.
                    - go to state 0.
                - else :
                    - error.
                    - exit.
             
         
*/

#define CMD_LEN 128
t_cmd cmds[CMD_LEN];



int isOperator(char c, char c1)
{
    return (0);
}




// the lexer is a state machine :

bool cmd_exist(char *cmd)
{

    char *PATH = getenv("PATH");

    char **paths = ft_split(PATH, ':');
    int i = 0;
    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, F_OK) == 0)
            return (true);
        else
            return (false);
    }
    while (paths[i])
    {
        char *path = paths[i];
        char *cmd_path = ft_strjoin(path, "/");
        cmd_path = ft_strjoin(cmd_path, cmd);
        if (access(cmd_path, F_OK) == 0)
        {
            return (true);
            
        }
        i++;
    }
    return false;
}


// int handle_cmd(char *argv)
// {
//     int j;
//     j = 0;
//     char *cmd_tmp;
//     while (argv[j]) {            
//     if (isOperator(argv[j]))
//          break;
//         cmd_tmp[j] = argv[j];
//     }
//     exitIF(cmd_exist(cmd_tmp) == false, "command not found");
//     // add the cmd to the cmds array
    
// }


void lexer(char *str)
{
        t_data *data = malloc(sizeof(*data));
        data->cmds = malloc(sizeof(*cmds)); 
        
        char **tmp = ft_splitq(str, ' ');
        int i = 0 ;
        while (tmp[i])
        {
            if (!strncmp(tmp[i], "<", 1))
            {
                exitIF(!tmp[i + 1] || access(tmp[i + 1], F_OK) == -1, "file not found"); 
                data->in = ft_strdup(tmp[i + 1]);
                // data->tokens =  ft_strjoin(data->tokens, IN);
                // data->tokens = ft_strjoin(data->tokens, " ");
                i++;
                
                // check if the file exist
                
               // we assume that next char is a file name.
                    // - we check if the file exist.
                    // - if it exist. 
                        // - we tokenize the in redirection. 
                        // add the infile to the data instance.
                    // - else :
                        // - error.
                        // - exit.
                
                
                
            }
            else if (!strncmp(tmp[i], ">", 1))
            {
                printf("outfile detected\n");
            }
            else if (!strncmp(tmp[i], "|", 1))
            {
                printf("pipe detected\n");
            }
            else if (!strncmp(tmp[i], "\"", 1))
            {
                printf("quote detected\n");
            }
            else if (!strncmp(tmp[i], "$", 1))
            {
                printf("env detected\n");
            }
            else
            {
                printf("cmd detected\n");
            }
           
            i++;
        }
                
}





int main(int argc, char **argv)
{
    // lexer(argc, argv);
    // print all arguments
    
    while(1)
    {
        char *line = readline("$> ");
        if (line == NULL)
            break;
        add_history(line);
        lexer(line);
        free(line);
    }
    return (0);
}