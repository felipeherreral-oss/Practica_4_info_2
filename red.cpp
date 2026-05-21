#include "red.h"

// Constructor
Red::Red() {}

// Agrega un nuevo enrutador si no existe previamente
void Red::agregarEnrutador(string id) {
    if (enrutadores.find(id) == enrutadores.end()) {
        enrutadores.insert({id, Enrutador(id)});
        cout << "[SISTEMA] Enrutador " << id << " agregado a la red.\n";
        actualizarTodasLasTablas(); // Recalcular por cambio de topología
    } else {
        cout << "[ERROR] El enrutador " << id << " ya existe.\n";
    }
}

// Elimina un enrutador y limpia todos los enlaces hacia él desde sus vecinos
void Red::eliminarEnrutador(string id) {
    if (enrutadores.find(id) != enrutadores.end()) {
        // Almacenar temporalmente sus vecinos para desconectarlos mutuamente
        map<string, int> susVecinos = enrutadores.at(id).getVecinos();
        for (const auto& par : susVecinos) {
            string idVecino = par.first;
            enrutadores.at(idVecino).eliminarVecino(id); // El vecino olvida al nodo eliminado
        }

        enrutadores.erase(id);
        cout << "[SISTEMA] Enrutador " << id << " eliminado de la red por completo.\n";
        actualizarTodasLasTablas(); // Recalcular por cambio de topología
    } else {
        cout << "[ERROR] El enrutador " << id << " no existe en la red.\n";
    }
}

// Conecta o modifica el costo de un enlace bidireccional entre dos enrutadores
void Red::conectar(string origen, string destino, int costo) {
    if (enrutadores.find(origen) != enrutadores.end() && enrutadores.find(destino) != enrutadores.end()) {
        enrutadores.at(origen).agregarVecino(destino, costo);
        enrutadores.at(destino).agregarVecino(origen, costo);
        cout << "[SISTEMA] Enlace establecido: " << origen << " <-> " << destino << " (Costo: " << costo << ").\n";
        actualizarTodasLasTablas(); // Recalcular por cambio de topología
    } else {
        cout << "[ERROR] Uno o ambos enrutadores no existen para realizar la conexion.\n";
    }
}

// Rompe el enlace bidireccional entre dos enrutadores
void Red::desconectar(string origen, string destino) {
    if (enrutadores.find(origen) != enrutadores.end() && enrutadores.find(destino) != enrutadores.end()) {
        enrutadores.at(origen).eliminarVecino(destino);
        enrutadores.at(destino).eliminarVecino(origen);
        cout << "[SISTEMA] Enlace eliminado entre " << origen << " y " << destino << ".\n";
        actualizarTodasLasTablas(); // Recalcular por cambio de topología
    } else {
        cout << "[ERROR] Uno o ambos enrutadores no existen.\n";
    }
}

// --- NÚCLEO DE RED: IMPLEMENTACIÓN DEL ALGORITMO DE DIJKSTRA ---

void Red::actualizarTodasLasTablas() {
    const int INF = 1e9; // Infinito seguro para evitar desbordamientos aritméticos

    // Ejecutamos Dijkstra tomando cada nodo de la red como origen
    for (auto& parOrigen : enrutadores) {
        string origen = parOrigen.first;
        enrutadores.at(origen).reiniciarTabla(); // Limpiar tabla de costos previa

        map<string, int> distancias;
        for (const auto& p : enrutadores) distancias[p.first] = INF;
        distancias[origen] = 0;

        // Cola de prioridad estructurada como Min-Heap: <Costo_Acumulado, ID_Nodo>
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> cola;
        cola.push({0, origen});

        while (!cola.empty()) {
            string u = cola.top().second;
            int dist_u = cola.top().first;
            cola.pop();

            if (dist_u > distancias[u]) continue;

            // Explorar los vecinos directos de 'u'
            map<string, int> vecinos = enrutadores.at(u).getVecinos();
            for (const auto& v_par : vecinos) {
                string v = v_par.first;
                int pesoEnlace = v_par.second;

                // Relajación de la arista (Encontrar un camino más corto a 'v')
                if (distancias[u] + pesoEnlace < distancias[v]) {
                    distancias[v] = distancias[u] + pesoEnlace;
                    cola.push({distancias[v], v});
                }
            }
        }

        // Guardar de forma centralizada los costos óptimos calculados en el enrutador de origen
        for (const auto& d : distancias) {
            if (d.second != INF && d.first != origen) {
                enrutadores.at(origen).actualizarTabla(d.first, d.second);
            }
        }
    }
}

