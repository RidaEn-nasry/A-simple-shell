/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:38:43 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/12 16:38:47 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// if you find a single quote , 

#include <readline/history.h>
#include <readline/readline.h>


    

// the lexer will take the given string and create tokens out if it.
// the lexer will also handle errors on the fly.
// the lexer will return a list of tokens.


// the values and their tokens are: 
// -> cmd: <cmd flags>

// get the part after <cmd and before >
 


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


// the lexer is a state machine :

char *cmd_exist(char *cmd)
{

    char *PATH = getenv("PATH");

    char **paths = ft_split(PATH, ':');
    int i = 0;
    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, F_OK) == 0)
            return (cmd);
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
            return (cmd_path);
        }
        i++;
    }
    return false;
}





int getState(char c, char c1)
{
    if (ft_isspace(c))
        return (0);
    else if (ft_isalnum(c))
        return (1);
    else if (c == '\'' | c == '"')
        return (2);
    else if (c == '<' && c1 == '<')
        return (3);
    else if (c == '>' && c1 == '>')
        return (4);
    else if (c == '<')
        return (5);
    else if (c == '>')
        return (6);
    else if (c == '|' && c1 == '|')
        return (7);
    else if (c == '|')
        return (8);
    else if (c == '&' && c1 == '&')
        return (9);
    else if (c == '$' && c1 == '?')
        return (10);
    else if (c == '$')
        return (11);
    else 
        return (12);
}




// <in> <cmd ls -al> <pipe> <cmd cat> <pipe> <cmd wc -la> <out> 

        // if char is a space go to state 0
        // if char is alphanumeric go to state 1
        // if char is a '\'' or '"' go to state 2
        
        // - if char is a '>', go to state 3
        // - if char is a '<', go to state 4
        // - if char is a '|', go to state 5
        // - if char is a quote go to state 6
        // - if char is a '$', go to state 8
  


void lexer(char *line)
{
    
    t_data *data = NULL;
    data = init_data(data);

    
    size_t i = 0;
    while (line[i])
    {
        if (getState(line[i], line[i + 1]) == 0)
        {
            skip_space(line, &i);
        }
        else if (getState(line[i], line[i + 1]) == 1)
        {
            // don't forget to handle flag.
           if (!handle_cmd(data, line, &i))
                return;
        }
        else if (getState(line[i], line[i + 1]) == 2)
        {
            // handle quote, state 2
            
        }
        else if (getState(line[i], line[i + 1]) == 3)
        {
            // handle << , state 3
            handle_delim(data, line, &i);
        }
        else if (getState(line[i], line[i + 1])==4)
        {
                // handle >> , state 4  
                // printf(">>\n"); 
                // printf("%c | %c", line[i], line[i + 1]);
                if (!handle_app(data, line, &i))
                    return;

        }
        else if (getState(line[i], line[i + 1]) == 5)
        {
            
            if (!handle_delim(data, line, &i))
                return;
            // handle < , state 5
        }
        else if (getState(line[i], line[i + 1]) == 6)
        {
            if (!handle_app(data, line, &i))
                return;
            // handle > , state 6
            
        }
        else if (getState(line[i], line[i + 1]) == 7)
        {
            // handle || , state 7
            
        }
        else if (getState(line[i], line[i + 1]) == 8)
        {
            // handle | , state 7
            data->tokens = ft_strjoin(data->tokens, PIPE);
            exit_free_if(!data->tokens, data, "allocation failed");
            i++;
        }  
        else if (getState(line[i], line[i + 1]) == 9)
        {
            // hanle state && , state 8
        }
        
        else if (getState(line[i], line[i + 1]) == 10)
        {
            // handle $? , state 10
            // printf("$?\n");
            handle_env(data, line, &i);
            
        }
        else if (getState(line[i], line[i + 1]) == 11)
        {
            // handle $ , state 11
            handle_env(data, line, &i);
        }
        else 
            i++;
    }
    // for (int i = 0; data->files->out[i]; i++)
    // {
    //     printf("%s\n", data->files->out[i]);
    // }
    printf("%s\n", data->tokens);
   
    // printf("length: %zu\n", ft_doublen((const char **)data->files->out));
    printf("len : %zu\n", ll_len(data->cmds));
    
    t_cmd *cmd = data->cmds;
    while (cmd)
    {
        printf("last cmds: %s\n", cmd->cmd);
        cmd = cmd->next;
    }
    t_cmd *cmd2 = data->cmds;
    while (cmd2)
    {
        if (cmd2->args)
        
            for (int i = 0; cmd2->args[i]; i++)
            {
                printf("%s\n", cmd2->args[i]);
            }
        cmd2 = cmd2->next;
    }
}



int main(void)
{
    // lexer(argc, argv);
    // print all arguments
    char *line;
    while(1)
    {
        line = readline("$> ");
        if (line == NULL)
            break;
        add_history(line);
        lexer(line);
        free(line);
    }
    return (0);
}
