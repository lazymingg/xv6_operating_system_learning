#ifndef SYSINFO_H
#define SYSINFO_H

typedef unsigned long uint64;

struct Sysinfo {
    uint64 freemem;
    uint64 nproc;
    uint64 nopenfiles; 
};

#endif