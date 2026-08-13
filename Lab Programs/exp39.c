
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, seek = 0, i, j, temp;
    int disk = 199;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter request queue: ");
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    for(i = 0; i < n-1; i++)
        for(j = i+1; j < n; j++)
            if(a[i] > a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }

    printf("\nHead Movement: %d", head);

    /* Move right */
    for(i = 0; i < n; i++) {
        if(a[i] >= head) {
            seek += abs(head - a[i]);
            head = a[i];
            printf(" -> %d", head);
        }
    }

    /* Move to end */
    seek += disk - head;
    head = disk;
    printf(" -> %d", head);

    /* Jump to beginning */
    seek += disk;
    head = 0;
    printf(" -> %d", head);

    /* Continue from beginning */
    for(i = 0; i < n; i++) {
        if(a[i] < head)
            continue;

        if(a[i] < disk) {
            seek += abs(head - a[i]);
            head = a[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Seek Time: %d", seek);
    printf("\nAverage Seek Time: %.2f\n", (float)seek / n);

    return 0;
}
