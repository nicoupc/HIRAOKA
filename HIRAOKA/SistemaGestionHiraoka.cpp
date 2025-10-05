#include "SistemaGestionHiraoka.h"

// ========== FUNCION AUXILIAR SIMPLE ==========
// Funcion para dividir un texto por un separador
// Ejemplo: dividirTexto("Juan|25|Lima", '|', 0) = "Juan"
string SistemaGestionHiraoka::dividirTexto(string texto, char separador, int posicion) {
	string resultado = "";
	int posActual = 0;
	
	for (int i = 0; i < texto.length(); i++) {
		if (texto[i] == separador) {
			if (posActual == posicion) return resultado;
			posActual++;
			resultado = "";
		}
		else if (texto[i] != '\r' && texto[i] != '\n') {  // Ignorar saltos de linea
			resultado += texto[i];
		}
	}
	
	if (posActual == posicion) return resultado;
	return "";
}

void SistemaGestionHiraoka::cargarUsuarios() {
    ifstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            string usuario = dividirTexto(linea, '|', 0);
            string password = dividirTexto(linea, '|', 1);
            string tipo = dividirTexto(linea, '|', 2);
        }
        archivo.close();
    }
}

bool SistemaGestionHiraoka::loginAdmin() {
	limpiarPantalla();
	string user, pass;
	cout << "\n========================================" << endl;
	cout << "    LOGIN ADMINISTRADOR                 " << endl;
	cout << "========================================" << endl;
	cout << "Usuario: "; 
	cin >> user;
	cout << "Password: "; 
	cin >> pass;

	ifstream archivo("usuarios.txt");
	if (archivo.is_open()) {
		string linea;
		while (getline(archivo, linea)) {
			string usuario = dividirTexto(linea, '|', 0);
			string password = dividirTexto(linea, '|', 1);
			string tipo = dividirTexto(linea, '|', 2);

			if (usuario == user && password == pass && tipo == "admin") {
				usuarioActual = usuario;
				esAdmin = true;
				cout << "\nBienvenido Administrador " << usuarioActual << "!" << endl;
				archivo.close();
				pausa();
				return true;
			}
		}
		archivo.close();
	} else {
		cout << "\nNo se pudo abrir el archivo usuarios.txt" << endl;
	}

	cout << "\nCredenciales incorrectas o no es administrador." << endl;
	pausa();
	return false;
}

void SistemaGestionHiraoka::menuInicial() {
	limpiarPantalla();
	cout << "\n========================================" << endl;
	cout << "    BIENVENIDO A TIENDA HIRAOKA         " << endl;
	cout << "========================================" << endl;
	cout << "  Como deseas ingresar?" << endl;
	cout << "========================================" << endl;
	cout << "  1. Entrar como Cliente               " << endl;
	cout << "  2. Entrar como Administrador         " << endl;
	cout << "  0. Salir                             " << endl;
	cout << "========================================" << endl;
	cout << "\nSeleccione una opcion: ";
}


// ========== METODOS PARA LIMPIAR PANTALLA Y PAUSAR ==========
void SistemaGestionHiraoka::limpiarPantalla() {
	system("cls");
}

void SistemaGestionHiraoka::pausa() {
	cout << "\nPresione Enter para continuar...";
	cin.ignore();
	cin.get();
}

// ========== METODO PARA OBTENER FECHA ACTUAL ==========
string SistemaGestionHiraoka::obtenerFechaActual() {
	time_t ahora = time(0);
	tm tiempoLocal;
	localtime_s(&tiempoLocal, &ahora);
	
	// Usar strftime para formatear la fecha - SIMPLE Y FACIL
	char buffer[20];
	strftime(buffer, 20, "%d/%m/%Y", &tiempoLocal);
	return string(buffer);
}

// ========== MENU PRINCIPAL ==========
void SistemaGestionHiraoka::mostrarMenuPrincipal() {
	limpiarPantalla();
	cout << "========================================" << endl;
	cout << "    SISTEMA DE GESTION HIRAOKA          " << endl;
	cout << "    Usuario: " << usuarioActual << " (Admin)" << endl;
	cout << "========================================" << endl;
	cout << "  1. Gestion de Productos (LISTA)       " << endl;
	cout << "  2. Gestion de Clientes (PILA)         " << endl;
	cout << "  3. Gestion de Ventas (COLA)           " << endl;
	cout << "  0. Salir                              " << endl;
	cout << "========================================" << endl;
	cout << "Seleccione una opcion: ";
}

void SistemaGestionHiraoka::mostrarMenuCliente() {
	limpiarPantalla();
	cout << "========================================" << endl;
	cout << "    TIENDA HIRAOKA - BIENVENIDO        " << endl;
	
	// Mostrar estado del usuario
	if (dniClienteActual.empty()) {
		cout << "    Modo: Invitado                     " << endl;
	} else {
		// Buscar nombre del cliente (estilo del profesor)
		Cliente* cliente = nullptr;
		for (int i = 0; i < registroClientes.getTamanio(); i++) {
			Cliente* cli = registroClientes.obtenerEnPosicion(i);
			if (cli->getDni() == dniClienteActual) {
				cliente = cli;
				break;
			}
		}
		if (cliente != nullptr) {
			cout << "    Cliente: " << cliente->getNombres() << endl;
		}
	}
	
	cout << "========================================" << endl;
	cout << "  1. Ver Catalogo de Productos         " << endl;
	cout << "  2. Agregar al Carrito                " << endl;
	cout << "  3. Ver mi Carrito                    " << endl;
	cout << "  4. Finalizar Compra                  " << endl;
	cout << "  ----------------------------------------" << endl;
	
	// Opciones según si tiene cuenta o no
	if (dniClienteActual.empty()) {
		cout << "  5. Iniciar Sesion                    " << endl;
		cout << "  6. Registrarme                       " << endl;
	} else {
		cout << "  5. Mi Cuenta                         " << endl;
	}
	
	cout << "  0. Salir                             " << endl;
	cout << "========================================" << endl;
	
	// Mostrar info del carrito si tiene items
	if (!carritoActual.estaVacia()) {
		cout << "\n>> Tienes " << carritoActual.longitud() << " producto(s) en tu carrito" << endl;
	}
	
	cout << "\nSeleccione una opcion: ";
}

// ========== GESTION DE INVENTARIO (LISTA) ==========
void SistemaGestionHiraoka::menuGestionInventario() {
	int opcion;
	do {
		limpiarPantalla();
		cout << "\n========================================" << endl;
		cout << "    GESTION DE PRODUCTOS (LISTA)        " << endl;
		cout << "========================================" << endl;
		cout << "  1. Registrar producto                 " << endl;
		cout << "  2. Ver todos los productos            " << endl;
		cout << "  3. Buscar producto                    " << endl;
		cout << "  4. Modificar producto                 " << endl;
		cout << "  5. Eliminar producto                  " << endl;
		cout << "  6. Ordenar productos (Burbuja)        " << endl;
		cout << "  7. Ver estadisticas (con Lambda)      " << endl;
		cout << "  0. Volver                             " << endl;
		cout << "========================================" << endl;
		cout << "Seleccione una opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1: registrarProducto(); break;
		case 2: verTodosLosProductos(); break;
		case 3: buscarProducto(); break;
		case 4: modificarProducto(); break;
		case 5: eliminarProducto(); break;
		case 6: ordenarProductos(); break;
		case 7: verEstadisticasProductos(); break;
		case 0: break;
		default: cout << "Opcion invalida." << endl; pausa(); break;
		}
	} while (opcion != 0);
}

