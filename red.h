#ifndef RED_H
#define RED_H

#include "enrutador.h"
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Red {
private:
    map<string, Enrutador> enrutadores;

    // MÉTODO PRIVADO (Fase 3): Ejecuta Dijkstra para actualizar las tablas internas
    void actualizarTodasLasTablas();

public:
    Red();
    void agregarEnrutador(string id);
    void eliminarEnrutador(string id);
    void conectar(string origen, string destino, int costo);
    void desconectar(string origen, string destino);
    void imprimirRed() const;

    // MÉTODO PÚBLICO (Fase 3): Encuentra la ruta óptima entre dos puntos
    vector<string> obtenerRuta(string origen, string destino, int &costoTotal);
};

#endif // RED_H
