#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct Message{
    long type;
    int data;
};

int main(int argc, char const *argv[])
{
    int msgid = msgget(IPC_PRIVATE,IPC_CREAT|0666);
    if(msgid ==-1){
        std::cerr <<"failed to create message queue"<< std::endl;
        return 1;
    }

    pid_t pid = fork();
    if(pid == -1){
        std::cerr << "failede to create child process" << std::endl;
        return 1;
    }

    if(pid == 0){
        Message message;
        message.type = 1;
        message.data = 42;
        if(msgsnd(msgid ,&message,sizeof(message.data),0) == -1){
            std::cerr <<"failed to send message in child process" << std::endl;
            return 1;
        }else{
            Message messafe;
            if(msgrcv(msgid,&message,sizeof(message.data),1,0) == -1){
                std::cerr<<"failed to cerate message in parent process"<<std::endl;
                return 1;
            }
            std::cout<<"parent process:"<<message.data<<std::endl;
            if(msgctl(msgid,IPC_RMID,nullptr)==-1){
                std::cerr<<"failed to delete message queue"<<std::endl;
                return 1;
            }
        }
        return 0;
    }
    return 0;
}
