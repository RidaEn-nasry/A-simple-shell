/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:27:56 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/20 18:00:49 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exitIf(int condition, char *message)
{
    if (condition)
    {
        perror(message);
        exit(EXIT_FAILURE);
    }
    return (0);
}