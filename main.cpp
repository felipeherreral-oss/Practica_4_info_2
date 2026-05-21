#include <iostream>
#include "red.h"

using namespace std;

int main() {
    cout << "=== INICIANDO PRUEBA FASE 3: MOTOR DIJKSTRA ===" << endl << endl;

    Red redSimulada;

    // Crear 4 enrutadores
    redSimulada.agregarEnrutador("A");
    redSimulada.agregarEnrutador("B");
    redSimulada.agregarEnrutador("C");
    redSimulada.agregarEnrutador("D");

    // Conectar nodos creando rutas alternativas
    redSimulada.conectar("A", "B", 10); // Enlace directo pesado
    redSimulada.conectar("A", "C", 2);  // Enlace liviano a C
    redSimulada.conectar("C", "B", 3);  // De C a B es liviano (Costo total A-C-B = 5)
    redSimulada.conectar("B", "D", 4);  // Conectar B con un extremo D

    // 1. Verificar si las tablas se calcularon solas automáticamente
    redSimulada.imprimirRed();

    // 2. Solicitar una ruta específica de A hacia D
    cout << "--- Solicitando ruta óptima desde A hasta D ---" << endl;
    int costoRuta = 0;
    vector<string> camino = redSimulada.obtenerRuta("A", "D", costoRuta);

    if(!camino.empty()) {
        cout << "Camino encontrado: ";
        for(size_t i = 0; i < camino.size(); ++i) {
            cout << camino[i];
            if(i < camino.size() - 1) cout << " -> ";
        }
        cout << "\nCosto total del viaje: " << costoRuta << endl << endl;
    } else {
        cout << "No existe camino posible." << endl;
    }

    // 3. PROBAR DINAMISMO: Rompemos el camino liviano desconectando C y B
    cout << "--- ALERTA: Se rompe el enlace entre C y B ---" << endl;
    redSimulada.desconectar("C", "B");

    // Las tablas debieron mutar automáticamente. De A a B ahora la única opción es el enlace directo de 10.
    cout << "\nTablas recalculadas automáticamente tras la caída:" << endl;
    redSimulada.imprimirRed();

    // Volvemos a pedir la ruta A -> D
    camino = redSimulada.obtenerRuta("A", "D", costoRuta);
    cout << "Nuevo camino optimo A -> D: ";
    for(size_t i = 0; i < camino.size(); ++i) {
        cout << camino[i] << (i < camino.size() - 1 ? " -> " : "");
    }
    cout << "\nNuevo costo total: " << costoRuta << endl;

    cout << "\n=== PRUEBA FASE 3 CONCLUIDA ===" << endl;
    return 0;
}
