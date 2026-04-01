// Shortest Job First scheduling (non-preemptive)
#include<stdio.h>

int main(void)
{
    int n;
    printf("\nEnter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("\nInvalid number of processes.\n");
        return 1;
    }

    int process[n], burst_time[n], waiting_time[n], turnaround_time[n];
    printf("\nEnter the burst time of processes:\n");
    for (int i = 0; i < n; i++)
    {
        process[i] = i + 1;
        printf("P[%d]: ", process[i]);
        if (scanf("%d", &burst_time[i]) != 1 || burst_time[i] < 0)
        {
            printf("\nInvalid burst time.\n");
            return 1;
        }
    }

    // Sort by burst time while keeping process ids aligned.
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (burst_time[i] > burst_time[j])
            {
                int temp_bt = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp_bt;

                int temp_pid = process[i];
                process[i] = process[j];
                process[j] = temp_pid;
            }
        }
    }

    waiting_time[0] = 0;
    for (int i = 1; i < n; i++)
    {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
    }

    int total_waiting = 0, total_turnaround = 0;
    for (int i = 0; i < n; i++)
    {
        turnaround_time[i] = waiting_time[i] + burst_time[i];
        total_waiting += waiting_time[i];
        total_turnaround += turnaround_time[i];
    }

    float waiting_avg = (float)total_waiting / n;
    float turnaround_avg = (float)total_turnaround / n;
    int total_time = turnaround_time[n - 1];
    float throughput = total_time > 0 ? (float)n / total_time : 0.0f;

    printf("\nPROCESS\t\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for (int i = 0; i < n; i++)
    {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\n",process[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", waiting_avg);
    printf("Average Turnaround Time: %.2f\n", turnaround_avg);
    printf("Throughput: %.2f\n", throughput);
    return 0;
}
