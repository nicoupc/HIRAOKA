#pragma once

#include "Lista.h"
#include "Pila.h"
#include "Cola.h"
#include "Electrodomestico.h"
#include "Cliente.h"
#include "Venta.h"

#include <iostream>
#include <string>
#include <limits>
#include <functional>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

class SistemaGestionHiraoka {
private:
	// Estructuras de datos principales
	Lista<Electrodomestico*> inventario;
	Pila<Cliente*> registroClientes;
	Cola<Venta*> colaDeVentas;

	int contadorVentas;

	// ========== METODOS PARA LIMPIAR PANTALLA Y PAUSAR ==========
	void limpiarPantalla() {
		system("cls");
	}

	void pausa() {
		cout << "\nPresione Enter para continuar...";
		cin.ignore();
		cin.get();
	}

	// ========== METODO PARA OBTENER FECHA ACTUAL ==========
	string obtenerFechaActual() {
		time_t ahora = time(0);
		tm tiempoLocal; localtime_s(&tiempoLocal, &ahora);
		stringstream ss;
		ss << setfill('0') << setw(2) << tiempoLocal.tm_mday << "/"
			<< setw(2) << (tiempoLocal.tm_mon + 1) << "/"
			<< (tiempoLocal.tm_year + 1900);
		return ss.str();
	}

	// ========== MENU PRINCIPAL ==========
	void mostrarMenuPrincipal() {
		limpiarPantalla();
		cout << "========================================" << endl;
		cout << "    SISTEMA DE GESTION HIRAOKA          " << endl;
		cout << "========================================" << endl;
		cout << "  1. Gestion de Inventario              " << endl;
		cout << "  2. Gestion de Clientes                " << endl;
		cout << "  3. Gestion de Ventas                  " << endl;
		cout << "  4. Reportes y Estadisticas            " << endl;
		cout << "  5. Guardar Datos                      " << endl;
		cout << "  0. Salir                              " << endl;
		cout << "========================================" << endl;
		cout << "Seleccione una opcion: ";
	}

	// ========== GESTION DE INVENTARIO ==========
	void menuGestionInventario() {
		int opcion;
		do {
			limpiarPantalla();
			cout << "\n========== GESTION DE INVENTARIO ==========" << endl;
			cout << "1. Registrar nuevo producto" << endl;
			cout << "2. Listar todos los productos" << endl;
			cout << "3. Buscar producto por codigo" << endl;
			cout << "4. Buscar productos por marca" << endl;
			cout << "5. Ordenar productos por precio" << endl;
			cout << "6. Eliminar producto" << endl;
			cout << "0. Volver al menu principal" << endl;
			cout << "Seleccione una opcion: ";
			cin >> opcion;

			switch (opcion) {
			case 1: registrarProducto(); break;
			case 2: listarProductos(); break;
			case 3: buscarProductoPorCodigo(); break;
			case 4: buscarProductosPorMarca(); break;
			case 5: ordenarProductosPorPrecio(); break;
			case 6: eliminarProducto(); break;
			case 0: break;
			default: cout << "Opcion invalida." << endl; pausa(); break;
			}
		} while (opcion != 0);
	}

	void registrarProducto() {
		limpiarPantalla();
		cout << "\n--- Registrar Nuevo Producto ---" << endl;

		string codigo, nombre, marca, modelo;
		double precio;
		int anio, stock;

		cout << "Codigo: "; cin >> codigo;
		cin.ignore();
		cout << "Nombre: "; getline(cin, nombre);
		cout << "Marca: "; getline(cin, marca);
		cout << "Modelo: "; getline(cin, modelo);
		cout << "Precio: "; cin >> precio;
		cout << "Anio de fabricacion: "; cin >> anio;
		cout << "Stock inicial: "; cin >> stock;

		Electrodomestico* nuevo = new Electrodomestico(codigo, nombre, marca, modelo, precio, anio, stock);
		inventario.agregarFinal(nuevo);

		cout << "\nProducto registrado exitosamente!" << endl;
		pausa();
	}