void SistemaGestionHiraoka::registrarProducto() {
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

// Ver todos los productos (simple)
void SistemaGestionHiraoka::verTodosLosProductos() {
	limpiarPantalla();
	cout << "\n========== LISTA DE PRODUCTOS ==========" << endl;

	if (inventario.estaVacia()) {
		cout << "\nNo hay productos registrados." << endl;
		pausa();
		return;
	}

	cout << "\nTotal: " << inventario.longitud() << " productos" << endl;
	cout << "----------------------------------------" << endl;

	// Mostrar todos (estilo del profesor - bucle for)
	for (int i = 0; i < inventario.longitud(); i++) {
		Electrodomestico* prod = inventario.obtenerPosicion(i);
		cout << "\n[" << prod->getCodigo() << "] " << prod->getNombre() << endl;
		cout << "  Marca: " << prod->getMarca() << " | Modelo: " << prod->getModelo() << endl;
		cout << "  Precio: S/. " << fixed << setprecision(2) << prod->getPrecio() << endl;
		cout << "  Stock: " << prod->getStock() << " unidades" << endl;
	}

	cout << "----------------------------------------" << endl;
	pausa();
}

// Buscar producto (simple - por código)
void SistemaGestionHiraoka::buscarProducto() {
	limpiarPantalla();
	cout << "\n======== BUSCAR PRODUCTO ========" << endl;

	if (inventario.estaVacia()) {
		cout << "\nNo hay productos para buscar." << endl;
		pausa();
		return;
	}

	string codigo;
	cout << "\nIngrese el codigo del producto: ";
	cin >> codigo;

	// Buscar producto (estilo del profesor - bucle for)
	Electrodomestico* encontrado = nullptr;
	for (int i = 0; i < inventario.longitud(); i++) {
		Electrodomestico* prod = inventario.obtenerPosicion(i);
		if (prod->getCodigo() == codigo) {
			encontrado = prod;
			break;
		}
	}

	if (encontrado != nullptr) {
		cout << "\n[OK] Producto encontrado!" << endl;
		cout << "----------------------------------------" << endl;
		cout << "Codigo: " << encontrado->getCodigo() << endl;
		cout << "Nombre: " << encontrado->getNombre() << endl;
		cout << "Marca: " << encontrado->getMarca() << endl;
		cout << "Modelo: " << encontrado->getModelo() << endl;
		cout << "Precio: S/. " << encontrado->getPrecio() << endl;
		cout << "Stock: " << encontrado->getStock() << " unidades" << endl;
		cout << "----------------------------------------" << endl;
	}
	else {
		cout << "\nProducto no encontrado." << endl;
	}
	pausa();
}

// Modificar producto (muestra lista primero y permite modificar cualquier campo)
void SistemaGestionHiraoka::modificarProducto() {
	limpiarPantalla();
	cout << "\n======== MODIFICAR PRODUCTO ========" << endl;

	if (inventario.estaVacia()) {
		cout << "\nNo hay productos para modificar." << endl;
		pausa();
		return;
	}

	// Mostrar lista primero (estilo del profesor)
	cout << "\nProductos disponibles:" << endl;
	cout << "----------------------------------------" << endl;
	for (int i = 0; i < inventario.longitud(); i++) {
		Electrodomestico* prod = inventario.obtenerPosicion(i);
		cout << "[" << prod->getCodigo() << "] " << prod->getNombre() 
			 << " - Precio: S/. " << fixed << setprecision(2) << prod->getPrecio()
			 << " - Stock: " << prod->getStock() << endl;
	}
	cout << "----------------------------------------" << endl;

	string codigo;
	cout << "\nIngrese el codigo del producto a modificar (0 para cancelar): ";
	cin >> codigo;

	if (codigo == "0") return;

	// Buscar el producto (estilo del profesor)
	Electrodomestico* producto = nullptr;
	for (int i = 0; i < inventario.longitud(); i++) {
		Electrodomestico* prod = inventario.obtenerPosicion(i);
		if (prod->getCodigo() == codigo) {
			producto = prod;
			break;
		}
	}

	if (producto == nullptr) {
		cout << "\nProducto no encontrado." << endl;
		pausa();
		return;
	}

	// Mostrar info actual
	cout << "\n--- Producto actual ---" << endl;
	cout << "Codigo: " << producto->getCodigo() << endl;
	cout << "Nombre: " << producto->getNombre() << endl;
	cout << "Marca: " << producto->getMarca() << endl;
	cout << "Modelo: " << producto->getModelo() << endl;
	cout << "Precio: S/. " << producto->getPrecio() << endl;
	cout << "Stock: " << producto->getStock() << endl;

	// Menu de modificacion
	cout << "\n¿Que deseas modificar?" << endl;
	cout << "1. Nombre" << endl;
	cout << "2. Marca" << endl;
	cout << "3. Modelo" << endl;
	cout << "4. Precio" << endl;
	cout << "5. Stock" << endl;
	cout << "0. Cancelar" << endl;
	cout << "\nOpcion: ";
	
	int opcion;
	cin >> opcion;
	cin.ignore(); // Limpiar buffer

	switch (opcion) {
	case 1: {
		string nuevoNombre;
		cout << "\nNuevo nombre: ";
		getline(cin, nuevoNombre);
		if (!nuevoNombre.empty()) {
			producto->setNombre(nuevoNombre);
			cout << "\n[OK] Nombre actualizado!" << endl;
		}
		break;
	}
	case 2: {
		string nuevaMarca;
		cout << "\nNueva marca: ";
		getline(cin, nuevaMarca);
		if (!nuevaMarca.empty()) {
			producto->setMarca(nuevaMarca);
			cout << "\n[OK] Marca actualizada!" << endl;
		}
		break;
	}
	case 3: {
		string nuevoModelo;
		cout << "\nNuevo modelo: ";
		getline(cin, nuevoModelo);
		if (!nuevoModelo.empty()) {
			producto->setModelo(nuevoModelo);
			cout << "\n[OK] Modelo actualizado!" << endl;
		}
		break;
	}
	case 4: {
		double nuevoPrecio;
		cout << "\nNuevo precio: ";
		cin >> nuevoPrecio;
		if (nuevoPrecio > 0) {
			producto->setPrecio(nuevoPrecio);
			cout << "\n[OK] Precio actualizado!" << endl;
		} else {
			cout << "\nPrecio invalido." << endl;
		}
		break;
	}
	case 5: {
		int nuevoStock;
		cout << "\nNuevo stock: ";
		cin >> nuevoStock;
		if (nuevoStock >= 0) {
			producto->setStock(nuevoStock);
			cout << "\n[OK] Stock actualizado!" << endl;
		} else {
			cout << "\nStock invalido." << endl;
		}
		break;
	}
	case 0:
		cout << "\nModificacion cancelada." << endl;
		break;
	default:
		cout << "\nOpcion invalida." << endl;
		break;
	}

	pausa();
}

// Eliminar producto (muestra lista primero)
void SistemaGestionHiraoka::eliminarProducto() {
	limpiarPantalla();
	cout << "\n======== ELIMINAR PRODUCTO ========" << endl;

	if (inventario.estaVacia()) {
		cout << "\nNo hay productos para eliminar." << endl;
		pausa();
		return;
	}

	// Mostrar lista primero (estilo del profesor)
	cout << "\nProductos registrados:" << endl;
	cout << "----------------------------------------" << endl;
	for (int i = 0; i < inventario.longitud(); i++) {
		Electrodomestico* prod = inventario.obtenerPosicion(i);
		cout << "[" << prod->getCodigo() << "] " << prod->getNombre() << endl;
	}
	cout << "----------------------------------------" << endl;

	string codigo;
	cout << "\nIngrese el codigo del producto a eliminar (0 para cancelar): ";
	cin >> codigo;

	if (codigo == "0") return;

	// Buscar posición
	int posicion = -1;
	for (int i = 0; i < inventario.longitud(); i++) {
		if (inventario.obtenerPosicion(i)->getCodigo() == codigo) {
			posicion = i;
			break;
		}
	}

	if (posicion != -1) {
		Electrodomestico* prod = inventario.obtenerPosicion(posicion);
		
		cout << "\nEsta seguro de eliminar: " << prod->getNombre() << "? (S/N): ";
		char confirmar;
		cin >> confirmar;
		
		if (confirmar == 'S' || confirmar == 's') {
			delete prod;
			inventario.eliminarPosicion(posicion);
			cout << "\n[OK] Producto eliminado!" << endl;
		}
		else {
			cout << "\nEliminacion cancelada." << endl;
		}
	}
	else {
		cout << "\nProducto no encontrado." << endl;
	}
	pausa();
}

// ========== GESTION DE CLIENTES (PILA) ==========
void SistemaGestionHiraoka::menuGestionClientes() {
	int opcion;
	do {
		limpiarPantalla();
		cout << "\n========================================" << endl;
		cout << "    GESTION DE CLIENTES (PILA LIFO)     " << endl;
		cout << "========================================" << endl;
		cout << "  1. Registrar cliente                  " << endl;
		cout << "  2. Ver todos los clientes             " << endl;
		cout << "  3. Buscar cliente                     " << endl;
		cout << "  4. Ver ultimo cliente (tope)          " << endl;
		cout << "  5. Ordenar clientes (Insercion)       " << endl;
		cout << "  6. Ver estadisticas (con Lambda)      " << endl;
		cout << "  0. Volver                             " << endl;
		cout << "========================================" << endl;
		cout << "Seleccione una opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1: registrarCliente(); break;
		case 2: verTodosLosClientes(); break;
		case 3: buscarCliente(); break;
		case 4: verUltimoCliente(); break;
		case 5: ordenarClientes(); break;
		case 6: verEstadisticasClientes(); break;
		case 0: break;
		default: cout << "Opcion invalida." << endl; pausa(); break;
		}
	} while (opcion != 0);
}

