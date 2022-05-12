/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:53:09 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/12 11:53:20 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool    handle_delim(t_data *data, char *line, size_t *i)
{
    size_t index;

    index = *i;
    char *tmp;
    int flag;


    flag = 0;
    if (line[index] == '<' && line[index + 1] == '<')
        flag = 1;   // <<
    else
        flag = 0; // <

    tmp = ft_substr(line, index, index + (ft_strchr(&line[index], ' ') - line - index));
    if (!tmp)
    {
        free(tmp);
        exit_free_if(1, data, "allocation failed");
    }
        if (ft_strlen(tmp) > 2)
        {
            if (flag)
            {
                printf("flag\n");
                data->delim = ft_substr(line, index + 2, index + ft_strchr(&line[index], ' ') - line - index);    
                exit_free_if(!data->delim, data, "allocation failed");
            }
            else
            {
                printf("no flag\n");
                data->files->in = ft_substr(line, index + 1, index + ft_strchr(&line[index], ' ') - line - index);
                exit_free_if(!data->files->in, data, "allocation failed");
                if (!ft_validfname(data->files->in))
                {
                    free_if(1, data, "invalid file name");
                    return (false);
                }
            }
            next_space(line, &index);
        }
        else
        {
            next_space(line, &index);
            skip_space(line, &index);
            if (flag)
            {
                data->delim = ft_substr(line, index, index + (ft_strchr(&line[index], ' ') - line - index));
                exit_free_if(!data->delim, data, "allocation failed");
            }
            else
            {
                data->files->in = ft_substr(line, index, index + (ft_strchr(&line[index], ' ') - line - index));
                exit_free_if(!data->files->in, data, "allocation failed");
                if (!ft_validfname(data->files->in))
                {
                    free_if(1, data, "invalid file name");
                    return (false);
                }
            }
            next_space(line, &index); 
        }
        if (flag)
            data->tokens = ft_strjoin(data->tokens, HEREDOC);
        else 
            data->tokens = ft_strjoin(data->tokens, IN);
        exit_free_if(!data->tokens, data, "allocation failed");
        *i = index;
        return true;
}


