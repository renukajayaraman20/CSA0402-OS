
#include <stdio.h>
#include <sys/stat.h>

int main() {
    char file[] = "file.txt";

    if(chmod(file, 0664) == 0)
        printf("File permissions changed successfully.\n");
    else
        printf("Error changing file permissions.\n");

    return 0;
}
