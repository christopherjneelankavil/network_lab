#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void go_back_n();
void selective_repeat();
void stop_and_wait();

int main(){
    int choice;
    do{
        printf("1. Go Back N\n");
        printf("2. Selective Repeat\n");
        printf("3. Stop and Wait\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                go_back_n();
                break;
            case 2:
                selective_repeat();
                break;
            case 3:
                stop_and_wait();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }

    }while(choice != 4);
    return 0;
}

void go_back_n(){
    int frames,window_size;
    printf("Frames : ");
    scanf("%d",&frames);
    printf("\nWindow Size : ");
    scanf("%d",&window_size);

    int start = 0;
    while(1){
        for(int i = 0; i < window_size; i++){
            if(start == frames){
                return;
            }
            printf("Sent %d\n",start + 1);
            start++;
        }
        if(start == frames){
            return;
        }
        int ack = rand() % window_size + 1;
        ack = (start - window_size) + ack;
        start = ack;
        printf("Last ack : %d\n",ack);
    }
}

void selective_repeat(){
    int frames,window_size;
    printf("Frames : ");
    scanf("%d",&frames);
    printf("\nWindow Size : ");
    scanf("%d",&window_size);

    int start = 0;
    while(1){
        for(int i = 0; i < window_size; i++){
            if(start == frames){
                return;
            }
            printf("Sent %d\n",start + 1);
            start++;
        }
        if(start == frames){
            return;
        }
        int ack = rand() % window_size + 1;
        ack = (start - window_size) + ack;
        printf("No ack from %d\nSending again\nAck recv",ack);
    }
}

void stop_and_wait(){
    int frames;
    printf("Frames : ");
    scanf("%d",&frames);
    
    for(int i = 0; i < frames; i++){
        if(rand() % 2 == 1){
            printf("ack recv %d\n",i+1);
        }else{
            printf("No ack recv from %d\n",i+1);
            printf("Waiting...");
            sleep(3);
            i--;
        }
    }
}
