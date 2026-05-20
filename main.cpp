#include <iostream>
#include "red.h"

using namespace std;

int main() {
    cout << "=== INICIANDO PRUEBA FASE 2: CLASE RED ===" << endl << endl;

    Red miRed;

    // 1. Agregar nodos
    miRed.agregarEnrutador("A");
    miRed.agregarEnrutador("B");
    miRed.agregarEnrutador("C");

    // 2. Conectar nodos (Triángulo)
    miRed.conectar("A", "B", 5);
    miRed.conectar("B", "C", 10);
    miRed.conectar("A", "C", 15);

    // 3. Imprimir estado inicial
    miRed.imprimirRed();

    // 4. Desconectar un cable específico
    cout << "--- Desconectando cable entre B y C ---" << endl;
    miRed.desconectar("B", "C");
    miRed.imprimirRed();

    // 5. Eliminar un nodo por completo (A)
    cout << "--- Eliminando el nodo A de la red ---" << endl;
    // Al eliminar A, el nodo B y C deben perder su conexión con A automáticamente.
    miRed.eliminarEnrutador("A");
    miRed.imprimirRed();

    cout << "=== PRUEBA FINALIZADA CON EXITO ===" << endl;
    return 0;
}
