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

    ofstream archivo(direccion, ios::binary | ios::app);

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

    cout << "\n Compresion en RLE: \n";
    cout << comprimido << endl;

    //Convertir a bytes
    int cantidadDatos = static_cast<int>(comprimido.size());

    unsigned char *datos = new unsigned char[cantidadDatos];

    for(int i = 0; i < cantidadDatos; i++){
        datos[i] = static_cast<unsigned char>(comprimido[i]);
    }

    comprimido += "\n";

    // Guardamos el resultado en el archivo final especificado por el usuario
    guardarArchivoRLE(archivoFinal, comprimido);

    //Encriptar y desencriptar datos
    encriptar(datos, cantidadDatos, posiciones, clave);
    cout << "\nDatos encriptados exitosamente: \n";


    //Convertir a Char
    string datosEncriptadosStr;
    for(int i = 0; i < cantidadDatos; i++){
        datosEncriptadosStr += static_cast<char>(datos[i]);
    }
    cout << datosEncriptadosStr << endl;
    datosEncriptadosStr += "\n";
    // Guardamos el resultado en el archivo final especificado por el usuario
    guardarArchivoRLE(archivoFinal, datosEncriptadosStr);

    desencriptar(datos, cantidadDatos, posiciones, clave);
    cout << "Datos desencriptados exitosamente :\n";

    //Convertir de nuevo a string
    string comprimidoRecuperado;

    for(int i = 0; i < cantidadDatos; i++){
        comprimidoRecuperado += static_cast<char>(datos[i]);
    }
    cout << comprimidoRecuperado << endl;

    //Descomprimirlo
    string recuperado = descomprimir_RLE(comprimidoRecuperado);
    cout << "Datos descomprimidos exitosamente :\n";
    cout << recuperado << endl;

    string recuperadosave = recuperado + "\n";
    //Guardar archivo recuperado
    guardarArchivoRLE(archivoFinal, recuperadosave);

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
void ejecutarLZ78(const string &direccion, const string &archivoFinal, int posiciones, unsigned char clave) {
    //  Leer el archivo original
    string original = leerArchivoRLE(direccion);

    cout << "\nArchivo leido correctamente.\n";
    cout << "Cantidad de caracteres: " << original.size() << endl;

    //  Variables para recibir los resultados la compresión LZ78
    int* lista_prefi = nullptr;
    char* lista_cade = nullptr;
    int num_parejas = 0;

    // Ejecutamos tu compresión manual (pasa el contenido como const char*)
    compresion_LZ78(original.c_str(), lista_prefi, lista_cade, num_parejas);

    // Convertimos las parejas a un formato de texto para  y guardar
    // Empezamos en 1 porque el índice 0 es la raíz vacía interna
    string comprimidoTexto = "";
    for(int i = 1; i < num_parejas; i++) {
        comprimidoTexto += to_string(lista_prefi[i]) + lista_cade[i];
    }
    cout << "\nCompresion en LZ78: \n";
    //Mostramos las parejas de la compresion
    for(int i = 1; i < num_parejas; i++){
        cout << "Se agrego al diccionario : (" << lista_prefi[i] << ", "<< lista_cade[i] <<"), " << endl ;
    }

    // Guardamos el resultado comprimido
    string comprimidoTextoSave = comprimidoTexto + "\n";
    guardarArchivoRLE(archivoFinal, comprimidoTextoSave);

    //  Convertir a bytes para realizar la encriptación
    int cantidadDatos = static_cast<int>(comprimidoTexto.size());
    unsigned char *datos = new unsigned char[cantidadDatos];

    for(int i = 0; i < cantidadDatos; i++) {
        datos[i] = static_cast<unsigned char>(comprimidoTexto[i]);
    }

    // Encriptamos datos en memoria
    encriptar(datos, cantidadDatos, posiciones, clave);
    cout << "\nDatos encriptados exitosamente: \n";

    // Convertimos bytes encriptados a Char para mostrar y guardar en la segunda línea
    string datosEncriptadosStr;
    for(int i = 0; i < cantidadDatos; i++) {
        datosEncriptadosStr += static_cast<char>(datos[i]);
    }
    cout << datosEncriptadosStr << endl;

    datosEncriptadosStr += "\n";
    guardarArchivoRLE(archivoFinal, datosEncriptadosStr);

    // 5. Desencriptar datos en memoria
    desencriptar(datos, cantidadDatos, posiciones, clave);
    cout << "\nDatos desencriptados exitosamente:\n";

    // Convertir de nuevo a string para verificar lo recuperado
    string comprimidoRecuperado;
    for(int i = 0; i < cantidadDatos; i++) {
        comprimidoRecuperado += static_cast<char>(datos[i]);
    }
    cout << comprimidoRecuperado << endl;

    // Descompresión LZ78

    char* finalDescomprimido = nullptr;
    descompresion_LZ78(lista_prefi, lista_cade, num_parejas, finalDescomprimido);

    cout << "Datos descomprimidos exitosamente:\n";
    cout << finalDescomprimido << endl;

    // Guardamos el resultado recuperado
    string recuperadosave = string(finalDescomprimido) + "\n";
    guardarArchivoRLE(archivoFinal, recuperadosave);

    // Verificación de igualdad
    if(original == finalDescomprimido) {
        cout << "El archivo recuperado coincide exactamente con el archivo original.\n";
    } else {
        cout << "Los archivos no coinciden.\n";
    }

    // Limpieza de memoria dinámica de todos los punteros ocupados
    delete[] datos;
    delete[] lista_prefi;
    delete[] lista_cade;
    delete[] finalDescomprimido;
}

