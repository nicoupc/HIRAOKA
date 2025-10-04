# WARP.md

This file provides guidance to WARP (warp.dev) when working with code in this repository.

## Project Overview

This is **Sistema de Gestión Hiraoka** - a C++ console application for managing an electronics retail store. It's an academic project implementing Object-Oriented Programming (OOP) and Generic Programming paradigms using Visual Studio on Windows.

### Core Architecture

The system follows a **three-layer data structure approach**:

1. **Lista&lt;Electrodomestico*&gt;** (Simple Linked List) - Manages product inventory
2. **Pila&lt;Cliente*&gt;** (Stack/LIFO) - Manages customer registration history
3. **Cola&lt;Venta*&gt;** (Queue/FIFO) - Manages sales processing queue

**Key Design Principle**: Each data structure serves a specific business purpose and includes custom template implementations with lambda functions and recursive methods to meet academic requirements.

### Project Structure

```
HIRAOKA/
├── HIRAOKA.sln                    # Visual Studio solution file
├── HIRAOKA/
│   ├── *.h                        # Header files (templates + classes)
│   ├── *.cpp                      # Implementation files
│   ├── *.txt                      # Data persistence files
│   └── HIRAOKA.vcxproj           # Project configuration
├── DOCUMENTACION_TECNICA.md       # Lambda & recursion examples
├── RESUMEN_IMPLEMENTACION.md      # Implementation summary
└── data files (inventario.txt, clientes.txt, usuarios.txt)
```

## Build & Development Commands

### Building the Project
```powershell
# Open solution in Visual Studio
start HIRAOKA.sln

# Or build via MSBuild (if available)
msbuild HIRAOKA.sln /p:Configuration=Debug /p:Platform=x64
```

### Running the Application
```powershell
# After building, run from output directory
.\HIRAOKA\x64\Debug\HIRAOKA.exe

# Or press F5 in Visual Studio to run with debugging
```

### Development Workflow
```powershell
# Check project structure
Get-ChildItem -Recurse -Include *.h, *.cpp

# View data files (for debugging persistence)
Get-Content .\HIRAOKA\inventario.txt
Get-Content .\HIRAOKA\clientes.txt
Get-Content .\HIRAOKA\usuarios.txt
```

## High-Level Architecture

### Data Flow Architecture

The system uses a **template-based generic architecture** where each major entity flows through a specific data structure:

**Inventario (Lista)** → **Clientes (Pila)** → **Ventas (Cola)**

This design reflects the business flow: products are managed in inventory, customers are registered (last-in-first-served for recent activity), and sales are processed in order.

### Template System Design

All data structures are implemented from scratch using C++ templates with three critical academic components:

1. **Lambda Functions**: Each structure has exactly 3+ lambda-based methods
   - `recorrer()` - traverse with custom action
   - `filtrar()` / `buscar()` - search with custom condition  
   - `contar()` - count with custom predicate

2. **Recursive Methods**: Each structure implements recursive traversal
   - Lista: `buscarRecursivo()` 
   - Pila: `imprimirRecursivo()` (reverse order)
   - Cola: `imprimirRecursivo()` (normal order)

3. **Advanced Sorting**: Lista implements `ordenarBurbuja()` with lambda comparators

### Class Hierarchy

```cpp
// Domain Models (Business Logic)
Cliente          // Customer data with DNI, name, contact info
Electrodomestico // Product data with code, price, stock
Venta           // Sale transaction linking customer + product

// Generic Data Structures (Templates)
Nodo<T>         // Basic linked node for all structures
Lista<T>        // Simple linked list with lambda methods
Pila<T>         // Stack (LIFO) with lambda methods  
Cola<T>         // Queue (FIFO) with lambda methods

// System Controller
SistemaGestionHiraoka // Main orchestrator managing all operations
```

### Memory Management Pattern

The system uses **raw pointer management** with careful cleanup in destructors. All data structures implement proper destructors that traverse and delete all nodes to prevent memory leaks.

### Persistence Architecture

**File-based persistence** using simple text format:
- `usuarios.txt`: username|password|role format
- `inventario.txt`: pipe-separated product data  
- `clientes.txt`: pipe-separated customer data
- Data loads on system startup, saves on system shutdown

## Key Implementation Patterns

### Lambda Usage Pattern
```cpp
// Standard lambda pattern used throughout
structure.recorrer([](T* item) {
    // Custom action on each item
});

structure.filtrar([condition](T* item) {
    return item->getAttribute() == condition;
});
```

### Template Method Pattern
All data structures follow the same interface pattern but implement different underlying behaviors (LIFO vs FIFO vs indexed access).

### Business Logic Separation
The `SistemaGestionHiraoka` class acts as a **facade** that orchestrates interactions between the generic data structures and domain-specific business rules.

## Development Guidelines

### Code Standards
- **Language**: Spanish identifiers and comments (academic requirement)
- **Style**: Consistent indentation, descriptive variable names
- **Memory**: Manual memory management with proper cleanup
- **Templates**: All data structures must be generic

### Testing Approach
- **Console-based testing**: Run application and test through menu system
- **Data verification**: Check .txt files for persistence correctness
- **Memory testing**: Use Visual Studio debugger to check for leaks

### Academic Compliance
This project fulfills specific academic requirements:
- ✅ Minimum 3 data structures (Lista, Pila, Cola)
- ✅ Minimum 3 lambda functions per structure
- ✅ Minimum 1 recursive method per structure  
- ✅ Advanced sorting algorithm (bubble sort with lambdas)
- ✅ Console interface with menus
- ✅ File persistence for all major entities

## Important Notes

- **Platform**: Windows-only Visual Studio project
- **Language Standard**: C++14 or later (for lambda support)
- **Dependencies**: None (all data structures implemented from scratch)
- **Data Format**: Simple pipe-separated text files for persistence
- **User System**: Basic username/password authentication with admin/client roles
