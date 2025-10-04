#pragma once
#include <string>
#include "Electrodomestico.h"

using namespace std;

// Clase simple para representar un item en el carrito
class ItemCarrito {
private:
	Electrodomestico* producto;
	int cantidad;

public:
	// Constructor
	ItemCarrito(Electrodomestico* prod, int cant) {
		producto = prod;
		cantidad = cant;
	}

	// Getters
	Electrodomestico* getProducto() { return producto; }
	int getCantidad() { return cantidad; }

	// Setters
	void setCantidad(int cant) { cantidad = cant; }

	// Calcular subtotal
	double getSubtotal() {
		return producto->getPrecio() * cantidad;
	}

	// Mostrar item
	void mostrar() {
		cout << producto->getNombre() 
			 << " x" << cantidad 
			 << " = S/. " << getSubtotal() << endl;
	}
};
