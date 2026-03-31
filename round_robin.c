//round robin scheduling
#include<stdio.h>
 //Calculate the average time
void RoundRobin(int bt[],int n,int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    
    // Find waiting time of all processes
    //Store remaining burst time
    int rem_bt[n],i;
    for ( i = 0 ; i < n ; i++){
        rem_bt[i] = bt[i];
    }
        int ct = 0; // Current time
        while (1)
        {
        int done = 1;
        for ( i = 0 ; i < n; i++)
        {
    
        if (rem_bt[i] > 0)
        {
        done = 0; // pending process
        
        if (rem_bt[i] > quantum)
        {
        
        ct += quantum;
        
        
        rem_bt[i] -= quantum;
        }
        else
        {
        ct = ct + rem_bt[i];
    
        // Waiting time = current time- time
        // used in this process
        wt[i] = ct - bt[i];
        //process is fully executed
        rem_bt[i] = 0;
        }
    }
}
    
    
    if (done == 1)
    break;
    }
    
    //Find turn around time for all processes
    for (int i = 0; i < n ; i++){
    tat[i] = bt[i] + wt[i];
    total_wt += wt[i];
    total_tat += tat[i];
    }
    
    
    // Calculate average waiting and turnaround times
        float avg_wt = (float)total_wt / n;
        float avg_tat = (float)total_tat / n;
    
        // Display process details
        printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
        printf("-------------------------------------------------\n");
        for (int i = 0; i < n; i++) {
            printf("%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
        }
    
        printf("\nAverage Waiting Time: %.2f\n", avg_wt);
        printf("Average Turnaround Time: %.2f\n", avg_tat);
    }
    
    
 
int main()
{
    int n;
 
    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
 
    int bt[n];
 
    // Input burst time for each process
    printf("Enter Burst Time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
    }
    
    int time_quantum;
    printf("Enter the time quantum:: ");
    scanf("%d", &time_quantum);
    
    // Call FCFS scheduling function
    RoundRobin(bt,n,time_quantum);
 
    return 0;
}