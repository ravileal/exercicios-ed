#include <iostream>
#include <string>
#include <climits>
#include "List.h"

using namespace std;

/* 
 * ============================
 *      Estrutura inicial
 * ============================ 
*/

// Nó inicial
struct Node {
    int value;
    Node *next;
    Node *back;
    ~Node() { std::cout << "no com valor " << value << " liberado" << std::endl; }
};


// Construtor da lista
List::List() {
    head = new Node; // cria nó cabeca
    head -> next = head; // inicializa next do nó cabeca
    head -> back = head; // inicializa back do nó cabeca
    head -> value = INT_MIN;
}

// Destrutor: libera toda memoria que foi alocada
List::~List() {
    clear();
    delete head;
    std::cout << "lista liberada" << std::endl;
}


/* 
 * ============================
 *      Funcões de pesquisa
 * ============================ 
*/

// Operacao auxiliar: retorna o no com valor x; 
// ou retorna nullptr caso nenhum no com valor x esteja presente
Node * List :: search ( int key ) {
    if( empty() ){ // Lista vazia
        return nullptr;
    }
    Node * aux = head -> next;
    do {
        if( aux -> value == key ){
            return aux ;
        }
        aux = aux -> next;
    }while ( aux != head -> next );
    return nullptr ;
}


/* 
 * ============================
 *    Funcões de adicionar
 * ============================ 
*/

// push_back: insere um no com valor x ao final da lista
void List::push_back(int key) {
    Node * novo = new Node;
    novo -> value = key;
 
    if( empty() ) { // Caso a lista esteja vazia
        // atualizacao do novo nó
        novo -> next = head; // Cria o próximo do novo nó
        novo -> back = head; // Cria o anterior do novo nó
    
        // atualizacao do nó head
        head -> next = novo; // Atualiza o proximo do nó head
        head -> back = novo; // Atualiza o anterior do nó head
    }
    else { // Caso a lista nao esteja vazia

        // atualiza o novo nó
        novo -> next = head;
        novo -> back = head -> back;    

        // atualizar o ultimo nó anterior
        Node * last  = head -> back;      
        last -> next = novo;

        // atualizar o nó head
        head -> back = novo;
    }

}

// Insere um novo no com valor key apos o k-esimo no da lista.
// Deve-se ter 0 <= k < size() para que a insercao seja realizada; 
// caso contrario, nao sera realizada.
bool List::insertAfter( int key, int k ){
    if( k < 0 || k >= size() ){ // verifica o indice recebido está dentro do range aceitavel
        cout << "Erro: Posicao incorreta." << endl;
        return false;
    }else if( k != 0 && empty() ){
        cout << "Erro: Posicao incorreta. Lista Vazia" << endl;
        return false;
    }

    Node * novo = new Node;
    novo -> value = key;

    Node * aux = head;

    for (int i = 0; i < k; i++){
        aux = aux -> next;
    }

    Node * aux2 = aux -> next;
    aux2 -> back = novo;

    novo -> next = aux -> next; // Cria o próximo do novo nó
    novo -> back = aux; // Cria o anterior do novo nó

    aux -> next = novo;

    return true;
}

/* 
 * ============================
 *    Funcões de remover
 * ============================ 
*/

// removeAll: remove todos os nos com valor x
void List :: removeAll (int key) {
    while ( contains (key)){
        remove (key);
    }
}

// remove: remove o primeiro nó com valor x
void List :: remove (int key) {
    Node * noRem = search ( key );
    if( noRem == nullptr ){
        cout << "Erro: Valor nao encontrado." << endl;
        return ; // lista vazia ou nao tem x
    }
    // Percorrer a lista ate achar o antecessor do no
    Node * ant = noRem -> back;
    Node * pro = noRem -> next;
    // Ajusta ponteiros e remove o no com valor x
    ant -> next = noRem -> next;
    pro -> back = ant;

    delete noRem;
}

// pop_back: remove o elemento que esta no final da lista 
// retorna o valor do no caso ele exista; 
// ou retorna INT_MIN caso nao exista ultimo elemento
int List :: pop_back () {
    if( empty() ) { // Caso a lista esteja vazia
        return head -> value;
    }
    // Caso a lista nao esteja vazia //
    
    // Salva ultimo nó, que será excluído
    Node * last = head -> back;
    int value = last -> value;

    //atualiza o back do head
    head->back = last-> back;

    // atualiza o next do penultimo
    Node * aux = head -> back;
    aux -> next = head;

    delete last;
    return value;
}

