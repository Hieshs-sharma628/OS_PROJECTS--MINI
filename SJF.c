#include<stdio.h>
int main()
{
    int n;//number of tasks
    printf("\n Enter the number of processes::");
    scanf("%d",&n);
    int i,j,process[n],burst_time[n],waiting_time[n];/*Waiting time for each process is always 0*/
    int turnaround_time[n];
    printf("\nEnter the Burst time of processes::");
    for(i=0;i<n;i++)
    {
        scanf("%d",&burst_time[i]);
        process[i]=i+1;
    }
    //sort process by burst time
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(burst_time[i]>burst_time[j])
            {
                burst_time[i]=burst_time[i]+burst_time[j];
                burst_time[j]=burst_time[i]-burst_time[j];
                burst_time[i]=burst_time[i]-burst_time[j];

                process[i]=process[i]+process[j];
                process[j]=process[i]-process[j];
                process[i]=process[i]-process[j];
            }
        }
    }
    waiting_time[0]=0;
    for(i=1;i<=n;i++)//calculate waiting time
    {   
        waiting_time[i]=0;
        for(j=0;j<i;j++)
        {
        waiting_time[i]=waiting_time[i-1]+burst_time[i-1];
        }
    }
    int total_waiting=0;
    for(i=0;i<n;i++)//calculate total of waiting time
    {
        total_waiting+=waiting_time[i];
    }
    //now we calculate average of waiting time
    float waiting_avg=(float)total_waiting/n;
    

    //DISPLAY
    printf("\nPROCESS\t\tBURST TIME\tWAITING TIME");
    for(i=0;i<n;i++)
    {
        printf("\nP[%d]\t\t%d\t\t%d",i+1,burst_time[i],waiting_time[i]);
    }
    printf("\nAverage Waiting time ::%.2f", waiting_avg);
return 0;
}