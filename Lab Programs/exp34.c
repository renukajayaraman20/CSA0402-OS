
#include <stdio.h>

struct Record {
    int number;
    char data[100];
};

int main() {
    FILE *fp;
    struct Record r;
    int search;

    fp = fopen("sequential.txt", "w");

    printf("Enter records (0 to stop):\n");

    while(1) {
        printf("Record Number: ");
        scanf("%d", &r.number);

        if(r.number == 0)
            break;

        printf("Data: ");
        scanf(" %[^\n]", r.data);

        fwrite(&r, sizeof(r), 1, fp);
    }

    fclose(fp);

    fp = fopen("sequential.txt", "r");

    printf("\nEnter record number to read (0 to stop): ");

    while(scanf("%d", &search) && search != 0) {
        rewind(fp);

        while(fread(&r, sizeof(r), 1, fp)) {
            printf("Record Number: %d\n", r.number);
            printf("Data: %s\n", r.data);

            if(r.number == search)
                break;
        }

        printf("\nEnter record number to read (0 to stop): ");
    }

    fclose(fp);

    return 0;
}
