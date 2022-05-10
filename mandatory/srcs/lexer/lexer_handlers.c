/* ************************************************************************** */
/*          */
/* :::      ::::::::   */
/*   lexer_handlers.c  :+:      :+:    :+:   */
/*        +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*    +#+#+#+#+#+   +#+*/
/*   Created: 2022/05/10 13:43:11 by ren-nasr          #+#    #+#  */
/*   Updated: 2022/05/10 14:01:39 by ren-nasr         ###   ########.fr       */
/*          */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void    handle_delim(t_data *data, char *line, int *i)
{
    int index;

    index = *i;
    char *tmp;
    tmp = ft_substr(line, index, index + (ft_strchr(&line[index], ' ') - line - index));
    if (!tmp)
    {
        free(tmp);
        data->free(1, data, "allocation failed");
        }
        if (ft_strlen(tmp) > 2)
        {       
            data->delim = ft_substr(line, index + 2, index + (ft_strchr(&line[index], ' ') - line - index));
            data->free(!data->delim, data, "allocation failed");
            index += (ft_strchr(&line[index], ' ') - line - index);  
        }
        else
        {
            index += ft_strchr(&line[index], ' ') - line - index;
            index = skip_space(line, &index);
            data->delim = ft_substr(line, index, index + (ft_strchr(&line[index], ' ') - line - index));
            data->free(!data->delim, data, "allocation failed");
            index += (ft_strchr(&line[index], ' ') - line - index); 
        }
        data->tokens = ft_strjoin(data->tokens, HEREDOC);
        data->free(!data->tokens, data, "allocation failed");
        *i = index;    
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
    data->free(!tmp->cmd, data, "allocation failed");
    // the tmp for minimizing lines by freeing tmp->on the go 

    tmp->cmd = cmd_exist(tmp->cmd);
    data->free(!tmp->cmd, data, "command not found");
    // check if cmd is valid

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

void    handle_app(t_data *data, char *line, int *i)
{
    int index;

    index = 0;


    index = *i;

    // printf("len : %zu\n", ft_doublen((const char **)data->files->out));
    char *tmp = ft_substr(line, index, ft_strchr(line, ' ')  - line - index);
    if (ft_strlen(tmp) > 2)
    {
       /*
            if filename:
                -> store filename.
                -> tokonize the operator.
            else:
                -> error.
                -> exit.
       */
    
     
    
    }
    else
    {
        /*
            if !filename:
                error.
                exit.
            else:
                store filename.
                tokonize the operator.
                update index.
        */
        index += ft_strchr(line, ' ') - line - index;
        index = skip_space(line, &index);
        // printf("now index %d at %s\n",index , &line[index]);
        // printf("start: %d and end : %ld\n", index, getnextS(line[index]) - line - index);
        data->files->out = (char **)ft_doubrealloc((void **)data->files->out, ft_doublen((const char **)data->files->out) + 1);
        data->free(!data->files->out, data, "allocation failed");
        data->files->out[ft_doublen((const char **)data->files->out) - 1] = ft_substr(line, index, ft_strchr(&line[index], ' ') - line - index);
        printf("len: %zu\n outfile =  %s\n", ft_doublen((const char **)data->files->out) - 1, data->files->out[ft_doublen((const char **)data->files->out) - 1]);
        data->free(!data->files->out[ft_doublen((const char **)data->files->out) - 1], data, "outfile not found");
        index += (ft_strchr(&line[index], ' ') - line - index);
        index = skip_space(&line[index], &index);
        // printf("now index %d at %s\n",index , &line[index]);
    }
    data->tokens = ft_strjoin(data->tokens, APPEND);
    data->free(!data->tokens, data, "allocation failed");
    *i = index;
}
