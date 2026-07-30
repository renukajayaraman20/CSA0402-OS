#include <stdio.h>
#include <string.h>

#define MAX_DIR 5
#define MAX_FILES 10

struct File
{
    char filename[30];
};

struct Directory
{
    char dirname[30];
    struct File files[MAX_FILES];
    int fileCount;
};

int main()
{
    struct Directory dir[MAX_DIR];
    int dirCount = 0;
    int choice, i, j;
    char dname[30], fname[30];

    while (1)
    {
        printf("\n===== TWO LEVEL DIRECTORY =====\n");
        printf("1. Create Directory\n");
        printf("2. Create File\n");
        printf("3. Display Directories\n");
        printf("4. Display Files in Directory\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:

                if(dirCount == MAX_DIR)
                {
                    printf("Directory Limit Reached!\n");
                }
                else
                {
                    printf("Enter Directory Name: ");
                    scanf("%s", dir[dirCount].dirname);

                    dir[dirCount].fileCount = 0;
                    dirCount++;

                    printf("Directory Created Successfully.\n");
                }
                break;

            case 2:

                printf("Enter Directory Name: ");
                scanf("%s", dname);

                for(i = 0; i < dirCount; i++)
                {
                    if(strcmp(dir[i].dirname, dname) == 0)
                    {
                        if(dir[i].fileCount == MAX_FILES)
                        {
                            printf("Directory Full!\n");
                        }
                        else
                        {
                            printf("Enter File Name: ");
                            scanf("%s", fname);

                            strcpy(dir[i].files[dir[i].fileCount].filename, fname);
                            dir[i].fileCount++;

                            printf("File Created Successfully.\n");
                        }
                        break;
                    }
                }

                if(i == dirCount)
                    printf("Directory Not Found!\n");

                break;

            case 3:

                printf("\nDirectories:\n");

                if(dirCount == 0)
                {
                    printf("No Directories Available.\n");
                }
                else
                {
                    for(i = 0; i < dirCount; i++)
                    {
                        printf("%d. %s\n", i + 1, dir[i].dirname);
                    }
                }

                break;

            case 4:

                printf("Enter Directory Name: ");
                scanf("%s", dname);

                for(i = 0; i < dirCount; i++)
                {
                    if(strcmp(dir[i].dirname, dname) == 0)
                    {
                        printf("\nFiles in %s:\n", dname);

                        if(dir[i].fileCount == 0)
                        {
                            printf("No Files Available.\n");
                        }
                        else
                        {
                            for(j = 0; j < dir[i].fileCount; j++)
                            {
                                printf("%d. %s\n", j + 1,
                                dir[i].files[j].filename);
                            }
                        }
                        break;
                    }
                }

                if(i == dirCount)
                    printf("Directory Not Found!\n");

                break;

            case 5:

                printf("Program Exited.\n");
                return 0;

            default:

                printf("Invalid Choice!\n");
        }
    }

    return 0;
}
