#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES] = {3, 3, 2};

int maximum[MAX_PROCESSES][MAX_RESOURCES] =
{
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int allocation[MAX_PROCESSES][MAX_RESOURCES] =
{
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int need[MAX_PROCESSES][MAX_RESOURCES];

void calculateNeed()
{
    int i, j;

    for(i = 0; i < MAX_PROCESSES; i++)
    {
        for(j = 0; j < MAX_RESOURCES; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

int isSafe()
{
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int safeSequence[MAX_PROCESSES];
    int count = 0;
    int i, j;

    for(i = 0; i < MAX_RESOURCES; i++)
        work[i] = available[i];

    while(count < MAX_PROCESSES)
    {
        int found = 0;

        for(i = 0; i < MAX_PROCESSES; i++)
        {
            if(finish[i] == 0)
            {
                for(j = 0; j < MAX_RESOURCES; j++)
                {
                    if(need[i][j] > work[j])
                        break;
                }

                if(j == MAX_RESOURCES)
                {
                    for(j = 0; j < MAX_RESOURCES; j++)
                        work[j] += allocation[i][j];

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            return 0;
    }

    printf("\nSafe Sequence: ");

    for(i = 0; i < MAX_PROCESSES; i++)
        printf("P%d ", safeSequence[i]);

    printf("\n");

    return 1;
}

int requestResources(int process, int request[])
{
    int i;

    for(i = 0; i < MAX_RESOURCES; i++)
    {
        if(request[i] > need[process][i])
        {
            printf("Error: Request exceeds Need.\n");
            return 0;
        }

        if(request[i] > available[i])
        {
            printf("Resources are not available.\n");
            return 0;
        }
    }

    for(i = 0; i < MAX_RESOURCES; i++)
    {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if(isSafe())
    {
        return 1;
    }
    else
    {
        for(i = 0; i < MAX_RESOURCES; i++)
        {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }

        return 0;
    }
}

int main()
{
    int process;
    int request[MAX_RESOURCES];
    int i, j;

    calculateNeed();

    printf("Need Matrix:\n");

    for(i = 0; i < MAX_PROCESSES; i++)
    {
        printf("P%d : ", i);

        for(j = 0; j < MAX_RESOURCES; j++)
        {
            printf("%d ", need[i][j]);
        }

        printf("\n");
    }

    printf("\nEnter Process Number (0-4): ");
    scanf("%d", &process);

    printf("Enter Resource Request (3 values): ");

    for(i = 0; i < MAX_RESOURCES; i++)
        scanf("%d", &request[i]);

    if(requestResources(process, request))
        printf("\nRequest Granted. System is in Safe State.\n");
    else
        printf("\nRequest Denied. System is NOT in Safe State.\n");

    return 0;
}
