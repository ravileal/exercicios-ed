//Nome: Gabriel Lima Paixão Albuquerque de Resende
//Matrícula:398081
#ifndef MatrizESPA_H
#define MatrizESPA_H
#include <vector>

struct Node;

class Matriz {
public:
    // Construtor: cria uma Matriz simplesmente encadeada circular
    // com no cabeca. O no cabeca e obrigatorio na implementacao desta Matriz
    Matriz(); 

    //lê, de um arquivo de entrada e monta a matriz
    void lerMatriz(std::string nomeArquivo);

    // imprime a matriz
    void imprime();

    // insere o valor v na linha i, coluna j da matriz ou cria um no caso nao tenha
    void insere(int i, int j, double v);

    // remove o no da linha i, coluna j da matriz
    void remove(int i, int j);

    // recebe duas matrizes e devolve uma outra matriz
    // com a soma das matrizes anteriores
    Matriz * soma(Matriz *A, Matriz *B);

    // recebe duas matrizes e devolve uma outra matriz
    // com o produto das matrizes anteriores
    Matriz * multiplica(Matriz *A, Matriz *B);

private :
    // Ponteiro para o no cabeca da Matriz
    Node *head;

    std::vector<std::string> split(std::string text);

    int sizeLine();

    int sizeColumn ();

    bool empty();
};

#endif