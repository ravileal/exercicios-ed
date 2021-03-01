//Nome: Gabriel Lima Paixão Albuquerque de Resende
//Matrícula:398081
#include <iostream>
#include <string>
#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Matriz.h"
#include <vector>
using namespace std;

/* 
 * ============================
 *      Estrutura inicial
 * ============================ 
*/

// Nó inicial
struct Node {
    Node * right;
    Node * bottom;
    int line;
    int column;
    double value;
    ~Node() { std::cout << "no com valor " << value << " liberado" << std::endl; }
};

// Construtor da Matriz
Matriz::Matriz() {
    head = new Node;
    head -> right = head;
    head -> bottom = head;
    head -> line = -1;
    head -> column = -1;
    head -> value = INT_MIN;
}

/* 
 * ============================
 *      Funcões da matriz
 * ============================ 
*/

//lê, de um arquivo de entrada e monta a matriz
void Matriz :: lerMatriz(std::string nomeArquivo){
    string textoLinha;
    vector<string> linha;

    ifstream MyReadFile(nomeArquivo);
    

    // pegar o tamanho de linhas e colunas da matriz
    getline (MyReadFile, textoLinha);
    linha = split(textoLinha);

    // inicializa header das linhas
    int sizeLine = stoi(linha.at(0));


    Node *novo = new Node(); 
    novo -> bottom = head;
  
    head -> bottom = novo;

    Node *ante = novo; 
    for (int i = 1; i < sizeLine; i++){
        
        novo = new Node;
        ante -> bottom = novo;
        novo -> value = INT_MIN;
        novo -> column = INT_MIN;
        novo -> line = -1;
        novo -> right = novo;
        novo -> bottom = head;
        ante = novo;
    }

    // inicializa header das colunas
    int sizeColumn = stoi(linha.at(1));
    
    if(sizeColumn == 0 || sizeLine == 0){
        cout << "Matriz invalida" << endl;
        return;
    }
    
    novo = new Node;
    novo -> right = head;
    head -> right = novo;

    ante = novo; 
    for (int i = 1; i < sizeColumn; i++){
        novo = new Node;
        ante -> right = novo;
        novo -> value = INT_MIN;
        novo -> column = -1;
        novo -> line = INT_MIN;
        novo -> right = head;
        novo -> bottom = novo;
        ante = novo;
    }

    
    // insere os valores na matriz
    while ( getline(MyReadFile, textoLinha) ){
        linha = split(textoLinha);
        
        insere(
            stoi( linha.at(0) ), 
            stoi( linha.at(1) ), 
            stod( linha.at(2) )
        );
        
    }
    
}

// imprime a matriz
void Matriz :: imprime(){
    if( empty() ){
        cout << "Erro: Matriz vazia." << endl;
        return;
    }

    Node * headLine = head;
    Node * nodeColumn = head;
    for(int i=1; i < sizeLine(); i++){
        headLine = headLine -> bottom;
        nodeColumn = headLine -> right;
        for(int j=1; j < sizeColumn(); j++){
            if(nodeColumn -> line   == i 
            && nodeColumn -> column == j){
                cout << " " << nodeColumn -> value << " " << endl;
            }else{
                cout << " 0 " << endl;
            }
            nodeColumn = nodeColumn -> right;
        }
    }
}

