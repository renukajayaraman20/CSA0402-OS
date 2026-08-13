
#include <stdio.h>
#include <stdlib.h>

struct Block {
    int number;
    char data[100];
    struct Block *next;
};

int main() {
    struct Block *first = NULL, *last = NULL, *newBlock, *temp;
    int choice, num, count = 0;

    while(1) {
        printf("\n1. Write Block\n2. Read Block\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            newBlock = malloc(sizeof(struct Block));

            printf("Enter block number: ");
            scanf("%d", &newBlock->number);

            printf("Enter data: ");
            scanf(" %[^\n]", newBlock->data);

            newBlock->next = NULL;

            if(first == NULL)
                first = last = newBlock;
            else {
                last->next = newBlock;
                last = newBlock;
            }

            count++;
            printf("Block allocated successfully.\n");
        }
        else if(choice == 2) {
            printf("Enter block number to read: ");
            scanf("%d", &num);

            temp = first;

            while(temp != NULL && temp->number != num)
                temp = temp->next;

            if(temp == NULL)
                printf("Block not found.\n");
            else
                printf("Block %d Data: %s\n", temp->number, temp->data);
        }
        else
            break;
    }

    while(first != NULL) {
        temp = first;
        first = first->next;
        free(temp);
    }

    return 0;
}
