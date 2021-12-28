/*
** Direitos reservado à Gustavo Pantuza
** GitHub - https://github.com/pantuza
** Referência - https://blog.pantuza.com/artigos/tipos-abstratos-de-dados-tabela-hash
*/

#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>
#include <array>
#include <vector>


using namespace std;

/*
 * Classe que implementa uma tabela Hash. A classe recebe como parâmetros
 * do template as classes das chaves e dos valores
 *
 * Ex: HashTable<string, string> hash_table;
 *
 * Nesse exemplo ambos, chave e valor, são do tipo string.
 *
 */
template<class KeyType, class ValueType>
class HashTable {
 private:
    /* Struct que representa cada entrada da tabela */
    struct Entry {
        int index;
        KeyType key;
        ValueType value = ValueType("","","","",1);
    };

    /* Número atual de itens dentro da tabela */
    unsigned int entries_n = 0;

    /* Tamanho total da tabela a ser alocada */
    int MAX_SIZE = 0;

    /* Um item do tipo Entry vazio. Utilizado como valor default de itens */
    struct Entry DEFAULT_VALUE;

    /* Tabela de ites do tipo Entry com tamanho máximo permitido */
    //struct Entry (*table)[5];
    vector<struct Entry> table;

    /* Método privado para uso exclusivo de debbuging */
    void debbug(struct Entry* entry)
    {
        cout << "[" << entry->index << "]('" << entry->key
             << "', '" << entry->value << "')" << endl;
    }

    /**
    * Método da classe que gera um inteiro randômico
    * entre 0 e MAX_SIZE.
    */
    int randInt()
    {
         return (rand() % MAX_SIZE);
    }

    /*
     * O tão importante método de Hashing
     */
    int hash(KeyType key)
    {
       if (this->isTableFull()) {
            return this->DEFAULT_VALUE.index;
        }

        int counter = 0;

        /* Vamos usar o índice de cada caracter como multiplicador da letra.
         * Palavras que possuem as mesmas letras irão gerar colisão. Para tal
         * iremos considerar a posição da letra dentro da string
         */
        int i = 1;
        for (char& c : key) {
            counter += i++ * int(c); // Multiplica pelo índice dentro da string
        }

        /* Executa o passo de sondagem e retorna o índice */
        return this->probe(counter, key);
    }

    /*
     * Método responsável por executar o passo de sondagem (probing)
     * da estratégia Endereçamento aberto (Open Addressing)
     */
    int probe(const int counter, const KeyType key)
    {

        int index = static_cast<int>(counter % MAX_SIZE);

        /* Enquanto não é um endereço vazio */
        while(this->table[index].index != this->DEFAULT_VALUE.index) {

            /* Se a chave é a solicitada no hash, retornamos seu índice */
            if (this->table[index].key == key) {
                return index;
            }
            /*
             * Usamos a operação de MOD para garantir que sempre teremos
             * um índice válido entre 0 e MAX_SIZE
             */
            index = ++index % MAX_SIZE;
        }

        return index;
    }

    /*
     * Verifica se a tabela hash está cheia
     */
    bool isTableFull()
    {
        if (this->entries_n == MAX_SIZE) {
            return true;
        }
        return false;
    }

 public:
    /*
     * Construtor da tabela Hash
     */
    HashTable(int size)
    {
        /* Definindo o tamanho máximo da tabela Hash */
        MAX_SIZE = size;
        struct Entry aux;
        aux.key = -1;

        for(int i = 0; i < size; i++){
            aux.value.core = i;
            table.push_back(aux);
        }

        this->DEFAULT_VALUE.index = -1;
        /* gera semente aleatória para o método std::rand() */
        srand(time(nullptr));

        /* Inicializamos nossa tabela inteira com nosso valor default */
        for (auto& e : this->table) {
            e.index = this->DEFAULT_VALUE.index;
        }
    }

    void Print(){
        table.front().value.printHead(1);
        int used = 0;
        for(Entry data : table){
            data.value.print();
            if(data.value.name != ""){
                used++;
            }
        }
        table.front().value.printFooter();

        cout<<"Total de Memória RAM:    "<<table.size()<<endl;
        cout<<"Memória RAM Utilizada:   "<<used<<endl;
        cout<<"Memória RAM Disponível:  "<<table.size() - used<<endl;
    }




    /*
     * Busca por uma chave dentro da tabela utilizando a função hash
     */
    ValueType* LookUp(KeyType key)
    {
        int index = this->hash(key);

        /* Se não encontramos a chave retornamos um valor nulo */
        if (index == this->DEFAULT_VALUE.index) {
            this->debbug(&this->DEFAULT_VALUE);
            return new ValueType();

        } else {
            /* Se encontramos o item da chave, retornamos seu valor */
            this->debbug(&this->table[index]);
            return &this->table[index].value;
        }
    }

    /*
     * Insere uma nova chave com um valor dentro da tabela hash
     */
    bool Put(KeyType key, ValueType value)
    {
        if(this->isTableFull()) {
            cout << "Table full!" << endl;
            return false;
        }

        int index = this->hash(key);

        if (this->table[index].key == key) {
            cout << "Key '" << key << "' already exist" << endl;
            return false;
        }

        /* Criamos um novo objeto do struct Entry */
        struct Entry* entry = new Entry();
        entry->index = index;
        entry->key = key;
        entry->value = value;

        /* Inserimos o novo objeto no índice computado pela função Hash */
        this->table[index] = *entry;
        this->debbug(entry);
        this->entries_n++;
        return true;
    }

    /*
     * Atualiza o valor de uma chave
     */
    bool Update(KeyType key, ValueType value)
    {
        int index = this->hash(key);

        /* Se não encontramos a chave retornamos um valor nulo */
        if (index == this->DEFAULT_VALUE.index) {
            this->debbug(&this->DEFAULT_VALUE);
            return false;

        } else {

            /* Se encontramos o item da chave, atualizamos seu valor */
            this->table[index].value = value;
            this->debbug(&this->table[index]);
            return true;
        }
    }

    /*
     * Remove um item de dentro tabela através de sua chave
     */
    bool Del(KeyType key) {

        int index = this->hash(key);

        /* Se a chave não existe então não removemos nada */
        if (index == this->DEFAULT_VALUE.index) {
            return false;
        }

        /* Caso contrário removemos o item da tabela retornamos true */
        this->debbug(&this->table[index]);
        this->table[index] = this->DEFAULT_VALUE;
        this->entries_n--;
        return true;
    }
};