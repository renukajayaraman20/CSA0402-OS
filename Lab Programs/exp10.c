#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg
{
    long type;
    char text[100];
};

int main()
{
    struct msg m;

    int id = msgget(1234, 0666 | IPC_CREAT);

    m.type = 1;
    strcpy(m.text, "Hello Message Queue");

    msgsnd(id, &m, sizeof(m.text), 0);

    msgrcv(id, &m, sizeof(m.text), 1, 0);

    printf("Message: %s\n", m.text);

    msgctl(id, IPC_RMID, NULL);

    return 0;
}