	void listarProductos() {
		limpiarPantalla();
		cout << "\n========== LISTA DE PRODUCTOS ==========" << endl;

		if (inventario.estaVacia()) {
			cout << "No hay productos registrados." << endl;
		}
		else {
			cout << "\nTotal de productos: " << inventario.longitud() << endl;
			cout << "----------------------------------------" << endl;

			// Usando lambda para recorrer
			inventario.recorrer([](Electrodomestico* prod) {
				prod->mostrarDetalles();
				cout << "----------------------------------------" << endl;
				});
		}
		pausa();
	}

	void buscarProductoPorCodigo() {
		limpiarPantalla();
		cout << "\n--- Buscar Producto por Codigo ---" << endl;

		string codigo;
		cout << "Ingrese el codigo del producto: ";
		cin >> codigo;

		// Usando lambda para buscar recursivamente
		Electrodomestico* encontrado = inventario.buscarRecursivo(
			[codigo](Electrodomestico* prod) {
				return prod->getCodigo() == codigo;
			}
		);

		if (encontrado != nullptr) {
			cout << "\nProducto encontrado!" << endl;
			cout << "----------------------------------------" << endl;
			encontrado->mostrarDetalles();
		}
		else {
			cout << "\nProducto no encontrado." << endl;
		}
		pausa();
	}

	void buscarProductosPorMarca() {
		limpiarPantalla();
		cout << "\n--- Buscar Productos por Marca ---" << endl;

		string marca;
		cout << "Ingrese la marca: ";
		cin.ignore();
		getline(cin, marca);

		// Usando lambda para filtrar
		Lista<Electrodomestico*>* filtrados = inventario.filtrar(
			[marca](Electrodomestico* prod) {
				return prod->getMarca() == marca;
			}
		);

		if (filtrados->estaVacia()) {
			cout << "\nNo se encontraron productos de esa marca." << endl;
		}
		else {
			cout << "\nProductos encontrados: " << filtrados->longitud() << endl;
			cout << "----------------------------------------" << endl;
			filtrados->recorrer([](Electrodomestico* prod) {
				prod->mostrarDetalles();
				cout << "----------------------------------------" << endl;
				});
		}

		delete filtrados;
		pausa();
	}

	void ordenarProductosPorPrecio() {
		limpiarPantalla();
		cout << "\n--- Ordenar Productos por Precio ---" << endl;
		cout << "1. Menor a mayor" << endl;
		cout << "2. Mayor a menor" << endl;
		cout << "Seleccione: ";
		int opcion;
		cin >> opcion;

		if (opcion == 1) {
			// Ordenar de menor a mayor
			inventario.ordenarBurbuja([](Electrodomestico* a, Electrodomestico* b) {
				return a->getPrecio() < b->getPrecio();
				});
			cout << "\nProductos ordenados de menor a mayor precio!" << endl;
		}
		else if (opcion == 2) {
			// Ordenar de mayor a menor
			inventario.ordenarBurbuja([](Electrodomestico* a, Electrodomestico* b) {
				return a->getPrecio() > b->getPrecio();
				});
			cout << "\nProductos ordenados de mayor a menor precio!" << endl;
		}

		pausa();
	}

	void eliminarProducto() {
		limpiarPantalla();
		cout << "\n--- Eliminar Producto ---" << endl;

		string codigo;
		cout << "Ingrese el codigo del producto a eliminar: ";
		cin >> codigo;

		int posicion = -1;
		for (int i = 0; i < inventario.longitud(); i++) {
			if (inventario.obtenerPosicion(i)->getCodigo() == codigo) {
				posicion = i;
				break;
			}
		}

		if (posicion != -1) {
			Electrodomestico* prod = inventario.obtenerPosicion(posicion);
			cout << "\nProducto a eliminar:" << endl;
			prod->mostrarDetalles();
			cout << "\n¿Esta seguro? (S/N): ";
			char confirmar;
			cin >> confirmar;
			if (confirmar == 'S' || confirmar == 's') {
				delete prod;
				inventario.eliminarPosicion(posicion);
				cout << "\nProducto eliminado exitosamente!" << endl;
			}
		}
		else {
			cout << "\nProducto no encontrado." << endl;
		}
		pausa();
	}

