

#include "../../includes/minishell.h"

// handle_quotes(char *str);

int    skip_space(char *s, int *i)
{
    int index = *i;
    while (ft_isspace(s[index]))
        index++;
    *i = index;
    return index;
}

t_data *init_data(t_data *data)
{
    data = malloc(sizeof(*data));
    // functions 
    data->free = exitFreeIF;
    // cmd linked list : 
    data->cmds = malloc(sizeof(*data->cmds));

    data->cmds->next = NULL;
    
    data->tokens = malloc(sizeof(*data->tokens));
    data->env = malloc(sizeof(*data->env));
    data->env->index = 0;
    data->env->env = malloc(sizeof(*data->env->env));
    // files : 
    data->files = malloc(sizeof(*data->files));
    data->files->out = malloc(sizeof(*data->files->out) * 2);
    data->files->out[0] = ft_strdup(" "); 
    // printf("len %zu\n", ft_doublen((const char **)data->files->out));
    exitIF(!data || !data->cmds || !data->tokens || !data->env \
        || !data->env->env || !data->files->out || !data->files, "allocation failed");
    return (data);
}


// create a new linked list with for cmds

// create a function to imitate the behavior of switch :



