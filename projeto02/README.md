# Projeto 2 - Sistemas Operacionais
 Neste projeto vamos  ver o trecho de código tem como objetivo zerar o saldo de uma conta (from) através de várias transferências para a outra (to). Contudo, acontece uma falha em sua execução causada por um dos
problemas relativos à concorrência apresentados em sala. Para que o código seja executado com sucesso, é necessário identificar o problema e apresentar uma solução, com base nas observações relativas aos problemas e suas soluções discutidos em sala.

# Bibliotecas incluidas

#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h>

# Função de Transferência

![image](https://github.com/JoaoGian/labSO/assets/118188665/f3b4db98-f289-4be2-9d72-a6ce93058f2f)

o parâmetro: Recebe um ponteiro arg que indica a direção da transferência. É convertido para um inteiro (direction).
---Direção da Transferência:  
          0 (from -> to)
---Trava os mutexes lock_from e lock_to.
---Verifica se from.saldo é suficiente para a transferência.
---Realiza a transferência ajustando os saldos de from e to.
---Destrava os mutexes.
        1 (to -> from):
---Trava os mutexes lock_to e lock_from.
---Verifica se to.saldo é suficiente para a transferência.
---Realiza a transferência ajustando os saldos de to e from.
---Destrava os mutexes.
# Função Principal

![image](https://github.com/JoaoGian/labSO/assets/118188665/c05bd4b3-6ba1-460e-ad6a-c8412cd0bc3e)

![image](https://github.com/JoaoGian/labSO/assets/118188665/eb6b199b-4a3f-4d06-b0ee-552c6c9f4f09)


Inicialização dos Mutexes:

Inicializa os mutexes lock_from e lock_to.
Se a inicialização falhar, exibe uma mensagem de erro e encerra o programa.
Alocação da Pilha:

Aloca a pilha de tamanho FIBER_STACK.
Se a alocação falhar, exibe uma mensagem de erro e encerra o programa.
Configuração Inicial das Contas:

Define o saldo inicial das contas from e to como 100.
Criação das Threads:

Loop para criar 100 threads utilizando a chamada de sistema clone.
Alterna entre transferências de from para to (direção 0) e de to para from (direção 1).
Para cada iteração, ajusta a direção da transferência e cria uma thread para executar a função transferencia.
Se a criação da thread falhar, exibe uma mensagem de erro e encerra o programa.
Sincronização e Finalização:

O programa espera que todas as threads terminem usando a função wait.
Após a conclusão de todas as threads, a memória alocada para a pilha é liberada.
Os mutexes são destruídos para liberar recursos.
Exibe uma mensagem final indicando a conclusão das transferências e os saldos finais das contas.


# EXPLICACAO DO CODIGO 

Este código ilustra uma aplicação prática de sincronização de threads utilizando mutexes para garantir a integridade dos dados em operações concorrentes. Ele demonstra a criação e gerenciamento de threads, alocação de memória para pilhas de threads e uso de mutexes para evitar condições de corrida. Ao seguir as práticas de sincronização, o código assegura que as transferências entre as contas sejam realizadas de forma segura e correta, mesmo em um ambiente altamente concorrente.




























