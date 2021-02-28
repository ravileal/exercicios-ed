#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include "List.h"
using namespace std;

int main()
{
	vector <List*> listas; // vector que guarda todas as listas criadas

	while(true) {
		string cmd;
		getline(cin, cmd);

		std::stringstream ss{ cmd };
		vector<string> tokens;
		string buffer;

		while(ss >> buffer) {
			tokens.push_back(buffer);
		}

		if(tokens[0] == "exit") {
			for(int i = 0; i < listas.size(); ++i) {
				delete listas[i];
				listas[i] = nullptr;
			}
			listas.clear();
			break;
		}
		// createlist
		else if(tokens[0] == "createlist") {
			List *l = new (std::nothrow) List();
			listas.push_back( l );
			if(l != nullptr) cout << "lista " <<  listas.size()-1 << " criada" << endl;
		}

		// pushback [x] list [k]
		else if(tokens[0] == "pushback") {
			int x = std::stoi(tokens[1]);
			int k = std::stoi(tokens[3]);
			listas[k]->push_back(x);
			cout << x << " adicionado ao final da lista " << k << endl;
		}

		// removeback [k]
		else if(tokens[0] == "popback") {
			int k = std::stoi(tokens[1]);
			int elem = listas[k]->pop_back();
			if(elem != INT_MIN) cout << elem << " removido do final lista " << k << endl;
			else cout << " nao foi possivel remover do final da lista " << k << endl;
		}

		// insert [x] after [i] list [k]
		else if(tokens[0] == "insert") {
			int x = std::stoi(tokens[1]);
			int i = std::stoi(tokens[3]);
			int k = std::stoi(tokens[5]);
			if(listas[k]->insertAfter(x,i))
				cout << x << " inserido apos a posicao " << i << " da lista " << k << endl;
			else 
				cout << "falha ao inserir elemento " << x << " apos a posicao " << 
						i << " da lista " << k << endl;
		}
		
		// remove [x] list [k]
		else if(tokens[0] == "remove") {
			int x = std::stoi(tokens[1]);
			int k = std::stoi(tokens[3]);
			listas[k]->remove(x);
		}

		// removeall [x] list [k]
		else if(tokens[0] == "removeall") {
			int x = std::stoi(tokens[1]);
			int k = std::stoi(tokens[3]);
			listas[k]->removeAll(x);
		}

		// print [k]
		else if(tokens[0] == "print") {
			int k = std::stoi(tokens[1]);
			cout << "lista " << k << " = " << endl;
			listas[k]->print();
		}

		// reverse [k]
		else if(tokens[0] == "reverse") {
			int k = std::stoi(tokens[1]);
			listas[k]->printReverse();
			cout << "lista " << k << " invertida" << endl;
			cout << "lista " << k << " = " << endl;
			listas[k]->printReverse();
		}

		// empty [k]
		else if(tokens[0] == "empty") {
			int k = std::stoi(tokens[1]);
			if(listas[k]->empty()) cout << "lista " << k << " vazia" << endl;
			else cout << "ha elementos na lista " << k << endl;
		}
        // size [k]
		else if(tokens[0] == "size") {
			int k = std::stoi(tokens[1]);
			cout << "cardinalidade da lista " << k << " = " << listas[k]->size() << endl;
		}
        // clear [k]
		else if(tokens[0] == "clear") {
			int k = std::stoi(tokens[1]);
			listas[k]->clear();
			cout << "lista " << k << " vazia" << endl;
		}

		// concat [p] [q]
		else if(tokens[0] == "concat") {
			int p = std::stoi(tokens[1]);
			int q = std::stoi(tokens[2]);
			listas[p]->concat(listas[q]);
			cout << "listas " << p << " e " << q << " concatenadas" << endl;
			cout << "lista " << p << ": " << endl;
			listas[p]->print();
			cout << "lista " << q << ": " << endl;
			listas[q]->print();
		}

		// copy [k]
		else if(tokens[0] == "copy") {
			int k = std::stoi(tokens[1]);
			List *cp = listas[k]->copy();
			listas.push_back(cp);
			cout << "uma copia da lista " << k << " foi criada: ela eh a lista " << listas.size()-1 << endl;
		}

		// copyarray [n] [a1] [a2] [a3] .. [an] list [k]
		else if(tokens[0] == "copyarray") {
			int n = std::stoi(tokens[1]);
			int k = std::stoi(tokens[n+3]);
			int arr[n];
			for(int i = 0; i < n; i++) {
				arr[i] = std::stoi(tokens[2+i]);
			}
			listas[k]->copyArray(n, arr);
			cout << "array foi copiado para lista " << k << endl;
		}

		// equal [p] [q]
		else if(tokens[0] == "equal") {
			int p = std::stoi(tokens[1]);
			int q = std::stoi(tokens[2]);
			bool iguais = listas[p]->equal(listas[q]);
			if(iguais) cout << "listas " << p << " e " << q << " sao iguais" << endl;
			else cout << "listas " << p << " e " << q << " sao diferentes" << endl;
		}
		
		// contains [x] list [k]
		else if(tokens[0] == "contains") {
			int x = std::stoi(tokens[1]);
			int k = std::stoi(tokens[3]);
			if(listas[k]->contains(x)) cout << x << " esta na lista " << k << endl;
			else cout << x << " NAO esta na lista " << k << endl;
		}
		else {
			cout << "comando inexistente" << endl;
		}
	}
	return 0;
}