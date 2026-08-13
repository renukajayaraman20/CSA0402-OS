
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, seek = 0, i;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int request[n];

    printf("Enter request queue: ");
    for(i = 0; i < n; i++)
        scanf("%d", &request[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nHead Movement: %d", head);

    for(i = 0; i < n; i++) {
        seek += abs(head - request[i]);
        head = request[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d", seek);
    printf("\nAverage Seek Time: %.2f\n", (float)seek / n);

    return 0;
}
