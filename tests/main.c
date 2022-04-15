



// create a command line argument parser

int parser(int argc, char **argv)
{
    // loop through the arguments

}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc - 1; i++)
    {
        if (argv[i] == "--CheckMem=")
        {
            checkMemoryLeaks(argv[i + 1]);
        }
         
    }
    return 0;

}