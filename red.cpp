#include "red.h"

Red::Red() {}

// --- MÉTODOS DE GESTIÓN ACTUALIZADOS (Llaman a actualizarTodasLasTablas al final) ---

void Red::agregarEnrutador(string id) {
    if (enrutadores.find(id) == enrutadores.end()) {
        enrutadores.insert({id, Enrutador(id)});
        actualizarTodasLasTablas(); // <--- ¡Cambio de topología!
    }
}

void Red::eliminarEnrutador(string id) {
    if (enrutadores.find(id) != enrutadores.end()) {
        map<string, int> susVecinos = enrutadores.at(id).getVecinos();
        for (const auto& par : susVecinos) {
            enrutadores.at(par.first).eliminarVecino(id);
        }
        enrutadores.erase(id);
        cout << "Enrutador " << id << " eliminado.\n";
        actualizarTodasLasTablas(); // <--- ¡Cambio de topología!
    }
}

void Red::conectar(string origen, string destino, int costo) {
    if (enrutadores.find(origen) != enrutadores.end() && enrutadores.find(destino) != enrutadores.end()) {
        enrutadores.at(origen).agregarVecino(destino, costo);
        enrutadores.at(destino).agregarVecino(origen, costo);
        actualizarTodasLasTablas(); // <--- ¡Cambio de topología!
    }
}

void Red::desconectar(string origen, string destino) {
    if (enrutadores.find(origen) != enrutadores.end() && enrutadores.find(destino) != enrutadores.end()) {
        enrutadores.at(origen).eliminarVecino(destino);
        enrutadores.at(destino).eliminarVecino(origen);
        actualizarTodasLasTablas(); // <--- ¡Cambio de topología!
    }
}

// --- CORE DEL PROYECTO: ALGORITMO DE DIJKSTRA ---

void Red::actualizarTodasLasTablas() {
    // Definimos un valor infinito seguro para evitar desbordamientos (overflow)
    const int INF = 1e9;

    // Ejecutamos Dijkstra tomando cada nodo de la red como origen
    for (auto& parOrigen : enrutadores) {
        string origen = parOrigen.first;
        enrutadores.at(origen).reiniciarTabla(); // Limpiamos datos viejos

        // Mapas locales para el cálculo de este origen
        map<string, int> distancias;
        for (const auto& p : enrutadores) distancias[p.first] = INF;
        distancias[origen] = 0;

        // Cola de prioridad (Min-Heap) -> Almacena pares: <Costo Acumulado, ID_Nodo>
        // Tal como sugieren los ejemplos de la profesora, usamos greater<> para que el menor costo salga primero
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> cola;
        cola.push({0, origen});

        while (!cola.empty()) {
            string u = cola.top().second;
            int dist_u = cola.top().first;
            cola.pop();

            if (dist_u > distancias[u]) continue;

            // Revisamos los vecinos del nodo 'u'
            map<string, int> vecinos = enrutadores.at(u).getVecinos();
            for (const auto& v_par : vecinos) {
                string v = v_par.first;
                int pesoEnlace = v_par.second;

                if (distancias[u] + pesoEnlace < distancias[v]) {
                    distancias[v] = distancias[u] + pesoEnlace;
                    cola.push({distancias[v], v});
                }
            }
        }

        // Guardamos los resultados óptimos en la tabla interna del enrutador origen
        for (const auto& d : distancias) {
            if (d.second != INF && d.first != origen) {
                enrutadores.at(origen).actualizarTabla(d.first, d.second);
            }
        }
    }
}

vector<string> Red::obtenerRuta(string origen, string destino, int &costoTotal) {
    const int INF = 1e9;
    vector<string> caminoFinal;
    costoTotal = INF;

    if (enrutadores.find(origen) == enrutadores.end() || enrutadores.find(destino) == enrutadores.end()) {
        return caminoFinal; // Retorna vacío si uno no existe
    }

    // Volvemos a correr un Dijkstra enfocado, pero registrando PREDECESORES para armar el camino
    map<string, int> distancias;
    map<string, string> predecesor;
    for (const auto& p : enrutadores) distancias[p.first] = INF;
    distancias[origen] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> cola;
    cola.push({0, origen});

    while (!cola.empty()) {
        string u = cola.top().second;
        int dist_u = cola.top().first;
        cola.pop();

        if (u == destino) break; // Optimizacion: si llegamos al destino, paramos
        if (dist_u > distancias[u]) continue;

        for (const auto& v_par : enrutadores.at(u).getVecinos()) {
            string v = v_par.first;
            int peso = v_par.second;

            if (distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                predecesor[v] = u;
                cola.push({distancias[v], v});
            }
        }
    }

    costoTotal = distancias[destino];

    // Si es alcanzable, reconstruimos el camino marchando hacia atrás desde el destino
    if (costoTotal != INF) {
        string actual = destino;
        while (actual != origen) {
            caminoFinal.insert(caminoFinal.begin(), actual); // Inserta al principio
            actual = predecesor[actual];
        }
        caminoFinal.insert(caminoFinal.begin(), origen); // Al final insertamos el origen
    }

    return caminoFinal;
}

void Red::imprimirRed() const {
    cout << "\n=== TABLAS DE ENRUTAMIENTO ACTUALES DE LA RED ===\n";
    for (const auto& par : enrutadores) {
        par.second.imprimirTabla();
    }
    cout << "=================================================\n\n";
}
