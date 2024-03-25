#include <iostream>
#include <unistd.h>
#include <sys/types.h>
int main(int argc, char const *argv[])
{
    
    pid_t pid;
    pid = fork();

    if(pid ==-1)
    {
        std::cerr << "failed to fork " << std::endl;
        return 1;

    }
    if(pid == 0)
    {
        std::cout<<"this is child process pid ="<< pid <<std::endl;
    }
    else{
        std::cout<<"this is parent process pid ="<< pid <<std::endl;
    }


    return 0;
}
