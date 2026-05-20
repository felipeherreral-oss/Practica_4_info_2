#ifndef RED_H
#define RED_H

#include "enrutador.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;

class Red {
private:
    // Nuestro contenedor principal: <Nombre del Enrutador, Objeto Enrutador>
    map<string, Enrutador> enrutadores;

public:
    Red(); // Constructor

    // Métodos para gestionar la topología (Nodos)
    void agregarEnrutador(string id);
    void eliminarEnrutador(string id);

    // Métodos para gestionar enlaces (Cables)
    // Asumiremos conexiones bidireccionales (lo estándar en estas redes)
    void conectar(string origen, string destino, int costo);
    void desconectar(string origen, string destino);

    // Método para visualizar la red completa
    void imprimirRed() const;
};

#endif // RED_H
