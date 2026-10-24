#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include "NodoDoble.h"

// Lista doblemente enlazada que conserva los datos originales del generador.
class ListaDoble {
public:
    // Inicializa una lista vacía. Parámetros: ninguno. Retorno: ninguno. O(1).
    ListaDoble();
    // Libera los nodos de la lista. Parámetros: ninguno. Retorno: ninguno. O(n).
    ~ListaDoble();

    // Agrega al final. Parámetros: valor entero. Retorno: ninguno. Complejidad: O(1).
    void insertarAlFinal(int valor);

    // Indica si existe el valor. Parámetros: valor buscado. Retorno: true si existe. O(n).
    bool contiene(int valor) const;

    // Obtiene la cantidad de elementos. Parámetros: ninguno. Retorno: cantidad. O(1).
    int tamano() const;

    // Imprime cantidad y elementos en orden. Parámetros: ninguno. Retorno: ninguno. O(n).
    void mostrar() const;

    // Devuelve el primer nodo para que el ABB pueda recorrer la lista.
    // Parámetros: ninguno. Retorno: puntero al inicio o 0. Complejidad: O(1).
    const NodoDoble* obtenerPrimero() const;

private:
    NodoDoble* primero;
    NodoDoble* ultimo;
    int cantidad;

    ListaDoble(const ListaDoble& otra);
    ListaDoble& operator=(const ListaDoble& otra);
};

#endif
