
// start from here 
#include "tests.h"



int main(int argc, char **argv)
{

    for (int i = 1; i < argc - 1; i++)
    {
         if (argv[i] == "--help")
        {
             printf("options: \n");
            printf("--help: print this help\n");
            printf("--CheckMem=: check memory errors\n");
            
        }
        else if (argv[i] == "--CheckMem=")
        {
            checkMemoryLeaks(argv[i + 1]);
        }
    }
    return 0;
}