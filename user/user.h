//include tyde for all type (important)
// omg this make me 2 hours to find out
#include "../kernel/types.h"


struct stat;
//what we added
struct Sysinfo {
    uint64 freemem;
    uint64 nproc;
    uint64 nopenfiles;
};



// system calls
int fork(void);
int exit(int) __attribute__((noreturn));
int wait(int*);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(const char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
//what we added
uint hello(void);
uint64 trace(int);
uint64 sysinfo(struct Sysinfo*);
uint64 pgaccess(void *start_va, int num_pages, uint64 *bitmap);


// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void fprintf(int, const char*, ...) __attribute__ ((format (printf, 2, 3)));
void printf(const char*, ...) __attribute__ ((format (printf, 1, 2)));
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
int atoi(const char*);
int memcmp(const void *, const void *, uint);
void *memcpy(void *, const void *, uint);
#ifdef LAB_PGTBL
// usyscall region
int ugetpid(void);
#endif

// umalloc.c
void* malloc(uint);
void free(void*);
