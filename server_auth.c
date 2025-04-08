#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#define PORT 5000

//main function
void main(){
    struct sockaddr_in serveraddr,newaddr;
    int server_socket_id,new_socket_id;
    char buffer[1024];

    //create socket
    server_socket_id = socket(PF_INET,SOCK_STREAM,0);
    if(server_socket_id >= 0){
        printf("Server socket created successfully\n");
    }else{
        printf("Server socket creation failed\nExiting...\n");
        return;
    }

    //bind
    serveraddr.sin_family = PF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int bind_result = bind(server_socket_id,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(bind_result >= 0){
        printf("Bind success\n");
    }else{
        printf("Bind failed \nExiting...\n");
    }

    //listen for incoming transmissions
    listen(server_socket_id,1); //listen for only one client

    int size = sizeof(newaddr);
    new_socket_id = accept(server_socket_id,(struct sockaddr*)&newaddr,&size);
    if(new_socket_id >= 0){
        printf("Connection successful\n");
    }else{
        printf("Failed to accept connection\nExiting...\n");
    }

    //receiving data
    recv(new_socket_id,buffer,sizeof(buffer),0);
    if(strcmp(buffer,"admin") == 0){
        printf("Username is correct\nRequesting password...\n");
        send(new_socket_id,"Enter password",sizeof("Enter password"),0);
        printf("Waiting for password...\n");

        //password
        recv(new_socket_id,buffer,sizeof(buffer),0);
        if(strcmp(buffer,"password") == 0){
            printf("Password is correct\nGranting access...\n");
            send(new_socket_id,"Access granted",sizeof("Access granted"),0);
        }else{
            printf("Password incorrect\n");
            send(new_socket_id,"Invalid credentials",sizeof("Invalid credentials"),0);
            printf("Exiting...\n");
        }
    }else{
        printf("Invalid username\n");
        send(new_socket_id,"Invalid username",sizeof("Invalid username"),0);
        printf("Exiting...\n");
    }

    printf("Closing all sockets...");
    close(server_socket_id);
    close(new_socket_id);
    printf("Closed all sockets\nExiting from program..\n");

}
