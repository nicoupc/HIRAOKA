#include "Nodo.h"
#include <iostream>
#include <functional>

using namespace std;

template <class T>
class Cola
{
private:
	Nodo<T>* inicio;
	Nodo<T>* fin;
	int tamanio;

public:
	Cola()
	{
		this->inicio = nullptr;
		this->fin = nullptr;
		this->tamanio = 0;
	}

	~Cola()
	{
		while (!esVacia())
		{
			desencolar();
		}
	}

	bool esVacia()
	{
		return (inicio == nullptr);
	}

	int getTamanio()
	{
		return tamanio;
	}

	void encolar(T valor)
	{
		Nodo<T>* nodo = new Nodo<T>(valor);

		if (esVacia())
		{
			inicio = nodo;
			fin = inicio;
		}
		else
		{
			fin->siguiente = nodo;
			fin = nodo;
		}
		tamanio++;
	}

	T desencolar()
	{
		if (esVacia())
		{
			cout << "La cola esta vacia" << endl;
			return T();
		}

		T dato = inicio->dato;
		Nodo<T>* temp = inicio;

		if (inicio == fin)
		{
			inicio = nullptr;
			fin = nullptr;
		}
		else
		{
			inicio = inicio->siguiente;
		}

		delete temp;
		tamanio--;
		return dato;
	}

	T verPrimero()
	{
		if (esVacia())
		{
			cout << "La cola esta vacia" << endl;
			return T();
		}
		return inicio->dato;
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
	// METODO RECURSIVO - Integrante 3
	// ============================================================
	
	// Imprimir recursivamente - version privada
	void imprimirRecursivoPrivado(Nodo<T>* nodo, function<void(T)> accion) {
		if (nodo == nullptr) return;
		accion(nodo->dato);
		imprimirRecursivoPrivado(nodo->siguiente, accion);
	}

	// Imprimir recursivamente - version publica
	void imprimirRecursivo(function<void(T)> accion) {
		imprimirRecursivoPrivado(inicio, accion);
	}

	// ============================================================
	// ALGORITMO DE ORDENAMIENTO - Integrante 3
	// ============================================================
	
	// Integrante 3: Ordenamiento por Selección (Selection Sort)
	// Complejidad: O(n²)
	void ordenarSeleccion() {
		if (esVacia() || tamanio == 1) return;
		
		// Recorrer toda la cola
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			// Buscar el elemento mínimo desde actual hasta el final
			Nodo<T>* minimo = actual;
			Nodo<T>* temp = actual->siguiente;
			
			while (temp != nullptr) {
				// Comparar desreferenciando si son punteros
				if (*temp->dato < *minimo->dato) {
					minimo = temp;
				}
				temp = temp->siguiente;
			}
			
			// Intercambiar el dato del nodo actual con el mínimo encontrado
			if (minimo != actual) {
				T aux = actual->dato;
				actual->dato = minimo->dato;
				minimo->dato = aux;
			}
			
			actual = actual->siguiente;
		}
	}

	// ============================================================
	// OTROS METODOS AUXILIARES (Estilo del Profesor)
	// ============================================================
	
	// Metodo para obtener elemento en una posicion (como el profesor)
	T obtenerEnPosicion(int posicion) {
		if (posicion < 0 || posicion >= tamanio) {
			return T();
		}
		
		Nodo<T>* actual = inicio;
		for (int i = 0; i < posicion; i++) {
			actual = actual->siguiente;
		}
		
		return actual->dato;
	}

	Nodo<T>* getInicio() {
		return inicio;
	}
};
