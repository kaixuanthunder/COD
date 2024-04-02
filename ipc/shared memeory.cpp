#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int shmid = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT|0666);
    if(shmid == -1){
        std::cerr<<"failed to create shared meomery"<<std::endl;
        return 1;
    }

    int * sharedData = (int*)shmat(shmid,nullptr,0);
    if(sharedData == (int*)-1){
        std::cerr<<"failed to attach shared memory"<<std::endl;
        return 1;
    }

    *sharedData = 42;
     
    pid_t pid = fork();
    if(pid == -1)
    {
        std::cerr<<"failed to create child process"<<std::endl;
        return 1;
    }

    if(pid == 0){
        std::cout <<"child process:"<< *sharedData<<std::endl;
        if(shmdt(sharedData) == -1){
            std::cerr<<"failed to detach shared memory in child process"<<std::endl;
            return 1;
        }
        else{
            wait(nullptr);
            if (shmdt(sharedData) == -1) {
            std::cerr << "Failed to detach shared memory in parent process" << std::endl;
            return 1;
            }
        if (shmctl(shmid, IPC_RMID, nullptr) == -1) {
            std::cerr << "Failed to delete shared memory" << std::endl;
            return 1;
        }}}
    return 0;
}
