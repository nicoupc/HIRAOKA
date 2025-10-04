#pragma once

#include "Lista.h"
#include "Pila.h"
#include "Cola.h"
#include "Electrodomestico.h"
#include "Cliente.h"
#include "Venta.h"
#include "ItemCarrito.h"

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

    // Usuarios y login
    bool esAdmin;          // true si el que inicio sesion es admin
    string usuarioActual;  // guarda el username del login
	string dniClienteActual; // DNI del cliente logueado (si es cliente)
	bool modoInvitado;     // true si el cliente esta navegando sin cuenta

    void cargarUsuarios(); // lee usuarios.txt
    bool loginAdmin();     // login solo para admin
	void menuInicial();    // menu principal de entrada

	// Estructuras de datos principales - LAS 3 REQUERIDAS
	Lista<Electrodomestico*> inventario;      // LISTA: Para productos
	Pila<Cliente*> registroClientes;          // PILA: Para clientes (LIFO)
	Cola<Venta*> colaDeVentas;                // COLA: Para ventas (FIFO)

	// Carrito temporal para el cliente actual (solo mientras compra)
	Lista<ItemCarrito*> carritoActual;

	int contadorVentas;

	// ========== METODOS PARA LIMPIAR PANTALLA Y PAUSAR ==========
	void limpiarPantalla();
	void pausa();

	// ========== METODO PARA OBTENER FECHA ACTUAL ==========
	string obtenerFechaActual();

	// ========== MENU PRINCIPAL ==========
	void mostrarMenuPrincipal();
	void mostrarMenuCliente();

	// ========== GESTION DE INVENTARIO (LISTA) ==========
	void menuGestionInventario();
	void registrarProducto();
	void verTodosLosProductos();
	void buscarProducto();
	void modificarProducto();
	void eliminarProducto();

	// ========== GESTION DE CLIENTES (PILA) ==========
	void menuGestionClientes();
	void registrarCliente();
	void verTodosLosClientes();
	void buscarCliente();
	void verUltimoCliente();

	// ========== GESTION DE VENTAS (COLA FIFO) ==========
	void menuGestionVentas();
	void verVentasPendientes();
	void procesarSiguienteVenta();
	void verPrimeraVenta();

	// ========== FUNCIONES PARA CLIENTES ==========
	void verCatalogoProductos();
	void agregarAlCarrito();
	void verCarrito();
	void modificarCarrito();
	void finalizarCompra();
	void miCuenta();
	void registrarMiCuenta();
	void registrarseAhora();
	void iniciarSesionCliente();

	// ========== PERSISTENCIA DE DATOS ==========
	void guardarDatos();
	void guardarInventario();
	void guardarClientes();
	void cargarDatos();
	void cargarInventario();
	void cargarClientes();

public:
	// Constructor
	SistemaGestionHiraoka();

	// Destructor
	~SistemaGestionHiraoka();

	// Metodo principal
	void iniciar();
};