void SistemaGestionHiraoka::registrarCliente() {
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

// Ver último cliente (LIFO - tope de la pila)
void SistemaGestionHiraoka::verUltimoCliente() {
	limpiarPantalla();
	cout << "\n======== ULTIMO CLIENTE (TOPE PILA) ========" << endl;

	if (registroClientes.estaVacia()) {
		cout << "\nNo hay clientes registrados." << endl;
		pausa();
		return;
	}

	Cliente* ultimo = registroClientes.verCima();
	cout << "\nUltimo cliente registrado (LIFO):" << endl;
	cout << "----------------------------------------" << endl;
	cout << "DNI: " << ultimo->getDni() << endl;
	cout << "Nombre: " << ultimo->getNombreCompleto() << endl;
	cout << "Telefono: " << ultimo->getTelefono() << endl;
	cout << "Direccion: " << ultimo->getDireccion() << endl;
	cout << "----------------------------------------" << endl;

	pausa();
}

// ========== GESTION DE VENTAS (COLA FIFO) ==========

// Ver todos los clientes (simple)
void SistemaGestionHiraoka::verTodosLosClientes() {
	limpiarPantalla();
	cout << "\n========== LISTA DE CLIENTES ==========" << endl;

	if (registroClientes.estaVacia()) {
		cout << "\nNo hay clientes registrados." << endl;
		pausa();
		return;
	}

	cout << "\nTotal: " << registroClientes.getTamanio() << " clientes" << endl;
	cout << "----------------------------------------" << endl;

	// Mostrar todos los clientes (estilo del profesor)
	for (int i = 0; i < registroClientes.getTamanio(); i++) {
		Cliente* cli = registroClientes.obtenerEnPosicion(i);
		cout << "\n[" << cli->getDni() << "] " << cli->getNombreCompleto() << endl;
		cout << "  Telefono: " << cli->getTelefono() << endl;
		cout << "  Direccion: " << cli->getDireccion() << endl;
	}

	cout << "----------------------------------------" << endl;
	pausa();
}

// Buscar cliente (simple)
void SistemaGestionHiraoka::buscarCliente() {
	limpiarPantalla();
	cout << "\n======== BUSCAR CLIENTE ========" << endl;

	if (registroClientes.estaVacia()) {
		cout << "\nNo hay clientes para buscar." << endl;
		pausa();
		return;
	}

	string dni;
	cout << "\nIngrese el DNI del cliente: ";
	cin >> dni;

	// Buscar cliente (estilo del profesor)
	Cliente* encontrado = nullptr;
	for (int i = 0; i < registroClientes.getTamanio(); i++) {
		Cliente* cli = registroClientes.obtenerEnPosicion(i);
		if (cli->getDni() == dni) {
			encontrado = cli;
			break;
		}
	}

	if (encontrado != nullptr) {
		cout << "\n[OK] Cliente encontrado!" << endl;
		cout << "----------------------------------------" << endl;
		cout << "DNI: " << encontrado->getDni() << endl;
		cout << "Nombre: " << encontrado->getNombreCompleto() << endl;
		cout << "Telefono: " << encontrado->getTelefono() << endl;
		cout << "Direccion: " << encontrado->getDireccion() << endl;
		cout << "----------------------------------------" << endl;
	}
	else {
		cout << "\nCliente no encontrado." << endl;
	}
	pausa();
}

// ========== GESTION DE VENTAS (COLA FIFO) ==========

// Menu simple de ventas
void SistemaGestionHiraoka::menuGestionVentas() {
	int opcion;
	do {
		limpiarPantalla();
		cout << "\n========================================" << endl;
		cout << "    GESTION DE VENTAS (COLA FIFO)       " << endl;
		cout << "========================================" << endl;
		cout << "  1. Ver ventas pendientes              " << endl;
		cout << "  2. Procesar siguiente venta (FIFO)    " << endl;
		cout << "  3. Ver primera venta en cola          " << endl;
		cout << "  4. Ordenar ventas (Seleccion)         " << endl;
		cout << "  5. Ver estadisticas (con Lambda)      " << endl;
		cout << "  0. Volver                             " << endl;
		cout << "========================================" << endl;
		cout << "Seleccione una opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1: verVentasPendientes(); break;
		case 2: procesarSiguienteVenta(); break;
		case 3: verPrimeraVenta(); break;
		case 4: ordenarVentas(); break;
		case 5: verEstadisticasVentas(); break;
		case 0: break;
		default: cout << "Opcion invalida." << endl; pausa(); break;
		}
	} while (opcion != 0);
}

// Ver todas las ventas en la cola (sin sacarlas)
void SistemaGestionHiraoka::verVentasPendientes() {
	limpiarPantalla();
	cout << "\n========== VENTAS PENDIENTES (COLA) ==========" << endl;

	if (colaDeVentas.esVacia()) {
		cout << "\nNo hay ventas pendientes." << endl;
		pausa();
		return;
	}

	int total = colaDeVentas.getTamanio();
	cout << "\nTotal: " << total << " venta(s) pendiente(s)" << endl;

	// Calcular monto total (estilo del profesor)
	double montoTotal = 0;
	for (int i = 0; i < colaDeVentas.getTamanio(); i++) {
		Venta* venta = colaDeVentas.obtenerEnPosicion(i);
		montoTotal += venta->getMontoTotal();
	}
	cout << "Monto total: S/. " << fixed << setprecision(2) << montoTotal << endl;
	cout << "----------------------------------------" << endl;

	// Mostrar todas (estilo del profesor)
	for (int i = 0; i < colaDeVentas.getTamanio(); i++) {
		Venta* venta = colaDeVentas.obtenerEnPosicion(i);
		cout << "\n[" << venta->getIdVenta() << "] " << venta->getNombreCliente() << endl;
		cout << "  Producto: " << venta->getNombreProducto() << endl;
		cout << "  Cantidad: " << venta->getCantidad() << endl;
		cout << "  Total: S/. " << fixed << setprecision(2) << venta->getMontoTotal() << endl;
	}

	cout << "----------------------------------------" << endl;
	pausa();
}

