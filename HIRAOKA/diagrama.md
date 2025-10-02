@startuml
' === CONFIGURACIÓN DE ESTILO PARA UN DIAGRAMA PROFESIONAL ===
skinparam classAttributeIconSize 0
skinparam style strictuml
skinparam groupInheritance 2
hide empty members

' === NOTA GENERAL DEL PROYECTO ===
note as ProjectNote
  **TB1: Sistema de Gestión de Ventas "Hiraoka"**
  Este diagrama modela la arquitectura del sistema cumpliendo con:
  - Paradigma POO y Programación Genérica.
  - Mínimo 15 clases.
  - 3 Estructuras de Datos distintas implementadas desde cero.
  - Relaciones lógicas entre todas las entidades.
end note

' === SECCIÓN 1: ESTRUCTURAS DE DATOS GENÉRICAS (EL CORAZÓN TÉCNICO) ===
package "Estructuras de Datos Genéricas (Templates)" {
    ' --- El Nodo: Ladrillo fundamental de las estructuras enlazadas ---
    class "Nodo<T>" as Nodo {
        + dato: T
        + siguiente: Nodo<T>*
    }

    ' --- Estructura 1: Lista Simple Enlazada (Asignada al Integrante 1) ---
    class "ListaSimple<T>" as Lista {
        - cabeza: Nodo<T>*
        - longitud: int
        + agregar(T): void
        + buscar(string): T
        + eliminar(string): bool
        ' Métodos específicos de la rúbrica
        + ordenarPorPrecio_QuickSort(): void
        + buscarPorCodigo_Recursivo(string): T
        + filtrarPorMarca_Lambda(string, function): void
    }
    note right of Lista
        **Responsable: Integrante 1**
        Contendrá los **Electrodomesticos**.
        Justificación: Flexibilidad para
        búsquedas, inserciones y
        eliminaciones en el inventario.
    end note

    ' --- Estructura 2: Pila (Asignada al Integrante 2) ---
    class "Pila<T>" as Pila {
        - cima: Nodo<T>*
        + push(T): void
        + pop(): T
        + top(): T
        ' Métodos específicos de la rúbrica
        + imprimirPila_Recursivo(): void
        + buscarCliente_Lambda(string, function): T
    }
    note right of Pila
        **Responsable: Integrante 2**
        Contendrá los **Clientes**.
        Justificación: Útil para un log
        de "últimos clientes atendidos"
        (LIFO - Last In, First Out).
    end note

    ' --- Estructura 3: Cola (Asignada al Integrante 3) ---
    class "Cola<T>" as Cola {
        - frente: Nodo<T>*
        - final: Nodo<T>*
        + enqueue(T): void
        + dequeue(): T
        + front(): T
        ' Métodos específicos de la rúbrica
        + ordenarVentas_MergeSort(): void
        + contarVentasPorFecha_Lambda(string, function): int
    }
    note right of Cola
        **Responsable: Integrante 3**
        Contendrá las **Ventas**.
        Justificación: Ideal para procesar
        pedidos en orden de llegada
        (FIFO - First In, First Out).
    end note
}

' === SECCIÓN 2: ENTIDADES DEL DOMINIO (POO) ===
package "Modelo de Negocio (Entidades POO)" {
    ' --- Jerarquía de Persona ---
    abstract class Persona {
        # dni: string
        # nombres: string
        # apellidos: string
    }

    class Cliente extends Persona {
        + direccion: string
        + telefono: string
        + guardarEnArchivo(): void
        + cargarDesdeArchivo(): void
    }

    class Empleado extends Persona {
        + id_empleado: string
        + cargo: string
        + salario: double
    }

    ' --- Jerarquía de Electrodoméstico ---
    abstract class Electrodomestico {
        # codigo: string
        # marca: string
        # modelo: string
        # precio: double
        # anio_fabricacion: int
        + virtual mostrarDetalles(): void
    }

    class Televisor extends Electrodomestico {
        + pulgadas: int
        + tipo_panel: string
        + mostrarDetalles(): void
    }

    class Refrigeradora extends Electrodomestico {
        + capacidad_litros: int
        + tiene_freezer: bool
        + mostrarDetalles(): void
    }
    
    class Lavadora extends Electrodomestico {
        + carga_kg: double
        + es_automatica: bool
        + mostrarDetalles(): void
    }

    ' --- Entidades de Transacción ---
    class Venta {
        + id_venta: string
        + fecha: string
        + monto_total: double
        + guardarEnArchivo(): void
    }

    class DetalleVenta {
        + cantidad: int
        + precio_unitario: double
        + calcularSubtotal(): double
    }
    
    class Sucursal {
        + id_sucursal: int
        + nombre: string
        + direccion: string
    }
}

' === SECCIÓN 3: CLASE ORQUESTADORA Y RELACIONES ===
package "Sistema y Relaciones" {
    ' --- Clase Principal del Sistema ---
    class SistemaGestionHiraoka {
        - inventario: ListaSimple<Electrodomestico*>
        - registroClientes: Pila<Cliente*>
        - colaDeVentas: Cola<Venta*>
        + iniciar(): void
        + mostrarMenuPrincipal(): void
        + registrarNuevoProducto(): void
        + procesarSiguienteVenta(): void
        + guardarTodo(): void
        + cargarTodo(): void
    }

    ' --- Relaciones entre Entidades ---
    Venta "1" *-- "1..*" DetalleVenta : contiene
    DetalleVenta "1" -- "1" Electrodomestico : corresponde a
    Venta "1" -- "1" Cliente : realizada por
    Venta "1" -- "1" Empleado : atendida por
    Sucursal "1" o-- "0..*" Empleado : emplea a

    ' --- Relaciones de Contenedor (Estructuras de Datos) ---
    SistemaGestionHiraoka o-- Lista : gestiona inventario
    SistemaGestionHiraoka o-- Pila : gestiona clientes
    SistemaGestionHiraoka o-- Cola : gestiona ventas
}

' --- Dependencia de Nodos ---
Lista ..> Nodo
Pila ..> Nodo
Cola ..> Nodo
@enduml