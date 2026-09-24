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
    descomprimido.clear();
    int n = enigma.length(); // numero de pares encriptados

    for(int i = 0; i < n - 1; i+=2){
        char letra = enigma[i];
        int repeticiones = enigma[i+1] - '0';
        descomprimido.append(repeticiones, letra);  //Guardar la cadena descomprimida
    }

    return descomprimido;
}


