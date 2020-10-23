#include <signal.h>
#include <stdlib.h>
#include <asm/types.h>
#include <asm/ioctl.h>
#include <sys/wait.h>
#include <asm/ptrace.h>
#include <sys/syscall.h>
#include <sys/user.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    // initialize program
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

        //char* envp_child[] = {nullptr};
        if (execvp("phosphor-hwmon-readd", argv) < 0) {
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
            struct pt_regs regs;
            ptrace(PTRACE_GETREGS, pid, 0, &regs);
            long syscall = regs.uregs[7];
            if (regs.uregs[7] != 3) {
                ptrace(PTRACE_SYSCALL, pid, 0, 0);
                continue;
            }

            // pre-execution
            fprintf(stdout, "%ld(%ld, %ld, %ld)",
                    syscall,
                    regs.uregs[0], regs.uregs[1], regs.uregs[2]);

            // post-execution, get result
            ptrace(PTRACE_SYSCALL, pid, 0, 0);
            waitpid(pid, &wstatus, 0);

            ptrace(PTRACE_GETREGS, pid, 0, &regs);
            fprintf(stdout, " = %ld\n", regs.uregs[0];

/*             if (regs.rdi == 3 && regs.rdx == 8191) {
                char replace_val[5] = "8952";
                long new_sensor_val;
                memcpy(&new_sensor_val, replace_val, 4);

                if (regs.rsi) {
                    ptrace(PTRACE_POKEDATA, pid, regs.rsi, new_sensor_val);
                }
                else {
                    cout << "PEEKTEXT ERROR" << endl;
                    ptrace(PTRACE_SYSCALL, pid, 0);
                    continue;
                }
            } */

            ptrace(PTRACE_SYSCALL, pid, 0, 0);
        }
    }
    return 0;
}
