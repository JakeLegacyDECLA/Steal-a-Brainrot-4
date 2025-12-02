/*
Nombre: César Daniel Aguilar Kuri
Matricula: A01712823
Nombre del Proyecto: Steal a Brainrot!
Materia: Programación de estructuras de datos y algoritmos fundamentales
Profesor: Eduardo Daniel Juárez Pineda
*/

#ifndef STACKINVENTARIO_H
#define STACKINVENTARIO_H

#include <string>   // O(1)
#include <vector>   // O(1)
#include <fstream>  // O(1)
#include <iostream> // O(1)
using namespace std; // O(1)

// Estructura para cada personaje
struct RowStack { // O(1)
    string nombre; // O(1)
    string rareza; // O(1)
    float costo;   // O(1)
};

// Stack dinámico para manejar el inventario completo
class StackInventario {
private:
    struct Node {            // O(1)
        RowStack data;       // O(1)
        Node* next;          // O(1)
        Node(const RowStack& v) : data(v), next(NULL) {} // O(1)
    };

    Node* topNode; // O(1)

public:
    StackInventario() : topNode(NULL) {
    } // O(1)

    bool empty() const {  // O(1)
        return topNode == NULL; 
    } 

    // Agregar personaje al inventario dinámico
    void push(const RowStack& r) { // O(1)
        Node* nuevo = new Node(r); // O(1)
        nuevo->next = topNode;     // O(1)
        topNode = nuevo;           // O(1)
    }

    // Eliminar personaje del inventario
    bool pop(RowStack& out) { // O(1)
        if (empty()) return false; // O(1)
        Node* temp = topNode;      // O(1)
        out = temp->data;          // O(1)
        topNode = temp->next;      // O(1)
        delete temp;               // O(1)
        return true;               // O(1)
    }

    // Recorrer el Stack para pasarlo a vectores (para MergeSort)
    void toVectors(vector<string>& nombres,    // O(n)
                   vector<string>& rarezas,    // O(n)
                   vector<float>& costos) const // O(n)
    {
        Node* p = topNode;                      // O(1)
        while (p != NULL) {                     // O(n)
            nombres.push_back(p->data.nombre);  // O(1)
            rarezas.push_back(p->data.rareza);  // O(1)
            costos.push_back(p->data.costo);    // O(1)
            p = p->next;                        // O(1)
        }
    }

    // Cargar el Stack desde los vectores principales
    // Complejidad: O(n)
    void fromVectors(const vector<string>& nombres,
                    const vector<string>& rarezas,
                    const vector<float>& costos) 
    {
        Node* p = topNode;              // O(1)
        while (p != NULL) {             // O(n)
            Node* nxt = p->next;        // O(1)
            delete p;                   // O(1)
            p = nxt;                    // O(1)
        }
        topNode = NULL;                 // O(1)

    // Insertar al revés para que el stack mantenga el orden correcto
    for (int i = (int)nombres.size() - 1; i >= 0; i--) {  // O(n)
        RowStack r = {nombres[i], rarezas[i], costos[i]}; // O(1)
        push(r);                                          // O(1)
        }
    }


    // Guardar el inventario dinámico en CSV
    bool guardarCSV(const string& ruta) const { // O(n)
        ofstream out(ruta);                     // O(1)
        if (!out.is_open()){
            return false;                       // O(1)
        }

        out << "Nombre,Rareza,Costo\n";         // O(1)

        Node* p = topNode;                      // O(1)
        while (p != NULL) {                     // O(n)
            out << p->data.nombre << ","        // O(1)
                << p->data.rareza << ","        // O(1)
                << p->data.costo  << "\n";      // O(1)
            p = p->next;                        // O(1)
        }
        return true; // O(1)
    }

    // Cargar un CSV directamente en el Stack
    bool cargarCSV(const string& ruta,          // O(n)
                   const vector<string>& rarezasValidas) // O(n)
    {
        ifstream in(ruta);                      // O(1)
        if (!in.is_open()) return false;        // O(1)

        string linea;                            // O(1)
        bool primera = true;                     // O(1)

        while (getline(in, linea)) {             // O(n)
            if (primera) {  // O(1)
                primera = false; 
                continue; 
            } 
            if (linea.empty()) {continue;
            }         // O(1)

            string nombre, rareza, costoStr;     // O(1)
            size_t pos1 = linea.find(',');       // O(1)
            size_t pos2 = linea.find(',', pos1+1); // O(1)

            if (pos1 == string::npos || pos2 == string::npos) {
                continue; // O(1)
            }

            nombre = linea.substr(0, pos1);       // O(1)
            rareza = linea.substr(pos1 + 1, pos2 - pos1 - 1); // O(1)
            costoStr = linea.substr(pos2 + 1);    // O(1)

            // validar rareza
            bool ok = false;                      // O(1)
            for (auto& r : rarezasValidas) {      // O(n)
                if (rareza == r) { ok = true; break; } // O(1)
            }
            if (!ok) {  // O(1)
                rareza = "Common";
            }           

            float costo = stof(costoStr);         // O(1)

            RowStack row = {nombre, rareza, costo}; // O(1)
            push(row);                             // O(1)
        }

        return true; // O(1)
    }
};

#endif
