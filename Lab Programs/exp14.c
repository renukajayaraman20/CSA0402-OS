
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void createFile()
{
    FILE *fp;

    fp = fopen("sample.txt", "w");

    if(fp == NULL)
    {
        printf("File cannot be created.\n");
        return;
    }

    fprintf(fp, "Operating Systems Lab\n");
    fclose(fp);

    printf("File created successfully.\n");
}

void copyFile()
{
    int source_fd, dest_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    source_fd = open("sample.txt", O_RDONLY);

    if(source_fd < 0)
    {
        printf("Source file not found.\n");
        return;
    }

    dest_fd = open("copy.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if(dest_fd < 0)
    {
        printf("Destination file cannot be created.\n");
        close(source_fd);
        return;
    }

    while((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0)
    {
        write(dest_fd, buffer, bytesRead);
    }

    close(source_fd);
    close(dest_fd);

    printf("File copied successfully.\n");
}

void deleteFile()
{
    if(remove("sample.txt") == 0)
        printf("File deleted successfully.\n");
    else
        printf("File not found.\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n===== Single Level Directory =====\n");
        printf("1. Create File\n");
        printf("2. Copy File\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                createFile();
                break;

            case 2:
                copyFile();
                break;

            case 3:
                deleteFile();
                break;

            case 4:
                printf("Program Exited.\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 4);

    return 0;
}
