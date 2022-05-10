

#include <stdio.h>
#include "tests.h"


// A function takes path to exec and checks for common memory errors:
//    - memory leaks
//    - bad memory access
//    - using uninitialized memory and undefined values.
//    - double free. and use of freed memory.

void checkMemoryLeaks(char *path)
{
    char command[1024];
    sprintf(command, "valgrind --tool=memcheck --leak-check=full --show-reachable=yes %s", path);
    system(command);
}


