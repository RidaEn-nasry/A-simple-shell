
#include "tests.h"

void    CheckMallocProtection(char *path)
{
    int fd = open(path, O_RDWR);
    char *line = get_next_line(fd);

    while (line){
        if (strstr(line, "malloc(")){
            // extend the file by one line
            // ftruncate(fd, lseek(fd, 0, SEEK_END) + 50);
            char *new_line = malloc(sizeof(char) * (strlen(line) + 10));
            sprintf(new_line, "%s", "malloc(NULL);");
            // reposition the file pointer to new line.
            lseek(fd, -strlen(line), SEEK_CUR);
            write(fd, new_line, strlen(new_line));
        }
        free(line);
        free(new_line);
        line = get_next_line(fd);
    }

}

// int main()
// {
//     char *path = "./test.c";
//     CheckMallocProtection(path);
//     return 0;
// }