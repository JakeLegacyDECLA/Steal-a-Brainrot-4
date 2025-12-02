/*
Nombre: César Daniel Aguilar Kuri
Matricula: A01712823
Nombre del Proyecto: Steal a Brainrot!
Materia: Programación de estructuras de datos y algoritmos fundamentales
Profesor: Eduardo Daniel Juárez Pineda
*/

#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector> // O(1)
using namespace std; // O(1)

// ===============================
// COMBINA dos mitades
// Complejidad: O(n)
// ===============================
template <class T, class Compare>
void mergeCombine(vector<T>& arr, size_t left, size_t mid, size_t right, Compare cmp) {
    size_t n1 = mid - left + 1; // O(1)
    size_t n2 = right - mid;    // O(1)

    vector<T> L(n1), R(n2);     // O(n)

    for (size_t i = 0; i < n1; i++) { // O(n)
        L[i] = arr[left + i];
    }
    for (size_t j = 0; j < n2; j++) { // O(n)
        R[j] = arr[mid + 1 + j];
    }

    size_t i = 0, j = 0, k = left; // O(1)

    while (i < n1 && j < n2) { // O(n)
        if (cmp(L[i], R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) { // O(n)
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) { // O(n)
        arr[k] = R[j];
        j++;
        k++;
    }
}

// ===============================
// RECURSIVO
// Complejidad: O(n log n)
// ===============================
template <class T, class Compare>
void mergeSortRec(vector<T>& arr, size_t left, size_t right, Compare cmp) {
    if (left >= right) {
        return;
    }

    size_t mid = left + (right - left) / 2;

    mergeSortRec(arr, left, mid, cmp);       // O(n log n)
    mergeSortRec(arr, mid + 1, right, cmp);  // O(n log n)

    mergeCombine(arr, left, mid, right, cmp); // O(n)
}

// ===============================
// PÚBLICA
// Complejidad: O(n log n)
// ===============================
template <class T, class Compare>
void mergeSort(vector<T>& arr, Compare cmp) {
    if (arr.size() < 2) {
        return;
    }
    mergeSortRec(arr, 0, arr.size() - 1, cmp);
}

#endif // MERGESORT_H
