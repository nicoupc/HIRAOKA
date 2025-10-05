#include "Nodo.h"
#include <iostream>
#include <functional>
using namespace std;

template <class T>
class Pila
{
private:
	Nodo<T>* cima;
	int tamanio;

public:
	Pila()
	{
		cima = nullptr;
		tamanio = 0;
	}

	~Pila()
	{
		while (!estaVacia())
		{
			desapilar();
		}
	}

	bool estaVacia()
	{
		return cima == nullptr;
	}

	int getTamanio()
	{
		return tamanio;
	}

	void apilar(T dato)
	{
		Nodo<T>* nuevoNodo = new Nodo<T>(dato);
		nuevoNodo->siguiente = cima;
		cima = nuevoNodo;
		tamanio++;
	}

	T desapilar()
	{
		if (estaVacia())
		{
			cout << "La pila esta vacia" << endl;
			return T();
		}
		else
		{
			T elemento = cima->dato;
			Nodo<T>* temp = cima;
			cima = cima->siguiente;
			delete temp;
			tamanio--;
			return elemento;
		}
	}

	T verCima()
	{
		if (estaVacia())
		{
			cout << "La pila esta vacia" << endl;
			return T();
		}
		return cima->dato;
	}

	// ============================================================
	// METODOS CON LAMBDAS (3 requeridos)
	// ============================================================
	
	// Lambda 1: Mostrar todos los elementos
	void mostrarTodos() {
		auto mostrar = [](T dato) { cout << dato << " "; };
		
		Nodo<T>* actual = cima;
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
		Nodo<T>* actual = cima;
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
		Nodo<T>* actual = cima;
		while (actual != nullptr) {
			suma = sumar(suma, actual->dato);
			actual = actual->siguiente;
		}
		return suma;
	}

	// ============================================================
	// METODO RECURSIVO - Integrante 2
	// ============================================================
	
	// Contar elementos recursivamente - version privada
	int contarRecursivoPrivado(Nodo<T>* nodo) {
		if (nodo == nullptr) return 0;
		return 1 + contarRecursivoPrivado(nodo->siguiente);
	}

	// Contar elementos recursivamente - version publica
	int contarRecursivo() {
		return contarRecursivoPrivado(cima);
	}

	// ============================================================
	// ALGORITMO DE ORDENAMIENTO - Integrante 2
	// ============================================================
	
	// Integrante 2: Ordenamiento por Inserción (Insertion Sort)
	// Complejidad: O(n²)
	void ordenarInsercion() {
		if (estaVacia() || tamanio == 1) return;
		
		// Crear una pila temporal ordenada
		Nodo<T>* ordenado = nullptr;
		Nodo<T>* actual = cima;
		
		// Procesar cada elemento
		while (actual != nullptr) {
			Nodo<T>* siguiente = actual->siguiente;
			
			// Insertar en la posición correcta en la pila ordenada
			// Comparar desreferenciando si son punteros
			if (ordenado == nullptr || *actual->dato < *ordenado->dato) {
				// Insertar al inicio
				actual->siguiente = ordenado;
				ordenado = actual;
			} else {
				// Buscar posición correcta
				Nodo<T>* temp = ordenado;
				while (temp->siguiente != nullptr && *temp->siguiente->dato < *actual->dato) {
					temp = temp->siguiente;
				}
				actual->siguiente = temp->siguiente;
				temp->siguiente = actual;
			}
			actual = siguiente;
		}
		
		// Actualizar la cima con la pila ordenada
		cima = ordenado;
	}

	// ============================================================
	// OTROS METODOS AUXILIARES (Estilo del Profesor)
	// ============================================================
	
	// Metodo para obtener elemento en una posicion (como el profesor)
	T obtenerEnPosicion(int posicion) {
		if (posicion < 0 || posicion >= tamanio) {
			return T();
		}
		
		Nodo<T>* actual = cima;
		for (int i = 0; i < posicion; i++) {
			actual = actual->siguiente;
		}
		
		return actual->dato;
	}

	// Metodo para obtener la cima (util para otras operaciones)
	Nodo<T>* getCima()
	{
		return cima;
	}
};