// Calcula y reconstruye paso a paso la secuencia exacta de nodos del camino óptimo
vector<string> Red::obtenerRuta(string origen, string destino, int &costoTotal) {
    const int INF = 1e9;
    vector<string> caminoFinal;
    costoTotal = INF;

    if (enrutadores.find(origen) == enrutadores.end() || enrutadores.find(destino) == enrutadores.end()) {
        return caminoFinal; // Retorna vacío si algún nodo no existe en la topología
    }

    map<string, int> distancias;
    map<string, string> predecesor; // Almacena de dónde venimos para reconstruir la ruta hacia atrás
    for (const auto& p : enrutadores) distancias[p.first] = INF;
    distancias[origen] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> cola;
    cola.push({0, origen});

    while (!cola.empty()) {
        string u = cola.top().second;
        int dist_u = cola.top().first;
        cola.pop();

        if (u == destino) break; // Optimización: Si extraemos el destino, terminamos
        if (dist_u > distancias[u]) continue;

        for (const auto& v_par : enrutadores.at(u).getVecinos()) {
            string v = v_par.first;
            int peso = v_par.second;

            if (distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                predecesor[v] = u; // Registrar que a 'v' se llegó de manera óptima por 'u'
                cola.push({distancias[v], v});
            }
        }
    }

    costoTotal = distancias[destino];

    // Si el destino es alcanzable, marchamos en reversa usando el mapa de predecesores
    if (costoTotal != INF) {
        string actual = destino;
        while (actual != origen) {
            caminoFinal.insert(caminoFinal.begin(), actual); // Insertar al inicio para ordenar correctamente
            actual = predecesor[actual];
        }
        caminoFinal.insert(caminoFinal.begin(), origen); // Insertar finalmente el nodo de origen
    }

    return caminoFinal;
}

// Carga la topología desde un archivo .txt con formato: "Origen Destino Costo"
void Red::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo abrir o encontrar el archivo: " << nombreArchivo << "\n";
        return;
    }

    // Reiniciar la red por completo antes de cargar los nuevos datos
    enrutadores.clear();

    string origen, destino;
    int costo;

    // Procesar iterativamente cada línea del archivo plano
    while (archivo >> origen >> destino >> costo) {
        // Asegurar la existencia de ambos enrutadores en la red
        if (enrutadores.find(origen) == enrutadores.end()) {
            enrutadores.insert({origen, Enrutador(origen)});
        }
        if (enrutadores.find(destino) == enrutadores.end()) {
            enrutadores.insert({destino, Enrutador(destino)});
        }

        // Crear la conexión bidireccional directa
        enrutadores.at(origen).agregarVecino(destino, costo);
        enrutadores.at(destino).agregarVecino(origen, costo);
    }

    archivo.close();

    // Ejecutar Dijkstra masivo una sola vez al terminar la lectura por máxima eficiencia
    actualizarTodasLasTablas();

    cout << "[ÉXITO] Red y tablas de enrutamiento cargadas correctamente desde el archivo.\n";
}

// Muestra en consola el volcado completo de todas las tablas calculadas
void Red::imprimirRed() const {
    cout << "\n=================================================\n";
    cout << "     TABLAS DE ENRUTAMIENTO ACTUALES EN LA RED   \n";
    cout << "=================================================\n";
    for (const auto& par : enrutadores) {
        par.second.imprimirTabla();
    }
}
