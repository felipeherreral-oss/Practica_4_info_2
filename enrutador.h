#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>
#include <iostream>

using namespace std;

class Enrutador {
private:
    string id;
    // Mapa de vecinos directos: <ID del vecino, Costo del enlace>
    map<string, int> vecinos;
    // Tabla de enrutamiento final: <ID del destino, Costo total óptimo>
    map<string, int> tablaCostos;

public:
    // Constructor
    Enrutador(string _id);

    // Métodos para gestionar vecinos
    void agregarVecino(string idVecino, int costo);
    void eliminarVecino(string idVecino);
    map<string, int> getVecinos() const;

    // Métodos para la tabla de costos (Dijkstra la actualizará luego)
    void actualizarTabla(string destino, int costo);
    void imprimirTabla() const;
    void reiniciarTabla();

    // Getters
    string getId() const;
};

#endif // ENRUTADOR_H
