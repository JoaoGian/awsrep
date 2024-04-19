#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Definição da estrutura para armazenar informações de cada pessoa
typedef struct {
    int arrival_time;
    int direction;
} Person;

// Função que simula a operação da escada rolante para cada pessoa
void *escalator_simulation(void *arg) {
    Person *person = (Person *)arg;
    sleep(person->arrival_time); // Simula o tempo até a pessoa chegar na escada
    printf("Pessoa chegou no tempo %d, querendo ir na direção %d\n", person->arrival_time, person->direction);
    // Adicionar lógica para controle da escada aqui
    return NULL;
}

int main() {
    FILE *file;
    int num_people;
    Person *people;

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

    // Limpeza
    free(people);
    free(threads);
    fclose(file);

    printf("Último momento em que a escada para: %d\n", /* último tempo calculado */);

    return 0;
}

