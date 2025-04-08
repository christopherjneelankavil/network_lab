#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 5000

int main(){
    struct sockaddr_in serveraddr;
    int client_socket_id;
    char buffer[1024];

    //socket
    client_socket_id = socket(AF_INET,SOCK_DGRAM,0);
    if(client_socket_id >= 0){
        printf("Success\n");
    }else{
        printf("Failed\n");
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Data: ");
    scanf("%s",buffer);
    sendto(client_socket_id,buffer,sizeof(buffer),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

    close(client_socket_id);
    return 0;
}
