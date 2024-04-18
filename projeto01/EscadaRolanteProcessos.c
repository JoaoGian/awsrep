#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SEM_MUTEX 0
#define SEM_EMPTY 1

int main() {
    int shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    int *direction = (int *)shmat(shm_id, NULL, 0);
    *direction = -1;  // Inicialmente a escada está parada

    int sem_id = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    semctl(sem_id, SEM_MUTEX, SETVAL, 1);
    semctl(sem_id, SEM_EMPTY, SETVAL, 1);

    // Exemplo de uso com processos
    int N = 3;  // Número de pessoas
    int times[] = {5, 8, 13};
    int directions[] = {0, 0, 0};

    for (int i = 0; i < N; i++) {
        if (fork() == 0) {
            // Processo filho
            struct sembuf p = {SEM_MUTEX, -1, 0};
            semop(sem_id, &p, 1);

            while (*direction != -1 && *direction != directions[i]) {
                struct sembuf v = {SEM_MUTEX, 1, 0};
                semop(sem_id, &v, 1);
                sleep(1);  // Espera a escada ficar livre
                semop(sem_id, &p, 1);
            }

            *direction = directions[i];
            printf("Pessoa %d usando a escada na direção %d no tempo %d\n", i, directions[i], times[i]);
            sleep(10);  // Simula o uso da escada

            *direction = -1;
            struct sembuf v = {SEM_MUTEX, 1, 0};
            semop(sem_id, &v, 1);
            exit(0);
        }
    }

    while (wait(NULL) > 0);  // Aguarda todos os processos filhos

    shmdt(direction);
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);

    return 0;
}
