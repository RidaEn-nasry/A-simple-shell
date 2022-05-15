/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:11:40 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/05/15 11:02:01 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
    @description:
       - this handler is used to handle env variables and $?.
       - it returns a new line with the env variable replaced by its value.

*/

#include <minishell.h>
// handle env should check and expand the env variables and return a new line with the expanded env variables.

char    *expand_env(t_shell *shell, char *line, size_t *i)
{
    // check if env var exist 
    // if it exist expand it, create a new line and return it.
    // if it doesn't exist, display error
    char    *env_name;
    size_t index;
    extern char **envs;
    char    *env_value;
    index = *i;
    next_cmd(line, &index);

    env_name = ft_substr(line, *i, index);
    if (ft_envexist(envs, env_name))
    {
        env_value = ft_strdup(ft_getenv(envs, env_name));
        *i = index;
        return (env_value);
    }
    else
    {
        free_if(1, shell, "minishell:\terror:\tinvalid env variable");
        return NULL;
    }
}


char    *handle_env(t_shell *shell, char *line, size_t *i)
{
    /*
        check if env variable is valid , if it's expand create a new line and return it.
        if it's not valid, display error.
    */
    (void)shell;
    char    *env_name;
    size_t index;
    extern char **envs;
    char    *env_value;
    char    *new_line;
    
    index = *i;
    next_cmd(line, &index);
    env_name = ft_substr(line, *i, index);
    printf("env_name: %s\n", env_name);
    env_value = ft_envexp(envs, env_name);

    if (env_value)
    { 
        // create a new line with the env variable replaced by its value.
        new_line = ft_lineinsert(line, env_value, *i, ft_strlen(env_name));
        printf("new_line: %s\n", new_line);        
        exit(0);
    }
    
    return (NULL);
    // get the env variable name

    // env_name = ft_getenv()
}