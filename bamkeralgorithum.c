#include <stdio.h>

#define RESOURCES 3

int main(void)
{
    int n, i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int alloc[n][RESOURCES];
    int max[n][RESOURCES];
    int remain[n][RESOURCES];          /* remain = need = max - allocation */
    int available[RESOURCES];
    int work[RESOURCES];
    int finish[n];
    int safeSeq[n];
    int availableAfter[n][RESOURCES];  /* available list after each safe step */

    for (j = 0; j < RESOURCES; j++) {
        printf("Enter available units for R%d: ", j);
        scanf("%d", &available[j]);
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < RESOURCES; j++) {
            printf("Enter allocation of P[%d] for R%d: ", i, j);
            scanf("%d", &alloc[i][j]);
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < RESOURCES; j++) {
            printf("Enter max need of P[%d] for R%d: ", i, j);
            scanf("%d", &max[i][j]);
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < RESOURCES; j++) {
            remain[i][j] = max[i][j] - alloc[i][j];
            if (remain[i][j] < 0) {
                printf("\nInvalid input: max need cannot be less than allocation.\n");
                return 1;
            }
        }
    }

    for (j = 0; j < RESOURCES; j++) {
        work[j] = available[j];
    }
    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int count = 0;
    while (count < n) {
        int found = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canRun = 1;
                for (j = 0; j < RESOURCES; j++) {
                    if (remain[i][j] > work[j]) {
                        canRun = 0;
                        break;
                    }
                }

                if (canRun) {
                    for (j = 0; j < RESOURCES; j++) {
                        work[j] += alloc[i][j];
                        availableAfter[count][j] = work[j];
                    }
                    safeSeq[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if (!found) {
            break;
        }
    }

    printf("\nInitial Available: [%d %d %d]\n", available[0], available[1], available[2]);
    printf("\nProcess   Allocation   MaxNeed      Remaining(Need)\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]      [%d %d %d]     [%d %d %d]     [%d %d %d]\n",
               i,
               alloc[i][0], alloc[i][1], alloc[i][2],
               max[i][0], max[i][1], max[i][2],
               remain[i][0], remain[i][1], remain[i][2]);
    }

    if (count == n) {
        printf("\nSystem is in a SAFE state.\n");
        printf("Safe sequence: ");
        for (i = 0; i < n; i++) {
            printf("P[%d]", safeSeq[i]);
            if (i != n - 1) {
                printf(" -> ");
            }
        }
        printf("\n");

        printf("\nAvailable list after each completed process:\n");
        for (i = 0; i < n; i++) {
            printf("After P[%d]: [%d %d %d]\n",
                   safeSeq[i],
                   availableAfter[i][0], availableAfter[i][1], availableAfter[i][2]);
        }
    } else {
        printf("\nSystem is in an UNSAFE state (no full safe sequence found).\n");
        printf("Processes completed before stop: %d out of %d\n", count, n);
    }

    return 0;
}
