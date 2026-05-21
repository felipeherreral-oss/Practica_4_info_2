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
    cout << "4. Desconectar Enlace\n";
    cout << "5. Calcular Ruta Optima (Dijkstra)\n";
    cout << "6. Ver Topologia y Tablas de Enrutamiento\n";
    cout << "7. Cargar Topologia desde Archivo (.txt)\n"; // Nueva opción
    cout << "8. Salir\n";
    cout << "=====================================================\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    Red miRed;
    int opcion = 0;
    string orig, dest, nombreArchivo;
    int costo;

    while (opcion != 8) {
        mostrarMenu();
        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Intente de nuevo.\n";
            cin.clear();
            string descarte; cin >> descarte;
            continue;
        }

        switch (opcion) {
        case 1:
            cout << "ID del nuevo enrutador: "; cin >> orig;
            miRed.agregarEnrutador(orig);
            break;
        case 2:
            cout << "ID del enrutador a eliminar: "; cin >> orig;
            miRed.eliminarEnrutador(orig);
            break;
        case 3:
            cout << "Nodo Origen: "; cin >> orig;
            cout << "Nodo Destino: "; cin >> dest;
            cout << "Costo: "; cin >> costo;
            miRed.conectar(orig, dest, costo);
            break;
        case 4:
            cout << "Nodo Origen: "; cin >> orig;
            cout << "Nodo Destino: "; cin >> dest;
            miRed.desconectar(orig, dest);
            break;
        case 5: {
            cout << "Origen: "; cin >> orig;
            cout << "Destino: "; cin >> dest;
            int costoRuta = 0;
            vector<string> camino = miRed.obtenerRuta(orig, dest, costoRuta);
            if (!camino.empty()) {
                cout << "\n[RESULTADO] Camino: ";
                for (size_t i = 0; i < camino.size(); ++i) cout << camino[i] << (i < camino.size() - 1 ? " -> " : "");
                cout << "\n[RESULTADO] Costo total: " << costoRuta << "\n";
            } else {
                cout << "\n[ERROR] No se encontro camino.\n";
            }
            break;
        }
        case 6:
            miRed.imprimirRed();
            break;
        case 7:
            cout << "Ingrese el nombre del archivo (ej. topologia.txt): ";
            cin >> nombreArchivo;
            miRed.cargarDesdeArchivo(nombreArchivo);
            break;
        case 8:
            cout << "Saliendo del simulador. ¡Hasta luego!\n";
            break;
        default:
            cout << "Opcion no valida.\n";
            break;
        }
    }
    return 0;
}
