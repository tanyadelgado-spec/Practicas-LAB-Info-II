#ifndef LZ78_H
#define LZ78_H

//Funcion para comprimir datos con el sistema LZ78
void compresion_LZ78(const char* cadena, int*& lista_prefijos, char*& lista_cadenas, int &nparejas);

//Funcion para descomprimir con el sistema LZ78
void descompresion_LZ78();

//Funcion para buscar una cadena dentro del diccionario
int buscar(int* dic_prefijos, char* dic_cadenas, int tamanio, int prefijo, char lbuscada);

//Funcion para agrandar el diccionario
void agrandar_dicc(int& capacidad, int*& lista_prefijos, char*& lista_cadenas);

#endif // LZ78_H
