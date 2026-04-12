/*
    ===== BANKER'S ALGORITHM =====
    This program checks if the system is safe from deadlock using the Banker's Algorithm.

    SIMPLE EXPLANATION:
    - Think of it like a banker who loans money to customers
    - The banker checks: "Can I safely give resources to this process?"
    - If ALL processes can be satisfied, the system is SAFE
    - If even one process gets stuck, the system is UNSAFE
*/

#include <stdio.h>

int main()
{
    // STEP 1: Get input from user
    int numberOfProcesses, numberOfResources;

    printf("===== BANKER'S ALGORITHM =====\n\n");
    printf("Enter the number of processes: ");
    scanf("%d", &numberOfProcesses);

    printf("Enter the number of resources: ");
    scanf("%d", &numberOfResources);

    // STEP 2: Create arrays to store data
    // allocated[i][j] = resources already given to process i
    int allocated[numberOfProcesses][numberOfResources];

    // maximum[i][j] = total resources process i needs
    int maximum[numberOfProcesses][numberOfResources];

    // needed[i][j] = resources still needed (maximum - allocated)
    int needed[numberOfProcesses][numberOfResources];

    // available[j] = free resources available system
    int available[numberOfResources];

    // work[j] = helper array for algorithm (copy of available)
    int work[numberOfResources];

    // isFinished[i] = has process i finished? (0=NO, 1=YES)
    int isFinished[numberOfProcesses];

    // safeSequence[i] = order of safe process execution
    int safeSequence[numberOfProcesses];

    // resourcesAfter[i][j] = available resources after process i finishes
    int resourcesAfter[numberOfProcesses][numberOfResources];

    // STEP 3: Input available resources
    printf("\n--- Enter Available Resources ---\n");
    for (int j = 0; j < numberOfResources; j++)
    {
        printf("Enter available units of Resource %d: ", j);
        scanf("%d", &available[j]);
    }

    // STEP 4: Input allocated resources for each process
    printf("\n--- Enter Allocated Resources for Each Process ---\n");
    for (int i = 0; i < numberOfProcesses; i++)
    {
        printf("Process P%d:\n", i);
        for (int j = 0; j < numberOfResources; j++)
        {
            printf("  Allocated Resource %d: ", j);
            scanf("%d", &allocated[i][j]);
        }
    }

    // STEP 5: Input maximum resources each process may need
    printf("\n--- Enter Maximum Resources Each Process May Need ---\n");
    for (int i = 0; i < numberOfProcesses; i++)
    {
        printf("Process P%d:\n", i);
        for (int j = 0; j < numberOfResources; j++)
        {
            printf("  Maximum Resource %d: ", j);
            scanf("%d", &maximum[i][j]);
        }
    }

    // STEP 6: Calculate what each process still needs
    printf("\n--- Calculating Remaining Needs ---\n");
    for (int i = 0; i < numberOfProcesses; i++)
    {
        for (int j = 0; j < numberOfResources; j++)
        {
            needed[i][j] = maximum[i][j] - allocated[i][j];

            // Check if input is valid
            if (needed[i][j] < 0)
            {
                printf("\nERROR: Process P%d has invalid data!\n", i);
                printf("ERROR: Max need cannot be less than allocated!\n");
                return 1;
            }
        }
    }

    // STEP 7: Set up work array (copy of available)
    for (int j = 0; j < numberOfResources; j++)
    {
        work[j] = available[j];
    }

    // Initialize all processes as not finished
    for (int i = 0; i < numberOfProcesses; i++)
    {
        isFinished[i] = 0; // 0 means not finished yet
    }

    // STEP 8: Run the Banker's Algorithm
    printf("\n--- Running Banker's Algorithm ---\n");
    int processesComplete = 0;

    while (processesComplete < numberOfProcesses)
    {
        int foundSafeProcess = 0; // Did we find a process that can run?

        // Check each proces
        for (int i = 0; i < numberOfProcesses; i++)
        {
            // Skip if process already finished
            if (isFinished[i] == 1)
            {
                continue;
            }

            // Check if this process can get all remaining resources it needs
            int canProcessRun = 1; // Assume YES
            for (int j = 0; j < numberOfResources; j++)
            {
                if (needed[i][j] > work[j])
                {
                    // Process needs more than available
                    canProcessRun = 0; // Can't run
                    break;
                }
            }

            // If process can run, give it resources and finish it
            if (canProcessRun == 1)
            {
                printf("Process P%d can run!\n", i);

                // Give all resources to process and get them back
                for (int j = 0; j < numberOfResources; j++)
                {
                    work[j] += allocated[i][j]; // Get resources back
                    resourcesAfter[processesComplete][j] = work[j];
                }

                // Record this process in safe sequence
                safeSequence[processesComplete] = i;

                // Mark process as finished
                isFinished[i] = 1;

                processesComplete++;
                foundSafeProcess = 1;
            }
        }

        // If no safe process found, system is unsafe
        if (foundSafeProcess == 0)
        {
            break;
        }
    }

    // STEP 9: Print Results
    printf("\n\n===== RESULTS =====\n");
    printf("\nInitial Available Resources: ");
    for (int j = 0; j < numberOfResources; j++)
    {
        printf("[R%d: %d] ", j, available[j]);
    }

    printf("\n\n--- Process Details ---\n");
    printf("Process | Allocated | Maximum | Needed\n");
    printf("--------|-----------|---------|-------\n");
    for (int i = 0; i < numberOfProcesses; i++)
    {
        printf("P%d      | ", i);
        for (int j = 0; j < numberOfResources; j++)
        {
            printf("%d ", allocated[i][j]);
        }
        printf("| ");
        for (int j = 0; j < numberOfResources; j++)
        {
            printf("%d ", maximum[i][j]);
        }
        printf("| ");
        for (int j = 0; j < numberOfResources; j++)
        {
            printf("%d ", needed[i][j]);
        }
        printf("\n");
    }

    // Check if all processes finished safely
    if (processesComplete == numberOfProcesses)
    {
        printf("\n✓ System is SAFE!\n");
        printf("✓ Safe Execution Sequence: ");
        for (int i = 0; i < numberOfProcesses; i++)
        {
            printf("P%d", safeSequence[i]);
            if (i != numberOfProcesses - 1)
            {
                printf(" -> ");
            }
        }
        printf("\n");

        printf("\nResources available after each process completes:\n");
        for (int i = 0; i < numberOfProcesses; i++)
        {
            printf("After P%d finishes: ", safeSequence[i]);
            for (int j = 0; j < numberOfResources; j++)
            {
                printf("[R%d: %d] ", j, resourcesAfter[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("\n✗ System is UNSAFE!\n");
        printf("✗ Could not find a safe sequence for all processes.\n");
        printf("✗ Deadlock is possible!\n");
    }

    return 0;
}
