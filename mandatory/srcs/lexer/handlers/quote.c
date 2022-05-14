/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:42:16 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/13 19:59:01 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
    problem analysis:
    - even count of quotes gets what's enclosed inside the inverse quote without the inverse quotes themselves.
    - odd count of quotes gets what's enclosed inside the inverse quote with the inverse quotes themselves.

*/

bool    handle_quote(t_shell *shell, char *line, size_t *i)
{
    /*
        store quotes.
         while line[i] != store quote.
            i++;
        store contents of quotes.
        
    */
   
    char   quote;
    size_t index;

    quote = line[*i];
    index = *i;
    end = index;
    while(line[end] && line[end] != quote)
    {
        end++;
    }

    


}