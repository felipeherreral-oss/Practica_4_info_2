#include "red.h"

Red::Red() {}

void Red::agregarEnrutador(string id) {
    // Verificamos si el enrutador ya existe para no sobrescribirlo
    if (enrutadores.find(id) == enrutadores.end()) {
        enrutadores.insert({id, Enrutador(id)});
        cout << "Enrutador " << id << " agregado a la red.\n";
    } else {
        cout << "Error: El enrutador " << id << " ya existe.\n";
    }
}

void Red::eliminarEnrutador(string id) {
    if (enrutadores.find(id) != enrutadores.end()) {
        // 1. Primero, debemos desconectar este enrutador de todos sus vecinos
        map<string, int> susVecinos = enrutadores.at(id).getVecinos();
        for (const auto& par : susVecinos) {
            string idVecino = par.first;
            enrutadores.at(idVecino).eliminarVecino(id); // El vecino olvida a este nodo
        }

        // 2. Ahora sí lo eliminamos de la red
        enrutadores.erase(id);
        cout << "Enrutador " << id << " eliminado de la red por completo.\n";
    }
}

void Red::conectar(string origen, string destino, int costo) {
    // Validamos que ambos nodos existan en la red
    if (enrutadores.find(origen) != enrutadores.end() && enrutadores.find(destino) != enrutadores.end()) {
        enrutadores.at(origen).agregarVecino(destino, costo);
        enrutadores.at(destino).agregarVecino(origen, costo);
        cout << "Conectados " << origen << " y " << destino << " con costo " << costo << ".\n";
    } else {
        cout << "Error: Uno o ambos enrutadores no existen en la red.\n";
    }
}

void Red::desconectar(string origen, string destino) {
    if (enrutadores.find(origen) != enrutadores.end() && enrutadores.find(destino) != enrutadores.end()) {
        enrutadores.at(origen).eliminarVecino(destino);
        enrutadores.at(destino).eliminarVecino(origen);
        cout << "Enlace entre " << origen << " y " << destino << " eliminado.\n";
    }
}

void Red::imprimirRed() const {
    cout << "\n=== TOPOLOGIA DE LA RED ===\n";
    for (const auto& par : enrutadores) {
        cout << "Enrutador [" << par.first << "] conectado a:\n";
        map<string, int> vecinos = par.second.getVecinos();
        if (vecinos.empty()) {
            cout << "  (Sin conexiones)\n";
        } else {
            for (const auto& v : vecinos) {
                cout << "  -> " << v.first << " (Costo: " << v.second << ")\n";
            }
        }
    }
    cout << "===========================\n\n";
}
