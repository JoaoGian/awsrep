#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Estrutura para armazenar informações de cada pessoa
typedef struct {
    int tempo_chegada;
    int direcao;
} Pessoa;

// Função para simular a operação da escada rolante para cada pessoa
void simula_pessoa(Pessoa pessoa) {
    sleep(pessoa.tempo_chegada); // Simula o tempo até a pessoa chegar na escada
    printf("Pessoa chegou no tempo %d, querendo ir na direção %d\n", pessoa.tempo_chegada, pessoa.direcao);
    // Adicionar lógica para controle da escada aqui
}

int main() {
    FILE *file;
    int num_pessoas;
    Pessoa *pessoas;

    file = fopen("entrada.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lê o número de pessoas do arquivo
    fscanf(file, "%d", &num_pessoas);
    pessoas = malloc(num_pessoas * sizeof(Pessoa));

    // Lê os tempos de chegada e as direções do arquivo
    for (int i = 0; i < num_pessoas; i++) {
        fscanf(file, "%d %d", &pessoas[i].tempo_chegada, &pessoas[i].direcao);
    }

    for (int i = 0; i < num_pessoas; i++) {
        pid_t pid = fork();
        if (pid == 0) { // Processo filho
            simula_pessoa(pessoas[i]);
            exit(0);
        }
    }

    // Processo pai espera todos os filhos terminarem
    for (int i = 0; i < num_pessoas; i++) {
        wait(NULL);
    }

    // Limpeza
    free(pessoas);
    fclose(file);

    printf("Último momento em que a escada para: %d\n", /* último tempo calculado */);

    return 0;
}

