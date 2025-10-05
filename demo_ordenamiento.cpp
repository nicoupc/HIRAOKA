#include <iostream>
#include <string>
using namespace std;

// Programa simple para demostrar cómo se comparan strings

int main() {
    cout << "\n========================================" << endl;
    cout << "  DEMOSTRACION: Como se comparan strings" << endl;
    cout << "========================================\n" << endl;
    
    // Ejemplos de comparación
    cout << "1. Comparaciones básicas:\n" << endl;
    cout << "   \"A\" < \"B\" = " << ("A" < "B" ? "true" : "false") << endl;
    cout << "   \"1\" < \"2\" = " << ("1" < "2" ? "true" : "false") << endl;
    cout << "   \"P001\" < \"P002\" = " << (string("P001") < string("P002") ? "true" : "false") << endl;
    
    cout << "\n2. Comparaciones de DNI:\n" << endl;
    cout << "   \"12345678\" < \"23456789\" = " << (string("12345678") < string("23456789") ? "true" : "false") << endl;
    cout << "   \"45678901\" < \"87654321\" = " << (string("45678901") < string("87654321") ? "true" : "false") << endl;
    
    cout << "\n3. Orden alfabético de códigos de producto:\n" << endl;
    string codigos[] = {"P003", "P001", "P005", "P002"};
    cout << "   ANTES: ";
    for (int i = 0; i < 4; i++) cout << codigos[i] << " ";
    cout << endl;
    
    // Ordenamiento burbuja simple
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (codigos[j] > codigos[j + 1]) {
                string temp = codigos[j];
                codigos[j] = codigos[j + 1];
                codigos[j + 1] = temp;
            }
        }
    }
    
    cout << "   DESPUÉS: ";
    for (int i = 0; i < 4; i++) cout << codigos[i] << " ";
    cout << endl;
    
    cout << "\n4. Orden alfabético de DNI:\n" << endl;
    string dnis[] = {"87654321", "12345678", "45678901"};
    cout << "   ANTES: ";
    for (int i = 0; i < 3; i++) cout << dnis[i] << " ";
    cout << endl;
    
    // Ordenamiento burbuja simple
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2 - i; j++) {
            if (dnis[j] > dnis[j + 1]) {
                string temp = dnis[j];
                dnis[j] = dnis[j + 1];
                dnis[j + 1] = temp;
            }
        }
    }
    
    cout << "   DESPUÉS: ";
    for (int i = 0; i < 3; i++) cout << dnis[i] << " ";
    cout << endl;
    
    cout << "\n========================================" << endl;
    cout << "  CONCLUSIÓN: Los strings se ordenan" << endl;
    cout << "  alfabéticamente, carácter por carácter" << endl;
    cout << "========================================\n" << endl;
    
    return 0;
}
