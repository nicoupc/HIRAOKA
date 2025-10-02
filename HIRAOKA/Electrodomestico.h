#pragma once
#include <string>
#include <iostream>

using namespace std;

class Electrodomestico {
private:
	string codigo;
	string nombre;
	string marca;
	string modelo;
	double precio;
	int anioFabricacion;
	int stock;

public:
	// Constructor por defecto
	Electrodomestico() {
		codigo = "";
		nombre = "";
		marca = "";
		modelo = "";
		precio = 0.0;
		anioFabricacion = 0;
		stock = 0;
	}

	// Constructor con parametros
	Electrodomestico(string _codigo, string _nombre, string _marca, string _modelo, double _precio, int _anio, int _stock) {
		codigo = _codigo;
		nombre = _nombre;
		marca = _marca;
		modelo = _modelo;
		precio = _precio;
		anioFabricacion = _anio;
		stock = _stock;
	}

	// Getters
	string getCodigo() { return codigo; }
	string getNombre() { return nombre; }
	string getMarca() { return marca; }
	string getModelo() { return modelo; }
	double getPrecio() { return precio; }
	int getAnioFabricacion() { return anioFabricacion; }
	int getStock() { return stock; }

	// Setters
	void setCodigo(string _codigo) { codigo = _codigo; }
	void setNombre(string _nombre) { nombre = _nombre; }
	void setMarca(string _marca) { marca = _marca; }
	void setModelo(string _modelo) { modelo = _modelo; }
	void setPrecio(double _precio) { precio = _precio; }
	void setAnioFabricacion(int _anio) { anioFabricacion = _anio; }
	void setStock(int _stock) { stock = _stock; }

	// Metodo para mostrar detalles
	void mostrarDetalles() {
		cout << "Codigo: " << codigo << endl;
		cout << "Nombre: " << nombre << endl;
		cout << "Marca: " << marca << endl;
		cout << "Modelo: " << modelo << endl;
		cout << "Precio: S/. " << precio << endl;
		cout << "Anio: " << anioFabricacion << endl;
		cout << "Stock: " << stock << " unidades" << endl;
	}

	// Metodo para reducir stock (cuando se vende)
	bool reducirStock(int cantidad) {
		if (stock >= cantidad) {
			stock -= cantidad;
			return true;
		}
		return false;
	}

	// Metodo para aumentar stock
	void aumentarStock(int cantidad) {
		stock += cantidad;
	}
};
