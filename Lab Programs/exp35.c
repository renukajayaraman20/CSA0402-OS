
#include <stdio.h>

struct Block {
    int number;
    char data[100];
};

int main() {
    FILE *fp;
    struct Block b;
    long index[100] = {0};
    int num;

    fp = fopen("indexed.txt", "w+");

    printf("Enter blocks (0 to stop):\n");

    while(1) {
        printf("Block Number: ");
        scanf("%d", &b.number);

        if(b.number == 0)
            break;

        printf("Data: ");
        scanf(" %[^\n]", b.data);

        index[b.number] = ftell(fp);
        fwrite(&b, sizeof(b), 1, fp);
    }

    printf("\nEnter block number to read (0 to stop): ");

    while(scanf("%d", &num) && num != 0) {
        if(index[num] == 0) {
            printf("Block not found.\n");
        } else {
            fseek(fp, index[num], SEEK_SET);
            fread(&b, sizeof(b), 1, fp);

            printf("Block Number: %d\n", b.number);
            printf("Data: %s\n", b.data);
        }

        printf("\nEnter block number to read (0 to stop): ");
    }

    fclose(fp);

    return 0;
}
