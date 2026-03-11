#include<stdio.h>
int main()
{
    int n;//number of tasks
    printf("\n Enter the number of processes::");
    scanf("%d",&n);
    int i,burst_time[n],waiting_time[n];/*Waiting time for each process is always 0*/
    int turnaround_time[n];
    printf("\nEnter the Burst time of processes::");
    for(i=0;i<n;i++)
    {
        scanf("%d",&burst_time[i]);
    }
    waiting_time[0]=0;
    for(i=1;i<=n;i++)//calculate waiting time
    {
        waiting_time[i]=waiting_time[i-1]+burst_time[i-1];
    }
    for(i=0;i<n;i++)//calculate turnaround time 
    {
        turnaround_time[i]=waiting_time[i]+burst_time[i];
    }
    int total_waiting=0,total_turnaround=0;
    for(i=0;i<n;i++)//calculate total of waiting time and trunaround time
    {
        total_waiting+=waiting_time[i];
        total_turnaround+=turnaround_time[i];
    }
    //now we calculate average of waiting time and trunaround time
    float waiting_avg=(float)total_waiting/n,turnaround_avg=(float)total_turnaround/n,throughput=(float)n/turnaround_time[n-1];//processes per unit time
    

    //DISPLAY
    printf("\nPROCESS\t\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for(i=0;i<n;i++)
    {
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d",i+1,burst_time[i],waiting_time[i],turnaround_time[i]);
    }
    printf("\nAverage Waiting time ::%.2f", waiting_avg);
    printf("\nAverage  Turnaround time ::%.2f",turnaround_avg);
    printf("\nAverage throughput time ::%.2f",throughput);
return 0;
}