	// ========== GESTION DE CLIENTES ==========
	void menuGestionClientes() {
		int opcion;
		do {
			limpiarPantalla();
			cout << "\n========== GESTION DE CLIENTES ==========" << endl;
			cout << "1. Registrar nuevo cliente" << endl;
			cout << "2. Ver ultimo cliente registrado" << endl;
			cout << "3. Listar todos los clientes" << endl;
			cout << "4. Buscar cliente por DNI" << endl;
			cout << "5. Contar clientes registrados" << endl;
			cout << "0. Volver al menu principal" << endl;
			cout << "Seleccione una opcion: ";
			cin >> opcion;

			switch (opcion) {
			case 1: registrarCliente(); break;
			case 2: verUltimoCliente(); break;
			case 3: listarClientes(); break;
			case 4: buscarClientePorDNI(); break;
			case 5: contarClientes(); break;
			case 0: break;
			default: cout << "Opcion invalida." << endl; pausa(); break;
			}
		} while (opcion != 0);
	}

	void registrarCliente() {
		limpiarPantalla();
		cout << "\n--- Registrar Nuevo Cliente ---" << endl;

		string dni, nombres, apellidos, telefono, direccion;

		cout << "DNI: "; cin >> dni;
		cin.ignore();
		cout << "Nombres: "; getline(cin, nombres);
		cout << "Apellidos: "; getline(cin, apellidos);
		cout << "Telefono: "; getline(cin, telefono);
		cout << "Direccion: "; getline(cin, direccion);

		Cliente* nuevo = new Cliente(dni, nombres, apellidos, telefono, direccion);
		registroClientes.apilar(nuevo);

		cout << "\nCliente registrado exitosamente!" << endl;
		pausa();
	}

	void verUltimoCliente() {
		limpiarPantalla();
		cout << "\n--- Ultimo Cliente Registrado ---" << endl;

		if (registroClientes.estaVacia()) {
			cout << "No hay clientes registrados." << endl;
		}
		else {
			Cliente* ultimo = registroClientes.verCima();
			cout << "----------------------------------------" << endl;
			ultimo->mostrarDatos();
			cout << "----------------------------------------" << endl;
		}
		pausa();
	}

	void listarClientes() {
		limpiarPantalla();
		cout << "\n========== LISTA DE CLIENTES ==========" << endl;

		if (registroClientes.estaVacia()) {
			cout << "No hay clientes registrados." << endl;
		}
		else {
			cout << "\nTotal de clientes: " << registroClientes.getTamanio() << endl;
			cout << "----------------------------------------" << endl;

			// Usando metodo recursivo
			registroClientes.imprimirRecursivo([](Cliente* cli) {
				cli->mostrarDatos();
				cout << "----------------------------------------" << endl;
				});
		}
		pausa();
	}

	void buscarClientePorDNI() {
		limpiarPantalla();
		cout << "\n--- Buscar Cliente por DNI ---" << endl;

		string dni;
		cout << "Ingrese el DNI: ";
		cin >> dni;

		// Usando lambda para buscar
		Cliente* encontrado = registroClientes.buscar([dni](Cliente* cli) {
			return cli->getDni() == dni;
			});

		if (encontrado != nullptr) {
			cout << "\nCliente encontrado!" << endl;
			cout << "----------------------------------------" << endl;
			encontrado->mostrarDatos();
			cout << "----------------------------------------" << endl;
		}
		else {
			cout << "\nCliente no encontrado." << endl;
		}
		pausa();
	}

	void contarClientes() {
		limpiarPantalla();
		cout << "\n--- Estadisticas de Clientes ---" << endl;
		cout << "Total de clientes registrados: " << registroClientes.getTamanio() << endl;
		pausa();
	}

