

// create a function that takes a path to a file and checks if every malloc call is protected by injecting NULL pointers for every malloc call.
//
// The function should return the number of errors found.

// The function should print the errors to stderr.
#include "tests.h"

void    CheckMallocProtection(char *path)
{
    // open the file
    // read the file line by line
    // if the line contains a malloc call
    //  replace what's in the line with "malloc(NULL);"
    //  write the line back to the file
    // close the file

    int fd = open(path, O_RDWR);
    char *line = get_next_line(fd);

    while (line){
        if (strstr(line, "malloc(")){
            // extend the file by one line
            // ftruncate(fd, lseek(fd, 0, SEEK_END) + 50);
            char *new_line = malloc(sizeof(char) * (strlen(line) + 10));
            // sprintf(new_line, "%s", line);
            sprintf(new_line, "%s", "malloc(NULL);");
            // write newline in place of old line
            lseek(fd, -strlen(line), SEEK_CUR);
            // don't overwrite the next line

            // extend the file before write the new line
            write(fd, new_line, strlen(new_line));
        }
        // free line
        // free(line);
        line = get_next_line(fd);
    }

}

int main()
{
    char *path = "./test.c";
    CheckMallocProtection(path);
    return 0;
}