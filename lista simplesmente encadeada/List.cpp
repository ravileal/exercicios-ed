#include <iostream>
#include <string>
#include <climits>
#include "List.h"
using namespace std;

struct Node {
    int value;
    Node *next;
    ~Node() { std::cout << "no com valor " << value << " liberado" << std::endl; }
};

List::List() {
    head = new Node;
    head->next = head;
    head->value = 77777777;
}

// Destrutor: libera toda memoria que foi alocada
List::~List() {
    clear();
    delete head;
    std::cout << "lista liberada" << std::endl;
}

// contains: retorna true se a lista contem um no com valor x;
// retorna false caso contrario
bool List :: contains ( int x) {
     return ( search (x) != nullptr );
}

 // empty: retorna true se a lista estiver vazia;
// retorna false caso contrario
bool List :: empty () {
    return ( head == head ->next );
}

// size: retorna a quantidade de elementos na lista
int List :: size () {
    if ( head == head -> next ){
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
    if( head != head -> next ) { // Se o head não é vazio, faça
        Node * aux = head -> next;
        while ( aux -> next != head -> next ) {
            Node * aux2 = aux ;
            aux = aux -> next ;
            delete aux2;
        }
        delete aux;
        head ->next = head ;
    }
}

// add_back: insere um no com valor x ao final da lista
void List::add_back(int x) {
    Node * novo = new Node ;
    novo -> value = x;
    if( head == head ->next ) {
        novo -> next = novo; // Criando lista circular consigo mesmo
        head -> next = novo; // Diz para o nó cabeça qual é o nó de início
    }
    else {
        Node *last = head -> next;
        while(last -> next != head -> next) {
            last = last -> next;
        }
        last -> next = novo;
        novo -> next = head -> next; 
    }
}

// add_front: insere um no com valor x no inicio da lista
void List :: add_front (int x) {
    Node * novo = new Node ;
    novo -> value = x;
    if( head == head -> next ) {
        novo -> next = novo; // Criando lista circular consigo mesmo
        head -> next = novo; // Diz para o nó cabeça qual é o nó de início
    }
    else {
        novo -> next = head -> next; // aponta pro antigo novo
        Node *last = head -> next;
        while(last -> next != head -> next) {
            last = last -> next;
        }
        last -> next = novo;
        head -> next = novo; // atualiza ponteiro para o primeiro
    }
}

// remove_front: remove o elemento que esta no inicio da lista
// retorna o valor do no caso ele exista; 
// ou retorna INT_MIN caso não exista primeiro elemento
int List :: remove_front () {
    if(head == head -> next){
        return INT_MIN;
    }
    else{
        Node *aux = head -> next;
        Node *last = head -> next;
        while(last -> next != head -> next) {
            last = last -> next;
        }
        last -> next = aux -> next;
        if(head ->next == last){
            head -> next = head;
        }
        else{
            head -> next = aux -> next;
        }
        int val = aux-> value;
        delete aux;
        return val;  
    }
}

// remove_back: remove o elemento que esta no final da lista 
// retorna o valor do no caso ele exista; 
// ou retorna INT_MIN caso não exista ultimo elemento
int List :: remove_back () {
    if( head == head ->next ) {
        return INT_MIN;
    }
    else {
        Node *last = head -> next;
        while(last -> next != head -> next) {
            last = last -> next;
        }
        Node *lastbone = last ->next;
        while(lastbone -> next != last) {
            lastbone = lastbone -> next;
        }
        lastbone -> next = last -> next;
        if(head ->next == last){
            head -> next = head;
        }
        int val = last-> value;
        delete last;
        return val;
    }
}

// remove: remove o primeiro no com valor x
void List :: remove (int x) {
    Node * noRem = search (x );
    if( noRem == nullptr ){
        return ; // lista vazia ou nao tem x
    }
    // A lista contem apenas o no a ser removido
    if( noRem == noRem -> next ) {
        delete noRem ;
        head ->next = head ;
        return ; // finaliza remocao neste caso
    }
    // Percorrer a lista ate achar o antecessor do no
    Node * aux = noRem ;
    while ( aux -> next != noRem ){
        aux = aux -> next ;
    }
    // Ajusta ponteiros e remove o no com valor x
    aux -> next = noRem -> next ;
    if( head ->next == noRem ){ 
        head ->next= noRem -> next ;
    }
    delete noRem;
}

// removeAll: remove todos os nos com valor x
void List :: removeAll (int x) {
    while ( contains (x)){
        remove (x);
    }
}

// toString: retorna a lista como uma std::string

std::string List:: toString(){
    if( head -> next == head){
        return "[]";
    }
    std::string s = "[";
    Node * aux = head->next;
    s += std::to_string(aux-> value);
    aux = aux -> next ;
    while ( aux != head -> next ){
        s += ",";
        s += std::to_string(aux-> value);
        aux = aux -> next ;
    }
    s += "]";
    return s;
}

// Operacao auxiliar: retorna o no anterior ao no com valor x; 
// ou retorna nullptr caso nenhum no com valor x esteja presente
Node * List :: search ( int x ) {
    if( head -> next == head ){ // Lista vazia
        return nullptr ;
    }
    Node * aux = head -> next ;
    do {
        if( aux -> value == x ){
            return aux ;
        }
        aux = aux -> next ;
    }while ( aux != head -> next );
    return nullptr ;
}