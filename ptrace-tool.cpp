#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <asm/ptrace.h>
#include <sys/syscall.h>
#include <sys/user.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>

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

        if (execvp("phosphor-hwmon-readd", argv) < 0) {
            std::perror("execve error");
            exit(EXIT_FAILURE);
        }
        cout << "exiting instance" << endl;

        exit(EXIT_FAILURE);
    }

    int wstatus;
    while (true) {
        waitpid(pid, &wstatus, 0);
        if (WIFSTOPPED(wstatus) && WSTOPSIG(wstatus) == SIGSTOP) {
            break;
        }
        else {
            ptrace(PTRACE_CONT, pid, (caddr_t)1, 0);
        }
    }

    // start tracing
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
            ptrace(static_cast<__ptrace_request>(PTRACE_GETREGS), pid, 0, &regs);
            if (regs.uregs[7] != 3 && regs.uregs[7] != 322) {
/*                 fprintf(stdout, "INTERCEPTED: %ld(%ld, %ld, %ld)\n",
                    regs.uregs[7],
                    regs.uregs[0], regs.uregs[1], regs.uregs[2]);
                if (regs.uregs[7] == 5) {
                    cout << "FOUND AN OPEN CALL" << endl;
                } */
                ptrace(PTRACE_SYSCALL, pid, 0, 0);
                continue;
            }

            if (regs.uregs[7] == 322) {
                // pre-execution
                ptrace(static_cast<__ptrace_request>(PTRACE_GETREGS), pid, 0, &regs);
                int i = 0;
                std::string path;
                bool reached_end = false;
                while (!reached_end) {
                    std::stringstream ss;
                    ss << std::hex << ptrace(PTRACE_PEEKDATA, pid, regs.uregs[1] + i*sizeof(long));
                    std::string path_chunk;
                    ss >> path_chunk;
                    //std::cout << "path chunk: " << path_chunk << std::endl;
                    
                    if (path_chunk.size() != 8) {
                        break;
                    }

                    for (int j = 3; j >= 0; --j) {
                        char next_char = static_cast<char>(std::stoul(path_chunk.substr(j*2, 2), nullptr, 16));
                        if (next_char == '\0') {
                            reached_end = true;
                            break;
                        }
                        path += next_char;
                    }
                    ++i;
                }
                cout << "opening path: " << path << " ";

                // post-execution
                ptrace(PTRACE_SYSCALL, pid, 0, 0);
                waitpid(pid, &wstatus, 0);

                ptrace(static_cast<__ptrace_request>(PTRACE_GETREGS), pid, 0, &regs);
                cout << "with file descriptor: " << regs.uregs[0] << endl;
                ptrace(PTRACE_SYSCALL, pid, 0, 0);
                continue;
            }

            // pre-execution
            /* fprintf(stdout, "PRE: %ld(%ld, %ld, %ld)\n",
                    regs.uregs[7],
                    regs.uregs[0], regs.uregs[1], regs.uregs[2]); */

            // change syscall value to invalid value
            if (regs.uregs[2] == 8191) {
                long new_syscall = -1;
                ptrace(static_cast<__ptrace_request>(PTRACE_SET_SYSCALL), pid, 0, new_syscall);
            }


            // post-execution, get result
            ptrace(PTRACE_SYSCALL, pid, 0, 0);
            waitpid(pid, &wstatus, 0);

/*             if (regs.uregs[2] == 8191) {
                ptrace(static_cast<__ptrace_request>(PTRACE_GETREGS), pid, 0, &regs);
                fprintf(stdout, "POST: %ld(%ld, %ld, %ld)",
                        regs.uregs[7],
                        regs.uregs[0], regs.uregs[1], regs.uregs[2]);
            } */

            if (regs.uregs[2] == 8191) {
                ptrace(static_cast<__ptrace_request>(PTRACE_GETREGS), pid, 0, &regs);
                char replace_val[5] = "5678";
                long new_sensor_val;
                memcpy(&new_sensor_val, replace_val, 4);

                if (regs.uregs[1]) {
                    ptrace(PTRACE_POKEDATA, pid, regs.uregs[1], new_sensor_val);

                    // will need to overload return value for error injection here
                    //regs.uregs[0] = 4;
                }
                else {
                    cout << "ARG ERROR" << endl;
                }
            }

            ptrace(PTRACE_SYSCALL, pid, 0, 0);
        }
    }
    return 0;
}
