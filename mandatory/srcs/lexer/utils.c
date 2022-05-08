

#include "../../includes/minishell.h"

handle_quotes(char *str);


// create a new linked list with for cmds
t_cmd *new_cmd(char *cmd, char **args, int fd[2])
{
    t_cmd *new = malloc(sizeof(*new));
    new->cmd = cmd;
    new->args = ft_ternary(args, args, NULL);

}

void    exitFree(t_data *data, char *msg)
{
    // free linked list 
    t_cmd *tmp = data->cmds;
    int i = 0;
    while (data->cmds)
    {
        tmp = data->cmds;
        data->cmds = data->cmds->next;
        ft_safeFree(tmp->cmd);
        while (tmp->args[i])
        {
            ft_safeFree(tmp->args[i]);
            i++;
        }
        ft_safeFree(tmp->args);
        free(tmp);
    }
    ft_safeFree(data->tokens);
    ft_safeFree(data->in);
    ft_safeFree(data->out);
    free(data);
    perror(msg);
    exit(EXIT_FAILURE);
}


// create a function to imitate the behavior of switch :



