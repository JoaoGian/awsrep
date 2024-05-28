## Projeto 2 - Sistemas Operacionais

## Tranferência de fundos entre duas contas
Neste projeto, foi desenvolvido um programa para simular a transferência de fundos entre duas contas, denominadas To (destino) e From (origem). O programa é implementado utilizando threads da biblioteca Pthreads no Linux, onde cada thread representa uma operação de transferência entre as contas. Para resolver os problemas de concorrência e evitar condições de corrida, o programa utiliza mutexes da biblioteca Pthreads. Esses mutexes garantem que apenas uma thread por vez possa acessar a região crítica de memória, onde o saldo da conta de origem é atualizado. O programa permite que as transferências ocorram em ambas as direções  da conta From para a conta To e vice-versa - durante a execução. Isso é controlado de acordo com a direção especificada para cada thread, e o saldo só é transferido se a conta de origem tiver fundos suficientes.


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

![image](https://github.com/JoaoGian/labSO/assets/118188665/3d973cf8-7fd9-40a8-9a17-d6df1735fd63)





![image](https://github.com/JoaoGian/labSO/assets/118188665/92a83bf6-7d7d-41b2-bb14-fde6af336e46)




3.A conta from não pode enviar dinheiro se não tiver mais saldo;

![image](https://github.com/JoaoGian/labSO/assets/118188665/79707356-0b01-4da0-9b29-ac79dae052a5)


![image](https://github.com/JoaoGian/labSO/assets/118188665/7a993898-9f06-4cae-a1d1-a5fa959bcf0d)

![image](https://github.com/JoaoGian/labSO/assets/118188665/34dd0d83-ebeb-45a0-80fd-bd540d157988)
A conta foi insuficiente, pois as transferencias estavam sendo feitas de 20 em 20





![image](https://github.com/JoaoGian/labSO/assets/118188665/79707356-0b01-4da0-9b29-ac79dae052a5)





4.A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode
receber e a conta que recebia pode enviar;

![image](https://github.com/JoaoGian/labSO/assets/118188665/04da05ae-a8ce-4bc1-b146-7422d0fe2827)



![image](https://github.com/JoaoGian/labSO/assets/118188665/bcffc091-a4d1-4e16-9532-e73d4ae36c29)


5.Poderão ser realizadas até 100 transações simultâneas de transferência;

![image](https://github.com/JoaoGian/labSO/assets/118188665/99e252fd-de8b-46da-9c2a-f5c8268c8c8b)

![image](https://github.com/JoaoGian/labSO/assets/118188665/3d4b33f6-cce8-44e4-9d88-aed939c930ae)

![image](https://github.com/JoaoGian/labSO/assets/118188665/aeb6a100-9230-445c-94c3-b16bb0af1462)

![image](https://github.com/JoaoGian/labSO/assets/118188665/bd6becde-71f5-4688-a9a3-b6d33156d21d)

![image](https://github.com/JoaoGian/labSO/assets/118188665/075833a1-f5ad-4096-97d3-619912c567b5)

![image](https://github.com/JoaoGian/labSO/assets/118188665/a4ae0e6a-8e67-4aa9-967c-a8a4be723052)

![image](https://github.com/JoaoGian/labSO/assets/118188665/98bedb30-cfb5-4bcd-b8b0-8708cf016400)

![image](https://github.com/JoaoGian/labSO/assets/118188665/42ab01f6-950d-4db8-b86b-d040ab9f7dbe)















##Execucao do programa sendo realizada

1.Duas contas transferindo o mesmo valor entre si





2.Conta To enviando todo o dinheiro para From


























