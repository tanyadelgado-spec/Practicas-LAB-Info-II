#include "RLE.h"
#include <bitset>
#include <iostream>
#include <fstream>  // libreria para leer archivos
#include <string>
using namespace std;


string comprimir_RLE(const string& codigo){
    string comprimido;
    int n = codigo.length();

    for(int i = 0; i < n; i++){
        int repeticion =1;
        while(i < n - 1 && codigo[i] == codigo[i+1]){
            repeticion++;
            i++;
        }
        //Guardar el caracter y su contador
        comprimido += codigo[i];
        comprimido += to_string(repeticion);
    }

    return comprimido;
}

string descomprimir_RLE(const string& enigma){
    string descomprimido="";
    int n = enigma.length(); // numero de pares encriptados
    int i = 0;

    while (i < n) {
        char letra = enigma[i]; // Tomamos el carácter
        i++;

        // Reconstruimos el número completo dígito por dígito si tiene más de una cifra
        string numeroStr = "";
        while (i < n && isdigit(enigma[i])) {
            numeroStr += enigma[i];
            i++;
        }

        // Convertimos el string numérico acumulado a un entero
        int repeticiones = 0;
        for (char digito : numeroStr) {
            repeticiones = repeticiones * 10 + (digito - '0');
        }

        //  Añadimos la letra la cantidad exacta de veces al texto final
        if (repeticiones > 0) {
            descomprimido.append(repeticiones, letra);
        }
    }

    return descomprimido;
}


