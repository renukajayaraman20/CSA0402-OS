#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void searchFile(const char *pattern, const char *filename)
{
    FILE *file;
    char line[MAX_LINE_LENGTH];

    file = fopen(filename, "r");

    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, pattern) != NULL)
        {
            printf("%s", line);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    char pattern[100];
    char filename[100];

    printf("Enter the pattern: ");
    scanf("%s", pattern);

    printf("Enter the filename: ");
    scanf("%s", filename);

    searchFile(pattern, filename);

    return 0;
}
