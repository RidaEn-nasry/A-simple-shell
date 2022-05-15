/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:38:43 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/14 20:21:56 by ren-nasr         ###   ########.fr       */
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
 

char **envs;

#include <minishell.h>

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



// agree surely there is as many standards as there's many tastes, not the point though , the point is 
// depending in the project at hand one should give more focus to project core subject. if it's a graphic projects focus more ough to the graphics part.


int getState(char c, char c1)
{
    if (ft_isspace(c))
        return (0);
    else if (ft_isalnum(c))
        return (1);
    else if (c == '\'' || c == '"')  
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
    
    t_shell *shell = NULL;
    shell = init_data(shell);


    // char *line;
    // line = ft_strdup(line);
    
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
            // printf("%s\n", "command");
           if (!handle_cmd(shell, line, &i))
                return;
            // printf("now i is %zu\n", i);
            // printf("tokens: %s\n", shell->tokens);
        }
        else if (getState(line[i], line[i + 1]) == 2)
        {
            // handle quote, state 2
            // printf("line at lexer: %s\n", line);
            line = handle_quote(shell, line, &i);
            if (!line)
                return;
            // printf("line at lexer: %s\n", line);
            // printf("now i is %zu\n", i);
            // if ()
            // if (!handle_quote(shell, line, &i))
            //     return;
        }
        else if (getState(line[i], line[i + 1]) == 3)
        {
            // handle << , state 3
            if (!delim_in(shell, line, &i))
                return;
        }
        else if (getState(line[i], line[i + 1])==4)
        {
                // handle >> , state 4  
                if (!append_out(shell, line, &i))
                    return;
        }
        else if (getState(line[i], line[i + 1]) == 5)
        {
            // handle < , state 5
            
            if (!delim_in(shell, line, &i))
                return;
        }
        else if (getState(line[i], line[i + 1]) == 6)
        {
            if (!append_out(shell, line, &i))
                return;
            // handle > , state 6
            
        }
        else if (getState(line[i], line[i + 1]) == 7)
        {
            // handle || , state 7
            shell->tokens = ft_strjoin(shell->tokens, OR);
            exit_free_if(!shell->tokens, shell, "allocation failed");
            i += 2;
        }
        else if (getState(line[i], line[i + 1]) == 8)
        {
            // handle | , state 7
            shell->tokens = ft_strjoin(shell->tokens, PIPE);
            exit_free_if(!shell->tokens, shell, "allocation failed");
            i++;
        }  
        else if (getState(line[i], line[i + 1]) == 9)
        {
            // hanle state && , state 8
            printf("im here\n");
            shell->tokens = ft_strjoin(shell->tokens, AND);
            exit_free_if(!shell->tokens, shell, "allocation failed");
            i += 2;
        }
        
        else if (getState(line[i], line[i + 1]) == 10)
        {
            // handle $? , state 10
            handle_env(shell, line, &i);
            
        }
        else if (getState(line[i], line[i + 1]) == 11)
        {
            // handle $ , state 11
            handle_env(shell, line, &i);
        }
        else 
        {
            free_if(1, shell, "invalid character");
            return;
        } 
    }
    if (shell->files->in)
        for (int i = 0; shell->files->in[i]; i++)
            printf("in: %s\n", shell->files->in[i]);
    printf("tokens last: %s\n", shell->tokens);
    // printf("len: %zu\n", ft_doublen((const char **)shell->delim));
    // for (int i = 0; shell->delim[i]; i++)
    // {
    //     printf("%s\n", shell->delim[i]);
    // }
    // printf("length: %zu\n", ft_doublen((const char **)shell->files->out));
    
    t_cmd *cmd = shell->cmds;
    while (cmd)
    {
        printf("last cmds: %s\n", cmd->cmd);
        cmd = cmd->next;
    }
    // t_cmd *cmd2 = shell->cmds;
    // while (cmd2)
    // {
    //     if (cmd2->args)
        
    //         for (int i = 0; cmd2->args[i]; i++)
    //         {
    //             printf("%s\n", cmd2->args[i]);
    //         }
    //     cmd2 = cmd2->next;
    // }
    // for (int i = 0; shell->files->out[i]; i++)
    // {
    //     printf("outfiles: %s\n", shell->files->out[i]);
    // }
    for (int i = 0; shell->env[i]; i++)
    {
        printf("env: %s\n", shell->env[i]);
    }
    
}

int main(int argc, char **argv, char **env)
{
    char *line;

    envs = env;
    (void)argc;
    (void)argv;
    while(1)
    {
        line = readline("$> ");
        if (line == NULL)
            break;
        add_history(line);
        lexer(line);
        // free(line);
    }
    return (0);
}


