#pragma once
#include <string>
#include <iostream>

using namespace std;

class Venta {
private:
	string idVenta;
	string fecha;
	string dniCliente;
	string nombreCliente;
	string codigoProducto;
	string nombreProducto;
	int cantidad;
	double precioUnitario;
	double montoTotal;

public:
	// Constructor por defecto
	Venta() {
		idVenta = "";
		fecha = "";
		dniCliente = "";
		nombreCliente = "";
		codigoProducto = "";
		nombreProducto = "";
		cantidad = 0;
		precioUnitario = 0.0;
		montoTotal = 0.0;
	}

	// Constructor con parametros
	Venta(string _id, string _fecha, string _dniCliente, string _nombreCliente,
		string _codigoProducto, string _nombreProducto, int _cantidad, double _precioUnit) {
		idVenta = _id;
		fecha = _fecha;
		dniCliente = _dniCliente;
		nombreCliente = _nombreCliente;
		codigoProducto = _codigoProducto;
		nombreProducto = _nombreProducto;
		cantidad = _cantidad;
		precioUnitario = _precioUnit;
		montoTotal = _cantidad * _precioUnit;
	}

	// Getters
	string getIdVenta() { return idVenta; }
	string getFecha() { return fecha; }
	string getDniCliente() { return dniCliente; }
	string getNombreCliente() { return nombreCliente; }
	string getCodigoProducto() { return codigoProducto; }
	string getNombreProducto() { return nombreProducto; }
	int getCantidad() { return cantidad; }
	double getPrecioUnitario() { return precioUnitario; }
	double getMontoTotal() { return montoTotal; }

	// Setters
	void setIdVenta(string _id) { idVenta = _id; }
	void setFecha(string _fecha) { fecha = _fecha; }
	void setDniCliente(string _dni) { dniCliente = _dni; }
	void setNombreCliente(string _nombre) { nombreCliente = _nombre; }
	void setCodigoProducto(string _codigo) { codigoProducto = _codigo; }
	void setNombreProducto(string _nombre) { nombreProducto = _nombre; }
	void setCantidad(int _cant) {
		cantidad = _cant;
		montoTotal = cantidad * precioUnitario;
	}
	void setPrecioUnitario(double _precio) {
		precioUnitario = _precio;
		montoTotal = cantidad * precioUnitario;
	}

	// Metodo para mostrar venta
	void mostrarVenta() {
		cout << "========================================" << endl;
		cout << "ID Venta: " << idVenta << endl;
		cout << "Fecha: " << fecha << endl;
		cout << "Cliente: " << nombreCliente << " (DNI: " << dniCliente << ")" << endl;
		cout << "Producto: " << nombreProducto << " (Cod: " << codigoProducto << ")" << endl;
		cout << "Cantidad: " << cantidad << endl;
		cout << "Precio Unitario: S/. " << precioUnitario << endl;
		cout << "Monto Total: S/. " << montoTotal << endl;
		cout << "========================================" << endl;
	}

	// Metodo para calcular el total
	double calcularTotal() {
		montoTotal = cantidad * precioUnitario;
		return montoTotal;
	}

	// Operador de comparacion para ordenamiento (compara por ID)
	bool operator<(const Venta& otra) const {
		return idVenta < otra.idVenta;
	}

	bool operator>(const Venta& otra) const {
		return idVenta > otra.idVenta;
	}
};
