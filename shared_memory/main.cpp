//// TASK description:
/// Процес 1 породжує нащадка 2, вони приєднують до себе подіюлювану
/// пам'ять обсягом N*sizeof(int). Процес 1 пише в неї к1 чисел відразу,
/// процес 2 переписує к2 чисел з памяті в файл. Процес 1 може робити запис
/// тільки якщо в памяті досить місця, а процес 2 переписувати, якщо є не
/// менше, ніж к2 чисел. Після кожного запису(читання) процеси засинають на
/// t сек. Після кожного запису процес 1 збільшує значення записуваних чисел
/// на 1. Використовуючи семафори, забезпечити синхронізацію роботи процесів
/// відповідно до заданих умов. Параметри N, k1, k2, t задаються у вигляду
/// аргументів командного рядка.

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

// Define default value
// for size of memory, delay, etc.
const int   N_DEFAULT = 5,
            T_DEFAULT = 1,
            K1_DEFAULT = 5,
            K2_DEFAULT = 2;
//
// Name semaphore
const char SEMAPHORE_NAME[] = "/my_semaphore";

key_t key = 75;
key_t keysem = 76;
int count_written_num = 0;
pid_t pid1, pid2;
int shmid;

sem_t *semap;

void _terminating(int signum=0)
{
    if( getpid() == pid1 ){
        if( shmid>0 ){
            shmctl(shmid,IPC_RMID,0);
            cout << "Forced:\t Process(PID=" <<  pid1 << ") succesfully cleanup shared memory"
                 << "(ID=" << shmid << ")\n";
        }
        sem_close(semap);
        sem_unlink(SEMAPHORE_NAME);
        cout << "Forced:\t Process(PID=" << getpid() << ") unlinked semaphore\n";
        kill(0,SIGTERM);
    }
    else if( getpid() == pid2 ){
        sem_close(semap);
    }

    cout << "Forced:\t Premature terminating process(PID=" << getpid() << ")\n";
    exit(0);
}

int main(int argc, char* argv[])
{

    setpgrp();
    pid1 = getpid();
    cout << "SysMsg:\t Process(PID=" << getpid() << ") started\n";

    int N, t, k1, k2;
    if(argc > 4){
        // Assign values of input parameters
        N = atoi(argv[1]);
        t = atoi(argv[2]);
        k1 = atoi(argv[3]);
        k2 = atoi(argv[4]);
    }
    else {
        // When there is no input parameters
        // set default values
        N = N_DEFAULT;sem_close(semap);
        t = T_DEFAULT;
        k1 = K1_DEFAULT;
        k2 = K2_DEFAULT;
    }

    if( (semap = sem_open(SEMAPHORE_NAME,O_CREAT,0777,0)) == SEM_FAILED ){
        cout << "err";
        exit(0);
    }
    cout << "SysMsg:\t Process(PID=" << getpid() << ") taked semaphore\n";

    //
    // Create child process
    // (which will be read data)
    pid2 = fork();
    if(pid2<0){
        cout << "_Error:\t Could not create child process\n";
        _terminating();
    }
    else
        if(pid2==0){
        //
        // Process 2 (child)
        cout << "SysMsg:\t Process(PID=" << getpid() << ") started\n";

        if ( (semap = sem_open(SEMAPHORE_NAME, 0)) == SEM_FAILED ){
            cout << "err2";
            exit(0);
        }

        sem_wait(semap);
        cout << "SysMsg:\t Process(PID=" << getpid() << ") taked semaphore\n";

        signal(SIGTERM,_terminating);

        shmid = shmget(key, N*sizeof(int), 0777);
        if(shmid <= 0){
            cout << "SysMsg:\t Process(PID=" << getpid() << ") doesn found any shared memory\n";
            _terminating();
        }
        void* addr = shmat(shmid,0,0);


        cout << "SysMsg:\t Process(PID=" << getpid() << ") got access to shared memory"
                << "(ID=" << shmid << ")\n";

        if(k2 > k1){
            //
            // When available data for read not enough

            cout << "_Error:\t Process(PID=" << getpid() << ") cant read so much(require "
                 << k2*sizeof(int) << " bytes, available " << k1*sizeof(int) << " bytes)\n";
            _terminating();

        }

        //
        // Read some data from shared memory
        ofstream fout("out.txt",ios_base::out);
        if(!fout.is_open()){
            cout << "_Error:\t Process" << getpid() << ") cant open file\n";
            _terminating();
        }
        int* pint = (int*) addr;
        for(int i=0; i<k2; i++){
            cout << "SysMsg:\t Process(PID=" << getpid() << ") succesfully read " << *pint << "\n";
            fout << *pint;
            pint++;
            sleep(t);
        }
        fout.close();

        sem_close(semap);
        cout << "SysMsg:\t Process(PID=" << getpid() << ") dropped semaphore\n";

    }
    else {
        //
        // Process 1 (parent)

        // Create and accession shared memory
        shmid = shmget(key, N*sizeof(int), 0777|IPC_CREAT);
        void* addr = shmat(shmid,0,0);
        cout << "SysMsg:\t Process(PID=" << getpid() << ") has created shared memory"
             << "(ID=" << shmid << ", CAPACITY=" << N*sizeof(int) <<" bytes)\n";

        if(k1 > N){
            //
            // When available shared memory size not enough

            cout << "_Error:\t Process(PID=" << getpid() << ") cant write so much(require "
                 << k1*sizeof(int) << " bytes, available " << N*sizeof(int) << " bytes)" << endl;
            _terminating();
        }

        //
        // Write some data to shared memory
        int* pint = (int*) addr;
        for(int i=0; i<k1; i++){

            *pint = i;
            count_written_num++;
            cout << "SysMsg:\t Process(PID=" << getpid() << ") succesfully write " << *pint << "\n";
            pint++;

            sleep(t);
        }
        sem_post(semap);
        cout << "SysMsg:\t Process(PID=" << getpid() << ") dropped semaphore\n";

        int ires;
        wait(&ires);


        shmctl(shmid,IPC_RMID,0);
        cout << "Forced:\t Process(PID=" <<  pid1 << ") succesfully cleanup shared memory"
             << "(ID=" << shmid << ")\n";
        sem_close(semap);
        sem_unlink(SEMAPHORE_NAME);
        cout << "SysMsg:\t Process(PID=" << getpid() << ") unlinked semaphore\n";
     }

    return 0;
}

