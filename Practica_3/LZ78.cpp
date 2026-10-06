#include "LZ78.h"
#include <bitset>
#include <iostream>
#include <fstream>  // libreria para leer archivos
#include <string>
using namespace std;

//Buscar si la letra ya existe en el diccionario
int buscar(int* dic_prefijos, char* dic_cadenas, int tamanio, int prefijo, char lbuscada){
    for(int i = 1; i < tamanio; i++){
        if(lbuscada == dic_cadenas[i] && prefijo == dic_prefijos[i]){
            return i;
        }
    }
    return -1;
}

void agrandar_dicc(int& capacidad, int*& lista_prefijos, char*& lista_cadenas){
    int ncapacidad = capacidad * 2;
    int* nlprefijos = new int[ncapacidad]; // creamos nuevos diccionarios para almacenar los datos
    char* nlcadena = new char[ncapacidad];

    //llenamos los nuevos diccionarios con la info que ya esta en la lista antes de agregar nuevos elementos
    for(int j = 0; j< capacidad; j++){
        nlprefijos[j] = lista_prefijos[j];
        nlcadena[j] = lista_cadenas[j];
    }
    delete[] lista_prefijos;
    delete[] lista_cadenas;
    // las listas iniciales se les asigna la direccion de memoria de los nuevos arreglos
    lista_prefijos = nlprefijos;
    lista_cadenas = nlcadena;
    capacidad = ncapacidad;
}

// Algoritmo de compresion
void compresion_LZ78(const char* cadena, int*& lista_prefijos, char*& lista_cadenas, int& nparejas){
    int capacidad = 4;  // Capacidad inicial del arreglo dinamico
    int tamanio = 1; // Tamanio inicial del arreglo con la cadena vacia ""

    //Creacion de los diccionarios con arreglos dinamicos
    int* dic_prefijos = new int[capacidad];
    char* dic_cadenas = new char[capacidad];

    //Iniciamos la posicion 0 para la cadena vacia
    dic_prefijos[0] = 0;
    dic_cadenas[0] = '\0';

    int i = 0; // indice para moverse dentro de una cadena
    int prefijo = 0;
    while(cadena[i] != '\0'){
        char lactual = cadena[i];

        int indice = buscar(dic_prefijos, dic_cadenas, tamanio, prefijo,  lactual);

        if(indice == -1){

            //Si la cadena no existe


            // verificamos si el diccionario esta lleno
            if(tamanio >= capacidad){
                agrandar_dicc(capacidad, dic_prefijos, dic_cadenas);
            }

            //se guarda el par en los diccionarios
            dic_cadenas[tamanio] = lactual;
            dic_prefijos[tamanio] = prefijo;
            tamanio++;
            // se reinicia el prefijo
            prefijo = 0;
        }else{
            //si la cadena existe el prefijo se actualiza
            prefijo = indice;
        }

        i++;
    }
    lista_prefijos = dic_prefijos;
    lista_cadenas = dic_cadenas;
    nparejas = tamanio;
}



void descompresion_LZ78(){

}