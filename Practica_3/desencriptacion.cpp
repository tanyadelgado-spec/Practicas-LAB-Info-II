#include "desencriptacion.h"
#include <bitset>

desencriptacion::desencriptacion() {}

/*Encriptacion y desencirptacion.
    Implemente un modulo de encriptacion que opere sobre los datos comprimidos. El proceso debera:
    1. Aplicar una rotacion de bits hacia la izquierda a cada byte, con un valor n definido por el usuario
    (0 < n < 8).
    2. Aplicar posteriormente una operacion XOR con una clave de un byte K.
    Implemente tambien el proceso inverso que permita recuperar los datos originales-
*/

/*
void mostrarByte(unsigned char byte, const string& mensaje){
    cout << mensaje << ": " << bitset<8>(byte) << endl;
}
*/

//Rotacion a la izquierda
unsigned char rotacionIzquierda(unsigned char byte, int posiciones){

    return ((byte << posiciones) | (byte >> (8 - posiciones)));
}

//Rotacion a la derecha
unsigned char rotacionDerecha(unsigned char byte, int posiciones){

    return ((byte >> posiciones) | (byte << (8 - posiciones)));
}

//Encriptacion
void encriptar(unsigned char *datos, int cantidad, int posiciones, unsigned char clave){

    for (int i = 0; i < cantidad; ++i) {

        //Rotar a la izquierda
        datos[i] = rotacionIzquierda(datos[i], posiciones);
        //Aplicar XOR
        datos[i] = datos[i] ^ clave;
    }
}

//Desencriptacion
void desencriptar(unsigned char *datos, int cantidad, int posiciones, unsigned char clave){

    for (int i = 0; i < cantidad; ++i) {

        //Deshacer XOR
        datos[i] = datos[i] ^ clave;
        //Deshacer rotacion
        datos[i] = rotacionDerecha(datos[i], posiciones);
    }
}