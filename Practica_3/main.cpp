#include <iostream>
#include <desencriptacion.h>

using namespace std;

int main(){

    //5.3 Encriptacion y desencriptacion
    unsigned char datosComprimidos[8];//Arreglo de bytes producidos en la encriptacion
    int cantidadDatos = sizeof(datosComprimidos);

    int posiciones;
    char clave = 'K';

    do{
        cout << "Ingrese el numero de posiciones a rotar (1-7): ";
        cin >> posiciones;

    }while(posiciones <= 0 | posiciones >= 8);

    cout << "\nDatos originales:\n";
    for (int i = 0; i < cantidadDatos; ++i) {
        cout << static_cast<int>(datosComprimidos[i]) << " ";
    }

    //Encriptar
    encriptar(datosComprimidos, cantidadDatos, posiciones, clave);
    cout << "\n\nDatos encriptados:\n";
    for (int i = 0; i < cantidadDatos; ++i) {
        cout << static_cast<int>(datosComprimidos[i]) << " ";
    }

    //Desencriptar
    desencriptar(datosComprimidos, cantidadDatos, posiciones, clave);
    cout << "\n\nDatos recuperados:\n";
    for (int i = 0; i < cantidadDatos; ++i) {
        cout << static_cast<int>(datosComprimidos[i]) << " ";
    }
    cout << endl;


    return 0;
}
