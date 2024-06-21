#include <iostream>
#include "FiboHeap.h"
using namespace  std;
//Testing

// CASO EN DONDE ELIMINO EL MENOR Y SOLO ES UNA CLAVE
// CASO DE INSERCION

int main() {
    std::cout << "Hello, World!" << std::endl;
    Fiboheap<int> fh;
    Fiboheap<int> fh2;
    fh.insert(10);
    fh.insert(20);
    fh.insert(30);
    fh.insert(40);

    fh2.insert(10);
    fh2.insert(20);
    fh2.insert(30);

    cout<<fh.findMin()<<endl;
    cout<<fh.size()<<endl;
    Fiboheap<int> fh3 = Union(fh, fh2);
    cout<<"AA"<<endl;
    fh.ExtractMin();


    return 0;
}