// Procesar la siguiente venta (FIFO - la primera en entrar)
void SistemaGestionHiraoka::procesarSiguienteVenta() {
	limpiarPantalla();
	cout << "\n======== PROCESAR VENTA (FIFO) ========" << endl;

	if (colaDeVentas.esVacia()) {
		cout << "\nNo hay ventas para procesar." << endl;
		pausa();
		return;
	}

	// Desencolar (FIFO - saca la primera)
	Venta* venta = colaDeVentas.desencolar();
	
	cout << "\nProcesando..." << endl;
	cout << "----------------------------------------" << endl;
	cout << "ID: " << venta->getIdVenta() << endl;
	cout << "Cliente: " << venta->getNombreCliente() << endl;
	cout << "Producto: " << venta->getNombreProducto() << endl;
	cout << "Cantidad: " << venta->getCantidad() << endl;
	cout << "Total: S/. " << fixed << setprecision(2) << venta->getMontoTotal() << endl;
	cout << "----------------------------------------" << endl;
	cout << "\n[OK] Venta procesada!" << endl;

	// Liberar memoria
	delete venta;
	pausa();
}

// Ver la primera venta sin sacarla
void SistemaGestionHiraoka::verPrimeraVenta() {
	limpiarPantalla();
	cout << "\n======== PRIMERA VENTA (COLA FIFO) ========" << endl;

	if (colaDeVentas.esVacia()) {
		cout << "\nNo hay ventas pendientes." << endl;
		pausa();
		return;
	}

	Venta* primera = colaDeVentas.verPrimero();
	cout << "\nPrimera venta en la cola (siguiente a procesar):" << endl;
	cout << "----------------------------------------" << endl;
	cout << "ID: " << primera->getIdVenta() << endl;
	cout << "Cliente: " << primera->getNombreCliente() << endl;
	cout << "Producto: " << primera->getNombreProducto() << endl;
	cout << "Cantidad: " << primera->getCantidad() << endl;
	cout << "Total: S/. " << primera->getMontoTotal() << endl;
	cout << "----------------------------------------" << endl;

	pausa();
}

// ========== FUNCIONES PARA CLIENTES ==========

void SistemaGestionHiraoka::verCatalogoProductos() {
	limpiarPantalla();
	cout << "\n========================================" << endl;
	cout << "      CATALOGO DE PRODUCTOS             " << endl;
	cout << "========================================\n" << endl;

	if (inventario.estaVacia()) {
		cout << "No hay productos disponibles en este momento." << endl;
		pausa();
		return;
	}

	int contador = 1;
	for (int i = 0; i < inventario.longitud(); i++) {
		Electrodomestico* prod = inventario.obtenerPosicion(i);
		if (prod->getStock() > 0) {
			cout << "----------------------------------------" << endl;
			cout << " " << contador++ << ". " << prod->getNombre() << endl;
			cout << "    Marca: " << prod->getMarca() << " | Modelo: " << prod->getModelo() << endl;
			cout << "    Precio: S/. " << fixed << setprecision(2) << prod->getPrecio() << endl;
			cout << "    Stock: " << prod->getStock() << " unidades" << endl;
			cout << "    Codigo: " << prod->getCodigo() << endl;
			cout << "----------------------------------------" << endl;
		}
	}

	if (contador == 1) {
		cout << "No hay productos con stock disponible." << endl;
	}

	pausa();
}

void SistemaGestionHiraoka::agregarAlCarrito() {
	limpiarPantalla();
	cout << "\n========================================" << endl;
	cout << "        AGREGAR AL CARRITO              " << endl;
	cout << "========================================\n" << endl;

	if (inventario.estaVacia()) {
		cout << "No hay productos disponibles." << endl;
		pausa();
		return;
	}

	// Mostrar productos disponibles de forma compacta (estilo del profesor)
	cout << "Productos disponibles:\n" << endl;
	for (int i = 0; i < inventario.longitud(); i++) {
		Electrodomestico* prod = inventario.obtenerPosicion(i);
		if (prod->getStock() > 0) {
			cout << "  [" << prod->getCodigo() << "] " 
				 << prod->getNombre() 
				 << " - S/. " << prod->getPrecio()
				 << " (Stock: " << prod->getStock() << ")" << endl;
		}
	}

	cout << "\nIngrese el codigo del producto (o '0' para cancelar): ";
	string codigo;
	cin >> codigo;

	if (codigo == "0") return;

	// Buscar el producto (estilo del profesor)
	Electrodomestico* producto = nullptr;
	for (int i = 0; i < inventario.longitud(); i++) {
		Electrodomestico* prod = inventario.obtenerPosicion(i);
		if (prod->getCodigo() == codigo) {
			producto = prod;
			break;
		}
	}

	if (producto == nullptr) {
		cout << "\nProducto no encontrado." << endl;
		pausa();
		return;
	}

	if (producto->getStock() == 0) {
		cout << "\nProducto sin stock." << endl;
		pausa();
		return;
	}

	cout << "\nProducto: " << producto->getNombre() << endl;
	cout << "Precio: S/. " << producto->getPrecio() << endl;
	cout << "Stock disponible: " << producto->getStock() << endl;
	
	cout << "\nCuantas unidades deseas agregar? ";
	int cantidad;
	cin >> cantidad;

	if (cantidad <= 0) {
		cout << "\nCantidad invalida." << endl;
		pausa();
		return;
	}

	if (cantidad > producto->getStock()) {
		cout << "\nStock insuficiente. Solo hay " << producto->getStock() << " unidades." << endl;
		pausa();
		return;
	}

	// Verificar si ya existe en el carrito
	bool encontrado = false;
	for (int i = 0; i < carritoActual.longitud(); i++) {
		ItemCarrito* item = carritoActual.obtenerPosicion(i);
		if (item->getProducto()->getCodigo() == codigo) {
			// Ya existe, actualizar cantidad
			int nuevaCantidad = item->getCantidad() + cantidad;
			if (nuevaCantidad > producto->getStock()) {
				cout << "\nNo puedes agregar mas. Ya tienes " << item->getCantidad() 
					 << " en el carrito y solo hay " << producto->getStock() << " en stock." << endl;
				pausa();
				return;
			}
			item->setCantidad(nuevaCantidad);
			encontrado = true;
			break;
		}
	}

	if (!encontrado) {
		// Agregar nuevo item al carrito
		ItemCarrito* nuevoItem = new ItemCarrito(producto, cantidad);
		carritoActual.agregarFinal(nuevoItem);
	}

	cout << "\n[OK] Producto agregado al carrito exitosamente!" << endl;
	cout << "Tienes " << carritoActual.longitud() << " producto(s) en tu carrito." << endl;
	pausa();
}

