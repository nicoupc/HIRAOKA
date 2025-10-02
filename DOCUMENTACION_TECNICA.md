# DOCUMENTACIÓN TÉCNICA - SISTEMA HIRAOKA
## Ejemplos de Uso de Lambdas y Recursividad

---

## 📚 FUNCIONES LAMBDA IMPLEMENTADAS

### 1. Lista Simple Enlazada (inventario)

#### Lambda 1: recorrer()
**Propósito**: Ejecutar una acción sobre cada elemento de la lista

\\\cpp
// Ejemplo: Mostrar todos los productos
inventario.recorrer([](Electrodomestico* prod) {
    prod->mostrarDetalles();
    cout << "----------------------------------------" << endl;
});
\\\

**Complejidad**: O(n) - Recorre toda la lista una vez

---

#### Lambda 2: filtrar()
**Propósito**: Crear una nueva lista con elementos que cumplen una condición

\\\cpp
// Ejemplo: Filtrar productos por marca
Lista<Electrodomestico*>* filtrados = inventario.filtrar(
    [marca](Electrodomestico* prod) {
        return prod->getMarca() == marca;
    }
);
\\\

**Complejidad**: O(n) - Recorre toda la lista para filtrar

---

#### Lambda 3: contar()
**Propósito**: Contar elementos que cumplen una condición

\\\cpp
// Ejemplo: Contar productos con stock bajo
int cantidad = inventario.contar([stockMinimo](Electrodomestico* prod) {
    return prod->getStock() <= stockMinimo;
});
\\\

**Complejidad**: O(n) - Recorre toda la lista contando

---

#### Lambda 4: ordenarBurbuja()
**Propósito**: Ordenar elementos según una función comparadora

\\\cpp
// Ejemplo: Ordenar de menor a mayor precio
inventario.ordenarBurbuja([](Electrodomestico* a, Electrodomestico* b) {
    return a->getPrecio() < b->getPrecio();
});

// Ejemplo: Ordenar de mayor a menor precio
inventario.ordenarBurbuja([](Electrodomestico* a, Electrodomestico* b) {
    return a->getPrecio() > b->getPrecio();
});
\\\

**Complejidad**: O(n²) - Algoritmo de burbuja clásico

---

### 2. Pila (registroClientes)

#### Lambda 1: recorrer()
**Propósito**: Ejecutar una acción sobre cada cliente

\\\cpp
// Ejemplo: Mostrar todos los clientes
registroClientes.recorrer([](Cliente* cli) {
    cli->mostrarDatos();
});
\\\

**Complejidad**: O(n)

---

#### Lambda 2: buscar()
**Propósito**: Encontrar un cliente que cumpla una condición

\\\cpp
// Ejemplo: Buscar cliente por DNI
Cliente* encontrado = registroClientes.buscar([dni](Cliente* cli) {
    return cli->getDni() == dni;
});
\\\

**Complejidad**: O(n) - En el peor caso recorre toda la pila

---

#### Lambda 3: contar()
**Propósito**: Contar clientes que cumplen una condición

\\\cpp
// Ejemplo: Contar clientes de una ciudad específica
int cantidad = registroClientes.contar([ciudad](Cliente* cli) {
    return cli->getDireccion().find(ciudad) != string::npos;
});
\\\

**Complejidad**: O(n)

---

### 3. Cola (colaDeVentas)

#### Lambda 1: recorrer()
**Propósito**: Ejecutar una acción sobre cada venta

\\\cpp
// Ejemplo: Calcular monto total de ventas pendientes
double montoTotal = 0;
colaDeVentas.recorrer([&montoTotal](Venta* venta) {
    montoTotal += venta->getMontoTotal();
});
\\\

**Complejidad**: O(n)

---

#### Lambda 2: contar()
**Propósito**: Contar ventas que cumplen una condición

\\\cpp
// Ejemplo: Contar ventas de un cliente específico
int cantidad = colaDeVentas.contar([dni](Venta* venta) {
    return venta->getDniCliente() == dni;
});
\\\

**Complejidad**: O(n)

---

#### Lambda 3: buscar()
**Propósito**: Encontrar una venta que cumpla una condición

\\\cpp
// Ejemplo: Buscar venta por ID
Venta* encontrada = colaDeVentas.buscar([id](Venta* venta) {
    return venta->getIdVenta() == id;
});
\\\

**Complejidad**: O(n)

---

## 🔄 MÉTODOS RECURSIVOS IMPLEMENTADOS

### 1. Lista: buscarRecursivo()

**Código**:
\\\cpp
T buscarRecursivo(Nodo<T>* nodo, function<bool(T)> condicion) {
    if (nodo == nullptr) {
        return T(); // Caso base: no encontrado
    }
    if (condicion(nodo->dato)) {
        return nodo->dato; // Caso base: encontrado
    }
    return buscarRecursivo(nodo->siguiente, condicion); // Llamada recursiva
}
\\\

**Uso**:
\\\cpp
Electrodomestico* encontrado = inventario.buscarRecursivo(
    [codigo](Electrodomestico* prod) {
        return prod->getCodigo() == codigo;
    }
);
\\\

**Complejidad**: 
- Tiempo: O(n) - En el peor caso recorre toda la lista
- Espacio: O(n) - Usa la pila de llamadas recursivas

---

### 2. Pila: imprimirRecursivo()

**Código**:
\\\cpp
void imprimirRecursivo(Nodo<T>* nodo, function<void(T)> mostrar) {
    if (nodo == nullptr) return; // Caso base
    imprimirRecursivo(nodo->siguiente, mostrar); // Primero recursión
    mostrar(nodo->dato); // Luego acción (imprime en orden inverso)
}
\\\

