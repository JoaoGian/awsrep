## Projeto 2 - Sistemas Operacionais

## Tranferência de fundos entre duas contas

Este código ilustra uma aplicação prática de sincronização de threads utilizando mutexes para garantir a integridade dos dados em operações concorrentes. Ele demonstra a criação e gerenciamento de threads, alocação de memória para pilhas de threads e uso de mutexes para evitar condições de corrida. Ao seguir as práticas de sincronização, o código assegura que as transferências entre as contas sejam realizadas de forma segura e correta, mesmo em um ambiente altamente concorrente.

## Bibliotecas incluidas

#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h>

#para executar o programa





##Comprovante dos resultados 

1.A conta to pode receber mais de uma transferência simultânea;



2.A conta from pode enviar mais de uma transferência simultânea;


3.A conta from não pode enviar dinheiro se não tiver mais saldo;



4.A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode
receber e a conta que recebia pode enviar;


5.Poderão ser realizadas até 100 transações simultâneas de transferência;



##Execucao do programa sendo realizada

1.Duas contas transferindo o mesmo valor entre si





2.Conta To enviando todo o dinheiro para From


























