#include <iostream>
#include <string>
#include <vector>
#include "red.h"

using namespace std;

void mostrarMenu() {
    cout << "\n========== SIMULADOR DE RED DE ENRUTADORES ==========\n";
    cout << "1. Agregar Enrutador (Nodo)\n";
    cout << "2. Eliminar Enrutador (Nodo)\n";
    cout << "3. Conectar / Modificar Enlace (Arista)\n";
    cout << "4. Desconectar Enlace (Quitar cable)\n";
    cout << "5. Calcular Ruta Optima (Dijkstra)\n";
    cout << "6. Ver Topologia y Tablas de Enrutamiento\n";
    cout << "7. Salir\n";
    cout << "=====================================================\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    Red miRed;
    int opcion = 0;
    string orig, dest;
    int costo;

    // Poblar la red con unos nodos iniciales para no empezar desde cero
    miRed.agregarEnrutador("A");
    miRed.agregarEnrutador("B");
    miRed.agregarEnrutador("C");
    miRed.conectar("A", "B", 4);
    miRed.conectar("B", "C", 2);
    miRed.conectar("A", "C", 10);

    while (opcion != 7) {
        mostrarMenu();
        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Intente de nuevo.\n";
            cin.clear();
            string descarte;
            cin >> descarte;
            continue;
        }

        switch (opcion) {
        case 1:
            cout << "Ingrese el ID del nuevo enrutador (ej. D): ";
            cin >> orig;
            miRed.agregarEnrutador(orig);
            break;

        case 2:
            cout << "Ingrese el ID del enrutador a eliminar: ";
            cin >> orig;
            miRed.eliminarEnrutador(orig);
            break;

        case 3:
            cout << "Ingrese Nodo Origen: "; cin >> orig;
            cout << "Ingrese Nodo Destino: "; cin >> dest;
            cout << "Ingrese Costo del enlace: "; cin >> costo;
            miRed.conectar(orig, dest, costo);
            break;

        case 4:
            cout << "Ingrese Nodo Origen: "; cin >> orig;
            cout << "Ingrese Nodo Destino: "; cin >> dest;
            miRed.desconectar(orig, dest);
            break;

        case 5: {
            cout << "Ingrese Enrutador de Origen: "; cin >> orig;
            cout << "Ingrese Enrutador de Destino: "; cin >> dest;

            int costoRuta = 0;
            vector<string> camino = miRed.obtenerRuta(orig, dest, costoRuta);

            if (!camino.empty()) {
                cout << "\n[RESULTADO] Camino mas corto: ";
                for (size_t i = 0; i < camino.size(); ++i) {
                    cout << camino[i] << (i < camino.size() - 1 ? " -> " : "");
                }
                cout << "\n[RESULTADO] Costo total: " << costoRuta << "\n";
            } else {
                cout << "\n[ERROR] No se encontro un camino posible entre " << orig << " y " << dest << ".\n";
            }
            break;
        }

        case 6:
            miRed.imprimirRed();
            break;

        case 7:
            cout << "Saliendo del simulador. ¡Hasta luego!\n";
            break;

        default:
            cout << "Opcion no valida. Intente de nuevo.\n";
            break;
        }
    }

    return 0;
}
