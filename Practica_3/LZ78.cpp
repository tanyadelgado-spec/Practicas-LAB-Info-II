#include "LZ78.h"
#include <bitset>
#include <iostream>
#include <fstream>  // libreria para leer archivos
#include <string>
using namespace std;

char compresion_LZ78(){
    int capacidad = 4;  // Capacidad inicial del arreglo dinamico
    int tamanio = 1; // Tamanio inicial del arreglo con la cadena vacia ""

    //Creacion de los diccionarios con arreglos dinamicos
    int* diccionario_prefijos = new int[capacidad];
    char* diccionario_cadenas = new int[capacidad];

    //Iniciamos la posicion 0 para la cadena vacia
    diccionario_prefijos[0] = 0;
    diccionario_cadenas[0] = '\0';

    char cadena[1000];
    cout << "Ingrese la cadena a comprimir : " << endl;
    cin.getline(cadena,1000);

    int i = 0; // indice para moverse dentro de una cadena
    while(cadena[i] != '\0'){
        char lactual = cadena[i];

        //Buscar si la letra ya existe en el diccionario



        i++;
    }



}



descompresion_LZ78(){

}