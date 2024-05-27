#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h> // Inclui a biblioteca para usar mutex


#define FIBER_STACK 1024*64

struct c {
    int saldo;
};
typedef struct c conta;

conta from, to;
int valor;
pthread_mutex_t lock_from, lock_to; // Define os mutexes

// A função de transferência agora usa mutexes para sincronização
int transferencia(void *arg) {
    int direction = *(int *)arg; // Direção da transferência: 0 para from -> to, 1 para to -> from

    if (direction == 0) {
        pthread_mutex_lock(&lock_from);
        pthread_mutex_lock(&lock_to);
        if (from.saldo >= valor) {
            from.saldo -= valor;
            to.saldo += valor;
            printf("Transferência concluída com sucesso! (from -> to)\n");
        } else {
            printf("Saldo insuficiente na conta 'from'.\n");
        }
        pthread_mutex_unlock(&lock_to);
        pthread_mutex_unlock(&lock_from);
    } else {
        pthread_mutex_lock(&lock_to);
        pthread_mutex_lock(&lock_from);
        if (to.saldo >= valor) {
            to.saldo -= valor;
            from.saldo += valor;
            printf("Transferência concluída com sucesso! (to -> from)\n");
        } else {
            printf("Saldo insuficiente na conta 'to'.\n");
        }
        pthread_mutex_unlock(&lock_from);
        pthread_mutex_unlock(&lock_to);
    }

    printf("Saldo de 'from': %d\n", from.saldo);
    printf("Saldo de 'to': %d\n", to.saldo);
    return 0;
}

int main() {
    void* stack;
    pid_t pid;
    int i;
    int direction[2] = {0, 1}; // Direções das transferências

    // Inicializa os mutexes
    if (pthread_mutex_init(&lock_from, NULL) != 0 || pthread_mutex_init(&lock_to, NULL) != 0) {
        perror("pthread_mutex_init: could not initialize mutexes");
        exit(1);
    }

    // Allocate the stack
    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;
    printf("Transferindo 10 para a conta 'to'\n");
    valor = 10;

    for (i = 0; i < 100; i++) {
        // Alterna entre transferências from -> to e to -> from
        int dir = i % 2;
        // Call the clone system call to create the child thread
        pid = clone(&transferencia, (char*) stack + FIBER_STACK,
                    SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &direction[dir]);
        if (pid == -1) {
            perror("clone");
            exit(2);
        }
    }

    // Espera todos os processos filhos terminarem
    while (wait(NULL) > 0);

    // Free the stack
    free(stack);
    printf("Transferências concluídas e memória liberada.\n");

    // Destroi os mutexes
    pthread_mutex_destroy(&lock_from);
    pthread_mutex_destroy(&lock_to);

    return 0;
}

