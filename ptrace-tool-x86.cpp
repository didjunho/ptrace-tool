#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/user.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <thread>

using namespace std;

int main(int argc, char** argv) {
    // initialize program
    pid_t pid;
    cin >> pid;

    if (ptrace(PTRACE_ATTACH, pid, 0, 0) < 0) {
        std::perror("ptrace(PTRACE_ATTACH) error");
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

    // store all valid files
    unordered_map<string, int> valid_files;

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
            struct user_regs_struct regs;
            ptrace(PTRACE_GETREGS, pid, 0, &regs);
            if (regs.orig_rax != 0 && regs.orig_rax != 257) {
                fprintf(stdout, "INTERCEPTED: %ld(%ld, %ld, %ld)\n",
                    regs.orig_rax,
                    regs.rdi, regs.rsi, regs.rdx);
                if (regs.orig_rax == 5) {
                    cout << "FOUND AN OPEN CALL" << endl;
                }
                ptrace(PTRACE_SYSCALL, pid, 0, 0);
                continue;
            }

            if (regs.orig_rax == 257) {
                // pre-execution
                ptrace(PTRACE_GETREGS, pid, 0, &regs);
                int i = 0;
                std::string path;
                bool reached_end = false;
                while (!reached_end) {
                    std::stringstream ss;
                    ss << std::hex << ptrace(PTRACE_PEEKDATA, pid, regs.rsi + i*sizeof(long));
                    std::string path_chunk;
                    ss >> path_chunk;
                    
                    if (path_chunk.size() != 16) {
                        break;
                    }

                    for (int j = 7; j >= 0; --j) {
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

                ptrace(PTRACE_GETREGS, pid, 0, &regs);
                cout << "with file descriptor: " << regs.rax << endl;

                if (valid_files.find(path) == valid_files.end()) {
                    valid_files[path] = regs.rax;
                    outFile << regs.rax << ": " << path << endl;
                }

                ptrace(PTRACE_SYSCALL, pid, 0, 0);
                continue;
            }


            // change syscall value to invalid value
            if (regs.rdx == 8191) {
                //long new_syscall = -1;
                regs.orig_rax = -1;
                ptrace(PTRACE_SETREGS, pid, 0, regs);
                //ptrace(PTRACE_SET_SYSCALL, pid, 0, new_syscall);
            }

            // post-execution, get result
            ptrace(PTRACE_SYSCALL, pid, 0, 0);
            waitpid(pid, &wstatus, 0);

            if (regs.rdx == 8191) {
                ptrace(PTRACE_GETREGS, pid, 0, &regs);
                fprintf(stdout, "POST: %ld(%ld, %ld, %ld) = %ld\n",
                        regs.orig_rax,
                        regs.rdi, regs.rsi, regs.rdx, regs.rax);

                char replace_val[5] = "5678";
                long new_sensor_val;
                memcpy(&new_sensor_val, replace_val, 4);

                if (regs.rsi) {
                    ptrace(PTRACE_POKEDATA, pid, regs.rsi, new_sensor_val);

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
