

#include "../../includes/minishell.h"

handle_quotes(char *str);


// create a new linked list with for cmds
t_cmd *new_cmd(char *cmd, char **args, int fd[2])
{
    t_cmd *new = malloc(sizeof(*new));
    new->cmd = cmd;
    new->args = ft_ternary(args, args, NULL);
}

// create a function to imitate the behavior of switch :



