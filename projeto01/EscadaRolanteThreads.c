#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;  // Tempo de chegada
    int direction;  // Direção desejada
} Person;

// Mutex e variáveis de condição
pthread_mutex_t mutex;
pthread_cond_t cond;

int current_direction = -1;  // Direção atual da escada (-1 indica parada)

void* use_escalator(void* arg) {
    Person* p = (Person*) arg;
    
    pthread_mutex_lock(&mutex);
    while (current_direction != -1 && current_direction != p->direction) {
        pthread_cond_wait(&cond, &mutex);
    }
    current_direction = p->direction;
    printf("Pessoa usando a escada na direção %d no tempo %d\n", p->direction, p->time);
    pthread_mutex_unlock(&mutex);
    
    // Simular o uso da escada
    sleep(10);
    
    pthread_mutex_lock(&mutex);
    current_direction = -1;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    
    // Exemplo: substituir por leitura de entrada real
    int N = 3;  // Número de pessoas
    Person people[] = {{5, 0}, {8, 0}, {13, 0}};
    
    pthread_t threads[N];
    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, use_escalator, (void*)&people[i]);
    }
    
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    
    return 0;
}
