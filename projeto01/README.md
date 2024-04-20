PROBLEMA - PROCESSOS

1. Qual aa estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?

No código de processos apresentado, não foi incluído nenhum mecanismo específico para impedir que duas pessoas acessem a escada rolante simultaneamente. Cada processo simula individualmente a chegada e ação de uma pessoa. Em um cenário real com um sistema operacional e uma aplicação prática, seria essencial implementar mecanismos de sincronização usando IPC, como semáforos ou memória compartilhada com locks(travas), para controlar o acesso à escada rolante e garantir que apenas um processo (pessoa) possa utilizá-la por vez.
 
2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

Para assegurar que apenas um lado da escada rolante esteja em funcionamento em um ambiente com múltiplos processos, é necessário estabelecer uma comunicação entre os processos para coordenar qual direção está ativa.
Nos vamos fazer isso com semáforos, ja que se pode usar semáforos para bloquear o acesso à escada quando uma direção está ativa, forçando os processos que desejam movê-la na direção oposta a esperar. Ou podemos utilizar a memória compartilhada ja que uma área de memória compartilhada pode ser utilizada para armazenar o estado atual da escada (direção e operação). 


PROBLEMA - THREADS

1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?
No entanto, no código acima eu não implementei qualquer mecanismo específico para impedir que duas pessoas acessem a escada rolante ao mesmo tempo. Isso ocorre porque, apesar de criar threads para que pudessem simular a chegada de pessoas em horários diferentes, isso não impede que elas tentem acessar a escada rolante ao mesmo tempo. Para conseguir resolver esse problema seria ideal usar mutexes ou semáforos para sincronizar o acesso à escada rolante, para que somente uma thread ou pessoa podesse operá-la em qualquer momento


2.  Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens? 

Um sistema de multi-thread em que apenas uma direção da escada rolante esteja em uso a qualquer momento em um sistema de threads múltiplas pode ser implementado com uma variável de condição adicional junto com um mutex. A variável de condição usaria o estatuto para bloquear threads que tentaram aceder à escada rolante para cima mesmo quando a escada rolante está a ser utilizada para baixo, até a escada estar livre novamente.




PROBLEMA QUESTAO 3 DE PROCESSOS E THREADS

3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.

 As threads compartilham memória e recursos com o processo principal(pai), tornando a comunicação e a sincronização entre elas mais fáceis. Por outro lado, os processos são isolados e precisam de mecanismos externos (IPC) para compartilhar informações, o que geralmente é menos eficiente. Os processos proporcionam um isolamento mais eficaz, o que é positivo para a segurança e estabilidade do sistema em geral. No entanto, em situações que requerem uma comunicação intensa e coordenação, como neste exemplo, isso pode representar um obstáculo. Tambem e bom lembrar que Threads são mais leves e rápidas gerenciar do que processos. Visto isso, a implementação utilizando threads é geralmente mais eficiente para o problema em questão,  e  a comunicação e sincronização entre threads são mais diretas e além disso, a gestão de threads por um único processo permite uma coordenação mais eficiente da lógica de controle, como a direção de uma  escada rolante, devido à menor complexidade e ao menor overhead de gerenciamento e sincronização.


