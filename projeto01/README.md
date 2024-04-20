PROBLEMA - PROCESSOS

1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?

No código fornecido, a estratégia utilizada envolve controlar o acesso à escada rolante por meio de uma simulação de relógio (simulationClock) e de uma variável que registra o tempo final de operação (endTime). O programa garante que cada passageiro inicie sua travessia apenas quando o simulationClock é igual ou maior que seu tempo de chegada (timeOfArrival) e somente se a escada estiver operando na direção desejada (travelDirection). Caso a escada esteja operando na direção oposta, o passageiro é colocado em espera (isCommuterWaiting setado como verdadeiro e o passageiro é armazenado em delayedCommuter), até que a escada rolante termine seu ciclo atual e possa ser reiniciada na direção correta. Esta abordagem serializa efetivamente o acesso à escada, garantindo que apenas uma operação de travessia ocorra dentro de cada período de 10 segundos.
 
2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

Para assegurar que apenas um lado da escada rolante esteja em funcionamento em um ambiente com múltiplos processos, é necessário estabelecer uma comunicação entre os processos para coordenar qual direção está ativa.
Nos vamos fazer isso com semáforos, ja que se pode usar semáforos para bloquear o acesso à escada quando uma direção está ativa, forçando os processos que desejam movê-la na direção oposta a esperar. Ou podemos utilizar a memória compartilhada ja que uma área de memória compartilhada pode ser utilizada para armazenar o estado atual da escada (direção e operação).-- O controle da direção da escada é gerido pela variável operatingDirection, que é alternada cada vez que um ciclo de 10 segundos se completa sem mais passageiros para processar na direção corrente ou quando um passageiro em espera pode ser processado na direção oposta. A alternância é feita por uma lógica condicional que verifica se um passageiro em espera (delayedCommuter) tem a direção compatível com a direção atualmente necessária. Se sim, a direção da escada é ajustada para essa direção e a operação continua. Esse mecanismo assegura que, em qualquer momento, a escada só possa operar em uma direção, mudando apenas quando não houver mais passageiros para aquela direção ou quando um passageiro em espera precisa ser atendido na direção oposta.


PROBLEMA - THREADS

1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?
O programa usa um mutex(exclusão mútua) para controlar o acesso à variável last_exit_time, garantindo que apenas uma thread por vez possa ajustar o momento em que a última pessoa terminará de usar a escada rolante. Isso impede que duas pessoas acessem a escada ao mesmo tempo. A apesar de criar threads para que pudessem simular a chegada de pessoas em horários diferentes, isso não impede que elas tentem acessar a escada rolante ao mesmo tempo. Para conseguir resolver esse problema seria ideal usar mutex ou semáforos para sincronizar o acesso à escada rolante, para que somente uma thread ou pessoa podesse operá-la em qualquer momento.


2.  Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens? 

 incluir uma variável global como por exemplo (current_direction) que registre a direção atual da escada e ajustar esse valor conforme as pessoas a utilizem, além de sincronizar as mudanças de direção para garantir que a escada opere em apenas uma direção por vez. Ou um sistema de multi-thread em que apenas uma direção da escada rolante esteja em uso a qualquer momento em um sistema de threads múltiplas pode ser implementado com uma variável de condição adicional junto com um mutex. A variável de condição usaria o estatuto para bloquear threads que tentaram aceder à escada rolante para cima mesmo quando a escada rolante está a ser utilizada para baixo, até a escada estar livre novamente.




PROBLEMA QUESTAO 3 DE PROCESSOS E THREADS

3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.

 As threads compartilham memória e recursos com o processo principal(pai), tornando a comunicação e a sincronização entre elas mais fáceis. Por outro lado, os processos são isolados e precisam de mecanismos externos (IPC) para compartilhar informações, o que geralmente é menos eficiente. Os processos proporcionam um isolamento mais eficaz, o que é positivo para a segurança e estabilidade do sistema em geral. No entanto, em situações que requerem uma comunicação intensa e coordenação, como neste exemplo, isso pode representar um obstáculo. Tambem e bom lembrar que Threads são mais leves e rápidas gerenciar do que processos. Visto isso, a implementação utilizando threads é geralmente mais eficiente para o problema em questão,  e  a comunicação e sincronização entre threads são mais diretas e além disso, a gestão de threads por um único processo permite uma coordenação mais eficiente da lógica de controle, como a direção de uma  escada rolante, devido à menor complexidade e ao menor overhead de gerenciamento e sincronização.


print --- processo

![image](https://github.com/JoaoGian/labSO/assets/118188665/1d65e169-7d7d-4187-9add-8b981b9e4718)


print thread --- 

![image](https://github.com/JoaoGian/labSO/assets/118188665/2c018c74-e022-4d53-985a-3baf69a66203)

erros do codigo de threads: quando testei apesar de ter dado o tempo correto, no aws deu o resultado 43.

