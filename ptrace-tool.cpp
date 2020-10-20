#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/user.h>
#include <unistd.h>

#include <iostream>
#include <string>

using namespace std;

uint64_t swap_uint64( uint64_t val )
{
    val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
    val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
    return (val << 32) | (val >> 32);
}

int main(int argc, char** argv) {
    // initialize program
    // cout << "initializing" << endl;
    pid_t pid = fork();
    if (pid != 0) {
        cout << pid << endl;
    }
    
    if (pid == 0) {
        if (ptrace(PTRACE_TRACEME, pid, nullptr, 0) < 0) {
            std::perror("ptrace(PTRACE_TRACEME) error");
            exit(EXIT_FAILURE);
        }

        // waiting for parent 
        raise(SIGSTOP);

        char* envp_child[] = {nullptr};
        if (execve("read", argv, envp_child) < 0) {
            std::perror("execve error");
            exit(EXIT_FAILURE);
        }
        cout << "exiting instance" << endl;

        exit(EXIT_FAILURE);
    }

    int wstatus;
    while (true) {
        cout << "waiting for signal" << endl;
        waitpid(pid, &wstatus, 0);
        cout << "return from waitpid with wstatus: " << wstatus << endl;
        if (WIFSTOPPED(wstatus) && WSTOPSIG(wstatus) == SIGSTOP) {
            break;
        }
        else {
            cout << "other stop" << endl;
            ptrace(PTRACE_CONT, pid, (caddr_t)1, 0);
        }
    }

    ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);
    ptrace(PTRACE_SYSCALL, pid, 0, 0);
    while (true) {
        waitpid(pid, &wstatus, 0);
        if (WIFEXITED(wstatus)) {
            break;
        }
        else {
            // syscall encountered
            struct user_regs_struct regs;
            ptrace(PTRACE_GETREGS, pid, 0, &regs);
            long syscall = regs.orig_rax;
            if (regs.orig_rax != 0) {
                ptrace(PTRACE_SYSCALL, pid, 0, 0);
                continue;
            }

            // pre-execution
            fprintf(stdout, "%ld(%ld, %ld, %ld, %ld, %ld, %ld)",
                    syscall,
                    (long)regs.rdi, (long)regs.rsi, (long)regs.rdx,
                    (long)regs.r10, (long)regs.r8,  (long)regs.r9);

            // post-execution, get result
            ptrace(PTRACE_SYSCALL, pid, 0, 0);
            waitpid(pid, &wstatus, 0);

            ptrace(PTRACE_GETREGS, pid, 0, &regs);
            fprintf(stdout, " = %ld\n", (long)regs.rax);

            if (regs.rdx == 8191) {
                long replace_val = 5678;
                
                if (regs.rsi) {
                    cout << std::hex << "POKING: " << regs.rsi << endl;
                    ptrace(PTRACE_POKEDATA, pid, (void*)regs.rsi, (void*)replace_val);

                    cout << "POKED: " << ptrace(PTRACE_PEEKDATA, pid, (void*)regs.rsi) << endl;
                }
                else {
                    cout << "PEEKTEXT ERROR" << endl;
                    ptrace(PTRACE_SYSCALL, pid, 0);
                    continue;
                }
            }

            ptrace(PTRACE_SYSCALL, pid, 0, 0);
        }
    }
    return 0;
}