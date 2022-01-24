# Sistema Operacional

### Desenvolvedores: Gabriel de Souza, Patrick Menezes, Pedro Henrique e Wallace Ketler

-------------------------------------------------------------------------------------------

O projeto consiste no desenvolvimento de um sistema operacional básico em Shell que permita a verificação de informações de hardware referentes ao processador, memória primária e secundária. 

Para tanto, cada componente eletrônico do computador foi representado por estruturas de dados de forma que simule sua eficiência real (Uma vez que componentes como a memória RAM de um computador executam buscas de maneira mais veloz que a memória secundária, por exemplo).

Logo, o processador foi representado por uma Lista (através da biblioteca list), o disco por uma pilha (com a biblioteca stack) e a memória RAM por uma tabela Hash (por meio do código do programador Gustavo Pantuza, cujo GitHub se encontra em https://github.com/pantuza).

Informações como tamanho das memórias e a quantidade de cores do processador estão armazenadas no formato json.

-------------------------------------------------------------------------------------------
## Comando help
![help](https://user-images.githubusercontent.com/56899474/147612796-89829b27-3848-4014-acf2-30bb6d6cdb19.png)


Através do comando help e também ao entrarmos a primeira vez em nosso sistema, nos deparamos com as informações dos comandos passíveis de uso que podem ser vistos na imagem acima.

-------------------------------------------------------------------------------------------
## Comando cpuInfo

![cpuinfo](https://user-images.githubusercontent.com/56899474/147612794-99000269-7785-4a78-9ee8-db180294a587.png)

Ao usarmos o comando cpuInfo é possível visualizarmos tanto a quantidade total de cores como também quantos estão em uso. A partir disso, também podemos visualizar, para cada core, qual o id, nome, hora de acesso e descrição do processo executado neste local do CPU.


-------------------------------------------------------------------------------------------
## Comando memoryInfo

![memoryinfo](https://user-images.githubusercontent.com/56899474/147612797-7e42fa9e-a3c6-4575-9d21-d5467e64dadf.png)

O uso do comando memoryInfo nos permite visualizarmos a quantidade máxima de memória RAM e quanto dela está em uso. Além disso, para cada bloco de memória, podemos ver qual o id, nome, hora de acesso e descrição do processo que está sendo executado e que demandou alocação na memória primária.




-------------------------------------------------------------------------------------------
## Comando discInfo

![discinfo](https://user-images.githubusercontent.com/56899474/147612795-d96a623b-dc1c-4017-84c9-856a9c547bc8.png)

O último comando de visualização consiste na amostragem dos dados do disco, como o tamanho e quanto disso está em uso. Por consequência, também podemos ver o nome, tipo, tamanho e data e hora de escritura de determinado arquivo na memória ROM.

-------------------------------------------------------------------------------------------
## Comando exit

Permite a saída do programa.

-------------------------------------------------------------------------------------------

# Comandos adicionados após primeira entrega:
## htop

Permite verificarmos informações gerais dos processos em execução, como timeStamp, ciclos atuais que restam de execução, a prioridade e seu tipo (io-bound, memory-bound, ou cpu-bound), além do ID do processo.

![git3](https://user-images.githubusercontent.com/56899474/150046596-d5ada130-6250-40a5-8d29-aa6c3fed51c7.png)


## loadProcess

Este comando carrega os processos a partir de um .json para serem executados.


## Como seria possível melhorar tempo de execução dos processos?

A partir da análise do histórico gerado, que inclui o timeStamp de cada processo, percebemos que uma otimização poderia ser feita a partir de outro tipo de abordagem com as threads, já que, uma vez que permitissemos que cada tipo de processo executasse em uma thread diferente, teríamos, através de concorrência, uma execução mais eficaz.








A forma de compilar tal projeto segue com os comandos make e make run devido ao Makefile.
