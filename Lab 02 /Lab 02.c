#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LEN 256

int main(void) {
    int comunicacao[2]; // Pipeline para comunicação entre pai e filho
    pid_t pid;
    char msgPai[MAX_LEN] = "Mensagem do pai";
    char recebido[MAX_LEN];

    // Inicializa o pipe
    if (pipe(comunicacao) == -1) {
        perror("Falha ao abrir pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("Falha na criação do processo");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // No filho
        close(comunicacao[1]); // Fecha o canal de escrita no filho
        // Lê a mensagem do pai
        read(comunicacao[0], recebido, MAX_LEN);
        printf("Mensagem do filho: '%s'\n", recebido);
        close(comunicacao[0]); // Fecha o canal de leitura
        printf("Processo filho finalizado.\n");
        exit(EXIT_SUCCESS);
    } else { // No pai
        close(comunicacao[0]); // Fecha o canal de leitura no pai
        // Escreve para o filho
        write(comunicacao[1], msgPai, MAX_LEN);
        printf("Pai enviou mensagem.\n");
        close(comunicacao[1]); // Fecha o canal de escrita
        wait(NULL); // Aguarda o filho terminar
        printf("Processo pai finalizado.\n");
    }

    return EXIT_SUCCESS;
}

