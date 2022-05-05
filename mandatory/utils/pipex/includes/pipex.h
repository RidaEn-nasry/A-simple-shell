/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:13:14 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/20 20:25:40 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

#include "../../libft/libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "../../get_next_line/get_next_line.h"


#define READ_END 0
#define WRITE_END 1

// define the typedef of bool 
typedef enum { false, true } t_bool;

typedef struct s_cmd {
    char *cmd;
    char **flags;
} t_cmd;


typedef struct s_args {
    char **paths;
    char *infile;
    char *outfile;
    int fd[2];
    int len;
    int pipe;
    t_bool herdoc;
    char *limiter;
    char *data;
    t_cmd *cmds;

} t_args;







#endif // PIPEX_H