
#include <stdio.h>

#define MAX 3

int main() {
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2};
    int n = 13, frames[MAX] = {-1,-1,-1};
    int i, j, k, pos, farthest, next, found, faults = 0;

    printf("Reference String: ");
    for(i = 0; i < n; i++)
        printf("%d ", pages[i]);

    printf("\n\nPage Replacement:\n");

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < MAX; j++)
            if(frames[j] == pages[i])
                found = 1;

        if(!found) {
            faults++;
            pos = -1;

            /* Find empty frame */
            for(j = 0; j < MAX; j++) {
                if(frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            /* Find page used farthest in future */
            if(pos == -1) {
                farthest = -1;

                for(j = 0; j < MAX; j++) {
                    next = n + 1;

                    for(k = i + 1; k < n; k++) {
                        if(frames[j] == pages[k]) {
                            next = k;
                            break;
                        }
                    }

                    if(next > farthest) {
                        farthest = next;
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];

            printf("Page %d -> ", pages[i]);
            for(j = 0; j < MAX; j++)
                printf("%d ", frames[j]);
            printf("\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", faults);

    return 0;
}.
