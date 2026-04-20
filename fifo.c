//Use for decide that which task is neglated to gave memory to others this use basicaly for neglactesd the first task fist in
#include<stdio.h>
int main()
{
    int incoming_stream[]={7,0,1,2,0,3,0,4,2,8};
    int frames=3;
    int n=sizeof(incoming_stream)/sizeof(incoming_stream[0]);
    int temp[frames];
    int pagefault=0;
    int m,n_iter,s,current_oldest=0;

    for(m=0;m<frames;m++){
        temp[m]=-1;
    }
    printf("Incoming \t Frame 1 \t Frame 2\t Frame 3\n");
    for(m=0;m<n;m++){
        s=0;
        for(n_iter=0;n_iter<frames;n_iter++){
            if(incoming_stream[m] == temp[n_iter]){
                s=1;
                break;
            }
        }
        if(s == 0){
        temp[current_oldest] =incoming_stream[m];
        current_oldest=(current_oldest + 1 ) % frames;
        pagefault++;
        }
        printf("%d\t\t",incoming_stream[m]);
        for(n_iter=0;n_iter<frames;n_iter++){
            if(temp[n_iter] != 1){
                printf("%d\t\t",temp[n_iter]);
            }
            else{
                printf("-\t\t");
            }
        }
    printf("\n");
    }
    printf("\nTotal page Faults : %d\n",pagefault);
    return 0;
}