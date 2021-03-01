//Nome: Gabriel Lima Paixão Albuquerque de Resende
//Matrícula:398081
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include "Matriz.h"
using namespace std;

int main()
{
	Matriz *G = new Matriz();
	G->lerMatriz("A.txt"); 
	G->imprime();
}

/*B - > lerMatriz ("B.txt ") ; B - > imprime () ;
C = soma (A , B ) ; C - > imprime () ;
B - > lerMatriz ("B2.txt ") ;
A - > imprime () ; B - > imprime () ;
C = soma (A , B ) ; C - > imprime () ;
C = multiplica (A , B ) ; C - > imprimeMatriz () ;
C = multiplica (B , B ) ;
A - > imprime () ; B - > imprime () ; C - > imprime () ;
...
*/
