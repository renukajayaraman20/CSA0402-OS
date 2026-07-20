
#include <stdio.h>

int main()
{
    int n, bt[10], pr[10], i;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Burst Time and Priority of P%d: ",i+1);
        scanf("%d%d",&bt[i],&pr[i]);
    }

    printf("\nProcess\tBurst\tPriority\n");

    for(i=0;i<n;i++)
        printf("P%d\t%d\t%d\n",i+1,bt[i],pr[i]);

    printf("\n(Preemptive execution is based on highest priority.)");

    return 0;
}
