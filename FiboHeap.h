//
// Created by Jazmin on 15/06/2024.
//

#ifndef FIBOHEAP_FIBOHEAP_H
#define FIBOHEAP_FIBOHEAP_H
#include "Node.h"
#include <unordered_map>
#include <vector>
//Implementar constructores de copia, y con initializer list

template<typename  T>
class FiboHeap {
    int n; //Numero de nodos
    Node<T>* rootlist; //Se obtiene la lista enlazada del root y funciona como centinela
    Node<T>* ptr_min; //Puntero al minimo

    void Consolidar(){ //El metodo de consolidacion se encarga de garantizar que ningun arbol tengan degree repetido
        //std::unordered_map<int, Node<T>*> arrayDegree; //Usar vector tmb xd

        //Primero recorremos todo el rootlist
        auto tailptr  = rootlist->left;
        auto head = rootlist->right;
        //Extrayendo el grado y el ptr al nodo para guardarlo en el map
        int maxdegree = rootlist->degree;
        while(head != tailptr->right){
            if(maxdegree < head.degree){maxdegree = head.degree}
            head = head.right;
        }
        std::vector<Node<T>*> arrayDegree (maxdegree+1, nullptr);
        head = rootlist->right;
        //Extrayendo el grado y guardando el ptr en el vector

        do{
            if(arrayDegree[head.degree] == nullptr){
                arrayDegree[head.degree] = head;
            }else{
                //Aca hacemos la fusion
                auto ptr_n1 = arrayDegree[head.degree];
                if(ptr_n1.data > head.data){ //OBS: Algo anda mal con ptr_n1 y el vector
                    ptr_n1.child = head;
                    //Eliminar el head
                    auto ptr_head= head.right;

                    ptr_n1.right = ptr_head;
                    ptr_head.right = ptr_n1;

                    head = nullptr;
                    head = ptr_head;


                }else{
                    head.child = ptr_n1;

                }
            }

        } while (head != rootlist->right);
    }

    Node<T>* Mergear(Node<T>* n1, int d,std::vector<Node<T>*> & v){ //Este metodo va a hacer la el min heap
        if(v[d] == nullptr){
            v[d] = n1;
            return v[d];
        }else{

        }

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
