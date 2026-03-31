#include<stdio.h>
int main()
{
    int n,i,j;
    printf("Enter the number of processes::");
    scanf("%d",&n);
    int alloc[n][3],max[n][3],ava[n][3],remain[n][3];
    //given the avilable time
    ava[0][0]=3;
    ava[0][1]=3;
    ava[0][2]=0;

    for(i=0;i<n;i++){//input for alloacation
        for(j=0;j<3;j++){
            printf("\nEnter the allocation of process %d ::",i);
            scanf("%d",&alloc[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<n;i++){//input for max neeed
        for(j=0;j<3;j++){
            printf("\nEnter the maxneed of process %d ::",i);
            scanf("%d",&max[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<n;i++){//calculate remaining time
        for(j=0;j<3;j++){
            remain[i][j]=max[i][j]-alloc[i][j];
        }
    }
    for(i=0;i<n;i++){//calculate available time
        for(j=0;j<3;j++){
            if(ava[i][j] >= remain[i][j]){
                ava[i][j]=ava[i][j]+alloc[i][j];
            }
        }
    }
    
    //DISPLAY
    printf("\nProcesses\tAllocation\tMaxneed\t\tAvailable\tRemaining\n");
    
    for(i=0;i<n;i++){
        printf("P[%d]",i);
        for(j=0;j<3;j++){
            printf("\t\t %d \t\t%d \t\t%d \t\t%d\n ",alloc[i][j],max[i][j],ava[i][j],remain[i][j]);
        }
    }
}