void SistemaGestionHiraoka::verCarrito() {
	limpiarPantalla();
	cout << "\n========================================" << endl;
	cout << "        MI CARRITO DE COMPRAS           " << endl;
	cout << "========================================\n" << endl;

	if (carritoActual.estaVacia()) {
		cout << "Tu carrito esta vacio." << endl;
		cout << "\nAgrega productos desde el menu 'Agregar al Carrito'" << endl;
		pausa();
		return;
	}

	cout << "Productos en tu carrito:\n" << endl;
	cout << "----------------------------------------" << endl;

	double total = 0;
	int index = 1;
	// Recorrer carrito (estilo del profesor)
	for (int i = 0; i < carritoActual.longitud(); i++) {
		ItemCarrito* item = carritoActual.obtenerPosicion(i);
		cout << " " << index++ << ". ";
		Electrodomestico* prod = item->getProducto();
		cout << prod->getNombre() << endl;
		cout << "    Cantidad: " << item->getCantidad() 
			 << " x S/. " << prod->getPrecio()
			 << " = S/. " << fixed << setprecision(2) << item->getSubtotal() << endl;
		total += item->getSubtotal();
	}

	cout << "----------------------------------------" << endl;
	cout << " TOTAL A PAGAR: S/. " << fixed << setprecision(2) << total << endl;
	cout << "----------------------------------------" << endl;

	cout << "\nDeseas modificar el carrito? (S/N): ";
	char opcion;
	cin >> opcion;
	
	if (opcion == 'S' || opcion == 's') {
		modificarCarrito();
	}
}

void SistemaGestionHiraoka::modificarCarrito() {
	if (carritoActual.estaVacia()) {
		cout << "\nEl carrito esta vacio." << endl;
		pausa();
		return;
	}

	limpiarPantalla();
	cout << "\n========================================" << endl;
	cout << "        MODIFICAR CARRITO               " << endl;
	cout << "========================================\n" << endl;

	// Mostrar items con índice (estilo del profesor)
	int index = 1;
	for (int i = 0; i < carritoActual.longitud(); i++) {
		ItemCarrito* item = carritoActual.obtenerPosicion(i);
		cout << index++ << ". " << item->getProducto()->getNombre()
			 << " (Cantidad: " << item->getCantidad() << ")" << endl;
	}

	cout << "\nQue producto deseas modificar? (numero, 0 para cancelar): ";
	int numProducto;
	cin >> numProducto;

	if (numProducto <= 0 || numProducto > carritoActual.longitud()) {
		return;
	}

	ItemCarrito* item = carritoActual.obtenerPosicion(numProducto - 1);
	
	cout << "\nProducto: " << item->getProducto()->getNombre() << endl;
	cout << "Cantidad actual: " << item->getCantidad() << endl;
	cout << "\n1. Cambiar cantidad" << endl;
	cout << "2. Eliminar del carrito" << endl;
	cout << "Opcion: ";
	
	int opcion;
	cin >> opcion;

	if (opcion == 1) {
		cout << "\nNueva cantidad (Stock: " << item->getProducto()->getStock() << "): ";
		int nuevaCant;
		cin >> nuevaCant;

		if (nuevaCant <= 0) {
			cout << "\nEliminar este producto del carrito? (S/N): ";
			char confirma;
			cin >> confirma;
			if (confirma == 'S' || confirma == 's') {
				delete item;
				carritoActual.eliminarPosicion(numProducto - 1);
				cout << "\n[OK] Producto eliminado del carrito." << endl;
			}
		} else if (nuevaCant > item->getProducto()->getStock()) {
			cout << "\nStock insuficiente." << endl;
		} else {
			item->setCantidad(nuevaCant);
			cout << "\n[OK] Cantidad actualizada." << endl;
		}
	} else if (opcion == 2) {
		cout << "\nSeguro que deseas eliminar este producto? (S/N): ";
		char confirma;
		cin >> confirma;
		if (confirma == 'S' || confirma == 's') {
			delete item;
			carritoActual.eliminarPosicion(numProducto - 1);
			cout << "\n[OK] Producto eliminado del carrito." << endl;
		}
	}

	pausa();
}

void SistemaGestionHiraoka::finalizarCompra() {
	limpiarPantalla();
	cout << "\n========================================" << endl;
	cout << "        FINALIZAR COMPRA                " << endl;
	cout << "========================================\n" << endl;

	if (carritoActual.estaVacia()) {
		cout << "Tu carrito esta vacio." << endl;
		cout << "\nAgrega productos antes de finalizar la compra." << endl;
		pausa();
		return;
	}

	// Mostrar resumen de compra primero (estilo del profesor)
	cout << "========================================" << endl;
	cout << "        RESUMEN DE COMPRA               " << endl;
	cout << "========================================" << endl;

	double total = 0;
	for (int i = 0; i < carritoActual.longitud(); i++) {
		ItemCarrito* item = carritoActual.obtenerPosicion(i);
		Electrodomestico* prod = item->getProducto();
		cout << "  " << prod->getNombre() << endl;
		cout << "  " << item->getCantidad() << " x S/. " << prod->getPrecio()
			 << " = S/. " << fixed << setprecision(2) << item->getSubtotal() << endl;
		cout << "  --------------------------------------" << endl;
		total += item->getSubtotal();
	}

	cout << "\n  TOTAL A PAGAR: S/. " << fixed << setprecision(2) << total << endl;
	cout << "========================================\n" << endl;

	// Si no tiene cuenta, pedirla ahora de forma simple
	if (dniClienteActual.empty()) {
		cout << "Para completar tu compra, necesitamos tus datos:" << endl;
		cout << "----------------------------------------\n" << endl;
		
		string dni, nombres, apellidos, telefono, direccion;
		
		cout << "DNI: ";
		cin >> dni;
		
		// Verificar si ya existe (estilo del profesor)
		Cliente* existe = nullptr;
		for (int i = 0; i < registroClientes.getTamanio(); i++) {
			Cliente* cli = registroClientes.obtenerEnPosicion(i);
			if (cli->getDni() == dni) {
				existe = cli;
				break;
			}
		}
		
		if (existe != nullptr) {
			// Ya tiene cuenta
			dniClienteActual = dni;
			cout << "\n[OK] Bienvenido nuevamente " << existe->getNombreCompleto() << "!" << endl;
		} else {
			// Registrar nuevo cliente
			cin.ignore();
			cout << "Nombres: ";
			getline(cin, nombres);
			cout << "Apellidos: ";
			getline(cin, apellidos);
			cout << "Telefono: ";
			getline(cin, telefono);
			cout << "Direccion: ";
			getline(cin, direccion);
			
			Cliente* nuevoCliente = new Cliente(dni, nombres, apellidos, telefono, direccion);
			registroClientes.apilar(nuevoCliente);
			dniClienteActual = dni;
			cout << "\n[OK] Cuenta creada exitosamente!" << endl;
		}
		cout << endl;
	}

	cout << "Confirmar compra? (S/N): ";
	char confirma;
	cin >> confirma;

	if (confirma != 'S' && confirma != 's') {
		cout << "\nCompra cancelada." << endl;
		pausa();
		return;
	}

	// Buscar datos del cliente (estilo del profesor)
	Cliente* cliente = nullptr;
	for (int i = 0; i < registroClientes.getTamanio(); i++) {
		Cliente* cli = registroClientes.obtenerEnPosicion(i);
		if (cli->getDni() == dniClienteActual) {
			cliente = cli;
			break;
		}
	}

	if (cliente == nullptr) {
		cout << "\nError: Cliente no encontrado." << endl;
		pausa();
		return;
	}

	// Procesar cada item del carrito
	string fecha = obtenerFechaActual();
	bool todoCorrecto = true;

	// Validar stock antes de procesar
	for (int i = 0; i < carritoActual.longitud(); i++) {
		ItemCarrito* item = carritoActual.obtenerPosicion(i);
		if (item->getProducto()->getStock() < item->getCantidad()) {
			cout << "\nError: Stock insuficiente para " << item->getProducto()->getNombre() << endl;
			todoCorrecto = false;
			break;
		}
	}

	if (!todoCorrecto) {
		pausa();
		return;
	}

	// Crear ventas y reducir stock (SIMPLE)
	for (int i = 0; i < carritoActual.longitud(); i++) {
		ItemCarrito* item = carritoActual.obtenerPosicion(i);
		Electrodomestico* producto = item->getProducto();

		contadorVentas++;
		string idVenta = "V" + to_string(contadorVentas);

		// Crear venta
		Venta* nuevaVenta = new Venta(
			idVenta,
			fecha,
			cliente->getDni(),
			cliente->getNombreCompleto(),
			producto->getCodigo(),
			producto->getNombre(),
			item->getCantidad(),
			producto->getPrecio()
		);

		// Reducir stock
		producto->reducirStock(item->getCantidad());

		// ENCOLAR la venta (FIFO) - El admin la procesará después
		colaDeVentas.encolar(nuevaVenta);
	}

	// Limpiar carrito
	while (!carritoActual.estaVacia()) {
		ItemCarrito* item = carritoActual.obtenerPosicion(0);
		delete item;
		carritoActual.eliminarInicio();
	}

	cout << "\n========================================" << endl;
	cout << "    COMPRA REALIZADA CON EXITO!        " << endl;
	cout << "========================================" << endl;
	cout << "  Gracias por tu compra!" << endl;
	cout << "  Tu pedido sera procesado pronto" << endl;
	cout << "========================================" << endl;

	guardarDatos(); // Guardar automáticamente
	pausa();
}