/* 
 * ============================
 *      Funcões utilitarias
 * ============================ 
*/

// contains: retorna true se a lista contem um no com valor x;
// retorna false caso contrario
bool List :: contains ( int x) {
    return ( search (x) != nullptr );
}

// empty: retorna true se a lista estiver vazia;
// retorna false caso contrario
bool List :: empty () {
    return ( head == head -> next );
}

// size: retorna a quantidade de elementos na lista
int List :: size () {
    if ( empty() ){
        return 0;
    }
    Node * aux = head -> next ;
    int s = 1;
    while ( aux -> next != head -> next ) {
        s++;
        aux = aux -> next;
    }
    return s;
}

// clear: deixa a lista vazia, sem elementos 
void List :: clear () {
    if( empty() ){
        return;
    }    
    // Se o head nao é vazio, faca

    Node * aux = head->next;

    while ( aux -> next != head ){
        Node * aux2 = aux;
        aux = aux -> next;
        delete aux2;
    }

    delete aux;
    // resetando nó cabeca
    head->next = head;
    head->back = head;
}


// imprime todos os itens da lista
void List:: print(){
    if( empty() ){
        cout << "Erro: Lista vazia." << endl;
        return;
    }
    std::string s = "[ ";

    Node * aux = head -> next;
    
    s += std::to_string( aux -> value );
    aux = aux -> next;
    while ( aux != head ){
        s += ", ";
        s += std::to_string( aux -> value );
        aux = aux -> next;
    }

    cout << s << " ]"<< endl;
}

// imprime todos os itens da lista em ordem reversa
void List:: printReverse(){
    if( empty() ){
        cout << "Erro: Lista vazia." << endl;
        return;
    }
    std::string s = "[ ";

    Node * aux = head -> back;
    
    s += std::to_string( aux -> value );
    aux = aux -> back;
    while ( aux != head ){
        s += ", ";
        s += std::to_string( aux -> value );
        aux = aux -> back;
    }

    cout << s << " ]"<< endl;
}

//Concatena a lista atual com a lista lst passada por
//parametro. Apos essa operacao ser executada, lst sera uma lista vazia, ou seja, o
//unico no de lst sera o no cabeca.
void List::concat(List * lst){
    if(lst -> empty()){
        cout << "Atencao: Lista vazia" << endl;
        return;
    }

    Node * aux = lst -> head -> next;
    int value = 0;

    for( int i = 0; i <= lst -> size(); i++){
        value = aux -> value;
        aux = aux -> next;
        push_back(value);
        lst -> remove(value);
    }

    cout << "Concatenacao concluida!." << endl;
}

//Retorna um ponteiro para uma copia desta lista.
List * List::copy(){
    List * newList = new List();
    if( empty() ){
        return newList;
    }

    Node * aux = head -> next;
    for(int i = 0; i < size()-1; i++){
        newList -> push_back( aux->value );
        aux = aux -> next;
    }

    return newList;
}

//Copia os elementos do array arr para a
//lista. O array arr tem n elementos. Todos os elementos anteriores da lista sao
//mantidos e os elementos do array arr devem ser adicionados apos os elementos
//originais.
void List::copyArray(int n, int arr[]){
    for(int i=0; i < n; i++){
        push_back(arr[i]);
    }
    cout << "Itens do array adicionados a lista" << endl;
}

// Determina se a lista passada por parametro e igual a
//lista em questao. Duas listas sao iguais se elas possuem o mesmo tamanho e o valor
//do k-esimo elemento da primeira lista e igual ao k-esimo elemento da segunda lista.
bool List::equal(List *lst){
    if( size() != lst -> size()){
        return false;
    }

    Node *no_atu = head-> next;
    Node *no_par = lst -> head -> next;

    for(int i = 0; i < size(); i++){
        if(no_atu -> value != no_par -> value)
            return false;

        no_atu = no_atu -> next;
        no_par = no_par -> next;
    }
    
    return true;
}