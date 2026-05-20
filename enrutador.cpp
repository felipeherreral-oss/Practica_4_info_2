#include "enrutador.h"

// Constructor
Enrutador::Enrutador(string _id) : id(_id) {
    // El costo para llegar a sí mismo es 0
    tablaCostos[id] = 0;
}

void Enrutador::agregarVecino(string idVecino, int costo) {
    vecinos[idVecino] = costo;
    // El costo a un vecino es el costo del enlace
    tablaCostos[idVecino] = costo;
}

void Enrutador::eliminarVecino(string idVecino) {
    vecinos.erase(idVecino);
}

map<string, int> Enrutador::getVecinos() const {
    return vecinos;
}

void Enrutador::actualizarTabla(string destino, int costo) {
    tablaCostos[destino] = costo;
}

void Enrutador::imprimirTabla() const {
    cout << "Tabla de Enrutamiento del Nodo [" << id << "]:\n";
    for (const auto& par : tablaCostos) {
        cout << "  -> Destino: " << par.first << " | Costo: " << par.second << "\n";
    }
    cout << "-----------------------------------\n";
}

string Enrutador::getId() const {
    return id;
}
