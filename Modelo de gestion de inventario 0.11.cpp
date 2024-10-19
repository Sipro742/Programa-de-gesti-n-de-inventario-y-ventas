#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Para usar system("cls") o system("clear")
#include <limits>  // Para manejar errores de entrada

using namespace std;

// Clase Producto
class Producto {
private:
    string nombre;
    double precio;
    int cantidad;

public:
    Producto(string n, double p, int c) : nombre(n), precio(p), cantidad(c) {}

    string getNombre() { return nombre; }
    double getPrecio() { return precio; }
    int getCantidad() { return cantidad; }

    void setNombre(string n) { nombre = n; }
    void setPrecio(double p) { precio = p; }
    void setCantidad(int c) { cantidad = c; }

    void mostrarProducto() {
        cout << "Nombre: " << nombre << " | Precio: " << precio << " | Cantidad: " << cantidad << endl;
    }

    bool vender(int cantidadVendida) {
        if (cantidadVendida > cantidad) {
            cout << "No hay suficiente inventario para vender esa cantidad.\n";
            return false;
        }
        cantidad -= cantidadVendida;
        return true;
    }
};

// Clase Usuario
class Usuario {
private:
    string nombre;
    string rol; // "admin" o "vendedor"
    string contrasena;

public:
    Usuario(string n, string r, string c) : nombre(n), rol(r), contrasena(c) {}

    string getNombre() { return nombre; }
    string getRol() { return rol; }
    bool verificarContrasena(string c) { return contrasena == c; }

    void setContrasena(string c) { contrasena = c; }
};

// Clase SistemaUsuarios
class SistemaUsuarios {
private:
    vector<Usuario> usuarios;
    Usuario* usuarioActual; // Puntero al usuario actualmente autenticado

public:
    SistemaUsuarios() : usuarioActual(nullptr) {}

    void agregarUsuario(string nombre, string rol, string contrasena) {
        if (nombre.empty() || rol.empty() || contrasena.empty()) {
            cout << "Error: Los campos no pueden estar vacios.\n";
            return;
        }
        usuarios.push_back(Usuario(nombre, rol, contrasena));
        cout << "Usuario agregado con exito.\n";
    }

    bool iniciarSesion(string nombre, string contrasena) {
        for (auto& usuario : usuarios) {
            if (usuario.getNombre() == nombre) {
                if (usuario.getRol() == "vendedor" && usuario.verificarContrasena(contrasena)) {
                    usuarioActual = &usuario;
                    cout << "Inicio de sesion exitoso.\n";
                    return true;
                }
                else if (usuario.getRol() == "admin") {
                    usuarioActual = &usuario;
                    cout << "Inicio de sesion exitoso.\n";
                    return true;
                }
                else {
                    cout << "Contrasena incorrecta.\n";
                    return false;
                }
            }
        }
        cout << "Usuario no encontrado.\n";
        return false;
    }

    void cerrarSesion() {
        usuarioActual = nullptr;
        cout << "Sesion cerrada.\n";
    }

    Usuario* getUsuarioActual() {
        return usuarioActual;
    }

    bool esAdmin() {
        return usuarioActual != nullptr && usuarioActual->getRol() == "admin";
    }
};

// Clase Inventario
class Inventario {
private:
    vector<Producto> productos;

    void limpiarPantalla() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    bool validarEntradaNumerica() {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada no valida. Por favor ingrese un numero.\n";
            return false;
        }
        return true;
    }

