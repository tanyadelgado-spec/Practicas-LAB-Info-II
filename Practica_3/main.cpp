#include <iostream>
#include <desencriptacion.h>
#include <RLE.h>
#include <string>

using namespace std;

int main(){
    int opcion = 0;
    cout << "Ingrese una de las siguientes opciones : \n"
            "1. 5.1 Compresion y descompresion RLE \n"
            "2. 5.2 Compresion y descompresion LZ78 \n"
            "3. 5.3 Encriptacion y desencriptacion \n"
            "4. 5.4 Integracion " << endl;
    cin >> opcion;

    switch (opcion){

    case 1 :{
    //5.1 Compresion y descompresion RLE
    string cadena;
    cout << "Ingrese la cadena a comprimir: " << endl;
    cin >> cadena;
    string compressed = comprimir_RLE(cadena);
    string original = descomprimir_RLE(compressed);

    cout << "La cadena comprimida es : \n" << compressed << endl;

    cout << "La cadena descomprimida es : \n" << original << endl;

    break;
    }
    //
    case 2 :{
        break;
    }

    case 3 :{
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
    break;
    }
    case 4 :{

    }
    default :{
        cout << "Opcion invalida" << endl;
    }
    break;
    }

    return 0;
}
