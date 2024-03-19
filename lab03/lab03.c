#define _GNU_SOURCE // Essencial para habilitar funcionalidades específicas do GNU
#include <sched.h> // necessário para clone()
#include <signal.h> // para SIGCHLD
#include <stdio.h> // para printf()
#include <stdlib.h> // para malloc() e free()
#include <sys/types.h> // para pid_t
#include <sys/wait.h> // para waitpid()
#include <unistd.h> // para _exit()

#define TAM_PILHA 65536 // 64kB definidos em bytes

// Variável para mostrar o compartilhamento entre thread filho e processo pai
int dadoCompartilhado = 0;

// A thread filho vai executar esta função
int executarThreadFilho(void* arg) {
    printf("Thread filho ativa.\n");
    dadoCompartilhado = 42; // altera o valor da variável compartilhada
    printf("Thread filho modificou dadoCompartilhado para %d\n", dadoCompartilhado);
    _exit(0); // encerra a thread filho
}

int main(void) {
    void* pilha = NULL;
    pid_t pidFilho;

    // alocação de memória para a pilha do thread filho
    pilha = malloc(TAM_PILHA);
    if (!pilha) {
        perror("Falha na alocação da pilha");
        exit(EXIT_FAILURE);
    }

    printf("Iniciando a criação da thread filho...\n");

    // criação da thread filho
    pidFilho = clone(executarThreadFilho, (char*)pilha + TAM_PILHA,
                     SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, NULL);
    if (pidFilho == -1) {
        perror("clone falhou");
        exit(EXIT_FAILURE);
    }

    // espera a thread filho terminar
    waitpid(pidFilho, NULL, 0);
    printf("Processo pai viu dadoCompartilhado como %d\n", dadoCompartilhado);

    // liberação de recursos
    free(pilha);
    printf("Thread filho concluída, recursos liberados.\n");
    return EXIT_SUCCESS;
}

