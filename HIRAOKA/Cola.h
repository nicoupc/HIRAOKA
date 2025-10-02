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

	// Metodo para recorrer con lambda (REQUERIMIENTO: Lambda 1)
	void recorrer(function<void(T)> accion)
	{
		Nodo<T>* actual = inicio;
		while (actual != nullptr)
		{
			accion(actual->dato);
			actual = actual->siguiente;
		}
	}

	// Metodo para contar con lambda (REQUERIMIENTO: Lambda 2)
	int contar(function<bool(T)> condicion)
	{
		int contador = 0;
		Nodo<T>* actual = inicio;
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

	// Metodo para buscar con lambda (REQUERIMIENTO: Lambda 3)
	T buscar(function<bool(T)> condicion)
	{
		Nodo<T>* actual = inicio;
		while (actual != nullptr)
		{
			if (condicion(actual->dato))
			{
				return actual->dato;
			}
			actual = actual->siguiente;
		}
		return T();
	}

	// Metodo recursivo para imprimir (REQUERIMIENTO: Recursividad)
	void imprimirRecursivo(Nodo<T>* nodo, function<void(T)> mostrar)
	{
		if (nodo == nullptr) return;
		mostrar(nodo->dato);
		imprimirRecursivo(nodo->siguiente, mostrar);
	}

	void imprimirRecursivo(function<void(T)> mostrar)
	{
		imprimirRecursivo(inicio, mostrar);
	}

	// Metodo para obtener el inicio (util para otras operaciones)
	Nodo<T>* getInicio()
	{
		return inicio;
	}
};
