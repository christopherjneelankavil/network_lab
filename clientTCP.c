#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 5000

void main(){

    struct sockaddr_in serveraddr;
    int client_socket_id;
    char buffer[1024];

    //create client socket
    client_socket_id = socket(PF_INET,SOCK_STREAM,0);
    if(client_socket_id >= 0){
        printf("Client socket created successfully\nClient socket id : %d\n",client_socket_id);
    }else{
        printf("Client socket is not created\nExiting...");
        return;
    }

    //values
    serveraddr.sin_family = PF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //connect to server
    int connection_result = connect(client_socket_id,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(connection_result >= 0){
        printf("\nConnected to server successfully\nReady to transfer data\n");
    }else{
        printf("Failed to connect\nExiting...");
        return;
    }

    //read data
    printf("Enter the data to be sent : ");
    scanf("%s",buffer);
    printf("\nData received \nReady to send\n");

    //sending data
    printf("Sending data to server...\n");
    if(send(client_socket_id,buffer,sizeof(buffer),0) < 0){
        printf("Sending failed\nExiting...");
        return;
    }
    printf("Successfully sent data\n");
    printf("Enter the data to be sent : ");
    scanf("%s",buffer);
    printf("Sending data to server...\n");
    if(send(client_socket_id,buffer,sizeof(buffer),0) < 0){
        printf("Sending failed\nExiting...");
        return;
    }
    
    //close sockets
    printf("Closing client socket\n");
    close(client_socket_id);
    printf("Sockets closed\nExiting...");

}