public:
    void agregarProducto() {
        string nombre;
        double precio;
        int cantidad;
        cout << "Ingrese el nombre del producto: ";
        cin.ignore();
        getline(cin, nombre);
        if (nombre.empty()) {
            cout << "Error: El nombre no puede estar vacio.\n";
            return;
        }
        cout << "Ingrese el precio del producto: ";
        cin >> precio;
        if (!validarEntradaNumerica() || precio <= 0) {
            cout << "El precio debe ser un numero positivo.\n";
            return;
        }
        cout << "Ingrese la cantidad del producto: ";
        cin >> cantidad;
        if (!validarEntradaNumerica() || cantidad < 0) {
            cout << "La cantidad debe ser un numero no negativo.\n";
            return;
        }
        productos.push_back(Producto(nombre, precio, cantidad));
        cout << "Producto agregado con exito.\n";
    }

    void mostrarInventario() {
        limpiarPantalla();
        if (productos.empty()) {
            cout << "El inventario esta vacio.\n";
        }
        else {
            cout << "Inventario:\n";
            for (size_t i = 0; i < productos.size(); ++i) {
                cout << i + 1 << ". ";
                productos[i].mostrarProducto();
            }
        }
    }

    void modificarProducto() {
        mostrarInventario();
        int indice;
        cout << "Ingrese el numero del producto a modificar: ";
        cin >> indice;
        if (!validarEntradaNumerica() || indice <= 0 || indice > productos.size()) {
            cout << "Numero de producto no valido.\n";
            return;
        }
        string nombre;
        double precio;
        int cantidad;
        cout << "Ingrese el nuevo nombre del producto: ";
        cin.ignore();
        getline(cin, nombre);
        if (nombre.empty()) {
            cout << "Error: El nombre no puede estar vacio.\n";
            return;
        }
        cout << "Ingrese el nuevo precio del producto: ";
        cin >> precio;
        if (!validarEntradaNumerica() || precio <= 0) {
            cout << "El precio debe ser un numero positivo.\n";
            return;
        }
        cout << "Ingrese la nueva cantidad del producto: ";
        cin >> cantidad;
        if (!validarEntradaNumerica() || cantidad < 0) {
            cout << "La cantidad debe ser un numero no negativo.\n";
            return;
        }
        productos[indice - 1].setNombre(nombre);
        productos[indice - 1].setPrecio(precio);
        productos[indice - 1].setCantidad(cantidad);
        cout << "Producto modificado con exito.\n";
    }

    void venderProducto() {
        mostrarInventario();
        int indice, cantidad;
        cout << "Ingrese el numero del producto a vender: ";
        cin >> indice;
        if (!validarEntradaNumerica() || indice <= 0 || indice > productos.size()) {
            cout << "Numero de producto no valido.\n";
            return;
        }
        cout << "Ingrese la cantidad a vender: ";
        cin >> cantidad;
        if (!validarEntradaNumerica() || cantidad <= 0) {
            cout << "La cantidad debe ser un numero positivo.\n";
            return;
        }
        if (productos[indice - 1].vender(cantidad)) {
            cout << "Venta realizada con exito.\n";
        }
    }
};

// Funcion principal
int main() {
    try {
        Inventario inventario;
        SistemaUsuarios sistemaUsuarios;
        int opcion;

        do {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            Usuario* usuarioActual = sistemaUsuarios.getUsuarioActual();
            if (usuarioActual) {
                cout << "Usuario actual: " << usuarioActual->getNombre()
                    << " (" << usuarioActual->getRol() << ")\n";
            }
            else {
                cout << "No hay un usuario autenticado.\n";
            }

            cout << "\n--- Menu Principal ---\n";
            if (!usuarioActual || sistemaUsuarios.esAdmin()) {
                cout << "1. Crear usuario\n";
            }
            cout << "2. Iniciar sesion\n";
            cout << "3. Cerrar sesion\n";
            if (usuarioActual) {
                cout << "4. Agregar producto\n";
                cout << "5. Mostrar inventario\n";
                cout << "6. Modificar producto\n";
                cout << "7. Vender producto\n";
            }
            cout << "8. Salir\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            if (!cin || opcion < 1 || opcion > 8) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Opcion no valida. Intente nuevamente.\n";
                continue;
            }

            switch (opcion) {
            case 1:
                if (!usuarioActual || sistemaUsuarios.esAdmin()) {
                    int clave;
                    cout << "Ingrese la clave de autenticacion para crear un usuario: ";
                    cin >> clave;
                    if (clave == 3746) {
                        string nombre, rol, contrasena;
                        cout << "Ingrese el nombre del usuario: ";
                        cin.ignore();
                        getline(cin, nombre);
                        cout << "Ingrese el rol del usuario (admin/vendedor): ";
                        getline(cin, rol);
                        cout << "Ingrese la contrasena: ";
                        getline(cin, contrasena);
                        sistemaUsuarios.agregarUsuario(nombre, rol, contrasena);
                    }
                    else {
                        cout << "Clave de autenticacion incorrecta.\n";
                    }
                }
                break;
            case 2:
            {
                string nombre, contrasena;
                cout << "Ingrese el nombre de usuario: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la contrasena: ";
                getline(cin, contrasena);
                sistemaUsuarios.iniciarSesion(nombre, contrasena);
            }
            break;
            case 3:
                sistemaUsuarios.cerrarSesion();
                break;
            case 4:
                if (usuarioActual) inventario.agregarProducto();
                break;
            case 5:
                if (usuarioActual) inventario.mostrarInventario();
                break;
            case 6:
                if (usuarioActual) inventario.modificarProducto();
                break;
            case 7:
                if (usuarioActual) inventario.venderProducto();
                break;
            case 8:
                cout << "Saliendo del programa...\n";
                break;
            }

            if (opcion != 8) {
                cout << "\nPresione Enter para continuar...";
                cin.ignore();
                cin.get();
            }
        } while (opcion != 8);
    }
    catch (const exception& e) {
        cout << "Se produjo un error inesperado: " << e.what() << endl;
    }
    return 0;
}
