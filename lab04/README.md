LABORATORIO 04------Solução utilizando pthreads para resolver o problema da multiplicação matriz-vetor

![image](https://github.com/JoaoGian/labSO/assets/118188665/e88719bd-0fe3-4691-a5ad-60b11e80c935)

Relatorio:
O código em C realiza uma multiplicação de uma matriz por um vetor de forma paralela, utilizando  múltiplas threads. A multiplicação em questão é uma operação matemática onde um vetor resultante é obtido ao se calcular o produto escalar de cada linha da matriz pelo vetor dado. 
O código define primeiramente a matriz e o vetor com valores específicos. Em seguida, ele da várias threads para dividir o trabalho de multiplicação, onde cada thread calcula uma parte do vetor resultante. Isso permite que o programa tire proveito de múltiplos núcleos de processamento disponíveis em um computador moderno, realizando várias operações em paralelo e, assim, potencialmente acelerando o cálculo.
Cada thread é encarregada de multiplicar uma seção da matriz pelo vetor, e o alcance de cada seção é determinado pelos parâmetros passados para as threads. Após o início das threads, o programa espera que todas completem sua tarefa antes de proceder. Ao fim da execução das threads, o vetor resultante é coletado e impresso na saída padrão.

PRINT AWS:

![image](https://github.com/JoaoGian/labSO/assets/118188665/67c80ea2-c478-422d-aa5f-2945414561e4)
