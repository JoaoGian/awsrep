#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PESSOAS 3

// Estrutura para armazenar informações de cada pessoa
typedef struct {
    int tempo_chegada;
    int direcao;
} Pessoa;

// Simulação da escada rolante
void *simulacao_escada(void *arg) {
    Pessoa *pessoa = (Pessoa *)arg;
    sleep(pessoa->tempo_chegada); // Simula a espera até a pessoa chegar
    printf("Pessoa chegou no tempo %d, querendo ir na direção %d\n", pessoa->tempo_chegada, pessoa->direcao);
    // Adicione lógica para simular a movimentação na escada aqui
    return NULL;
}

int main() {
    pthread_t threads[NUM_PESSOAS];
    Pessoa pessoas[NUM_PESSOAS] = {
        {5, 0},
        {8, 0},
        {13, 0}
    };

    for (int i = 0; i < NUM_PESSOAS; i++) {
        pthread_create(&threads[i], NULL, simulacao_escada, (void *)&pessoas[i]);
    }

    for (int i = 0; i < NUM_PESSOAS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Último momento em que a escada para: %d\n", /* último tempo calculado */);

    return 0;
}