void SistemaGestionHiraoka::miCuenta() {
	limpiarPantalla();
	cout << "\n========================================" << endl;
	cout << "           MI CUENTA                    " << endl;
	cout << "========================================\n" << endl;

	if (dniClienteActual.empty()) {
		cout << "No tienes una sesion iniciada." << endl;
		cout << "\nPor favor, usa la opcion 'Iniciar Sesion' del menu." << endl;
		pausa();
		return;
	}

	// Buscar cliente (estilo del profesor)
	Cliente* cliente = nullptr;
	for (int i = 0; i < registroClientes.getTamanio(); i++) {
		Cliente* cli = registroClientes.obtenerEnPosicion(i);
		if (cli->getDni() == dniClienteActual) {
			cliente = cli;
			break;
		}
	}

	if (cliente == nullptr) {
		cout << "Error: No se encontro informacion de la cuenta." << endl;
		pausa();
		return;
	}

	cout << "========================================" << endl;
	cout << "  INFORMACION DE CUENTA" << endl;
	cout << "========================================" << endl;
	cout << "  DNI: " << cliente->getDni() << endl;
	cout << "  Nombre: " << cliente->getNombreCompleto() << endl;
	cout << "  Telefono: " << cliente->getTelefono() << endl;
	cout << "  Direccion: " << cliente->getDireccion() << endl;
	cout << "========================================" << endl;

	pausa();
}

void SistemaGestionHiraoka::registrarMiCuenta() {
	limpiarPantalla();
	cout << "\n========================================" << endl;
	cout << "      REGISTRAR MI CUENTA               " << endl;
	cout << "========================================\n" << endl;

	cout << "Por favor, completa tus datos:\n" << endl;

	string dni, nombres, apellidos, telefono, direccion;

	cout << "DNI: ";
	cin >> dni;

	// Verificar si ya existe (estilo del profesor)
	Cliente* existe = nullptr;
	for (int i = 0; i < registroClientes.getTamanio(); i++) {
		Cliente* cli = registroClientes.obtenerEnPosicion(i);
		if (cli->getDni() == dni) {
			existe = cli;
			break;
		}
	}

	if (existe != nullptr) {
		cout << "\n[OK] Este DNI ya esta registrado." << endl;
		cout << "Usando cuenta existente..." << endl;
		dniClienteActual = dni;
		pausa();
		return;
	}

	cin.ignore();
	cout << "Nombres: ";
	getline(cin, nombres);
	cout << "Apellidos: ";
	getline(cin, apellidos);
	cout << "Telefono: ";
	getline(cin, telefono);
	cout << "Direccion: ";
	getline(cin, direccion);

	// Crear cliente
	Cliente* nuevoCliente = new Cliente(dni, nombres, apellidos, telefono, direccion);
	registroClientes.apilar(nuevoCliente);
	dniClienteActual = dni;

	cout << "\n[OK] Cuenta registrada exitosamente!" << endl;
	cout << "========================================" << endl;
	cout << "  Bienvenido/a: " << nuevoCliente->getNombreCompleto() << endl;
	cout << "  Ahora puedes realizar compras" << endl;
	cout << "========================================" << endl;

	guardarClientes();
	pausa();
}

void SistemaGestionHiraoka::registrarseAhora() {
	registrarMiCuenta();
}

void SistemaGestionHiraoka::iniciarSesionCliente() {
	limpiarPantalla();
	cout << "\n========================================" << endl;
	cout << "      INICIAR SESION - CLIENTE          " << endl;
	cout << "========================================\n" << endl;
	
	string dni;
	cout << "Ingresa tu DNI: ";
	cin >> dni;
	
	// Buscar cliente (estilo del profesor)
	Cliente* cliente = nullptr;
	for (int i = 0; i < registroClientes.getTamanio(); i++) {
		Cliente* cli = registroClientes.obtenerEnPosicion(i);
		if (cli->getDni() == dni) {
			cliente = cli;
			break;
		}
	}
	
	if (cliente != nullptr) {
		dniClienteActual = dni;
		cout << "\n[OK] Bienvenido nuevamente " << cliente->getNombreCompleto() << "!" << endl;
		cout << "\nAhora puedes ver tu historial de compras y datos." << endl;
	} else {
		cout << "\nNo se encontro una cuenta con este DNI." << endl;
		cout << "\nDeseas registrarte? (S/N): ";
		char opcion;
		cin >> opcion;
		if (opcion == 'S' || opcion == 's') {
			// Volver atrás para que use la opción de registro
			cout << "\nPor favor, usa la opcion 6 'Registrarme' del menu." << endl;
		}
	}
	
	pausa();
}

// ========== PERSISTENCIA DE DATOS ==========
void SistemaGestionHiraoka::guardarDatos() {
	guardarInventario();
	guardarClientes();
	cout << "\n[OK] Datos guardados exitosamente!" << endl;
}

void SistemaGestionHiraoka::guardarInventario() {
	ofstream archivo("inventario.txt");
	if (archivo.is_open()) {
		// Guardar productos (estilo del profesor)
		for (int i = 0; i < inventario.longitud(); i++) {
			Electrodomestico* prod = inventario.obtenerPosicion(i);
			archivo << prod->getCodigo() << "|"
				<< prod->getNombre() << "|"
				<< prod->getMarca() << "|"
				<< prod->getModelo() << "|"
				<< prod->getPrecio() << "|"
				<< prod->getAnioFabricacion() << "|"
				<< prod->getStock() << endl;
		}
		archivo.close();
	}
}

void SistemaGestionHiraoka::guardarClientes() {
	ofstream archivo("clientes.txt");
	if (archivo.is_open()) {
		// Guardar clientes (estilo del profesor)
		for (int i = 0; i < registroClientes.getTamanio(); i++) {
			Cliente* cli = registroClientes.obtenerEnPosicion(i);
			archivo << cli->getDni() << "|"
				<< cli->getNombres() << "|"
				<< cli->getApellidos() << "|"
				<< cli->getTelefono() << "|"
				<< cli->getDireccion() << endl;
		}
		archivo.close();
	}
}

