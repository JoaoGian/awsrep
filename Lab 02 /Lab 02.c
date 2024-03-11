#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LEN 256

int main(void) {
    int comunicacao[2]; 
    pid_t pid;
    char msgPai[MAX_LEN] = "Mensagem do pai";
    char recebido[MAX_LEN];

   
    if (pipe(comunicacao) == -1) {
        perror("Falha ao abrir pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("Falha na criação do processo");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { 
        close(comunicacao[1]); 
        
        read(comunicacao[0], recebido, MAX_LEN);
        printf("Mensagem do filho: '%s'\n", recebido);
        close(comunicacao[0]); 
        printf("Processo filho finalizado.\n");
        exit(EXIT_SUCCESS);
    } else { 
        close(comunicacao[0]);
       
        write(comunicacao[1], msgPai, MAX_LEN);
        printf("Pai enviou mensagem.\n");
        close(comunicacao[1]); 
        wait(NULL); 
        printf("Processo pai finalizado.\n");
    }

    return EXIT_SUCCESS;
}

