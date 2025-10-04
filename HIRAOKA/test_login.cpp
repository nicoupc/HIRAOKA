#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    string user = "admin";
    string pass = "1234";
    
    ifstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        string linea;
        cout << "Archivo abierto correctamente" << endl;
        while (getline(archivo, linea)) {
            // Eliminar caracteres de retorno de carro
            if (!linea.empty() && linea[linea.length()-1] == '\r') {
                linea.erase(linea.length()-1);
            }
            
            cout << "Linea leida: [" << linea << "]" << endl;
            
            stringstream ss(linea);
            string usuario, password, tipo;
            getline(ss, usuario, '|');
            getline(ss, password, '|');
            getline(ss, tipo, '|');
            
            // Limpiar posibles espacios
            if (!tipo.empty() && tipo[tipo.length()-1] == '\r') {
                tipo.erase(tipo.length()-1);
            }
            
            cout << "  Usuario: [" << usuario << "]" << endl;
            cout << "  Password: [" << password << "]" << endl;
            cout << "  Tipo: [" << tipo << "]" << endl;
            
            if (usuario == user && password == pass && tipo == "admin") {
                cout << "LOGIN EXITOSO!" << endl;
                return 0;
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo" << endl;
    }
    
    cout << "LOGIN FALLIDO" << endl;
    return 1;
}