	// ========== GESTION DE VENTAS ==========
	void menuGestionVentas() {
		int opcion;
		do {
			limpiarPantalla();
			cout << "\n========== GESTION DE VENTAS ==========" << endl;
			cout << "1. Registrar nueva venta" << endl;
			cout << "2. Procesar siguiente venta" << endl;
			cout << "3. Ver siguiente venta en cola" << endl;
			cout << "4. Listar todas las ventas" << endl;
			cout << "5. Contar ventas en cola" << endl;
			cout << "0. Volver al menu principal" << endl;
			cout << "Seleccione una opcion: ";
			cin >> opcion;

			switch (opcion) {
			case 1: registrarVenta(); break;
			case 2: procesarVenta(); break;
			case 3: verSiguienteVenta(); break;
			case 4: listarVentas(); break;
			case 5: contarVentas(); break;
			case 0: break;
			default: cout << "Opcion invalida." << endl; pausa(); break;
			}
		} while (opcion != 0);
	}

	void registrarVenta() {
		limpiarPantalla();
		cout << "\n--- Registrar Nueva Venta ---" << endl;

		if (inventario.estaVacia()) {
			cout << "No hay productos en el inventario." << endl;
			pausa();
			return;
		}

		if (registroClientes.estaVacia()) {
			cout << "No hay clientes registrados." << endl;
			pausa();
			return;
		}

		string dniCliente, codigoProducto;
		int cantidad;

		cout << "DNI del cliente: "; cin >> dniCliente;

		Cliente* cliente = registroClientes.buscar([dniCliente](Cliente* cli) {
			return cli->getDni() == dniCliente;
			});

		if (cliente == nullptr) {
			cout << "\nCliente no encontrado." << endl;
			pausa();
			return;
		}

		cout << "Codigo del producto: "; cin >> codigoProducto;

		Electrodomestico* producto = inventario.buscarRecursivo(
			[codigoProducto](Electrodomestico* prod) {
				return prod->getCodigo() == codigoProducto;
			}
		);

		if (producto == nullptr) {
			cout << "\nProducto no encontrado." << endl;
			pausa();
			return;
		}

		cout << "Cantidad: "; cin >> cantidad;

		if (producto->getStock() < cantidad) {
			cout << "\nStock insuficiente. Stock disponible: " << producto->getStock() << endl;
			pausa();
			return;
		}

		// Crear venta
		contadorVentas++;
		string idVenta = "V" + to_string(contadorVentas);
		string fecha = obtenerFechaActual();

		Venta* nuevaVenta = new Venta(
			idVenta,
			fecha,
			cliente->getDni(),
			cliente->getNombreCompleto(),
			producto->getCodigo(),
			producto->getNombre(),
			cantidad,
			producto->getPrecio()
		);

		// Reducir stock
		producto->reducirStock(cantidad);

		// Agregar a la cola
		colaDeVentas.encolar(nuevaVenta);

		cout << "\nVenta registrada exitosamente!" << endl;
		cout << "ID de venta: " << idVenta << endl;
		cout << "Total: S/. " << nuevaVenta->getMontoTotal() << endl;
		pausa();
	}

	void procesarVenta() {
		limpiarPantalla();
		cout << "\n--- Procesar Venta ---" << endl;

		if (colaDeVentas.esVacia()) {
			cout << "No hay ventas pendientes de procesar." << endl;
			pausa();
			return;
		}

		Venta* venta = colaDeVentas.desencolar();
		cout << "\nVenta procesada:" << endl;
		venta->mostrarVenta();

		delete venta;
		pausa();
	}

	void verSiguienteVenta() {
		limpiarPantalla();
		cout << "\n--- Siguiente Venta en Cola ---" << endl;

		if (colaDeVentas.esVacia()) {
			cout << "No hay ventas pendientes." << endl;
		}
		else {
			Venta* siguiente = colaDeVentas.verPrimero();
			siguiente->mostrarVenta();
		}
		pausa();
	}

