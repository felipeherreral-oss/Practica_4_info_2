#include <iostream>
#include "enrutador.h"

using namespace std;

int main() {
    cout << "=== INICIANDO PRUEBA FASE 1: CLASE ENRUTADOR ===" << endl << endl;

    // 1. Crear un enrutador principal y un par de "vecinos" virtuales
    Enrutador nodoA("A");

    cout << "1. Nodo creado con ID: " << nodoA.getId() << endl;

    // 2. Agregar vecinos al nodo A
    // Supongamos que A se conecta a B con costo 5 y a C con costo 10
    nodoA.agregarVecino("B", 5);
    nodoA.agregarVecino("C", 10);

    // 3. Imprimir la tabla inicial (debería mostrar a sí mismo, a B y a C)
    cout << "\n2. Mostrando tabla inicial de A (solo conexiones directas):" << endl;
    nodoA.imprimirTabla();

    // 4. Simular que el algoritmo de la "Red" (Fase 3) encontró un camino más corto a C
    // Supongamos que descubrimos que por otro lado llegar a C cuesta solo 7
    cout << "3. Actualizando el costo hacia C en la tabla de enrutamiento..." << endl;
    nodoA.actualizarTabla("C", 7);

    // Y también descubrimos un nuevo destino D al que no estamos conectados directamente
    nodoA.actualizarTabla("D", 15);

    cout << "\nMostrando tabla actualizada de A:" << endl;
    nodoA.imprimirTabla();

    // 5. Probar la eliminación de un vecino (supongamos que el cable hacia B se rompe)
    cout << "4. Eliminando el vecino B (falla de enlace)..." << endl;
    nodoA.eliminarVecino("B");

    cout << "Vecinos actuales de A:" << endl;
    map<string, int> vecinosA = nodoA.getVecinos();
    for (const auto& par : vecinosA) {
        cout << "  -> Vecino directo: " << par.first << " | Costo enlace: " << par.second << endl;
    }

    cout << "\n=== PRUEBA FINALIZADA CON EXITO ===" << endl;

    return 0;
}
