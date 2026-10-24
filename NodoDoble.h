#ifndef NODO_DOBLE_H
#define NODO_DOBLE_H

// Nodo de una lista doblemente enlazada de enteros.
class NodoDoble {
public:
    explicit NodoDoble(int valor);

    int dato;
    NodoDoble* anterior;
    NodoDoble* siguiente;
};

#endif
