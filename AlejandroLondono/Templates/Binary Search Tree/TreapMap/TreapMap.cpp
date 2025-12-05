#include "TreapMap.hh"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int main() {
    TreapMap<int, int> treap;

treap.insert(50, 30);
treap.insert(30, 60);
treap.insert(70, 10);
treap.insert(20, 90);
treap.insert(40, 20);
treap.insert(60, 80);
treap.insert(80, 70);

treap.printTree();
}
