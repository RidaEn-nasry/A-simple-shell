

// create a function to check for memory errors
// The function will take the path of the executable as an argument.


#include "../includes/tests.h"




void    MemoryLeaks(char *path)
{
    int fd = open(path, O_RDONLY);
    int malloc_calls = 0;
    char *line = get_next_line(fd);
    // read line by line and for every "malloc()" call, check if there's a "free()" call
    // if there's a "free()" call, check if the pointer is the same as the one that was malloc()ed
    while (line)
    {
        if (strstr(line, "malloc"))
        {
            // incremnet the number of malloc() calls
            malloc_calls++;
            // cut what's before the "= malloc(" and store it in in a new string.


        }
    }


}