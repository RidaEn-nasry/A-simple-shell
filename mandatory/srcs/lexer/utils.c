

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

t_shell *init_data(t_shell *shell)
{
    shell = malloc(sizeof(*shell));
    // functions 
    // cmd linked list :
    // empty linked list checked by shell->cmds->cmd != NULL
    shell->cmds = NULL;
    

    // shell->cmds->next = NULL; 

    
    shell->tokens = malloc(sizeof(*shell->tokens));


    // env stuff.
    shell->env = malloc(sizeof(*shell->env));
    shell->env[0] = NULL;
    // files : 
    shell->files = malloc(sizeof(*shell->files));
    shell->files->out = NULL;
    shell->files->in = NULL;


    shell->delim = NULL;
    // cmds stuff
    // shell->cmds->args = NULL;
    // shell->files = NULL;
    // shell->files->out = malloc(sizeof(*shell->files->out) * 1);
    // shell->files->out[0] = NULL;
    // shell->files->out[0] = ft_strdup(" "); 
    // printf("len %zu\n", ft_doublen((const char **)shell->files->out));
    exitIF(!shell || !shell->tokens || !shell->env \
        || !shell->env || !shell->files, "allocation failed");
    return (shell);
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


