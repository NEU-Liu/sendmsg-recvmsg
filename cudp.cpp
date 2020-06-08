#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<iostream>
#include<string>

using namespace std;

int main()
{
    int sockfd=::socket(AF_INET,SOCK_DGRAM,0);
    uint16_t port = 1324;
    const char * ip = "127.0.0.1";
    struct sockaddr_in addr;
    addr.sin_family =AF_INET;
    addr.sin_port =htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    while(1){
        cout << "请输入要发送的信息:" << endl;
        string buffer;
        getline(cin,buffer);
        if(buffer == "Q" || buffer =="q"){
            break;
        }
        struct iovec msg_iov;
        msg_iov.iov_base = (void *) buffer.data();
        msg_iov.iov_len = buffer.length();
        msghdr msg;
        msg.msg_name = &addr;
        msg.msg_namelen = sizeof(addr);
        msg.msg_iov = &msg_iov;
        msg.msg_iovlen = 1;
        msg.msg_control = NULL;
        msg.msg_controllen = 0;
        msg.msg_flags = 0;
        sendmsg(sockfd,&msg,0);
    }
    ::close(sockfd);
}
