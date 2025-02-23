#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0; // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if (n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (killed(myproc()))
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_hello(void)
{
  printf("lazymingg chao cau <3 !!\n");
  return 0;
}

/*
 * sys_trace(void)
 * -----------------
 * Implements the `trace` system call, allowing a process to enable system call tracing.
 * 
 * - Retrieves the trace mask (integer) from the system call argument.
 * - If the mask is negative, returns `1` to indicate failure.
 * - Updates the `trace_mask` field in the process's `struct proc` to enable tracing.
 * - Returns `0` on success.
 * 
 * Parameters:
 * - `mask` (int): A bitmask specifying which system calls should be traced.
 * 
 * Return values:
 * - `0` if tracing is successfully enabled.
 * - `1` if the provided mask is invalid (negative value).
 */

 uint64 sys_trace(void) {
  int mask;
  argint(0, &mask);  // Retrieve the system call argument trace(mask)

  // Check for invalid (negative) mask values
  if (mask < 0)
      return 1;  // Return 1 to indicate failure

  // Update the process's trace_mask from in proc struct
  myproc()->trace_mask = mask;
  return 0;  // Return 0 to indicate success
}
