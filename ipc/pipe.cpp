#include <iostream>
#include <unistd.h>

int main()
{
    int fd[2];
    pid_t pid;
    char buff[256];

    if(pipe(fd)<0)
    std::cerr<<"创建管道失败"<<std::endl;
    if((pid =fork())<0)
    std::cerr<<"fork error"<<std::endl;
    else if(pid>0)
    {
        close(fd[0]);
        write(fd[1],"hello world\n",12);
        close(fd[0]);

    }
    else
    {
        close(fd[1]);
        read(fd[0],buff,20);
        std::cout<<"process:"<<buff<<std::endl;
    }

    return 0;

}