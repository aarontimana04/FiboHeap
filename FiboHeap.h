//
// Created by Jazmin on 15/06/2024.
//

#ifndef FIBOHEAP_FIBOHEAP_H
#define FIBOHEAP_FIBOHEAP_H
#include "Node.h"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
//Implementar constructores de copia, y con initializer list


#include<iostream>
#include<vector>
#include<math.h>
using namespace std;


template<typename T>
class Fiboheap{
private:
    Node<T>* rootlist;
    Node<T>* ptr_min;
    int n;

public:
    //METODOS
    Fiboheap():rootlist(nullptr), n(0){}
    void insert(T data);
    void ExtractMin();
    void Consolidar();
    void display();
    void LinkHeap(Node<T>* n1, Node<T>* n2);
    //void Decrase key()
    // Cut
    // Cascade cut
    // Print

    T findMin(){
        return ptr_min->data;
    }
    int size(){return n; }
    bool isEmpty(){return (n==0);}

    //template<typename T>
    friend Fiboheap<T> Union(Fiboheap<T> f1, Fiboheap<T> f2){ //FUNCIONA
        //PASOS
        //Vemos quien es el menor de los minimos de los dos fiboHeap y mantenemos su puntero
        //Luego unimos las rootlist de cada fiboheap
        Fiboheap<T> f3 ;
        Node<T>* tailf1;
        Node<T>* tailf2;
        if(f1.isEmpty() == true){
            f3.ptr_min = f2.ptr_min;
            tailf2 = f2.rootlist;
            f3.rootlist = tailf1;
        }else if(f2.isEmpty()){
            f3.ptr_min = f1.ptr_min;
            tailf1 = f2.rootlist;
            f3.rootlist = tailf1;

        }else{
            if(f1.findMin() < f2.findMin()){
                f3.ptr_min = f1.ptr_min;
            }else{
                f3.ptr_min = f2.ptr_min;
            }


            //Obtenemos el tail de f1
            tailf1 = f1.rootlist;
            tailf2 = f2.rootlist;

            /*cout<<"Head 1: "<<tailf1->data<<endl;
            cout<<"Tail 2:"<<tailf1->left->data<<endl;

            cout<<"Head 2: "<<tailf2->data<<endl;
            cout<<"Tail 2:"<<tailf2->left->data<<endl;
            */

            tailf1->left->right = tailf2 ;
            tailf2->left->right = tailf1;
            auto temp = tailf2->left;
            tailf2->left = tailf1->left;

            tailf1->left = temp;

            f3.rootlist = tailf1;
            //cout<<"Tail"<<f3.rootlist->left->data<<endl;
        }

        f3.n = f1.n + f2.n;

        return f3;

    }

    ~Fiboheap(){}
};



template<typename T>
void Fiboheap<T>::insert(T data){
    Node<T>* newnodo = new Node<T>(data);
    newnodo->left = newnodo->right = newnodo;

    if(rootlist == nullptr){
        rootlist = ptr_min = newnodo;
    }else{
        //Concatenamos
        newnodo->left = rootlist->left;
        newnodo->right = rootlist;
        rootlist->left->right = newnodo;
        rootlist->left = newnodo;

        // Actualiza ptr_min si el valor del nuevo nodo es menor
        if (ptr_min->data > data) {
            ptr_min = newnodo;
        }
    }
    n++;
}

template<typename T>
void Fiboheap<T>::LinkHeap(Node<T>* n1, Node<T>* n2){
    //PASOS
    //Primero desconectar n2 de su posicion en el rootlist
    // Hacer que n2 sea hijo de n1
    // Insertar n2 en la lista de hijos en n1 (Link siblings)
    // Hacer que n2 apunte a n1 como padre
    // Actualizar el grado de n1
    //El que vamos a remover es n2
    auto y = n2;
    n2->left->right = n2->right;
    n2->right->left = n2->left;

    if(n1->right == n1){
        ptr_min = n1;
    }

    //Haciendo que n2 sea hijo de n1
    //Volvemos en un nodo circular
    n2->left = n2;
    n2->right = n2;
    n2->parent = n1;

    //OBS: Solo unen los hijos mas no los nietos xd
    if(n1->child == nullptr){
        n1->child = n2;
    }
    //Conseguir el tail
    n2->left = n1->child->left;
    n2->right = n1->child;
    (n1->child)->left->right = n2;
    n1->child->left = n2;



    if(n2->data < n1->child->data){
        n1->child = n2;
    }

    n1->degree += 1;
}


