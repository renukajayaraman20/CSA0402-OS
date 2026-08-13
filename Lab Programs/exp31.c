#include <stdio.h>

#define MAX 3

int main() {
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2};
    int n = 13, frames[MAX] = {-1,-1,-1};
    int pointer = 0, faults = 0, i, j, found;

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
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % MAX;
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