	void listarVentas() {
		limpiarPantalla();
		cout << "\n========== LISTA DE VENTAS PENDIENTES ==========" << endl;

		if (colaDeVentas.esVacia()) {
			cout << "No hay ventas pendientes." << endl;
		}
		else {
			cout << "\nTotal de ventas en cola: " << colaDeVentas.getTamanio() << endl;
			cout << "----------------------------------------" << endl;

			// Usando metodo recursivo
			colaDeVentas.imprimirRecursivo([](Venta* venta) {
				venta->mostrarVenta();
				});
		}
		pausa();
	}

	void contarVentas() {
		limpiarPantalla();
		cout << "\n--- Estadisticas de Ventas ---" << endl;
		cout << "Ventas pendientes en cola: " << colaDeVentas.getTamanio() << endl;
		pausa();
	}

	// ========== REPORTES Y ESTADISTICAS ==========
	void menuReportes() {
		int opcion;
		do {
			limpiarPantalla();
			cout << "\n========== REPORTES Y ESTADISTICAS ==========" << endl;
			cout << "1. Productos con bajo stock" << endl;
			cout << "2. Total de productos en inventario" << endl;
			cout << "3. Total de clientes registrados" << endl;
			cout << "4. Total de ventas pendientes" << endl;
			cout << "0. Volver al menu principal" << endl;
			cout << "Seleccione una opcion: ";
			cin >> opcion;

			switch (opcion) {
			case 1: reporteBajoStock(); break;
			case 2: reporteTotalProductos(); break;
			case 3: reporteTotalClientes(); break;
			case 4: reporteVentasPendientes(); break;
			case 0: break;
			default: cout << "Opcion invalida." << endl; pausa(); break;
			}
		} while (opcion != 0);
	}

	void reporteBajoStock() {
		limpiarPantalla();
		cout << "\n--- Productos con Bajo Stock ---" << endl;
		cout << "Ingrese el stock minimo: ";
		int stockMinimo;
		cin >> stockMinimo;

		// Usando lambda para contar
		int cantidad = inventario.contar([stockMinimo](Electrodomestico* prod) {
			return prod->getStock() <= stockMinimo;
			});

		cout << "\nProductos con stock menor o igual a " << stockMinimo << ": " << cantidad << endl;

		if (cantidad > 0) {
			cout << "----------------------------------------" << endl;
			inventario.recorrer([stockMinimo](Electrodomestico* prod) {
				if (prod->getStock() <= stockMinimo) {
					prod->mostrarDetalles();
					cout << "----------------------------------------" << endl;
				}
				});
		}
		pausa();
	}

	void reporteTotalProductos() {
		limpiarPantalla();
		cout << "\n--- Reporte de Inventario ---" << endl;
		cout << "Total de productos: " << inventario.longitud() << endl;

		double valorTotal = 0;
		inventario.recorrer([&valorTotal](Electrodomestico* prod) {
			valorTotal += prod->getPrecio() * prod->getStock();
			});

		cout << "Valor total del inventario: S/. " << valorTotal << endl;
		pausa();
	}

	void reporteTotalClientes() {
		limpiarPantalla();
		cout << "\n--- Reporte de Clientes ---" << endl;
		cout << "Total de clientes registrados: " << registroClientes.getTamanio() << endl;
		pausa();
	}

	void reporteVentasPendientes() {
		limpiarPantalla();
		cout << "\n--- Reporte de Ventas ---" << endl;
		cout << "Ventas pendientes de procesar: " << colaDeVentas.getTamanio() << endl;

		double montoTotal = 0;
		colaDeVentas.recorrer([&montoTotal](Venta* venta) {
			montoTotal += venta->getMontoTotal();
			});

		cout << "Monto total de ventas pendientes: S/. " << montoTotal << endl;
		pausa();
	}

	// ========== PERSISTENCIA DE DATOS ==========
	void guardarDatos() {
		guardarInventario();
		guardarClientes();
		cout << "\nDatos guardados exitosamente!" << endl;
	}

