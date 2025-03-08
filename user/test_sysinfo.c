#include "user.h"

int main(int argc, char *argv[])
{
    struct Sysinfo info;
    if (sysinfo(&info) != 0)
    {
        printf("sysinfo failed\n");
        exit(1);
    }
    printf("Free memory: %d\n", info.freemem);
    printf("Number of processes: %d\n", info.nproc);
    printf("Number of open files: %d\n", info.nopenfiles);
    exit(0);
}