// insere o valor v na linha i, coluna j da matriz ou cria um no caso nao tenha
void Matriz :: insere(int i, int j, double v){
    // verifica o indice recebido está dentro do range aceitavel
    
    if( i < 1 || i >= sizeLine()
    ||  j < 1 || j >= sizeColumn() 
    ){ 
        cout << "Erro: Posicao incorreta." << endl;
        return;
    }else if( empty() ) {
        cout << "Erro: Nenhuma Matriz Encontrada." << endl;
        return;
    }

    Node * headLine = head;
    for(int linha = 1; linha <= i; linha++){
        headLine = headLine -> bottom;
    }

    Node * nodeLine = headLine -> right;
    Node * novo = new Node();
    do{
        if(nodeLine -> right  == headLine ){
            novo = new Node();
            nodeLine -> right = novo;
            novo -> right = nodeLine;
            novo -> value = v;
            novo -> line = i;
            novo -> column = j;
            novo -> bottom = novo;
            break;
        }
        else if(nodeLine -> column == j ){
            nodeLine -> value = v;
            break;
        }
        else if(nodeLine -> right  -> column > j ){ 
            novo = new Node();
            novo -> right = nodeLine -> right;
            nodeLine -> right = novo;
            novo -> value = v;
            novo -> line = i;
            novo -> column = j;
            novo -> bottom = novo;
            break;
        }
        else{
            nodeLine = nodeLine -> right;
        }
    }
    while (true);

    Node * headColumn = head;
    for(int coluna = 1; coluna <= j; coluna++){
        headColumn = headColumn -> right;
    }

    Node * nodeColumn = headColumn -> bottom;
    do{
        if(nodeColumn -> bottom  == headColumn ){
            nodeColumn -> bottom == novo;
            novo -> bottom = headColumn;
            break;
        }
        else if(nodeColumn -> bottom  -> line > i ){ 
            novo -> bottom = nodeColumn -> bottom;
            nodeColumn -> bottom = novo;
            break;
        }
        else{
            nodeColumn = nodeColumn -> bottom;
        }
    } while (true);

}

// remove o no da linha i, coluna j da matriz
void Matriz :: remove(int i, int j){
    if( i < 1 || i >= sizeLine()
    ||  j < 1 || j >= sizeColumn() 
    ){ 
        cout << "Erro: Posicao incorreta." << endl;
        return;
    }else if( empty() ) {
        cout << "Erro: Nenhuma Matriz Encontrada." << endl;
        return;
    }

    Node * headLine = head;
    for(int linha = 1; linha <= i; linha++){
        headLine = headLine -> bottom;
    }

    if(headLine -> right == headLine){
        cout << "linha invalida" << endl;
        return;
    }

    Node * nodeLine = headLine -> right;

    Node * noRem = new Node();;
    do{
        
        if(nodeLine -> column == j ){
            noRem = nodeLine;
            headLine -> right == nodeLine -> right;
            
            break;
        }
        else if(nodeLine -> right -> column == j ){
            noRem = nodeLine -> right;
            nodeLine -> right == noRem -> right;
            break;
        }
        else{
            nodeLine = nodeLine -> right;
        }
    }
    while (true);

    Node * headColumn = head;
    for(int coluna = 1; coluna <= j; coluna++){
        headColumn = headColumn -> right;
    }

    if(headColumn -> bottom == headColumn){
        cout << "coluna invalida" << endl;
        return;
    }

    Node * nodeColumn = headColumn -> bottom;
    do{
        if(nodeLine -> line == i){
            headColumn -> bottom == nodeLine -> bottom;
            delete nodeLine;
            break;
        }
        else if(nodeColumn -> bottom -> line == i ){
            noRem = nodeColumn -> bottom;
            nodeColumn -> bottom == noRem -> bottom;
            delete noRem;
            break;
        }
        else{
            nodeColumn = nodeColumn -> bottom;
        }
    } while (true);

}
// recebe duas matrizes e devolve uma outra matriz
// com a soma das matrizes anteriores
Matriz * Matriz :: soma(Matriz *A, Matriz *B){

}

// recebe duas matrizes e devolve uma outra matriz
// com o produto das matrizes anteriores
Matriz * Matriz :: multiplica(Matriz *A, Matriz *B){

}

// empty: retorna true se a Matriza estiver vazia;
// retorna false caso contrario
bool Matriz :: empty () {
    return ( head == head -> right || head == head -> bottom);
}

// sizeColumn: retorna a quantidade de Colunas na Matriz
int Matriz :: sizeColumn () {
    if ( empty() ){
        return 1;
    }
    Node *node = head;
    int count = 1;
    while ( node -> right != head){
        count++;
        node = node -> right;
    }
    return count;
}

// sizeLine: retorna a quantidade de Linhas na Matriz
int Matriz :: sizeLine () {
    if ( empty() ){
        return 1;
    }
    Node *node = head;
    int count = 1;
    while ( node -> bottom != head){
        count++;
        node = node -> bottom;
    }
    return count;
} 

std::vector <string> Matriz :: split(string text){
    vector<string> result;
    stringstream ss(text);
    string temp;
    while (ss >> temp){
        result.push_back(temp);
    }
    return result;
}
