#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 5000

//main function
void main(){

    struct sockaddr_in serveraddr,newaddr;
    int server_socket_id,new_socket_id;
    char buffer[1024];

    //create server socket
    server_socket_id = socket(PF_INET,SOCK_STREAM,0);
    if(server_socket_id >= 0){
        printf("Socket created successfully\nServer socket id : %d\n",server_socket_id);
    }else{
        printf("Failed to create server socket\n");
        return;
    }

    //values
    serveraddr.sin_family = PF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind
    int bind_result = bind(server_socket_id,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(bind_result == 0){
        printf("Bind success\n");
    }else{
        printf("Bind failed\n");
        return;
    }

    int size = sizeof(newaddr);
    listen(server_socket_id,0);

    new_socket_id = accept(server_socket_id,(struct sockaddr*)&newaddr,&size);
    if(new_socket_id >= 0){
        printf("Client socket created\nId : %d\n",new_socket_id);
    }else{
        printf("Client socket creation failed\n");
        return;
    }

    //receive data
    printf("Receiving data...\n");
    recv(new_socket_id,buffer,sizeof(buffer),0);
    printf("Data received : %s",buffer);

    printf("Receiving data...\n");
    recv(new_socket_id,buffer,sizeof(buffer),0);
    printf("Data received : %s",buffer);

    //close sockets
    close(server_socket_id);
    close(new_socket_id);
    printf("\nAll sockets are closed\nExiting...");

}
