

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>





int main()
{
    
    char serverName[] = "192.168.1.2";
    
    sockaddr_in serverAddr;
    sockaddr& serverAddrCast = reinterpret_cast<sockaddr&>(serverAddr);
    
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    
    inet_pton(AF_INET, serverName, &serverAddr.sin_addr);
    serverAddr.sin_port = htons(13);
    
    std::cout << ((serverAddr.sin_addr.s_addr) &0xFF000000);
    std::cout << " ";
//    std::cout << serverAddr.sin_addr.s_addr &0xFF0000;
//    std::cout << " ";
//    std::cout << serverAddr.sin_addr.s_addr &0xFF00;
//    std::cout << " ";
//    std::cout << serverAddr.sin_addr.s_addr &0xFF;
    std::cout << std::endl;
    std::cout << connect(sockFd, &serverAddrCast, sizeof(serverAddr));
    std::cout << std::endl;
    
    shutdown(sockFd, 2);
    close(sockFd);
    
    
    return 0;
}

