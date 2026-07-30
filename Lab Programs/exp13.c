#include <stdio.h>

#define MAX 20

void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[MAX];

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation\n");
    printf("Process\tSize\tBlock\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[MAX];

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int best = -1;

        for(int j = 0; j < m; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(best == -1 || blockSize[j] < blockSize[best])
                    best = j;
            }
        }

        if(best != -1)
        {
            allocation[i] = best;
            blockSize[best] -= processSize[i];
        }
    }

    printf("\nBest Fit Allocation\n");
    printf("Process\tSize\tBlock\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[MAX];

    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int worst = -1;

        for(int j = 0; j < m; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(worst == -1 || blockSize[j] > blockSize[worst])
                    worst = j;
            }
        }

        if(worst != -1)
        {
            allocation[i] = worst;
            blockSize[worst] -= processSize[i];
        }
    }

    printf("\nWorst Fit Allocation\n");
    printf("Process\tSize\tBlock\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main()
{
    int m, n, choice;
    int block[MAX], process[MAX];
    int temp[MAX];

    printf("Enter Number of Memory Blocks: ");
    scanf("%d", &m);

    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    printf("Enter Memory Block Sizes:\n");
    for(int i = 0; i < m; i++)
        scanf("%d", &block[i]);

    printf("Enter Process Sizes:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &process[i]);

    printf("\n1. First Fit\n");
    printf("2. Best Fit\n");
    printf("3. Worst Fit\n");

    printf("Enter Your Choice: ");
    scanf("%d", &choice);

    for(int i = 0; i < m; i++)
        temp[i] = block[i];

    switch(choice)
    {
        case 1:
            firstFit(temp, m, process, n);
            break;

        case 2:
            for(int i = 0; i < m; i++)
                temp[i] = block[i];
            bestFit(temp, m, process, n);
            break;

        case 3:
            for(int i = 0; i < m; i++)
                temp[i] = block[i];
            worstFit(temp, m, process, n);
            break;

        default:
            printf("Invalid Choice");
    }

    return 0;
}
