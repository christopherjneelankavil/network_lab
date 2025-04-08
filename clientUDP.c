#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 5000

void main(){
    struct sockaddr_in serveraddr;
    int client_socket_id;
    char buffer[1024];

    client_socket_id = socket(AF_INET,SOCK_DGRAM,0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    printf("Enter the string: ");
    scanf("%s",buffer);

    sendto(client_socket_id,buffer,sizeof(buffer),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    close(client_socket_id);
}