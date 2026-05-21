#ifndef RED_H
#define RED_H

#include "enrutador.h"
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>

using namespace std;

class Red {
private:
    // Contenedor principal: <ID_Enrutador, Objeto_Enrutador>
    map<string, Enrutador> enrutadores;

    // Ejecuta el algoritmo de Dijkstra desde cada nodo para mantener las tablas internas al día
    void actualizarTodasLasTablas();

public:
    // Constructor por defecto
    Red();

    // Métodos para la gestión dinámica de Enrutadores (Nodos)
    void agregarEnrutador(string id);
    void eliminarEnrutador(string id);

    // Métodos para la gestión dinámica de Enlaces (Aristas bidireccionales)
    void conectar(string origen, string destino, int costo);
    void desconectar(string origen, string destino);

    // Muestra en consola el estado de todas las tablas de enrutamiento
    void imprimirRed() const;

    // Encuentra el camino óptimo y devuelve el vector con la ruta detallada y su costo
    vector<string> obtenerRuta(string origen, string destino, int &costoTotal);

    // Carga y configura una topología completa desde un archivo de texto (.txt)
    void cargarDesdeArchivo(const string& nombreArchivo);
};

#endif // RED_H
