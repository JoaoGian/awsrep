## Projeto 2 - Sistemas Operacionais

## Tranferência de fundos entre duas contas

Neste projeto, foi desenvolvido um programa para simular a transferência de fundos entre duas contas,  To (destino) e From (origem). As duas contas, contaOrigem e contaDestino, começam com um saldo inicial de 100 unidades cada uma. O programa cria 100 threads, divididas igualmente para realizar duas operações: transferir um montante de contaOrigem para contaDestino (montante1 de 20 unidades) e transferir um montante de contaDestino para contaOrigem (montante2 de 10 unidades). 
As funcoes de cada transferencia  são protegidas por um mutex para evitar condições de erro, garantindo que apenas uma thread por vez possa modificar os saldos das contas.
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

./nome_criado_para_executar (proj02)




## Comprovante dos resultados 

1.A conta to(destino) pode receber mais de uma transferência simultânea;
2.A conta from(origem) pode enviar mais de uma transferência simultânea;


![image](https://github.com/JoaoGian/labSO/assets/118188665/e5bfcb7c-10c1-410f-9244-1f955af08c11)



A conta to esta recebendo em  mais de uma transferencia.







3.A conta from não pode enviar dinheiro se não tiver mais saldo;

![image](https://github.com/JoaoGian/labSO/assets/118188665/79707356-0b01-4da0-9b29-ac79dae052a5)


![image](https://github.com/JoaoGian/labSO/assets/118188665/7a993898-9f06-4cae-a1d1-a5fa959bcf0d)


![image](https://github.com/JoaoGian/labSO/assets/118188665/34dd0d83-ebeb-45a0-80fd-bd540d157988)


A conta foi insuficiente, pois as transferencias estavam sendo feitas de 20 em 20. O programa impede ao verificar o valor de tranferência da conta ,  permitindo a transferência caso tenha saldo maior igual ao valor anterior.





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










































