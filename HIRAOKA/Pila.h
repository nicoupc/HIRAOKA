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

	// Metodo para imprimir recursivamente (REQUERIMIENTO: Recursividad)
	void imprimirRecursivo(Nodo<T>* nodo, function<void(T)> mostrar)
	{
		if (nodo == nullptr) return;
		imprimirRecursivo(nodo->siguiente, mostrar);
		mostrar(nodo->dato);
	}

	void imprimirRecursivo(function<void(T)> mostrar)
	{
		imprimirRecursivo(cima, mostrar);
	}

	// Metodo para recorrer con lambda (REQUERIMIENTO: Lambda 1)
	void recorrer(function<void(T)> accion)
	{
		Nodo<T>* actual = cima;
		while (actual != nullptr)
		{
			accion(actual->dato);
			actual = actual->siguiente;
		}
	}

	// Metodo para buscar con lambda (REQUERIMIENTO: Lambda 2)
	T buscar(function<bool(T)> condicion)
	{
		Nodo<T>* actual = cima;
		while (actual != nullptr)
		{
			if (condicion(actual->dato))
			{
				return actual->dato;
			}
			actual = actual->siguiente;
		}
		return T(); // Retorna valor por defecto si no encuentra
	}

	// Metodo para contar con lambda (REQUERIMIENTO: Lambda 3)
	int contar(function<bool(T)> condicion)
	{
		int contador = 0;
		Nodo<T>* actual = cima;
		while (actual != nullptr)
		{
			if (condicion(actual->dato))
			{
				contador++;
			}
			actual = actual->siguiente;
		}
		return contador;
	}

	// Metodo para obtener la cima (util para otras operaciones)
	Nodo<T>* getCima()
	{
		return cima;
	}
};
