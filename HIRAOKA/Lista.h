#pragma once
#include "Nodo.h"
#include <functional>
#include <iostream>

using namespace std;

template <class T>
class Lista {
private:
	Nodo<T>* inicio;
	int tamanio;

public:
	// Constructor
	Lista() {
		inicio = nullptr;
		tamanio = 0;
	}

	// Destructor
	~Lista() {
		while (!estaVacia()) {
			eliminarInicio();
		}
	}

	// Operaciones basicas
	bool estaVacia() {
		return tamanio == 0;
	}

	int longitud() {
		return tamanio;
	}

	// Agregar elementos
	void agregarInicio(T elemento) {
		Nodo<T>* nuevo = new Nodo<T>(elemento);
		nuevo->siguiente = inicio;
		inicio = nuevo;
		tamanio++;
	}

	void agregarFinal(T elemento) {
		if (estaVacia()) {
			agregarInicio(elemento);
			return;
		}

		Nodo<T>* actual = inicio;
		while (actual->siguiente != nullptr) {
			actual = actual->siguiente;
		}

		actual->siguiente = new Nodo<T>(elemento);
		tamanio++;
	}

	void agregarPosicion(T elemento, int posicion) {
		if (posicion < 0 || posicion > tamanio) return;

		if (posicion == 0) {
			agregarInicio(elemento);
			return;
		}

		Nodo<T>* actual = inicio;
		for (int i = 0; i < posicion - 1; i++) {
			actual = actual->siguiente;
		}

		Nodo<T>* nuevo = new Nodo<T>(elemento);
		nuevo->siguiente = actual->siguiente;
		actual->siguiente = nuevo;
		tamanio++;
	}

	// Eliminar elementos
	void eliminarInicio() {
		if (estaVacia()) return;

		Nodo<T>* eliminar = inicio;
		inicio = inicio->siguiente;
		delete eliminar;
		tamanio--;
	}

	void eliminarFinal() {
		if (estaVacia()) return;

		if (tamanio == 1) {
			eliminarInicio();
			return;
		}

		Nodo<T>* actual = inicio;
		while (actual->siguiente->siguiente != nullptr) {
			actual = actual->siguiente;
		}

		delete actual->siguiente;
		actual->siguiente = nullptr;
		tamanio--;
	}

	void eliminarPosicion(int posicion) {
		if (posicion < 0 || posicion >= tamanio) return;

		if (posicion == 0) {
			eliminarInicio();
			return;
		}

		Nodo<T>* actual = inicio;
		for (int i = 0; i < posicion - 1; i++) {
			actual = actual->siguiente;
		}

		Nodo<T>* eliminar = actual->siguiente;
		actual->siguiente = eliminar->siguiente;
		delete eliminar;
		tamanio--;
	}

	// Obtener elementos
	T obtenerPosicion(int posicion) {
		if (posicion < 0 || posicion >= tamanio) {
			return T();
		}

		Nodo<T>* actual = inicio;
		for (int i = 0; i < posicion; i++) {
			actual = actual->siguiente;
		}

		return actual->dato;
	}

	// ============================================================
	// METODOS CON LAMBDAS (3 requeridos)
	// ============================================================
	
	// Lambda 1: Mostrar todos los elementos
	void mostrarTodos() {
		auto mostrar = [](T dato) { cout << dato << " "; };
		
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			mostrar(actual->dato);
			actual = actual->siguiente;
		}
		cout << endl;
	}

	// Lambda 2: Contar elementos
	int contarElementos() {
		auto contar = [](int a, int b) { return a + b; };
		
		int total = 0;
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			total = contar(total, 1);
			actual = actual->siguiente;
		}
		return total;
	}

	// Lambda 3: Sumar elementos
	T sumarElementos() {
		auto sumar = [](T a, T b) { return a + b; };
		
		T suma = T();
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			suma = sumar(suma, actual->dato);
			actual = actual->siguiente;
		}
		return suma;
	}

	// ============================================================
	// METODO RECURSIVO - Integrante 1
	// ============================================================
	
	// Buscar recursivamente - version privada
	T buscarRecursivoPrivado(Nodo<T>* nodo, function<bool(T)> condicion) {
		if (nodo == nullptr) return T();
		if (condicion(nodo->dato)) return nodo->dato;
		return buscarRecursivoPrivado(nodo->siguiente, condicion);
	}

	// Buscar recursivamente - version publica
	T buscarRecursivo(function<bool(T)> condicion) {
		return buscarRecursivoPrivado(inicio, condicion);
	}

	// ============================================================
	// ALGORITMO DE ORDENAMIENTO - Integrante 1
	// ============================================================
	
	// Integrante 1: Ordenamiento Burbuja (Bubble Sort)
	// Complejidad: O(n²)
	void ordenarBurbuja() {
		if (estaVacia() || tamanio == 1) return;
		
		// Algoritmo de burbuja: compara pares adyacentes y los intercambia
		for (int i = 0; i < tamanio - 1; i++) {
			Nodo<T>* actual = inicio;
			for (int j = 0; j < tamanio - i - 1; j++) {
				// Si el siguiente nodo existe y es necesario intercambiar
				if (actual->siguiente != nullptr) {
					// Comparar los datos (desreferenciar si son punteros)
					if (*actual->dato > *actual->siguiente->dato) {
						// Intercambiar los datos entre nodos
						T temp = actual->dato;
						actual->dato = actual->siguiente->dato;
						actual->siguiente->dato = temp;
					}
				}
				actual = actual->siguiente;
			}
		}
	}

	// ============================================================
	// OTROS METODOS AUXILIARES (Estilo del Profesor)
	// ============================================================

	// Metodo para obtener el nodo inicial (util para iteracion)
	Nodo<T>* getInicio() {
		return inicio;
	}
};
