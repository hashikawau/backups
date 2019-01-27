

#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BACKLOG 3
#define SERVICE_PORT 8888

int main()
{
    int s;
    int t;
    struct sockaddr_in sa;
    struct sockaddr_in ca;
    socklen_t calen;
    
    memset((char*)&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons( SERVICE_PORT );
    sa.sin_addr.s_addr = htonl( INADDR_ANY );
    
    if((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        return 1;
    
    if(bind(s,(const struct sockaddr*)&sa,sizeof(sa)) == -1){
        close(s);
        return 1;
    }
    if(listen(s,BACKLOG) == -1){
        close(s);
        return 1;
    }
    while(1){
        
        calen = sizeof(ca);
        if((t = accept(s,(struct sockaddr*)&ca, &calen)) == -1){
            close(s);
            return 1;
        }
        
        send(t, "Hello\r\n", 7, 0);
        close(t);
    }
    close(s);
    return 0;
}

