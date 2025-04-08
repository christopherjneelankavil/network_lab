#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 5000

void main(){

    struct sockaddr_in serveraddr,newaddr;
    int server_socket_id;
    char buffer[1024];

    server_socket_id = socket(AF_INET,SOCK_DGRAM,0);
    if(server_socket_id >= 0){
        printf("Server socket created\nId : %d\n",server_socket_id);
    }else{
        printf("Failed to create socket\n");
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(server_socket_id,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0){
        printf("Bind failed");
    }else{
        printf("Bind success\n");
    }

    int size = sizeof(newaddr);
    recvfrom(server_socket_id,buffer,sizeof(buffer),0,(struct sockaddr*)&newaddr,&size);
    printf("%s",buffer);

    close(server_socket_id);


}