// Cargar todos los datos al iniciar
void SistemaGestionHiraoka::cargarDatos() {
	cargarInventario();
	cargarClientes();
	cargarVentas();  // Agregar carga de ventas
}

void SistemaGestionHiraoka::cargarInventario() {
	ifstream archivo("inventario.txt");
	if (archivo.is_open()) {
		string linea;
		while (getline(archivo, linea)) {
			string codigo = dividirTexto(linea, '|', 0);
			string nombre = dividirTexto(linea, '|', 1);
			string marca = dividirTexto(linea, '|', 2);
			string modelo = dividirTexto(linea, '|', 3);
			string precioStr = dividirTexto(linea, '|', 4);
			string anioStr = dividirTexto(linea, '|', 5);
			string stockStr = dividirTexto(linea, '|', 6);

			// Usar funciones simples de C++ para convertir
			double precio = stod(precioStr);
			int anio = stoi(anioStr);
			int stock = stoi(stockStr);

			Electrodomestico* prod = new Electrodomestico(codigo, nombre, marca, modelo, precio, anio, stock);
			inventario.agregarFinal(prod);
		}
		archivo.close();
	}
}

void SistemaGestionHiraoka::cargarClientes() {
	ifstream archivo("clientes.txt");
	if (archivo.is_open()) {
		string linea;
		while (getline(archivo, linea)) {
			string dni = dividirTexto(linea, '|', 0);
			string nombres = dividirTexto(linea, '|', 1);
			string apellidos = dividirTexto(linea, '|', 2);
			string telefono = dividirTexto(linea, '|', 3);
			string direccion = dividirTexto(linea, '|', 4);

			Cliente* cli = new Cliente(dni, nombres, apellidos, telefono, direccion);
			registroClientes.apilar(cli);
		}
		archivo.close();
	}
}

void SistemaGestionHiraoka::cargarVentas() {
	ifstream archivo("historial_ventas.txt");
	if (archivo.is_open()) {
		string linea;
		while (getline(archivo, linea)) {
			string idVenta = dividirTexto(linea, '|', 0);
			string fecha = dividirTexto(linea, '|', 1);
			string dniCliente = dividirTexto(linea, '|', 2);
			string nombreCliente = dividirTexto(linea, '|', 3);
			string codigoProducto = dividirTexto(linea, '|', 4);
			string nombreProducto = dividirTexto(linea, '|', 5);
			string cantidadStr = dividirTexto(linea, '|', 6);
			string precioStr = dividirTexto(linea, '|', 7);

			// Convertir strings a números
			int cantidad = stoi(cantidadStr);
			double precio = stod(precioStr);

			Venta* venta = new Venta(idVenta, fecha, dniCliente, nombreCliente, 
									 codigoProducto, nombreProducto, cantidad, precio);
			colaDeVentas.encolar(venta);
		}
		archivo.close();
	}
}

// ========== CONSTRUCTOR ==========
SistemaGestionHiraoka::SistemaGestionHiraoka() {
	contadorVentas = 0;
	esAdmin = false;
	usuarioActual = "";
	dniClienteActual = "";
	modoInvitado = true; // Por defecto, cliente navega como invitado
	cout << "Iniciando Sistema de Gestion Hiraoka..." << endl;
	cargarDatos();
	cout << "Datos cargados correctamente." << endl;
}

// ========== DESTRUCTOR ==========
SistemaGestionHiraoka::~SistemaGestionHiraoka() {
	cout << "Cerrando sistema y liberando memoria..." << endl;

	// Liberar memoria del inventario (LISTA)
	while (!inventario.estaVacia()) {
		Electrodomestico* prod = inventario.obtenerPosicion(0);
		delete prod;
		inventario.eliminarInicio();
	}

	// Liberar memoria de clientes (PILA)
	while (!registroClientes.estaVacia()) {
		delete registroClientes.desapilar();
	}

	// Liberar memoria de ventas (COLA)
	while (!colaDeVentas.esVacia()) {
		delete colaDeVentas.desencolar();
	}

	// Liberar carrito actual
	while (!carritoActual.estaVacia()) {
		ItemCarrito* item = carritoActual.obtenerPosicion(0);
		delete item;
		carritoActual.eliminarInicio();
	}
}

// ========== METODO PRINCIPAL ==========
void SistemaGestionHiraoka::iniciar() {
	
	int opcionInicial;
	do {
		menuInicial();
		cin >> opcionInicial;

		// Validar entrada
		while (cin.fail()) {
			cout << "Entrada invalida. Ingrese un numero." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			menuInicial();
			cin >> opcionInicial;
		}

		switch (opcionInicial) {
		case 1: {
			// Entrar como cliente (modo invitado por defecto)
			esAdmin = false;
			modoInvitado = true;
			dniClienteActual = "";
			
			int opcion;
			do {
				mostrarMenuCliente();
				cin >> opcion;

				// Validar entrada
				while (cin.fail()) {
					cout << "Entrada invalida. Ingrese un numero." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					mostrarMenuCliente();
					cin >> opcion;
				}

				switch (opcion) {
				case 1: verCatalogoProductos(); break;
				case 2: agregarAlCarrito(); break;
				case 3: verCarrito(); break;
				case 4: finalizarCompra(); break;
				case 5:
					if (dniClienteActual.empty()) {
						iniciarSesionCliente(); // Login
					} else {
						miCuenta(); // Ver cuenta
					}
					break;
				case 6:
					if (dniClienteActual.empty()) {
						registrarseAhora(); // Registro
					}
					break;
				case 0:
					guardarDatos();
					cout << "\nGracias por tu visita! Vuelve pronto!" << endl;
					pausa();
					break;
				default:
					cout << "Opcion no valida. Intente de nuevo." << endl;
					pausa();
					break;
				}
			} while (opcion != 0);
			break;
		}
		case 2: {
			// Login como administrador
			if (loginAdmin()) {
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
					case 0:
						guardarDatos();
						cout << "\nGracias por usar el sistema. Hasta pronto!" << endl;
						pausa();
						break;
					default:
						cout << "Opcion no valida. Intente de nuevo." << endl;
						pausa();
						break;
					}
				} while (opcion != 0);
			}
			break;
		}
		case 0:
			cout << "\nGracias por visitar Tienda Hiraoka!" << endl;
			break;
		default:
			cout << "Opcion no valida. Intente de nuevo." << endl;
			pausa();
			break;
		}
	} while (opcionInicial != 0);
}

// ========== FUNCIONES DE ORDENAMIENTO (USO DE ALGORITMOS) ==========

// Ordenar productos usando Burbuja (Integrante 1 - Lista)
void SistemaGestionHiraoka::ordenarProductos() {
	limpiarPantalla();
	cout << "\n========== ORDENAR PRODUCTOS ==========" << endl;
	
	if (inventario.estaVacia()) {
		cout << "\nNo hay productos para ordenar." << endl;
		pausa();
		return;
	}
	
	cout << "\nOrdenando productos por codigo (Algoritmo Burbuja)..." << endl;
	inventario.ordenarBurbuja();
	cout << "\n[OK] Productos ordenados exitosamente!" << endl;
	cout << "\nProductos ordenados:" << endl;
	cout << "----------------------------------------" << endl;
	
	// Mostrar productos ordenados
	for (int i = 0; i < inventario.longitud(); i++) {
		Electrodomestico* prod = inventario.obtenerPosicion(i);
		cout << "[" << prod->getCodigo() << "] " << prod->getNombre() << endl;
	}
	
	cout << "----------------------------------------" << endl;
	guardarDatos(); // Guardar cambios
	pausa();
}

