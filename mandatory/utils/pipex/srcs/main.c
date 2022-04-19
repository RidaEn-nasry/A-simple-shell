/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:21:50 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/19 20:30:02 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/pipex.h"


#define READ_END 0
#define WRITE_END 1



/// =========== start of pseudo code ===========



// int main(int argc, char **argv, char **env)
// {
//     // grap the env varialable PATH from "**env"
//     // split the PATH varialable by ':'
//     // for each path in the PATH varialable
//     //     if the path is a directory
//     //         if the directory exist
//     //             if the directory is executable
//     //                 if the command exist
//     //                     create a pipe
//     //                     fork
//     //                     if the child process
//     //                         exec the command
//     //                     else
//     //                         wait for the child process
//     //                 else
//     //                     continue
//     //             else
//     //                 continue
//     //         else
//     //             continue
//     //     else
//     //         continue
//     // close the pipe
//     // wait for the child process
//     // if the child process return a value
//     //     if the value is 0
//     //         print the command
//     //     else
//     //         print the command and the return value
//     // else
//     //     print the command
//     // return (0);



// =========== end of pseudo code ===========



// ====== Summary ======

// example: dmesg | grep eth0 | wc -l 
// the shell starts all the commands (prcoesses) at the same time. and then connects them using pipes.
// -> here a pipe is setup to redirect stdout of dmesg to stdin of grep. the same is done between grep and wc.
// -> because wc is last in the pipeline its output it printed by the shell.

// > there 2 types of pipes:
//    1.anonymous pipes:
//       -> a pipe that is used to allow communication between two related processes. meanly processes that share file descriptors.(child and parent process).
//       -> anonymous pipes are created by the pipe() system call.
//       -> anonymous pipes are unidirectional.

//    2.named pipes:
//      -> a pipe that is a special file in the file system , any process with sufficient access rights can read and write to the pipe.
//      -> named pipes are created by the mkfifo() system call.


// data sent through a pipe is buffered by the kernel meaning that the data is not copied directly from the writer process to the reader process. but whay ? 

// -> heredoc 


// ========== end of summary ==========

char *check_exist(t_cmd cmd, t_args *args)
{
    int i = 0;
    
    char *tmp;
   // Check if cmd contains a '/'
    if (ft_strchr(cmd.cmd, '/'))
    {
        
        if (access(cmd.cmd, X_OK) == 0)
            return cmd.cmd;
        else {
        write(2, cmd.cmd, ft_strlen(cmd.cmd));
        write(2, ": Command not found\n", 19); 
        exit(EXIT_FAILURE);        
        }
    }
   
    while(args->paths[i]){
        // join path with cmd and check if it exist with access()
        tmp = ft_strjoin(args->paths[i], "/");
        tmp = ft_strjoin(tmp, cmd.cmd);
        
        if (access(tmp, X_OK) == 0)
            return (tmp);
        i++;
    }
    perror(cmd.cmd);
    perror(": Command not found.");
    exit(EXIT_FAILURE);

}




t_args *init_data(int argc, char **argv, char *PATH)
{
    int i = 2;
    t_args *args = malloc(sizeof(*args));
    args->len = argc - 3;

    args->cmds = malloc(sizeof(*args->cmds) * args->len);

    args->infile = argv[1];
    args->outfile = argv[argc - 1];
    
    args->paths = ft_split(PATH, ':');
  
    while (i < argc - 1)
    { 
        args->cmds[i - 2].cmd = ft_strdup(argv[i]);
        if (!ft_strchr(args->cmds[i - 2].cmd, ' '))
        {
           args->cmds[i - 2].flags = ft_split(argv[i], '\0');
        }
        else
            args->cmds[i - 2].flags = ft_split(argv[i], ' ');
        i++;
    }
 
    i = 0;
    while (i < args->len)
    {
        if (ft_strchr(args->cmds[i].cmd, '-'))
        {
            args->cmds[i].cmd = ft_substr(args->cmds[i].cmd, 0, ft_strlen(args->cmds[i].cmd) - ft_strlen(ft_strchr(args->cmds[i].cmd, '-')));
        }
        else if (ft_strchr(args->cmds[i].cmd, ' '))
        {
            args->cmds[i].cmd = ft_substr(args->cmds[i].cmd, 0, ft_strlen(args->cmds[i].cmd) - ft_strlen(ft_strchr(args->cmds[i].cmd, ' ')));

        }

        args->cmds[i].cmd = ft_strtrim(args->cmds[i].cmd, " ");
        if (args->cmds[i].flags)
        {
            int j = 0;
            while (args->cmds[i].flags[j])
            {
                args->cmds[i].flags[j] = ft_strtrim(args->cmds[i].flags[j], " ");
                j++;
            }
        }  
        i++;
    }
    return args;
}

int main(int argc, char **argv, char **env)
{
    
    char *PATH;

    (void)env;

     int i;
    
    i = 0;
    PATH = NULL;
    while (env[i])
    {
        // printf("%s\n", env[i]);
        if (ft_strstr(env[i], "PATH"))
        {
            PATH = env[i];
            break;
        }
        i++;
    };

    if (PATH == NULL)
    {
        write(2, "PATH not found\n", 15);
        exit(EXIT_FAILURE);
    };
    
    
    i = 0;
    t_args *args = init_data(argc, argv, PATH);
    
    for (int i = 0; i < args->len; i++)
    {
       args->cmds[i].cmd = check_exist(args->cmds[i], args);}
    int fd[2];
    
    int prev_pipe = open("infile", O_RDONLY);
    
    while(i < args->len - 1)
    {
    
        pipe(fd);
        
        // fork porocess becuase
        if (fork() == 0)
        {            
            if (prev_pipe != STDIN_FILENO)
            {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            execve(args->cmds[i].cmd, args->cmds[i].flags, env);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        close(prev_pipe);
        close(fd[1]);
        prev_pipe = fd[0];
        i++;
    }
    int outfile_fd = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (prev_pipe != STDIN_FILENO)
    {
        dup2(prev_pipe, STDIN_FILENO);
        close(prev_pipe);
    }
    dup2(outfile_fd, STDOUT_FILENO);
    execve(args->cmds[i].cmd, args->cmds[i].flags, env);
    perror("execve failed");
    waitpid(-1, NULL, 0);
    exit(EXIT_FAILURE);
}