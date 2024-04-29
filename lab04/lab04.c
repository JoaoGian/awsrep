#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_THREADS 4

// Estrutura para armazenar os parâmetros da thread
typedef struct {
    int start_row;
    int end_row;
} ThreadParams;

double matrix[4][3] = {
    {2, 2, 3},
    {4, 3, 6},
    {4, 4, 9},
    {5, 11, 6}
};
double vector[3] = {1, 3, 4};
double result[4];

// Função que realiza a multiplicação de uma seção da matriz pelo vetor
void* section_multiply(void* params) {
    ThreadParams* p = (ThreadParams*)params;
    for (int i = p->start_row; i <= p->end_row; ++i) {
        result[i] = 0;
        for (int j = 0; j < 3; ++j) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[MAX_THREADS];
    ThreadParams thread_params[MAX_THREADS];
    int rows_per_thread = 4 / MAX_THREADS;

    for (int i = 0; i < MAX_THREADS; ++i) {
        thread_params[i].start_row = i * rows_per_thread;
        thread_params[i].end_row = (i == MAX_THREADS - 1) ? 3 : (thread_params[i].start_row + rows_per_thread - 1);
        pthread_create(&threads[i], NULL, section_multiply, &thread_params[i]);
    }

    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < 4; ++i) {
        printf("Resultado[%d] = %f\n", i, result[i]);
    }

    return 0;
}
