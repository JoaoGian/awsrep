## LabSO--Lab02

#QUESTAO A : Você é capaz de identificar os trechos executados por pai e filho?

Da para identificar os trechos executados por pai e filho sim, a função fork() cria um novo processo copiando o processo existente (pai) e retorna um  PID diferente de zero para o processo pai, enquanto retorna zero para o processo filho recém-criado, portanto, o processo filho e caracterizado por else if (pid==0) que imprime que ele é o filho (o filho executa o comando  ls utilizando execlp), agora no pai, depois  da chamada fork() , o processo pai entrando no else, esperando a conclusao do processo filho no caso a funcao wait(NULL) ate que ela termine o processo pai se mantem, apos o termino do processo filho no caso a execucao do wait(NULL), o processo pai imprime que o processo filho esta completo. 

#QUESTAO B : Quantos processos serão criados?

 No caso a seguir serao criados exatos 8 processos ja que para cada chamada do fork() que cria um novo processo se duplicando cada vez.


# Codigo rodando no console da AWS


![Screenshot 2024-03-11 212105](https://github.com/JoaoGian/labSO/assets/118188665/a66c5dd3-0ecd-4f45-904a-709c367cda70)


