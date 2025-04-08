#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#define PORT 5000

void main(){

    struct sockaddr_in serveraddr;
    int client_socket_id;
    char buffer[1024];

    //create socket
    client_socket_id = socket(PF_INET,SOCK_STREAM,0);
    if(client_socket_id >= 0){
        printf("Client socket created successfully\nClient socket id : %d\n",client_socket_id);
    }else{
        printf("Client socket creation failed\n");
        printf("Exiting...\n");
        return;
    }

    //connect 
    serveraddr.sin_family = PF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int connection_result = connect(client_socket_id,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(connection_result >= 0){
        printf("Connected to server successfully \n");
    }else{
        printf("Failed to connect to server\nExiting...\n");
        return;
    }

    printf("Enter the user name : ");
    scanf("%s",buffer);
    printf("Sending data to server...\n");
    send(client_socket_id,buffer,sizeof(buffer),0);
    printf("Sent data to server\nWaiting for reply...\n");
    recv(client_socket_id,buffer,sizeof(buffer),0);

    if(strcmp(buffer,"Enter password") == 0){
        printf("\nEnter password : ");
        scanf("%s",buffer);
        printf("Sending password...\n");
        send(client_socket_id,buffer,sizeof(buffer),0);
        printf("Sent data to server\nWaiting for reply...\n");
        recv(client_socket_id,buffer,sizeof(buffer),0);

        if(strcmp(buffer,"Access granted") == 0){
            printf("\nAccess granted\n");
        }else{
            printf("\nAccess denied\n");
        }
    }else{
        printf("\nInvalid username\n");
        printf("Exiting...\n");
        return;
    }

    close(client_socket_id);
    printf("Closed client socket\nExiting from program...\n");
}