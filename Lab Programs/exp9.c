#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    key_t key = 1234;
    int shmid = shmget(key, 100, 0666 | IPC_CREAT);

    char *str = (char *)shmat(shmid, NULL, 0);

    strcpy(str, "Hello Shared Memory");

    printf("Data Written: %s\n", str);

    shmdt(str);

    return 0;
}
