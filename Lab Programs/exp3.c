
#include <stdio.h>

int main()
{
    int n, bt[10], wt[10], tat[10], i;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Burst Time P%d: ",i+1);
        scanf("%d",&bt[i]);
    }

    wt[0]=0;

    for(i=1;i<n;i++)
        wt[i]=wt[i-1]+bt[i-1];

    printf("\nP\tBT\tWT\tTAT\n");

    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        printf("P%d\t%d\t%d\t%d\n",i+1,bt[i],wt[i],tat[i]);
    }

    return 0;
}
