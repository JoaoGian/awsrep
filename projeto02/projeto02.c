#define _GNU_SOURCE
#include <malloc.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define STACK_SIZE 1024 * 64

typedef struct {
    int saldo;
} Conta;

Conta contaOrigem, contaDestino;
int montante1, montante2;
pthread_mutex_t lock; 

// Função de transferência protegida por mutex
void* executarTransferencia(void *arg) {
    pthread_mutex_lock(&lock); // Bloqueia o mutex antes de acessar as variáveis compartilhadas

    if (contaOrigem.saldo >= montante1) {
        contaOrigem.saldo -= montante1;
        contaDestino.saldo += montante1;
    } else {
        printf("Saldo insuficiente na conta de origem!\n");
        pthread_mutex_unlock(&lock);
        return NULL;
    }

    printf("Transferência concluída com sucesso! (Origem -> Destino)\n");
    printf("Saldo de Origem: %d\n", contaOrigem.saldo);
    printf("Saldo de Destino: %d\n", contaDestino.saldo);

    pthread_mutex_unlock(&lock); // Libera o mutex após o acesso às variáveis compartilhadas
    return NULL;
}

void* executarTransferenciaReversa(void *arg) {
    pthread_mutex_lock(&lock); // Bloqueia o mutex antes de acessar as variáveis compartilhadas

    if (contaDestino.saldo >= montante2) {
        contaDestino.saldo -= montante2;
        contaOrigem.saldo += montante2;
    } else {
        printf("Saldo insuficiente na conta de destino!\n");
        pthread_mutex_unlock(&lock);
        return NULL;
    }

    printf("Transferência concluída com sucesso! (Destino -> Origem)\n");
    printf("Saldo de Origem: %d\n", contaOrigem.saldo);
    printf("Saldo de Destino: %d\n", contaDestino.saldo);

    pthread_mutex_unlock(&lock); // Libera o mutex após o acesso às variáveis compartilhadas
    return NULL;
}

int main() {
    void* pilha;
    pthread_t threads[100];
    int i;

    // Inicialização das contas
    contaOrigem.saldo = 100;
    contaDestino.saldo = 100;
    montante1 = 20;
    montante2 = 10;

    pthread_mutex_init(&lock, NULL); // Inicializa o mutex

    
    pilha = malloc(STACK_SIZE);
    if (pilha == NULL) {
        perror("Erro na alocação da pilha");
        exit(1);
    }

    // Criação das threads para transferências
    for (i = 0; i < 50; i++) {
        if (pthread_create(&threads[i], NULL, executarTransferencia, NULL) != 0) {
            perror("Erro na criação da thread");
            exit(2);
        }

        if (pthread_create(&threads[i + 50], NULL, executarTransferenciaReversa, NULL) != 0) {
            perror("Erro na criação da thread");
            exit(2);
        }
    }

    // Espera todas as threads terminarem
    for (i = 0; i < 100; i++) {
        pthread_join(threads[i], NULL);
    }

    // Liberação da pilha e destruição do mutex
    free(pilha);
    pthread_mutex_destroy(&lock);

    printf("Todas as transferências foram concluídas e a memória foi liberada.\n");
    return 0;
}
