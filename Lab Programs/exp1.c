#include <stdio.h>
#include <windows.h>

int main()
{
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi;

    si.cb = sizeof(si);

    if (CreateProcess(
            NULL,
            "notepad.exe",
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi))
    {
        printf("Child process created successfully.\n");
        printf("Parent Process ID: %lu\n", GetCurrentProcessId());
        printf("Child Process ID : %lu\n", pi.dwProcessId);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else
    {
        printf("Process creation failed.\n");
    }

    return 0;
}