template<typename T>
void Fiboheap<T>::Consolidar(){
    //El metodo de consolidacion se encarga de garantizar que ningun arbol tengan degree repetido
    //Primero recorremos todo el rootlist
    auto tailptr  = rootlist->left;
    auto head = rootlist->right;
    //Extrayendo el grado y el ptr al nodo para guardarlo en el map
    float f = (log(n)) / (log(2));
    cout<<"F: "<< f<<endl;
    int newSizeRoot;
    int maxdegree = f;
    Node<T> *arrayDegree[maxdegree+1];

    for (int i = 0; i < maxdegree+1; i++)
        arrayDegree[i] = nullptr;

    auto ptr1 = ptr_min;
    Node<T>* ptr2;
    Node<T>* ptr3;
    auto ptr4 = ptr1; // Variable auxiliar con el cual nos vamos a desplazar
    //Extrayendo el grado y guardando el ptr en el vector
    do{
        //cout<<"GG"<<endl;
        ptr4 = ptr4->right;
        newSizeRoot = ptr1->degree;
        //cout<<"DATA "<<ptr1->data<<endl;
        //cout<<"GRADO"<<newSizeRoot<<endl;

        while(arrayDegree[newSizeRoot] != nullptr){
            //cout<<ptr1->data<<" "<<arrayDegree[newSizeRoot]->data <<endl;
            ptr2 = arrayDegree[newSizeRoot];

            if(ptr1->data > ptr2->data){
                //Hacemos un swap
                ptr3 = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr3;
            }

            if (ptr2 == ptr_min) {
                ptr_min = ptr1;
            }
            //cout<<"SS"<<endl;
            LinkHeap(ptr1, ptr2);
            //cout<< "Hijo: "<<ptr1->child->right->left->data<<endl;
            //cout<< "Grado ac: "<<ptr1->degree<<endl;
            //cout<<ptr1->degree<<endl;
            if (ptr1->right == ptr1) {
                ptr_min = ptr1;
            }


            //Ahora convertimos el degree anterior en null
            arrayDegree[newSizeRoot] = nullptr;
            newSizeRoot++;
            //cout<<"Nuevo size 1:" << newSizeRoot<<endl;
        }
        //cout<<"2WHILE"<<endl;
        //cout<<"Nuevo size 2 :" << newSizeRoot<<endl;
        arrayDegree[newSizeRoot] = ptr1;
        ptr1 = ptr1->right;
        //cout<<ptr1->data<<endl;
        //cout<<ptr_min->data<<endl;
    } while (ptr1 != ptr_min);

    //cout<<"Size final"<<newSizeRoot<<endl;


    //cout<<"1 WHILE"<<endl;

    //cout<<"AAA"<<endl;
    ptr_min= nullptr;
    rootlist = nullptr;
    //Este for busca rehacer todo el root list por lo cual el fib heap lo colocamos en null
    //Hacer otro bucle para todos los nodos almacenados en el vector

    //cout<<"DD:"<<arrayDegree[0]->data<<endl;
    //cout<<"DD:"<<arrayDegree[1]->data<<endl;

    for(int i=0; i<= maxdegree; ++i){
        //Comprobar si no es nullptr
        if(arrayDegree[i] != nullptr){
            cout<<"FF"<<arrayDegree[i]->data<<endl;
            arrayDegree[i]->left = arrayDegree[i];
            arrayDegree[i]->right = arrayDegree[i];
            if(rootlist != nullptr){
                //Insertamos el node en la rootlist
                arrayDegree[i]->left = rootlist->left;
                arrayDegree[i]->right = rootlist;
                rootlist->left->right = arrayDegree[i];
                rootlist->left = arrayDegree[i];

                if(ptr_min->data > arrayDegree[i]->data){
                    ptr_min = arrayDegree[i];
                }
            }else{
                //cout<<"A"<<endl;
                rootlist= ptr_min = arrayDegree[i];
            }

        }
    }
    //cout<<"Acabo"<<endl;
}


template<typename T>
void Fiboheap<T>::ExtractMin(){
    //PASOS
    //Guardamos el ptr_min
    //Verificamos si es nulo o no
    //Si no es nulo: Corremos por todos los hijos del ptr min
    // Agregamos los hijos al root list y hacemos a dichos hijos que tengan padre nulo
    // Remover el ptr_min del rootlist
    // Si el puntero derecho es igual al ptr_min entonces es el unico nodo dentro del rootlist
    // Si Y era el unico nodo(no tiene hijos) entonces el rootlist esta vacio y el ptr_min apunta a null
    // En caso contrario: Que el ptr_min sea el ptr_min antiguo a la derecha
    //Usamos la funcion consolidar
    // Disminuimos el numero de nodos
    if(ptr_min == nullptr){
        //Solo eliminarlo y aplicar consolidacion
        //cout<<"GG"<<endl;
        return;
    }else{
        auto dptrMin = ptr_min;
        //cout<<"B"<<endl;
        Node<T>* ptrn = dptrMin;
        Node<T>* minchild;

        // Verifica si se mantiene lo circular
        if(dptrMin->child != nullptr){
            auto minchild = dptrMin->child;

            do{
                ptrn = minchild->right;
                //Agregamos los hijos al root list
                ptr_min->left->right = minchild;
                minchild->left = ptr_min->left;

                minchild->right = ptr_min;
                ptr_min->left =  minchild;

                //cout<<"f"<<endl;
                if(minchild->data < ptr_min->data){
                    ptr_min = minchild;
                }

                minchild->parent = nullptr;
                minchild = ptrn;
            }while(ptrn != dptrMin->child);


        }
        //Conseguir el primero y el ultimo nodo de los hijos en la root lis

        dptrMin->left->right = dptrMin->right;
        dptrMin->right->left = dptrMin->left;
        //Consideramos que ahora el ptr_min
        ptr_min = dptrMin->right;

        if(dptrMin == dptrMin->right && dptrMin->child == nullptr){
            ptr_min = nullptr;
        }else{
            ptr_min = dptrMin->right;
            Consolidar();
        }
        n--;
    }
}





#endif //FIBOHEAP_FIBOHEAP_H
