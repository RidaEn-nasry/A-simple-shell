/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:27:56 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/22 11:25:28 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exitIF(int condition, char *message)
{
    if (condition)
    {
        perror(message);
        exit(EXIT_FAILURE);
    }
    return (0);
}
