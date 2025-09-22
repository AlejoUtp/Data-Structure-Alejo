#include "list.hh"
#include <iostream>

int main()
  {
    List<int> lista;
    List<int> copylist;

    copylist.push_back(7);
    copylist.push_back(3);
    lista.push_back(10);
    lista.push_back(20);
    lista.push_back(23);
    lista.push_back(40);
    lista.push_front(5);
    lista.push_front(6);
    lista.erase(3);
    lista.insert(2, 15);
    lista.reverse();

    List<int> copia(lista);
    cout << "Copia de la lista original: ";
    copia.print();
    copia.push_back(100);
    cout << "Copia modificada de la lista original: ";
    copia.print();
    cout << "elemento en el índice 2: " << lista.at(2) << endl;
    cout << "Tamaño de la lista: " << lista.size() << endl;
    cout << "Primer elemento: " << lista.front() << endl;
    cout << "Contenido de la lista: ";
    lista.print();

    cout << "copylist: ";
    copylist.print();
    lista.push_front(copylist);
    cout << "Lista después de push_front con copylist: ";
    lista.print();
    return 0;
  }