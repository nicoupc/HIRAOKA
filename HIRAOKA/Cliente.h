#pragma once
#include <string>
#include <iostream>

using namespace std;

class Cliente {
private:
	string dni;
	string nombres;
	string apellidos;
	string telefono;
	string direccion;

public:
	// Constructor por defecto
	Cliente() {
		dni = "";
		nombres = "";
		apellidos = "";
		telefono = "";
		direccion = "";
	}

	// Constructor con parametros
	Cliente(string _dni, string _nombres, string _apellidos, string _telefono, string _direccion) {
		dni = _dni;
		nombres = _nombres;
		apellidos = _apellidos;
		telefono = _telefono;
		direccion = _direccion;
	}

	// Getters
	string getDni() { return dni; }
	string getNombres() { return nombres; }
	string getApellidos() { return apellidos; }
	string getTelefono() { return telefono; }
	string getDireccion() { return direccion; }

	// Setters
	void setDni(string _dni) { dni = _dni; }
	void setNombres(string _nombres) { nombres = _nombres; }
	void setApellidos(string _apellidos) { apellidos = _apellidos; }
	void setTelefono(string _telefono) { telefono = _telefono; }
	void setDireccion(string _direccion) { direccion = _direccion; }

	// Metodo para mostrar datos
	void mostrarDatos() {
		cout << "DNI: " << dni << endl;
		cout << "Nombre: " << nombres << " " << apellidos << endl;
		cout << "Telefono: " << telefono << endl;
		cout << "Direccion: " << direccion << endl;
	}

	// Metodo para obtener nombre completo
	string getNombreCompleto() {
		return nombres + " " + apellidos;
	}

	// Operador de comparacion para ordenamiento (compara por DNI)
	bool operator<(const Cliente& otro) const {
		return dni < otro.dni;
	}

	bool operator>(const Cliente& otro) const {
		return dni > otro.dni;
	}
};
