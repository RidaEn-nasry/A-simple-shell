/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:13:14 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/17 14:35:05 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

#include "../../libft/libft.h"

#include <unistd.h>
#include <stdlib.h>


typedef struct s_cmd {
    char *cmd;
    char *flags;
} t_cmd;


typedef struct s_args {
    char **paths;
    char *infile;
    char *outfile;
    int fd[2];
    // data structure for t_cmd
    t_cmd *cmds;

} t_args;







#endif // PIPEX_H