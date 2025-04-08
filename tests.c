#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 5000

int main(){
    struct sockaddr_in serveraddr,newaddr;
    int server_socket_id;
    char buffer[1024];

    //socket
    server_socket_id = socket(AF_INET,SOCK_DGRAM,0);
    if(server_socket_id >= 0){
        printf("Success\n");
    }else{
        printf("Failed\n");
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind
    int bind_result = bind(server_socket_id,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(bind_result >= 0){
        printf("Success\n");
    }else{
        printf("Failed\n");
    }

    int size = sizeof(newaddr);
    recvfrom(server_socket_id,buffer,sizeof(buffer),0,(struct sockaddr*)&newaddr,&size);
    printf("%s",buffer);

    close(server_socket_id);
    return 0;
}
