#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file;
    char buffer[100];

    /* Create and open file in write mode */
    file = fopen("example.txt", "w");

    if (file == NULL)
    {
        printf("Error opening the file for writing.\n");
        return 1;
    }

    /* Write data into the file */
    fprintf(file, "Hello, World!\n");
    fprintf(file, "This is a C file management example.\n");

    /* Close the file */
    fclose(file);

    /* Open file in read mode */
    file = fopen("example.txt", "r");

    if (file == NULL)
    {
        printf("Error opening the file for reading.\n");
        return 1;
    }

    /* Read and display file contents */
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("%s", buffer);
    }

    /* Close the file */
    fclose(file);

    return 0;
}
