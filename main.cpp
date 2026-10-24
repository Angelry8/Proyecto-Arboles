#include "ArbolBST.h"
#include "GeneradorAleatorio.h"
#include "ListaDoble.h"
#include "Menu.h"
#include <iostream>

int main() {
    ListaDoble lista;
    GeneradorAleatorio generador;
    generador.cargarElementos(lista);

    std::cout << "Datos generados para el árbol:\n";
    lista.mostrar();

    ArbolBST arbol;
    arbol.cargarDesdeLista(lista);

    Menu menu;
    menu.ejecutar(arbol);
    return 0;
}
