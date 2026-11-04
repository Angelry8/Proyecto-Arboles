#include "ArbolBST.h"
#include "GeneradorAleatorio.h"
#include "ListaDoble.h"
#include "Menu.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    // La consola de Windows necesita UTF-8 para mostrar bien las tildes y la ñ.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    ListaDoble lista;
    GeneradorAleatorio generador;
    generador.cargarElementos(lista);

    // El enunciado pide mostrar la lista antes de cargar el árbol.
    std::cout << "Lista doble generada para el árbol:\n";
    lista.mostrar();

    ArbolBST arbol;
    arbol.cargarDesdeLista(lista);
    std::cout << "Árbol cargado con " << arbol.cantidadNodos() << " nodos.\n";

    Menu menu;
    menu.ejecutar(arbol);
    return 0;
}
