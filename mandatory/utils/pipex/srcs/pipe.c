/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:00:25 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/16 16:37:03 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <string.h>
#include <stdio.h>

// a pipe is a special file that is used to connect two processes. 
// The pipe is a unidirectional pipe, meaning that one end of the pipe is used to send data and the other end is used to receive data.

/*
    There is no external file descriptor associated with a pipe it is just a temprorary buffer of limited size;
    The kernel blocks a process when it tries to read from an empty pipe and or tries to write to a full pipe.
    A pipe can be used only between a process which created the pipe and the children of that process.
        (this restriction is not not applied to "named pipes");
*/


/* 
    The pipe() system call creates a pipe, which is a unidirectional communication channel.
    The read end of the pipe is referred to as the pipe’s reader and the write end of the pipe is referred to as the pipe’s writer.
    The pipe() system call returns -1 if an error occurs.
*/





// figure out where the path 
// ft_join(path, "commande");
// and if the commande if the command exist with access() function.
// 


// exev kill the process.
// pipe(fd) 

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


#define READ_END 0
#define WRITE_END 1



typedef struct pipes{
    int fd[2];
    char *command;
} pipes;


    // reads from argv as {infile cmd1 cmd2 cmd3 ... outfile}

// int main(int argc, char **argv)
// {
//     pipes *pipe_t = malloc(sizeof(*pipe_t));
//     pipe_t->command = argv[1];
//     if (pipe(pipe_t->fd) == -1)
//     {
//         perror("pipe failed");
//         exit(EXIT_FAILURE);
//     }
//     int pid = fork();

//     if(pid == -1)
//     {
//         perror("forking failed");
//         exit(EXIT_FAILURE);
//     }
//     if (pid == 0)
//     {
//         int x;
//         printf("Input a number: ");
//         scanf("%d", &x);
//         if (write(pipe_t->fd[WRITE_END], &x, sizeof(x)) == -1)
//         {
//             perror("writing failed");
//             exit(EXIT_FAILURE);
//         }
//         close(pipe_t->fd[WRITE_END]);
//         exit(0);
//     }
//     else {
//         int y; 
//         if( read(pipe_t->fd[READ_END], &y, sizeof(y)) == -1)
//         {
//             perror("reading failed");
//             exit(EXIT_FAILURE);
//         }
//         y *= y;
//         close(pipe_t->fd[READ_END]);
//         printf("%d\n", y);
//         wait(NULL);
//     }
//     return 0;

    

// }


int main(int argc, char **argv)
{
    // parse
}