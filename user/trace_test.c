#include "user.h"
// #include "fcntl.h"
#define O_RDONLY 0
int main() {
    printf("Parent PID: %d - Enabling trace for SYS_read\n", getpid());

    // Bật trace cho system call "read"
    if (trace(1 << 5) < 0) {
        printf("Trace failed\n");
        exit(1);
    }

    int pid = fork();  // Tạo tiến trình con
    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    char buf[10];
    int fd = open("README", O_RDONLY);

    if (pid == 0) {  // Tiến trình con
        printf("Child PID: %d - Reading file\n", getpid());
        read(fd, buf, 10);  // Nếu trace_mask được kế thừa, system call này sẽ bị log
    } else {  // Tiến trình cha
        wait(0);  // Chờ tiến trình con kết thúc
        printf("Parent PID: %d - Reading file\n", getpid());
        read(fd, buf, 10);  // System call này cũng bị log
    }

    close(fd);
    printf("Test completed\n");
    exit(0);
}
