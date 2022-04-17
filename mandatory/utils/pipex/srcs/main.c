/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:21:50 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/04/17 16:35:15 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/pipex.h"

// read argv line by line and create a pipe on each 
// an enviroment varialable is a variable that persist for the life of a terminal session.


// The PATH environment variable is a list of directories separated by the character ':'. w

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

    
// we should allocate memory for our struct in the following cases:
//      - if the struct needs to 
//     -> 


// a function that takes args and check if the path is a directory
// #define IS_DIR(path) (access(path, F_OK) == 0 && access(path, X_OK) == 0)
// char  *PATH = "PATH=/goinfre/ren-nasr/.brew/bin:/goinfre/ren-nasr/.brew/bin:/Users/ren-nasr/.nvm/versions/node/v17.6.0/bin:/Users/ren-nasr/goinfre/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Frameworks/Mono.framework/Versions/Current/Commands";


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
    // check if cmd contains any flags
    // if (ft_strchr(cmd.cmd, '-'))
    // {
    //     // add them to flags varialable
    //     // check if the flags are valid
    //     // if not print an error message
    //     // cut the flags from the cmd
    //     cmd.flags = ft_strdup(ft_strchr(cmd.cmd, '-'));
    //     cmd.cmd = ft_substr(cmd.cmd, 0, ft_strlen(cmd.cmd) - ft_strlen(ft_strchr(cmd.cmd, '-')));
    //     printf("%s\n", cmd.flags);
    //     printf("%s\n", cmd.cmd);
    // }
    while(args->paths[i]){
        // join path with cmd and check if it exist with access()
        tmp = ft_strjoin(args->paths[i], "/");
        tmp = ft_strjoin(tmp, cmd.cmd);
        
        if (access(tmp, X_OK) == 0)
        {
            // parse flags of cmd
            if (ft_strchr(cmd.cmd, '-'))
            {
                printf("%s\n", cmd.cmd);
            }
            // ft_strjoin(tmp, )
            return (tmp);
        }
        i++;
    }
    write(2, cmd.cmd, ft_strlen(cmd.cmd));
    // printf("here\n");
    write(2, ": Command not found\n", 19);
    exit(EXIT_FAILURE);

}


t_args *init_data(int argc, char **argv, char *PATH)
{
    int i = 2;
    t_args *args = malloc(sizeof(*args));
    // allocate memory for t_cmd
    args->cmds = malloc(sizeof(*args->cmds) * argc - 3);
    // allocate memory for each t_cmd

    args->infile = argv[1];
    args->outfile = argv[argc - 1];
    
    args->paths = ft_split(PATH, ':');
    
    // adda argv to each cmd
    while (i < argc - 1)
    { 
        args->cmds[i - 2].cmd = argv[i];
        i++;
    }
    // print all the cmds
    i = 0;
    while (args->cmds[i].cmd)
    {
        printf("%s\n", args->cmds[i].cmd);
        i++;
    }
    // store the commands in the t_cmd struct
    i = 0;
    while (i < argc - 1)
    {
        // allocate memory for the cmd
        // cut the flags from the cmd
        printf(" args->cmds[%d]: %s\n",i, args->cmds[i].cmd);
        if (ft_strchr(args->cmds[i - 2].cmd, '-'))
        {
            // printf("im here\n");
            args->cmds[i - 2].flags = ft_strdup(ft_strchr(args->cmds[i - 2].cmd, '-'));
            // printf("flags: %s\n", args->cmds[i - 2].flags);
            args->cmds[i - 2].cmd = ft_substr(args->cmds[i - 2].cmd, 0, ft_strlen(args->cmds[i - 2].cmd) - ft_strlen(ft_strchr(args->cmds[i - 2].cmd, '-')));
            // printf("cmd: %s\n", args->cmds[i - 2].cmd);
        }
        else 
        {
            // printf("in heeer\n");
            args->cmds[i - 2].flags = NULL;
            args->cmds[i - 2].cmd = ft_strdup(argv[i]);
        }
        i++;
    }
    
    return args;
}


// check first if the command exist in /bin . 
int main(int argc, char **argv, char **env)
{
    // grap the env varialable PATH from "**env"
    
    char *PATH;

    (void)env;

    // args = malloc(sizeof(*args));
    // args->infile = argv[1];
    // args->outfile = argv[argc - 1];
    
    // check if commands exist using access()
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
    
    
    
    // for (int i = 0; i < argc; i++)
    // {
    //    printf("paths[%d] = %s\n", i, args->paths[i]);
    // };
    // join the commands with the paths
    
   i = 2;
//    args->cmds = malloc(sizeof(*args->cmds) * (argc - 3));
    
//    for (int i = 2; i < argc - 1; i++)
//         args->commands[i - 2] = argv[i];
    

    // loop all the paths and check if the exucutable file exist
    i = 0;
    t_args *args = init_data(argc, argv, PATH);
    

    while(i < argc - 3)
    {
        // check_exist(args->commands[i], NULL);
       args->cmds[i].cmd= check_exist(args->cmds[i], args);
        i++;
    }
    // print all commands 
   for (int i = 0 ; i < argc - 3; i++)
   {
       printf("%s\n", args->cmds[i].cmd);
        // if (args->cmds[i].flags)
        //     printf("%s\n", args->cmds[i].flags);
   }
    // create the pipe
    // fork
    // if the child process
    //     exec the command
    // else
    //     wait for the child process
    // close the pipe
    
    

    // PIPING 
    

    // if (pipe(args->fd) == -1)
    // {
    //     // error
    //     write(2, "pipe error\n", 10);
    //     exit(EXIT_FAILURE);
    // }
    // if (fork() == 0)
    // {
    //     // we are in the child process 
    //     // close the read end of the pipe
    //     // dup the write end of the pipe to stdout
    //     // exec the command
    //     // 
    //     dup2(args->fd[1], 1);
    //     close(args->fd[0]);
    //     execve(args->commands[0], args->commands, env);
    // }
    // else
    // {
    //     close(args->fd[1]);
    //     wait(NULL);
    //     close(args->fd[0]);
    // }

    
    // for (int i = 0; i < argc - 1; i++)
    // {
    //    printf("commands[%d] = %s\n", i, args->commands[i]);
    // }
    // for (int i = 2; i < argc - 1; i++)
    //     printf("argv[%d] = %s\n", i, argv[i]);
    // printf("infile: %s\noutfile: %s\n", args->infile, args->outfile);
        // if (access(argv[i], F_OK | X_OK) == -1)
        // {
            
        //     write(2, argv[i], strlen(argv[i]));
        //     write(2, ": command not found\n", 20);
        //     exit(EXIT_FAILURE);
        // }
        // else
        //      args->commands[i] = argv[i];
    
        


    i = 0;
    // while (args->commands[i])
    // {
    //     printf("%s\n", args->commands[i]);
    //     i++;
    // }
    // for each path in path varialable check if the path is a directory
    i = 0;
    

    
    
    

    // while (args.paths[i])
    // {
    //     printf("%s\n", args.paths[i]);
    //     i++;
    // }
    
    // printf("PATH: %s\n", PATH);
    return 0;
    
}

