#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct {
    int timeOfArrival;
    int travelDirection;
} Commuter;

int simulationClock = 0;
int operatingDirection = -1;
int numberOfCommuters = 0;
int endTime = 0;
int commPipe[2];

void simulateEscalatorOperation(Commuter commuters[], int count) {
    operatingDirection = commuters[0].travelDirection;
    endTime = commuters[0].timeOfArrival + 10;
    int idx = 0;
    int processedCommuters = 0;
    int isCommuterWaiting = 0;
    Commuter delayedCommuter;

    while (processedCommuters < count) {
        if (simulationClock >= endTime) {
            operatingDirection = !operatingDirection;
            if (isCommuterWaiting && delayedCommuter.travelDirection == operatingDirection) {
                endTime = simulationClock + 10;
                processedCommuters++;
                isCommuterWaiting = 0;
                write(commPipe[1], &endTime, sizeof(endTime));
            }
        }

        if (idx < count && simulationClock >= commuters[idx].timeOfArrival) {
            if (commuters[idx].travelDirection == operatingDirection) {
                endTime = simulationClock + 10;
                processedCommuters++;
                write(commPipe[1], &endTime, sizeof(endTime));
                idx++;
            } else {
                delayedCommuter = commuters[idx++];
                isCommuterWaiting = 1;
            }
        }

        simulationClock++;
    }
}

int main() {
    FILE *inputStream = fopen("input.txt", "r");
    if (!inputStream) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fscanf(inputStream, "%d", &numberOfCommuters);
    Commuter *commuters = malloc(numberOfCommuters * sizeof(Commuter));

    for (int i = 0; i < numberOfCommuters; i++) {
        fscanf(inputStream, "%d %d", &commuters[i].timeOfArrival, &commuters[i].travelDirection);
    }
    fclose(inputStream);

    if (pipe(commPipe) != 0) {
        perror("Pipe creation failed");
        free(commuters);
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == 0) {
        close(commPipe[0]);
        simulateEscalatorOperation(commuters, numberOfCommuters);
        close(commPipe[1]);
        free(commuters);
        exit(EXIT_SUCCESS);
    }

    close(commPipe[1]);
    FILE *outputStream = fopen("output.txt", "w");
    int finalOperationTime;
    while (read(commPipe[0], &finalOperationTime, sizeof(finalOperationTime)) > 0) {
        fprintf(outputStream, "%d\n", finalOperationTime);
    }
    fclose(outputStream);
    close(commPipe[0]);

    printf("Final escalator operation ends at: %d\n", finalOperationTime);

    wait(NULL);
    return EXIT_SUCCESS;
}
