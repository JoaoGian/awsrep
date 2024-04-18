#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_PESSOAS 3

// Estrutura para armazenar informações de cada pessoa
typedef struct {
    int tempo_chegada;
    int direcao;
} Pessoa;

// Simulação da escada rolante
void simula_pessoa(Pessoa pessoa) {
    sleep(pessoa.tempo_chegada); // Simula a espera até a pessoa chegar
    printf("Pessoa chegou no tempo %d, querendo ir na direção %d\n", pessoa.tempo_chegada, pessoa.direcao);
    // Adicione lógica para simular a movimentação na escada aqui
}

int main() {
    Pessoa pessoas[NUM_PESSOAS] = {
        {5, 0},
        {8, 0},
        {13, 0}
    };

    for (int i = 0; i < NUM_PESSOAS; i++) {
        pid_t pid = fork();
        if (pid == 0) { // Processo filho
            simula_pessoa(pessoas[i]);
            return 0;
        }
    }

    // Processo pai espera todos os filhos terminarem
    for (int i = 0; i < NUM_PESSOAS; i++) {
        wait(NULL);
    }

    printf("Último momento em que a escada para: %d\n", /* último tempo calculado */);

    return 0;
}

