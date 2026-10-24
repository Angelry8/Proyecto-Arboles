#ifndef MENU_H
#define MENU_H

#include "ArbolBST.h"

// Controla interacción de consola y delega operaciones al ABB.
class Menu {
public:
    // Ejecuta el ciclo hasta elegir salir. Parámetros: árbol. Retorno: ninguno.
    void ejecutar(ArbolBST& arbol) const;

private:
    // Lee un entero validando entrada. Retorno: true si pudo leerlo.
    bool leerEntero(const char* indicacion, int& valor) const;
    // Imprime las ocho opciones. Parámetros: ninguno. Retorno: ninguno.
    void mostrarOpciones() const;
};

#endif