// Ordenar clientes usando Insercion (Integrante 2 - Pila)
void SistemaGestionHiraoka::ordenarClientes() {
	limpiarPantalla();
	cout << "\n========== ORDENAR CLIENTES ==========" << endl;
	
	if (registroClientes.estaVacia()) {
		cout << "\nNo hay clientes para ordenar." << endl;
		pausa();
		return;
	}
	
	cout << "\nOrdenando clientes por DNI (Algoritmo Insercion)..." << endl;
	registroClientes.ordenarInsercion();
	cout << "\n[OK] Clientes ordenados exitosamente!" << endl;
	cout << "\nClientes ordenados:" << endl;
	cout << "----------------------------------------" << endl;
	
	// Mostrar clientes ordenados
	for (int i = 0; i < registroClientes.getTamanio(); i++) {
		Cliente* cli = registroClientes.obtenerEnPosicion(i);
		cout << "[" << cli->getDni() << "] " << cli->getNombreCompleto() << endl;
	}
	
	cout << "----------------------------------------" << endl;
	guardarDatos(); // Guardar cambios
	pausa();
}

// Estadisticas de productos usando LAS 3 LAMBDAS (Integrante 1 - Lista)
void SistemaGestionHiraoka::verEstadisticasProductos() {
	limpiarPantalla();
	cout << "\n========== ESTADISTICAS - PRODUCTOS ==========\n" << endl;
	
	if (inventario.estaVacia()) {
		cout << "No hay productos registrados." << endl;
		pausa();
		return;
	}
	
	// Lambda 1: Contar elementos
	cout << "Total de productos: " << inventario.contarElementos() << endl;
	cout << "  [Lambda usada: auto contar = [](int a, int b) { return a + b; }]" << endl;
	
	// Lambda 2: Sumar stocks usando sumarElementos()
	Lista<int> listaStocks;
	for (int i = 0; i < inventario.longitud(); i++) {
		Electrodomestico* prod = inventario.obtenerPosicion(i);
		listaStocks.agregarFinal(prod->getStock());
	}
	int stockTotal = listaStocks.sumarElementos();
	cout << "\nUnidades en stock: " << stockTotal << endl;
	cout << "  [Lambda usada: auto sumar = [](int a, int b) { return a + b; }]" << endl;
	
	// Lambda 3: Mostrar precios usando mostrarTodos()
	Lista<double> listaPrecios;
	for (int i = 0; i < inventario.longitud(); i++) {
		Electrodomestico* prod = inventario.obtenerPosicion(i);
		listaPrecios.agregarFinal(prod->getPrecio());
	}
	double precioTotal = listaPrecios.sumarElementos();
	cout << "\nPrecio promedio: S/. " << fixed << setprecision(2) 
		 << (precioTotal / inventario.contarElementos()) << endl;
	
	cout << "\nTodos los precios: ";
	listaPrecios.mostrarTodos();
	cout << "  [Lambda usada: auto mostrar = [](double dato) { cout << dato << \" \"; }]" << endl;
	
	cout << "\n========================================" << endl;
	pausa();
}

// Estadisticas de clientes usando LAS 3 LAMBDAS (Integrante 2 - Pila)
void SistemaGestionHiraoka::verEstadisticasClientes() {
	limpiarPantalla();
	cout << "\n========== ESTADISTICAS - CLIENTES ==========\n" << endl;
	
	if (registroClientes.estaVacia()) {
		cout << "No hay clientes registrados." << endl;
		pausa();
		return;
	}
	
	// Lambda 1: Contar elementos
	cout << "Total de clientes: " << registroClientes.contarElementos() << endl;
	cout << "  [Lambda usada: auto contar = [](int a, int b) { return a + b; }]" << endl;
	
	// Lambda 2: Mostrar DNIs usando mostrarTodos()
	Lista<string> listaDNIs;
	for (int i = 0; i < registroClientes.getTamanio(); i++) {
		Cliente* cli = registroClientes.obtenerEnPosicion(i);
		listaDNIs.agregarFinal(cli->getDni());
	}
	cout << "\nDNIs de clientes: ";
	listaDNIs.mostrarTodos();
	cout << "  [Lambda usada: auto mostrar = [](string dato) { cout << dato << \" \"; }]" << endl;
	
	// Lambda 3: Contar clientes en Lima
	int clientesLima = 0;
	for (int i = 0; i < registroClientes.getTamanio(); i++) {
		Cliente* cli = registroClientes.obtenerEnPosicion(i);
		if (cli->getDireccion().find("Lima") != string::npos) {
			clientesLima++;
		}
	}
	cout << "\nClientes en Lima: " << clientesLima << endl;
	
	// Cliente mas reciente (tope de pila)
	if (!registroClientes.estaVacia()) {
		Cliente* ultimo = registroClientes.obtenerEnPosicion(0);
		cout << "Ultimo registrado: " << ultimo->getNombreCompleto() << endl;
	}
	
	cout << "\n========================================" << endl;
	pausa();
}

// Estadisticas de ventas usando LAS 3 LAMBDAS (Integrante 3 - Cola)
void SistemaGestionHiraoka::verEstadisticasVentas() {
	limpiarPantalla();
	cout << "\n========== ESTADISTICAS - VENTAS ==========\n" << endl;
	
	if (colaDeVentas.esVacia()) {
		cout << "No hay ventas registradas." << endl;
		pausa();
		return;
	}
	
	// Lambda 1: Contar elementos
	cout << "Total de ventas: " << colaDeVentas.contarElementos() << endl;
	cout << "  [Lambda usada: auto contar = [](int a, int b) { return a + b; }]" << endl;
	
	// Lambda 2: Sumar montos usando sumarElementos()
	Lista<double> listaMontos;
	for (int i = 0; i < colaDeVentas.getTamanio(); i++) {
		Venta* venta = colaDeVentas.obtenerEnPosicion(i);
		listaMontos.agregarFinal(venta->getMontoTotal());
	}
	double montoTotal = listaMontos.sumarElementos();
	cout << "\nMonto total: S/. " << fixed << setprecision(2) << montoTotal << endl;
	cout << "  [Lambda usada: auto sumar = [](double a, double b) { return a + b; }]" << endl;
	
	cout << "\nVenta promedio: S/. " << (montoTotal / colaDeVentas.contarElementos()) << endl;
	
	// Lambda 3: Mostrar todos los montos
	cout << "\nTodos los montos: S/. ";
	listaMontos.mostrarTodos();
	cout << "  [Lambda usada: auto mostrar = [](double dato) { cout << dato << \" \"; }]" << endl;
	
	cout << "\n========================================" << endl;
	pausa();
}


// Ordenar ventas usando Seleccion (Integrante 3 - Cola)
void SistemaGestionHiraoka::ordenarVentas() {
	limpiarPantalla();
	cout << "\n========== ORDENAR VENTAS ==========" << endl;
	
	if (colaDeVentas.esVacia()) {
		cout << "\nNo hay ventas para ordenar." << endl;
		pausa();
		return;
	}
	
	cout << "\nOrdenando ventas por ID (Algoritmo Seleccion)..." << endl;
	colaDeVentas.ordenarSeleccion();
	cout << "\n[OK] Ventas ordenadas exitosamente!" << endl;
	cout << "\nVentas ordenadas:" << endl;
	cout << "----------------------------------------" << endl;
	
	// Mostrar ventas ordenadas
	for (int i = 0; i < colaDeVentas.getTamanio(); i++) {
		Venta* venta = colaDeVentas.obtenerEnPosicion(i);
		cout << "[" << venta->getIdVenta() << "] " << venta->getNombreCliente() 
			 << " - S/. " << fixed << setprecision(2) << venta->getMontoTotal() << endl;
	}
	
	cout << "----------------------------------------" << endl;
	pausa();
}
