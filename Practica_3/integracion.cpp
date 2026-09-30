#include "integracion.h"

#include "RLE.h"
#include "LZ78.h"
#include "desencriptacion.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

integracion::integracion() {}

//-_-_-_-_-_-_-_-_-_-_-_- RLE -_-_-_-_-_--_-_-_-_-_-
//Leer el archivo para compresion RLE
string leerArchivoRLE(const string &direccion){

    ifstream archivo(direccion, ios::binary);//'ios::binary': abrir el archivo en binario, sin otras
                                            //conversiones de modo texto

    if(!archivo){
        throw runtime_error("No se pudo abrir el archivo ingresado.");
    }

    string texto;
    char caracter;

    while(archivo.get(caracter)){
        texto += caracter;
    }
    archivo.close();

    return texto;
}

//Guardar el archivo leido para RLE
void guardarArchivoRLE(const string &direccion, const string &texto){

    ofstream archivo(direccion, ios::binary);

    if(!archivo){
        throw runtime_error("No se pudo crear el archivo a comprimir.");
    }

    archivo.write(texto.data(), texto.size());//Escribir los bytes del archivo desde el inicio del texto con .data y
                                              //con su dimension en bytescon .size
    if(!archivo){
        throw runtime_error("Error al escribir el archivo.");
    }

    archivo.close();
}

//Verificar igualdad entre archivos -original/recuperado-
bool verificarRLE(const string &original, const string &recuperado){

    return original == recuperado;
}

//Ejecucción de compresion RLE
void ejecutarRLE(const string &direccion, const string &archivoFinal, int posiciones, unsigned char clave){

    //Leer archivo original
    string original = leerArchivoRLE(direccion);

    cout << "\nArchivo leido correctamente.\n";
    cout << "Cantidad de caracteres: " << original.size() << endl; //Verificar para que la cantidad coincida (opcional)

    //Comprimir
    string comprimido = comprimir_RLE(original);

    cout << "\nContenido del archivo (comprimido):\n";
    cout << comprimido << endl;

    //Convertir a bytes
    int cantidadDatos = static_cast<int>(comprimido.size());

    unsigned char *datos = new unsigned char[cantidadDatos];

    for(int i = 0; i < cantidadDatos; i++){
        datos[i] = static_cast<unsigned char>(comprimido[i]);
    }

    //Encriptar y desencriptar datos
    encriptar(datos, cantidadDatos, posiciones, clave);
    cout << "\nDatos encriptados exitosamente.\n";

    desencriptar(datos, cantidadDatos, posiciones, clave);
    cout << "Datos desencriptados exitosamente.\n";

    //Convertir de nuevo a string
    string comprimidoRecuperado;

    for(int i = 0; i < cantidadDatos; i++){
        comprimidoRecuperado += static_cast<char>(datos[i]);
    }

    //Descomprimirlo
    string recuperado = descomprimir_RLE(comprimidoRecuperado);

    //Guardar archivo recuperado
    guardarArchivoRLE(archivoFinal, recuperado);

    //Verificación de igualdad entre datos
    if(verificarRLE(original, recuperado)){
        cout << "El archivo recuperado coincide excatamente con el archivo original.\n";

    }else{
        cout << "Los archivos no coinciden.\n";
    }
    delete[] datos;
}

//-_-_-_-_-_-_-_-_-_-_-_- LZ78 -_-_-_-_-_--_-_-_-_-_-
//Leer archivo para compresion LZ78
char *leerArchivoLZ78(const char *direccion, int &tamanio){

    ifstream archivo(direccion, ios::binary);

    if(!archivo){
        throw runtime_error("No se pudo abrir el archivo ingresado.");
    }

    // Determinar tamaño del archivo
    archivo.seekg(0, ios::end);//mover el punto de inicio de lectura del archivo al final (0 bytes)
    streampos posicionFinal = archivo.tellg(); //'tellg()': posicion actual de lectura, es decir la posicion final dada lalinea anterior
                                                //'streampos': representar posiciones dentro de un flujo de archivos

    if(posicionFinal < 0){
        throw runtime_error("No se pudo determinar el tamaño del archivo.");
    }

    tamanio = static_cast<int>(posicionFinal);//Guardar el tamaño convirtiendolo a entero

    archivo.seekg(0, ios::beg);//mover el punto de inicio de lectura del archivo al inicio, se mueve 0bytes desde el comienzo

    // Reservar memoria dinámica
    char *texto = new char[tamanio + 1];//'+1': Para considerar la expresion de fin de cadema '/0'

    if(tamanio > 0){//Leer el archivo en caso de tener contenido
        archivo.read(texto, tamanio);
    }
    texto[tamanio] = '\0';//Agregar fin de cadena
    archivo.close();

    return texto;
}

//Guardar el archivo leido para LZ78
void guardarArchivoLZ78(const char *direccion, const char *texto, int tamanio){

    ofstream archivo(direccion, ios::binary);

    if(!archivo){
        throw runtime_error("No se pudo crear el archivo correctamente.");
    }

    archivo.write(texto, tamanio);
    if(!archivo){
        throw runtime_error("Error al escribir el archivo.");
    }
    archivo.close();
}

//Verificar igualdad entre archivos -original/recuperado-
bool verificarLZ78(const char *original, const char *recuperado, int tamanio){

    for(int i = 0; i < tamanio; i++){

        if(original[i] != recuperado[i]){
            return false;
        }
    }
    return true;
}


//Ejecucción de compresion LZ78
void ejecutarLZ78(const char *direccion, const char *archivoFinal, int posiciones, unsigned char clave){

}

