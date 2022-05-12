

#include "../../includes/minishell.h"

// handle_quotes(char *str);
// i think the reason it starts over with index == 0, what i should do instead is use a tmp
void    skip_space(char *s, size_t *index)
{
    size_t i;

    i = *index;
    while (s[i] && s[i] == ' ')
        i++;
    *index = i;
}

void    next_space(char *s, size_t *index)
{

    size_t i;

    i = *index;
    while (s[i] && s[i] != ' ')
        i++;
    *index = i;
}

size_t  ll_len(t_cmd *cmd)
{
    size_t i;
    t_cmd *head = cmd;
    i = 0;
    while (head)
    {
        head = head->next;
        i++;
    }
    return (i);

}

t_data *init_data(t_data *data)
{
    data = malloc(sizeof(*data));
    // functions 
    // cmd linked list :
    // empty linked list checked by data->cmds->cmd != NULL
    data->cmds = NULL;
    

    // data->cmds->next = NULL; 

    
    data->tokens = malloc(sizeof(*data->tokens));


    // env stuff.
    data->env = malloc(sizeof(*data->env));
    data->env[0] = NULL;
    // files : 
    data->files = malloc(sizeof(*data->files));
    data->files->out = NULL;

    // cmds stuff
    // data->cmds->args = NULL;
    // data->files = NULL;
    // data->files->out = malloc(sizeof(*data->files->out) * 1);
    // data->files->out[0] = NULL;
    // data->files->out[0] = ft_strdup(" "); 
    // printf("len %zu\n", ft_doublen((const char **)data->files->out));
    exitIF(!data || !data->tokens || !data->env \
        || !data->env || !data->files, "allocation failed");
    return (data);
}

// next stops at either a space or operater found.


void next_ope(char *s, size_t *index)
{
    size_t i;

    i = 0;
    // should stop at either a space or operator or alphanumeric.
    while ((s[i]) &&  (!((s[i] == ' ') || !(getState(s[i], s[i + 1]) > 2 \
        && (getState(s[i], s[i + 1]) < 9))) || ft_isalnum(s[i])))
        i++;
    *index = i;
}

// create a new linked list with for cmds

// create a function to imitate the behavior of switch :



