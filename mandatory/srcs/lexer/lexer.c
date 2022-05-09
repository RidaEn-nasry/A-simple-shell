/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:38:43 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/09 10:10:36 by ren-nasr         ###   ########.fr       */
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


t_data *init_data(t_data *data)
{
    data = malloc(sizeof(*data));
    // functions 
    data->free = exitFreeIF;
    // cmd linked list : 
    data->cmds = malloc(sizeof(*data->cmds)); 
    data->cmds->next = NULL;
    
    data->tokens = malloc(sizeof(*data->tokens));
    data->env = malloc(sizeof(*data->env));
    data->env->index = 0;
    data->env->env = malloc(sizeof(*data->env->env));
    exitIF(!data || !data->cmds || !data->tokens || !data->env \
        || !data->env->env, "allocation failed");
    return (data);
}

int    skip_space(char *s, int *i)
{
    int index = *i;
    while (ft_isspace(s[index]))
        index++;
    *i = index;
    return index;
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



void    handle_cmd(t_data *data, char *line, int *i)
{
    /*
        Pseudo code :
            -> get cmd.
                -> if cmd is valid.
                    -> if flag is set.
                        -> get flag.
                            -> if flag is valid.
                                -> store cmd.
                                -> store flag.
                                -> tokonize the cmd and flag.
                    -> else:
                        -> error.
                        -> exit.
                    -> else:
                        -> store cmd.
                        -> tokonize the cmd.
                -> else:
                    -> error.
                    -> exit.
    */
   // move to the last node of the cmd linked list.
   
    t_cmd *tmp = malloc(sizeof(*tmp));
    t_cmd *current;
    int index = *i;
     

    tmp->cmd = ft_substr(line, index, index + (ft_strchr(&line[index], ' ') - line - index));
    
    // check if cmd is valid
    
    tmp->cmd = cmd_exist(tmp->cmd);
    data->free(!tmp->cmd, data, "command not found");
    current = data->cmds;
    while (current->next)
        current = current->next;
    current = tmp;
    current->next = NULL;
    // tokonize the cmd
    data->tokens = ft_strjoin(data->tokens, CMD);
    data->free(!data->tokens, data, "allocation failed");
    index += (ft_strchr(&line[index], ' ') - line - index);
    // printf("%s\n", current->cmd);
    // printf("before : %d\n", index);
    index = skip_space(line, &index);
    // printf("%d, after\n", index);
    
    // check if flag is set 
    if (line[index] == '-' || getState(line[index], line[index + 1]) == 1)
    {
        // get flag 
        current->args = malloc(sizeof(*tmp->args) * 2);
        current->args[0] = ft_substr(line, index, index + (ft_strchr(&line[index], ' ') - line - index));
        exitFreeIF(!current->args || !current->args[0], data, "allocation failed");
        current->args[1] = NULL;
        index += (ft_strchr(&line[index], ' ') - line - index);
    }
    else
    {
        current->args = malloc(sizeof(*tmp->args) * 1);
        exitFreeIF(!current->args, data, "allocation failed");
        current->args[0] = NULL;
    }
    // if (current->cmd)
    //     printf("%s\n", current->cmd);
    // if (current->args[0])
    //     printf("%s\n", current->args[0]);
    // if (data->tokens)
    //     printf("%s\n", data->tokens);
    *i = index;
    
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
    char *tmp;
    
    int i = 0;
    while (line[i])
    {
        if (getState(line[i], line[i + 1]) == 0)
        {
            skip_space(line, &i);
        }
        else if (getState(line[i], line[i + 1]) == 1)
        {
            // don't forget to handle flag.
             handle_cmd(data, line, &i);
        }
        else if (getState(line[i], line[i + 1]) == 2)
        {
            // handle quote, state 2
            
            
        }
        else if (getState(line[i], line[i + 1]) == 3)
        {
            // handle << , state 3
            tmp = ft_substr(line, i, i + (ft_strchr(&line[i], ' ') - line - i));
            // printf("tmp : %s len is %zu\n", tmp, ft_strlen(tmp));
            if (ft_strlen(tmp) > 2)
            {
                
                data->delim = ft_substr(line, i + 2, i + (ft_strchr(&line[i], ' ') - line - i));
                exitFreeIF(!data->delim, data, "allocation failed");
                i += (ft_strchr(&line[i], ' ') - line - i);  
            }
            else{
                i += ft_strchr(&line[i], ' ') - line - i;
                i = skip_space(line, &i);
                data->delim = ft_substr(line, i, i + (ft_strchr(&line[i], ' ') - line - i));
                exitFreeIF(!data->delim, data, "allocation failed");
                i += (ft_strchr(&line[i], ' ') - line - i);
            }
            data->tokens = ft_strjoin(data->tokens, HEREDOC);
            data->free(!data->tokens, data, "allocation failed");

            
        }
        else if (getState(line[i], line[i + 1] == 4))
        {
            // handle >> , state 4 , what's called heredoc
        
           
            
        }
        else if (getState(line[i], line[i + 1] == 5))
        {
            // handle < , state 5
        }
        else if (getState(line[i], line[i + 1] == 6))
        {
            // handle > , state 6
        }
        else if (getState(line[i], line[i + 1]) == 7)
        {
            // handle || , state 7
        }
        else if (getState(line[i], line[i + 1] == 8))
        {
            // handle | , state 7
        }  
        else if (getState(line[i], line[i + 1] == 9))
        {
            // hanle state && , state 8
        }
        
        else if (getState(line[i], line[i + 1] == 10))
        {
            // handle $? , state 10
            
        }
        else if (getState(line[i], line[i + 1] == 11))
        {
            // handle $ , state 11
        }
        else 
            i++;
    }
    printf("%s\n", data->tokens);
}





int main(void)
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
