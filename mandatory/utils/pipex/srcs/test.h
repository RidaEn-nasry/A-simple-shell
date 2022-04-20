/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:45:33 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/20 12:47:34 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# include <stdio.h>
# include <unistd.h>
# define EXITIF(cond , msg) if (cond) { perror(msg); exit(EXIT_FAILURE); }
#endif