	void guardarInventario() {
		ofstream archivo("inventario.txt");
		if (archivo.is_open()) {
			inventario.recorrer([&archivo](Electrodomestico* prod) {
				archivo << prod->getCodigo() << "|"
					<< prod->getNombre() << "|"
					<< prod->getMarca() << "|"
					<< prod->getModelo() << "|"
					<< prod->getPrecio() << "|"
					<< prod->getAnioFabricacion() << "|"
					<< prod->getStock() << endl;
				});
			archivo.close();
		}
	}

	void guardarClientes() {
		ofstream archivo("clientes.txt");
		if (archivo.is_open()) {
			registroClientes.recorrer([&archivo](Cliente* cli) {
				archivo << cli->getDni() << "|"
					<< cli->getNombres() << "|"
					<< cli->getApellidos() << "|"
					<< cli->getTelefono() << "|"
					<< cli->getDireccion() << endl;
				});
			archivo.close();
		}
	}

	void cargarDatos() {
		cargarInventario();
		cargarClientes();
	}

	void cargarInventario() {
		ifstream archivo("inventario.txt");
		if (archivo.is_open()) {
			string linea;
			while (getline(archivo, linea)) {
				stringstream ss(linea);
				string codigo, nombre, marca, modelo, precioStr, anioStr, stockStr;

				getline(ss, codigo, '|');
				getline(ss, nombre, '|');
				getline(ss, marca, '|');
				getline(ss, modelo, '|');
				getline(ss, precioStr, '|');
				getline(ss, anioStr, '|');
				getline(ss, stockStr, '|');

				double precio = stod(precioStr);
				int anio = stoi(anioStr);
				int stock = stoi(stockStr);

				Electrodomestico* prod = new Electrodomestico(codigo, nombre, marca, modelo, precio, anio, stock);
				inventario.agregarFinal(prod);
			}
			archivo.close();
		}
	}

	void cargarClientes() {
		ifstream archivo("clientes.txt");
		if (archivo.is_open()) {
			string linea;
			while (getline(archivo, linea)) {
				stringstream ss(linea);
				string dni, nombres, apellidos, telefono, direccion;

				getline(ss, dni, '|');
				getline(ss, nombres, '|');
				getline(ss, apellidos, '|');
				getline(ss, telefono, '|');
				getline(ss, direccion, '|');

				Cliente* cli = new Cliente(dni, nombres, apellidos, telefono, direccion);
				registroClientes.apilar(cli);
			}
			archivo.close();
		}
	}

public:
	// Constructor
	SistemaGestionHiraoka() {
		contadorVentas = 0;
		cout << "Iniciando Sistema de Gestion Hiraoka..." << endl;
		cargarDatos();
		cout << "Datos cargados correctamente." << endl;
	}

	// Destructor
	~SistemaGestionHiraoka() {
		cout << "Cerrando sistema y liberando memoria..." << endl;

		// Liberar memoria del inventario
		while (!inventario.estaVacia()) {
			Electrodomestico* prod = inventario.obtenerPosicion(0);
			delete prod;
			inventario.eliminarInicio();
		}

		// Liberar memoria de clientes
		while (!registroClientes.estaVacia()) {
			delete registroClientes.desapilar();
		}

		// Liberar memoria de ventas
		while (!colaDeVentas.esVacia()) {
			delete colaDeVentas.desencolar();
		}
	}

	// Metodo principal
	void iniciar() {
		int opcion;
		do {
			mostrarMenuPrincipal();
			cin >> opcion;

			// Validar entrada
			while (cin.fail()) {
				cout << "Entrada invalida. Ingrese un numero." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				mostrarMenuPrincipal();
				cin >> opcion;
			}

			switch (opcion) {
			case 1: menuGestionInventario(); break;
			case 2: menuGestionClientes(); break;
			case 3: menuGestionVentas(); break;
			case 4: menuReportes(); break;
			case 5: guardarDatos(); pausa(); break;
			case 0:
				guardarDatos();
				cout << "\nGracias por usar el sistema. Hasta pronto!" << endl;
				break;
			default:
				cout << "Opcion no valida. Intente de nuevo." << endl;
				pausa();
				break;
			}
		} while (opcion != 0);
	}
};
