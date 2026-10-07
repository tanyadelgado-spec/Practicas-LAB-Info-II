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

        // filtro de validacion de captura de espacios vacios continua el programa
        if (lactual == '\n' || lactual == '\r') {
            i++;
            continue;
        }
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
    // Si el texto terminó pero nos quedamos con un prefijo acumulado
    if (prefijo != 0) {
        if(tamanio >= capacidad){
            agrandar_dicc(capacidad, dic_prefijos, dic_cadenas);
        }
        // Emitimos el residuo final usando el carácter nulo o el último carácter de esa rama conocidos
        dic_prefijos[tamanio] = dic_prefijos[prefijo];
        dic_cadenas[tamanio] = dic_cadenas[prefijo];
        tamanio++;
    }

    lista_prefijos = dic_prefijos;
    lista_cadenas = dic_cadenas;
    nparejas = tamanio;
}



void descompresion_LZ78(int* lista_prefijos, char* lista_cadenas, int nparejas, char*& texto_reconstruido){
    int capa_text = 4;
    int longitud_text = 0;

    // Reservamos memoria dinámica para el texto que vamos a recuperar
    texto_reconstruido = new char[capa_text];

    // Procesamos cada pareja. Empezamos en 1 porque el índice 0 es el vacío inicial.
    for (int i = 1; i < nparejas; i++) {
        int prefijo_actual = lista_prefijos[i];
        char caracter_actual = lista_cadenas[i];


        // Usamos un pequeño arreglo temporal estático para guardar la palabra actual al revés.
        char subfrase_al_reves[100];
        int tam_subfrase = 0;

        // El carácter del token actual es el último de la subfrase (el primero al revés)
        subfrase_al_reves[tam_subfrase] = caracter_actual;
        tam_subfrase++;

        // Subimos por el árbol de prefijos hasta llegar a la raíz (0)
        int nodo_actual = prefijo_actual;
        while (nodo_actual != 0) {
            subfrase_al_reves[tam_subfrase] = lista_cadenas[nodo_actual];
            tam_subfrase++;
            nodo_actual = lista_prefijos[nodo_actual]; // Escalamos al padre
        }

        // Si el texto acumulado más la nueva subfrase superan la capacidad, agrandamos el arreglo
        while (longitud_text + tam_subfrase >= capa_text) {
            int nueva_capacidad = capa_text * 2;
            char* nuevo_texto = new char[nueva_capacidad];

            // Copiamos lo que teníamos antes
            for (int j = 0; j < longitud_text; j++) {
                nuevo_texto[j] = texto_reconstruido[j];
            }

            delete[] texto_reconstruido; // Liberamos memoria vieja
            texto_reconstruido = nuevo_texto;
            capa_text = nueva_capacidad;
        }

        // Como subfrase_al_reves tiene las letras al revés, las leemos desde el final hacia el principio
        for (int j = tam_subfrase - 1; j >= 0; j--) {
            texto_reconstruido[longitud_text] = subfrase_al_reves[j];
            longitud_text++;
        }
    }

    // Al terminar de procesar todas las parejas, añadimos el terminador de cadena
    texto_reconstruido[longitud_text] = '\0';
}
