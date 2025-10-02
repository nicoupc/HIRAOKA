#pragma once

template <class T>
class Nodo
{
public:
	T dato;
	Nodo* siguiente;

	Nodo()
	{
		siguiente = nullptr;
	}

	Nodo(T valor)
	{
		dato = valor;
		siguiente = nullptr;
	}
};
