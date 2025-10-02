#pragma once
#include "Nodo.h"
#include <functional>

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

	// Metodo para recorrer con lambda (REQUERIMIENTO: Lambda 1)
	void recorrer(function<void(T)> accion) {
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			accion(actual->dato);
			actual = actual->siguiente;
		}
	}

	// Metodo para filtrar con lambda (REQUERIMIENTO: Lambda 2)
	Lista<T>* filtrar(function<bool(T)> condicion) {
		Lista<T>* listaFiltrada = new Lista<T>();
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			if (condicion(actual->dato)) {
				listaFiltrada->agregarFinal(actual->dato);
			}
			actual = actual->siguiente;
		}
		return listaFiltrada;
	}

	// Metodo de busqueda recursiva (REQUERIMIENTO: Recursividad)
	T buscarRecursivo(Nodo<T>* nodo, function<bool(T)> condicion) {
		if (nodo == nullptr) {
			return T(); // Retorna valor por defecto si no encuentra
		}
		if (condicion(nodo->dato)) {
			return nodo->dato;
		}
		return buscarRecursivo(nodo->siguiente, condicion);
	}

	T buscarRecursivo(function<bool(T)> condicion) {
		return buscarRecursivo(inicio, condicion);
	}

	// Metodo para ordenar por burbuja mejorado
	void ordenarBurbuja(function<bool(T, T)> comparar) {
		if (estaVacia() || tamanio == 1) return;

		for (int i = 0; i < tamanio - 1; i++) {
			Nodo<T>* actual = inicio;
			for (int j = 0; j < tamanio - i - 1; j++) {
				if (comparar(actual->siguiente->dato, actual->dato)) {
					// Intercambiar datos
					T temp = actual->dato;
					actual->dato = actual->siguiente->dato;
					actual->siguiente->dato = temp;
				}
				actual = actual->siguiente;
			}
		}
	}

	// Metodo para contar elementos que cumplen condicion (Lambda 3)
	int contar(function<bool(T)> condicion) {
		int contador = 0;
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			if (condicion(actual->dato)) {
				contador++;
			}
			actual = actual->siguiente;
		}
		return contador;
	}

	// Metodo para obtener el nodo inicial (util para iteracion)
	Nodo<T>* getInicio() {
		return inicio;
	}
};
