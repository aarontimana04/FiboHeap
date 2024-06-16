//
// Created by Jazmin on 15/06/2024.
//

#ifndef FIBOHEAP_FIBOHEAP_H
#define FIBOHEAP_FIBOHEAP_H
#include "Node.h"
//Implementar constructores de copia, y con initializer list

template<typename  T>
class FiboHeap {
    int n; //Numero de nodos
    Node<T>* rootlist; //Se obtiene la lista enlazada del root y funciona como centinela
    Node<T>* ptr_min; //Puntero al minimo

    void Consolidar(){

    }
public:
    //Metodos
    //Insert --
    //Union --
    //Decrease-key
    //Delete
    //Find minimo --
    //Consolidar (metodo privado)
    FiboHeap(){}

    void insert(T value){
        //PASOS:
        //1. Verificamos si el nodo no es null. Si lo es entonces actualizar el ptr_min
        //2. Siempre se va a insertar cualquier elemento a la izquierda del min pointer
        //3. Si llega un valor menor al min, aplicar el paso 2 y actualizar el ptr_min
        Node<T> newnode = new Node<T>(value);
        if(rootlist == nullptr){
            rootlist = ptr_min = newnode;
            rootlist->right = rootlist; //Se mantiene el hecho de que sea lista circular
            rootlist->left = rootlist;
        }else{
            ptr_min->left->right = newnode;
            newnode->left = ptr_min->left;
            ptr_min->left = newnode;
            newnode->right = ptr_min;

            if(ptr_min->data > value){ //Actualizamos el punteros
                ptr_min = newnode;
            }
        }
        ++n;
    }

    T findMin(){
        return ptr_min->data;
    }


    FiboHeap<T> Union(FiboHeap<T> f1, FiboHeap<T> f2){
        //PASOS
        //Vemos quien es el menor de los minimos de los dos fiboHeap y mantenemos su puntero
        //Luego unimos las rootlist de cada fiboheap
        FiboHeap<T> f3 = new FiboHeap();
        if(f1.findMin() < f2.findMin()){
            f3.ptr_min = f1.ptr_min;
        }else{
            f3.ptr_min = f2.ptr_min;
        }

        //Obtenemos el tail de f1
        auto tailf1 = f1.rootlist->left;
        auto tailf2 = f2.rootlist->left;

        tailf1->right = f2.rootlist ;
        f2.rootlist->left = tailf1;

        f1.rootlist->left = tailf2;
        tailf2->right = f1.rootlist;

        f3.rootlist = f1.rootlist;
        f3.n = f1.n + f2.n;

        return f3;

    }


};


#endif //FIBOHEAP_FIBOHEAP_H
