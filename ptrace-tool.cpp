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

using namespace std;

int main(int argc, char** argv) {
    // initialize program
    // cout << "initializing" << endl;
    pid_t pid = fork();
    if (pid != 0) {
        cout << pid << endl;
    }
    
    if (pid == 0) {
        if (ptrace(PT_TRACE_ME, pid, nullptr, 0) < 0) {
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
            ptrace(PT_CONTINUE, pid, (caddr_t)1, 0);
        }
    }

    ptrace(PT_CONTINUE, pid, (caddr_t)1, 0);
    while (true) {
        waitpid(pid, &wstatus, 0);
        if (WIFEXITED(wstatus)) {
            break;
        }
        else {
            cout << "other stop" << endl;
            ptrace(PT_CONTINUE, pid, (caddr_t)1, 0);
        }
    }

    cout << "completed" << endl;
    return 0;
}