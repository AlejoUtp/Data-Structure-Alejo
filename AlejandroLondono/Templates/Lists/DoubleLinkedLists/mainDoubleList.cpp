#include "DoubleLinkedList.hh"
#include <iostream>

using namespace std;

int
main()
{

  DoubleLinkedList<int> lista;

  lista.push_back(12);
  lista.push_back(45);
  lista.push_back(6);
  lista.push_back(2);
  lista.push_back(1);
  lista.print();

  lista.pop_back();
  lista.print();

  lista.push_front(3);
  lista.print();

  lista.pop_front();
  lista.pop_front();
  lista.print();

  lista.push_back(1);
  lista.push_back(2);
  lista.push_back(3);
  lista.print();

  lista.erase(5);
  lista.print();

  lista.insert(3, 34);
  lista.print();

  lista.reverse();
  lista.print();

  lista.push_back(1);
  lista.print();

  lista.push_front(3);
  lista.print();

  cout << "First: " << lista.front() << endl;
  cout << "Last: " << lista.back() << endl;

  DoubleLinkedList<int> copylista(lista);

  copylista.pop_front();
  copylista.pop_front();
  copylista.pop_front();
  copylista.pop_front();
  copylista.pop_front();

  copylista.print();
  lista.push_front(copylista);
  lista.print();

  return 0;
}