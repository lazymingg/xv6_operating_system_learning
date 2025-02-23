#include "user.h"

/*
 * main(int argc, char *argv[])
 * ----------------------------
 * A simple user-space program to enable system call tracing (`trace()`)
 * for a given program and then execute it.
 *
 * - Expects at least three arguments: `trace mask`, `traceProgram`, and optional arguments for `traceProgram`.
 * - Converts the first argument (`trace mask`) from a string to an integer.
 * - Calls `trace(trace_mask)` to enable tracing for the current process.
 * - If `trace()` fails, prints an error message and exits.
 * - Uses `exec(argv[2], &argv[2])` to replace the current process with `traceProgram`.
 * - If `exec()` fails, prints an error message and exits.
 */

int main(int argc, char *argv[])
{
    // Ensure at least three arguments are provided: trace mask, program name, and program arguments.
    if (argc < 3)
    {
        fprintf(2, "Usage: at least 3 arguments: trace mask traceProgram [args...]\n");
        exit(1);
    }

    // Convert the first argument (trace mask) from a string to an integer.
    int trace_mask = atoi(argv[1]);

    // Enable system call tracing for the current process.
    if (trace(trace_mask) == 1)
    { // If trace() fails, exit with an error.
        fprintf(2, "trace failed\n");
        exit(1);
    }

    // Execute the target program (argv[2]) with its arguments (argv[2] to argv[argc-1]).
    exec(argv[2], &argv[2]);

    // If exec() fails, print an error message and exit.
    fprintf(2, "exec failed\n");
    exit(1);
}