**Uso**:
\\\cpp
registroClientes.imprimirRecursivo([](Cliente* cli) {
    cli->mostrarDatos();
    cout << "----------------------------------------" << endl;
});
\\\

**Complejidad**: 
- Tiempo: O(n)
- Espacio: O(n) - Pila de llamadas

**Nota**: Imprime en orden inverso (del más antiguo al más reciente)

---

### 3. Cola: imprimirRecursivo()

**Código**:
\\\cpp
void imprimirRecursivo(Nodo<T>* nodo, function<void(T)> mostrar) {
    if (nodo == nullptr) return; // Caso base
    mostrar(nodo->dato); // Primero acción
    imprimirRecursivo(nodo->siguiente, mostrar); // Luego recursión
}
\\\

**Uso**:
\\\cpp
colaDeVentas.imprimirRecursivo([](Venta* venta) {
    venta->mostrarVenta();
});
\\\

**Complejidad**: 
- Tiempo: O(n)
- Espacio: O(n) - Pila de llamadas

**Nota**: Imprime en orden normal (del primero al último)

---

## 📊 ANÁLISIS DE COMPLEJIDAD DE 3 MÉTODOS PRINCIPALES

### 1. ordenarBurbuja() - Lista

**Descripción**: Ordena la lista usando el algoritmo de ordenamiento burbuja con función comparadora lambda.

**Código**:
\\\cpp
void ordenarBurbuja(function<bool(T, T)> comparar) {
    if (estaVacia() || tamanio == 1) return;
    
    for (int i = 0; i < tamanio - 1; i++) {              // n-1 iteraciones
        Nodo<T>* actual = inicio;
        for (int j = 0; j < tamanio - i - 1; j++) {      // (n-i-1) iteraciones
            if (comparar(actual->siguiente->dato, actual->dato)) {
                T temp = actual->dato;
                actual->dato = actual->siguiente->dato;
                actual->siguiente->dato = temp;
            }
            actual = actual->siguiente;
        }
    }
}
\\\

**Análisis**:
- **Mejor caso**: O(n²) - Incluso si ya está ordenado
- **Caso promedio**: O(n²)
- **Peor caso**: O(n²) - Lista en orden inverso
- **Espacio**: O(1) - Ordenamiento in-place

**Justificación**: 
Dos bucles anidados, el externo ejecuta (n-1) veces y el interno (n-i-1) veces.
Total de comparaciones: (n-1) + (n-2) + ... + 1 = n(n-1)/2 = O(n²)

---

### 2. buscarRecursivo() - Lista

**Descripción**: Busca un elemento en la lista de forma recursiva usando una función lambda como condición.

**Código**:
\\\cpp
T buscarRecursivo(Nodo<T>* nodo, function<bool(T)> condicion) {
    if (nodo == nullptr) {
        return T();
    }
    if (condicion(nodo->dato)) {
        return nodo->dato;
    }
    return buscarRecursivo(nodo->siguiente, condicion);
}
\\\

**Análisis**:
- **Mejor caso**: O(1) - Elemento en la primera posición
- **Caso promedio**: O(n/2) = O(n)
- **Peor caso**: O(n) - Elemento al final o no existe
- **Espacio**: O(n) - Pila de llamadas recursivas

**Justificación**:
En el peor caso, hace una llamada recursiva por cada nodo de la lista, 
generando n llamadas en la pila de ejecución.

---

### 3. filtrar() - Lista

**Descripción**: Crea una nueva lista con todos los elementos que cumplen una condición lambda.

**Código**:
\\\cpp
Lista<T>* filtrar(function<bool(T)> condicion) {
    Lista<T>* listaFiltrada = new Lista<T>();
    Nodo<T>* actual = inicio;
    while (actual != nullptr) {
        if (condicion(actual->dato)) {
            listaFiltrada->agregarFinal(actual->dato);
        }
        actual = actual->siguiente;
    }
    return listaFiltrada;
}
\\\

**Análisis**:
- **Mejor caso**: O(n) - Debe recorrer toda la lista
- **Caso promedio**: O(n)
- **Peor caso**: O(n) - Siempre recorre toda la lista
- **Espacio**: O(k) - Donde k es el número de elementos que cumplen la condición

**Justificación**:
Recorre todos los nodos exactamente una vez (n iteraciones).
La operación agregarFinal() dentro del ciclo no afecta la complejidad 
porque solo agrega al final (O(1) por inserción con puntero al final, 
pero en esta implementación es O(m) donde m es el tamaño de listaFiltrada).

**Complejidad total real**: O(n*m) en el peor caso si todos los elementos cumplen.
Pero típicamente se considera O(n) para el recorrido principal.

---

## 💡 VENTAJAS DEL USO DE LAMBDAS

1. **Código más limpio**: No necesitas crear funciones separadas
2. **Flexibilidad**: Puedes cambiar el comportamiento sin modificar la estructura
3. **Captura de variables**: Puedes usar variables del contexto externo
4. **Reusabilidad**: Las estructuras de datos son genéricas y adaptables

## 🎯 CUMPLIMIENTO DE REQUERIMIENTOS

✅ Mínimo 3 funciones lambda por estructura de datos
✅ Mínimo 1 método recursivo por estructura de datos  
✅ Templates en todas las estructuras de datos
✅ Justificación de uso de cada estructura
✅ Análisis de complejidad de 3 métodos importantes

