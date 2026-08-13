
#include <stdio.h>

#define MAX 3

int main() {
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2};
    int n = 13, frames[MAX] = {-1,-1,-1};
    int last[MAX] = {0}, time = 0;
    int i, j, pos, found, faults = 0;

    printf("Reference String: ");
    for(i = 0; i < n; i++)
        printf("%d ", pages[i]);

    printf("\n\nPage Replacement:\n");

    for(i = 0; i < n; i++) {
        time++;
        found = 0;

        for(j = 0; j < MAX; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                last[j] = time;
                break;
            }
        }

        if(!found) {
            pos = -1;

            for(j = 0; j < MAX; j++)
                if(frames[j] == -1) {
                    pos = j;
                    break;
                }

            if(pos == -1) {
                pos = 0;
                for(j = 1; j < MAX; j++)
                    if(last[j] < last[pos])
                        pos = j;
            }

            frames[pos] = pages[i];
            last[pos] = time;
            faults++;

            printf("Page %d -> ", pages[i]);
            for(j = 0; j < MAX; j++)
                printf("%d ", frames[j]);
            printf("\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", faults);

    return 0;
}
