// Priority Scheduling (non-preemptive)
#include <stdio.h>

struct process
{
    int id;       // Process ID (P1, P2, ...)
    int bt;       // Burst time (CPU time needed)
    int wt;       // Waiting time
    int tat;      // Turnaround time
    int priority; // Lower value means higher priority
};

// Waiting time of first process is 0.
// For the rest: wt[i] = wt[i-1] + bt[i-1].
void calculate_waiting_time(struct process p[], int n)
{
    p[0].wt = 0;
    for (int i = 1; i < n; i++)
    {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
    }
}

// Turnaround time is the total time from arrival to completion:
// tat[i] = wt[i] + bt[i]
void calculate_tat(struct process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].wt + p[i].bt;
    }
}

// Sort processes by priority (ascending).
// Example: priority 1 runs before priority 2.
void sort_by_priority(struct process p[], int n)
{
    struct process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].priority > p[j].priority)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void display(struct process p[], int n)
{
    int total_waiting = 0, total_turnaround = 0;
    int total_time = 0; // Sum of all burst times (total CPU execution time)

    printf("\nPROCESS\t\tBURST TIME\tPRIORITY\tWAITING TIME\tTURNAROUND TIME");
    for (int i = 0; i < n; i++)
    {
        total_waiting += p[i].wt;
        total_turnaround += p[i].tat;
        total_time += p[i].bt;

        printf("\nP[%d]\t\t%d\t\t%d\t\t%d\t\t%d",
               p[i].id, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    }

    // Average values are totals divided by number of processes.
    printf("\nAverage Waiting time ::%.2f", (float)total_waiting / n);
    printf("\nAverage  Turnaround time ::%.2f", (float)total_turnaround / n);

    // Throughput = number of completed processes / total execution time.
    // Guard with total_time > 0 to avoid division by zero.
    printf("\nThroughput ::%.2f", total_time > 0 ? (float)n / total_time : 0.0f);
}

int main(void)
{
    int n; // Number of processes
    printf("\n Enter the number of processes::");
    scanf("%d", &n);

    struct process p[n];
    printf("\nEnter the Burst time and priority of processes::");
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        printf("\nProcess %d\n", p[i].id);

        printf("Burst time::");
        scanf("%d", &p[i].bt);

        printf("Priority::");
        scanf("%d", &p[i].priority);
    }

    // Flow:
    // 1) Sort by priority
    // 2) Calculate waiting time
    // 3) Calculate turnaround time
    // 4) Print table and metrics
    sort_by_priority(p, n);
    calculate_waiting_time(p, n);
    calculate_tat(p, n);
    display(p, n);

    return 0;
}
