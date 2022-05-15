/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:42:16 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/15 10:48:48 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    problem analysis:
    - even count of quotes gets what's enclosed inside the inverse quote without the inverse quotes themselves.
    - odd count of quotes gets what's enclosed inside the inverse quote with the inverse quotes themselves.

*/
// set env variables for it to work.

#include <minishell.h>

void    next_q(char *s, size_t *index, char q)
{
    size_t  i;
    
    i = *index;
    while (s[i] && (s[i] != q))
        i++;
    *index = i;
}



/*

    single quotes don't interpolate variables.
    double quotes interpolate variables.
    

    ===============
    get quote.
    
    

    

    so if ' is found and 
*/

char    *handle_quote(t_shell *shell, char *line, size_t *i)
{
    /*
        store quotes.
        while line[i] != store quote.
            i++;
        store contents of quotes.
    */
    (void)shell;
    char *new_line;
   
    char   quote;
    size_t index;
    size_t end;

    quote = line[*i];
    index = *i;
    end = index + 1;
    next_q(line, &end, quote);
    // while (line[end] && line[end] != quote)
    //     end++;
    if (end == ft_strlen(line) && line[end] != quote)
    {
        free_if(1, shell, "minishell: error:\tunmatched quote");
        printf("end: %zu\n", end);
        return (NULL);
    }
  
    char *content = ft_substr(line, index + 1, end);
   if (quote == '"')
   {
       // if a en variable found in content replace it with the value of the variable.
       
        end = ft_strchr(content, '$') - content + 1;
        
       // get content of 
       printf("end: %zu\n", end);
       if (ft_strchr(content, '$'))
       {
           
           // get the env variable.
           
            // expand the env variable.
            char *expan = expand_env(shell, content, &end);
            printf("expan: %s\n", expan);
            if (!expan)
                return (NULL);
            else
            {
                // new_line = ft_lineinsert(line, expan, index + 1, ft_strlen(expan));
                // printf("new_line: %s\n", new_line);
                // exit(0);
                // // create a new line with the variable replaced.
                // char *tmp = ft_substr(line, 0, ft_strchr(content, '$') - content + 1);

                // printf("part one %s\n", tmp);
                // tmp = ft_strjoin(tmp, expan);
                // printf("part two %s\n", tmp);
                // // printf("end: %zu\n", ft_strlen(line) - end - 1);
                // tmp = ft_strjoin(tmp, ft_substr(line, end + 1, end + (ft_strlen(line) - end)));
    
                // printf("part three %s\n", tmp);
                // line = tmp;
                // end = index + 1;
                // next_q(line, &end, quote);
                // content = ft_substr(line, index + 1, end);
                // printf("content: %s\n", content);
                // printf("%s\n", line);
            }
       }
   }

        // get content from 0 index to quote index.
    new_line = ft_substr(line, 0, index);
    printf("first part: %s\n", new_line);
        
        // join new_line with content inside quotes.
    new_line = ft_strjoin(new_line, content);
    printf("second part: %s\n", new_line);
        // join new_line with the rest of the line.
    char *rest = ft_ternary(line[end + 1], ft_strdup(line + end + 1), ft_strdup(""));
     
    new_line = ft_strjoin(new_line, rest);
    printf("third part: %s\n", new_line);
    ft_sfree((void *)line);
    line = new_line;
    
    return (line);
    // }
}