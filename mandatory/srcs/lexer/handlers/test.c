
#include <unistd.h>

int main(int argc, char **argv, char **env)
{



    char *args[] = {"ls", "-l", NULL};
    execve("/bin/ls", args, env);
    return (0);
}