#ifndef ARBOL_BST_H
#define ARBOL_BST_H

#include "ListaDoble.h"

// Nodo privado de implementación de un árbol binario de búsqueda de enteros.
struct NodoArbol {
    explicit NodoArbol(int valor);
    int dato;
    NodoArbol* izquierdo;
    NodoArbol* derecho;
};

// ABB: los valores repetidos no deben insertarse; su origen es ListaDoble.
class ArbolBST {
public:
    // Inicializa un árbol vacío. Parámetros: ninguno. Retorno: ninguno. O(1).
    ArbolBST();
    // Libera los nodos del árbol. Parámetros: ninguno. Retorno: ninguno. O(n).
    ~ArbolBST();

    // Inserta un valor respetando el orden del ABB. Retorno: ninguno. O(h).
    void insertar(int valor);

    // Inserta en el ABB los elementos de la lista, en su orden actual. O(nh).
    void cargarDesdeLista(const ListaDoble& lista);

    // Retorno: cantidad de nodos. En árbol vacío retorna 0. O(n).
    int cantidadNodos() const;

    // Busca e informa existencia, categoría hoja/padre y si es raíz. O(h).
    // Retorno: true si existe; imprime el resultado de la búsqueda.
    bool buscar(int valor) const;

    // Imprime el recorrido raíz-izquierdo-derecho. Árbol vacío: mensaje claro. O(n).
    void preOrden() const;

    // Imprime el recorrido izquierdo-raíz-derecho. Árbol vacío: mensaje claro. O(n).
    void inOrden() const;

    // Imprime el recorrido izquierdo-derecho-raíz. Árbol vacío: mensaje claro. O(n).
    void postOrden() const;

    // Elimina por valor y muestra si no existe. Con dos hijos usa sucesor inorden.
    // Retorno: true si se eliminó. El origen ListaDoble no se modifica. O(h).
    bool eliminar(int valor);

    // Dibuja el ABB en consola; árbol vacío: mensaje claro. O(n).
    void mostrarArbol() const;

private:
    NodoArbol* raiz;

    // Auxiliares de consultas e inserción; contrato reservado a Parte 3.
    // Inserta recursivamente, cuenta nodos, busca con padre y realiza recorridos.
    void insertarRecursivo(NodoArbol*& nodo, int valor);
    int contarNodos(const NodoArbol* nodo) const;
    // Retorna el nodo encontrado o 0; padre queda en 0 si es la raíz.
    const NodoArbol* buscarNodo(int valor, const NodoArbol*& padre) const;
    void preOrdenRecursivo(const NodoArbol* nodo) const;
    void inOrdenRecursivo(const NodoArbol* nodo) const;
    void postOrdenRecursivo(const NodoArbol* nodo) const;

    // Auxiliares de liberación, eliminación, mínimo y dibujo; contrato de Parte 4.
    void liberar(NodoArbol* nodo);
    // Retorna la nueva raíz del subárbol luego de la eliminación.
    NodoArbol* eliminarRecursivo(NodoArbol* nodo, int valor, bool& eliminado);
    NodoArbol* minimo(NodoArbol* nodo) const;
    // Dibujo rotado 90 grados: subárbol derecho arriba e indentación por nivel.
    void dibujar(const NodoArbol* nodo, int nivel) const;

    ArbolBST(const ArbolBST& otro);
    ArbolBST& operator=(const ArbolBST& otro);
};

#endif
