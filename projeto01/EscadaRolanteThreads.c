#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TEMPO_TRAJETO 10

// Definição da estrutura para armazenar informações de cada pessoa
typedef struct {
    int arrival_time;  // tempo de chegada
    int direction;     // direção
} Person;

// Variável global para controlar o último tempo de saída da escada
int last_exit_time = 0;

// Mutex para controlar o acesso à variável global last_exit_time
pthread_mutex_t lock;

// Função que simula a operação da escada rolante para cada pessoa
void *escalator_simulation(void *arg) {
    Person *person = (Person *)arg;

    pthread_mutex_lock(&lock);
    if (last_exit_time == 0) {
        last_exit_time = person->arrival_time + TEMPO_TRAJETO;
    } else {
        int potential_start_time = person->arrival_time > last_exit_time - TEMPO_TRAJETO ? person->arrival_time : last_exit_time;
        last_exit_time = potential_start_time + TEMPO_TRAJETO;
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    FILE *file;
    FILE *output_file;
    int num_people;
    Person *people;

    pthread_mutex_init(&lock, NULL);

    file = fopen("entrada.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lê o número de pessoas do arquivo
    fscanf(file, "%d", &num_people);
    people = malloc(num_people * sizeof(Person));

    // Lê os tempos de chegada e as direções do arquivo
    for (int i = 0; i < num_people; i++) {
        fscanf(file, "%d %d", &people[i].arrival_time, &people[i].direction);
    }

    // Cria uma thread para cada pessoa
    pthread_t *threads = malloc(num_people * sizeof(pthread_t));
    for (int i = 0; i < num_people; i++) {
        pthread_create(&threads[i], NULL, escalator_simulation, (void *)&people[i]);
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < num_people; i++) {
        pthread_join(threads[i], NULL);
    }

    // Abre o arquivo de saída e escreve o último momento em que a escada para
    output_file = fopen("saida.txt", "w");
    if (output_file == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        free(people);
        free(threads);
        fclose(file);
        pthread_mutex_destroy(&lock);
        return 1;
    }
    fprintf(output_file, "%d\n", last_exit_time);
    fclose(output_file);

    // Limpeza
    free(people);
    free(threads);
    fclose(file);
    pthread_mutex_destroy(&lock);
    printf (" %d ",last_exit_time);
    return 0;
}
