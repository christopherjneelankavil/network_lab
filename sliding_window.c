#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void go_back_n();
void selective_repeat();
void stop_and_wait();

int main(){
    int choice;
    printf("Enter your choice: \n");
    do{
        printf("1 Go Back N\n2 Selective Repeat\n3 Stop and Wait\n4 Exit\n");
        scanf("%d",&choice);

        switch(choice){
            case 1 : go_back_n();
                     break;
            case 2 : selective_repeat();
                     break;
            case 3 : stop_and_wait();
                     break;
            case 4 : printf("Exiting...\n");
                     break;
            default: break;
        }
    }while(choice != 4);
    return 0;
}

void go_back_n(){
    int frames,window_size;
    printf("Enter the no.of frames : ");
    scanf("%d",&frames);
    printf("\nEnter the window size: ");
    scanf("%d",&window_size);

    int start_count = 0;
    while(1){
        for(int i = 0; i < window_size; i++){
            if(start_count == frames){
                return;
            }
            printf("Packet sent : %d\n",start_count+1);
            start_count++;
        }
        if(start_count == frames){
            return;
        }

        int ack = rand() % window_size;
        ack = (start_count - window_size) + ack;
        printf("\nLast acknowledgement received for %d\n",ack);
        start_count = ack;
    }
}

void selective_repeat(){

    int frames,window_size;
    printf("Enter the no.of frames : ");
    scanf("%d",&frames);
    printf("\nEnter the window size: ");
    scanf("%d",&window_size);
    int start_count = 0;
    while(1){
        for(int i = 0; i < window_size; i++){
            if(start_count == frames){
                return;
            }
            printf("Packet sent : %d\n",start_count+1);
            start_count++;
        }

        int no_ack = rand() % window_size;
        no_ack = (start_count - window_size) + no_ack;
        if(no_ack < 0){
            no_ack = 0;
        }
        printf("No acknowledment received for : %d\n",no_ack);
        printf("Retransmitting...\nAcknowledgement received for %d\n",no_ack);
    }
}

void stop_and_wait(){
    int frames;
    printf("Enter the no.of frames : ");
    scanf("%d",&frames);

    for(int i = 0; i < frames; i++){
        printf("Packet sent %d\n",i+1);
        if(rand() % 2 == 1){
            printf("Acknowledment received for %d\n",i+1);
        }else{
            printf("No acknowledment received for %d\nWaiting...\n",i+1);
            i--;
            sleep(3);
        }
    }
}