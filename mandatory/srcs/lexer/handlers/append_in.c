/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:35:00 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/12 17:45:40 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    @description: 
        - handles the operators: > and >>
    @note:
        - because the operator > can be handled on the same way as >>,
            except for it's length, we use the same handler for both.
        - append_in.c is a silly acronym for append and in redirection opperators.
*/

#include <minishell.h>


int    next_op(char *s, size_t *index)
{
    size_t i;

    i = *index;
    while (s[i] && (getState(s[i], s[i + 1])) > 11)
        i++;
    return (i);
}


// bool    handle_app(t_data *data, char *line, size_t *index)
// {
//     /*
//         get len of the operator
//         if len == 1
//         start from len
//         get next stop.
//             get outfile.
//             if outfile is valid.
//                 store outfile.
//                 tokenize operator.
//             else
//                 return error.
//     */
//     size_t i;
//     size_t end;
//     size_t len;
//     char *outfile;
    
//     if (getState(line[*index], line[*index + 1]) == 4)
//         len = 2;
//     else
//         len = 1;
//     i = *index;
//     skip_space(line, &i);
//     end = i;
//     next_op(line, &end);
//     outfile = ft_substr(line, i, end);
//     // check if filename exist in current directory.
//     if (access(outfile, F_OK) != -1)
//     {
//         // check
//     }
    


//     next_op(line, index);

    
// }


bool    handle_app(t_data *data, char *line, size_t *i)
{
    

    
    size_t index;


    size_t len;
    
    // len = ft_doublen((const char **)data->files->out);
    if (!data->files->out)
    {
        data->files->out = malloc(sizeof(char) * 1);
        len = 0;
    }
    else
        len = ft_doublen((const char **)data->files->out);
        
    size_t end;
    int op_len;
    
    index = *i; 
    
    if (getState(line[index], line[index + 1]) == 4)
        op_len = 2;
    else
        op_len = 1;
    
    // op_len = (int *)ft_ternary(getState(line[index], line[index + 1] == 4), (int *)2, (int *)1);

    end = index;
    next_op(line, &end);
    // printf("end: %zu\n", end);
    // exit(0);
    // next_space(line, &end);
    char *tmp = ft_substr(line, index, end);
    if ((int)ft_strlen(tmp) > op_len)
    {
        // next_space(line, &end);
        next_op(line, &end);
        data->files->out = (char **)ft_doubrealloc((void **)data->files->out, len + 1);
        exit_free_if(!data->files->out, data, "allocation failed");
        data->files->out[len] = ft_substr(line, index + op_len, end);
        exit_free_if(!data->files->out[len], data, "allocation failed");
        if (!access(data->files->out[len], W_OK, ) )
        {
            free_if(1, data, "invalid file name");
            return false;
        }
        index = end;
        next_space(line, &index);
        skip_space(line, &index);
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
        next_space(line, &index);
        skip_space(line, &index);
        data->files->out = (char **)ft_doubrealloc((void **)data->files->out, len + 1);
        end = index;
        next_space(line, &end);
        exit_free_if(!data->files->out, data, "allocation failed");
        data->files->out[len] = ft_substr(line, index, end);
        if (!ft_validfname(data->files->out[len]))
        {
            free_if(1, data, "invalid filename");
            return false;
        }
        next_space(line, &index);
        skip_space(line, &index);
        free(tmp);
    }
    if (op_len == 1)
        data->tokens = ft_strjoin(data->tokens, OUT);
    else
    {
        data->tokens = ft_strjoin(data->tokens, APPEND);
        printf("here\n");
    }
    *i = index; 
    return true;
}
