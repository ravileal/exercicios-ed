#ifndef LISTCIRC2_H
#define LISTCIRC2_H

struct Node;

class List {
public:
    // Construtor: cria uma lista simplesmente encadeada circular
    // com no cabeca. O no cabeca eh obrigatorio na implementacao desta lista
    List(); 

    // Destrutor: libera toda memoria que foi alocada
    ~List(); 


    // push_back: insere um no com valor x ao final da lista
    void push_back(int key); 

    // pop_back: remove o elemento que esta no final da lista 
    // retorna o valor do no caso ele exista; 
    // ou retorna INT_MIN caso não exista ultimo elemento
    int pop_back();

    //Insere um novo no com valor key apos o
    //k-esimo no da lista.
    bool insertAfter(int key, int k);

    // remove: remove o primeiro no com valor x
    void remove(int key); 

    // removeAll: remove todos os nos com valor x
    void removeAll(int key); 

    void print();

    void printReverse();

    // empty: retorna true se a lista estiver vazia;
    // retorna false caso contrario
    bool empty(); 

    // size: retorna a quantidade de elementos na lista
    int size(); 

    // clear: deixa a lista vazia, sem elementos  
    void clear();

    void concat(List *lst);

    List *copy();

    void copyArray(int n, int arr[]);

    bool equal(List *lst);

    // contains: retorna true se a lista contem um no com valor x;
    // retorna false caso contrario
    bool contains(int x);


private:
    // Ponteiro para o no cabeca da lista
    Node *head;

    // Operacao auxiliar: retorna o no anterior ao no com valor x; 
    // ou retorna nullptr caso nenhum no com valor x esteja presente 
    Node *search(int x);
};

#endif