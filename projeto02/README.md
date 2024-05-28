## Projeto 2 - Sistemas Operacionais

## Tranferência de fundos entre duas contas
Neste projeto, foi desenvolvido um programa para simular a transferência de fundos entre duas contas, denominadas To (destino) e From (origem). O programa é implementado utilizando threads da biblioteca Pthreads no Linux, onde cada thread representa uma operação de transferência entre as contas. Para resolver os problemas de concorrência e evitar condições de corrida, o programa utiliza mutexes da biblioteca Pthreads. Esses mutexes garantem que apenas uma thread por vez possa acessar a região crítica de memória, onde o saldo da conta de origem é atualizado. O programa permite que as transferências ocorram em ambas as direções  da conta From para a conta To e vice-versa - durante a execução. Isso é controlado de acordo com a direção especificada para cada thread, e o saldo só é transferido se a conta de origem tiver fundos suficientes.
Na primeira abordagem, as transferências das duas  direções utilizam o mesmo valor de 100 unidades. Na segunda abordagem, valores diferentes são usados nas transferências - 100  em uma direção e 0 na outra. 

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





## Comprovante dos resultados 

1.A conta to pode receber mais de uma transferência simultânea;



2.A conta from pode enviar mais de uma transferência simultânea;


3.A conta from não pode enviar dinheiro se não tiver mais saldo;



4.A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode
receber e a conta que recebia pode enviar;


5.Poderão ser realizadas até 100 transações simultâneas de transferência;



##Execucao do programa sendo realizada

1.Duas contas transferindo o mesmo valor entre si





2.Conta To enviando todo o dinheiro para From


























