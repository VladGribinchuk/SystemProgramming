/// Процес 1 породжує нащадка 2. Обидва процеси після цього
/// відкривають той самий файл і пишуть у нього по черзі
/// N байт. Організувати М циклів запису за допомогою сигналів.

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <signal.h>
#include <cstdlib>
using namespace std;

const char FILENAME[] = "file";
int N = 5,
    M = 6;
fstream file;
pid_t pid1, pid2;

void usr_handler1(int signum)
{
    //// Write N bytes to file "FILENAME"
        file.open(FILENAME,ios::out|ios::app);
        for(int i=0;i<N;++i)
            file << "1";
        file.close();
    ////
    cout << "PID " << pid1 << " write to file now...\n";

    M-=2;
    if(M >= 0)
        kill(pid2,SIGUSR2);
    else
        kill(0, SIGTERM);
}

void usr_handler2(int signum)
{
    //// Write N bytes to file "FILENAME"
        file.open(FILENAME,ios::out|ios::app);
        for(int i=0;i<N;++i)
            file << "2";
        file.close();
    ////
    cout << "PID " << pid2 << " write to file now...\n";
    M-=2;
    if(M >= 0)
        kill(pid1,SIGUSR1);
    else
        kill(0, SIGTERM);
}

void term_handler(int signum)
{
    cout << "PID " << getpid() << " terminating now...\n";
    exit(EXIT_SUCCESS);
}

int main()
{
    setpgrp();

    //// pid1 = PID parent process
        pid1 = getpid();
        cout << "PID " << pid1 << "(parent) has been created already...\n";
    ////

    //// Clear file before write it
        file.open(FILENAME, ios::out);
        file.close();
    ////

    //// Create child process
        pid2 = fork();
    ////

    if(pid2 == -1){
        //
        // In case fork() return error value
        //
        cout << "Couldnt create process\n";
        return 1;
    } else
        if(pid2 == 0){
            //
            // in child process2
            //

            //// Decrement M for odd/even iterations
                M -= 1;
            ////

            //// pid2 = PID child process
                pid2 = getpid();
                cout << "PID " << pid2 << "(child) has been created already...\n";
            ////

            //// Define handler
                signal(SIGUSR2,usr_handler2);
                signal(SIGTERM,term_handler);
            ////

                kill(pid1,SIGUSR1);
                while(1);
        }
        else {
            //
            // in parent process1
            //
            //// Define handler
                signal(SIGUSR1,usr_handler1);
                signal(SIGTERM,term_handler);
            ////

                while(1);
        }

    return 0;
}
