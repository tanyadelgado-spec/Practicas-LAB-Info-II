#ifndef INTEGRACION_H
#define INTEGRACION_H

#include <iostream>
#include <string>

using namespace std;

class integracion
{
public:
    integracion();
};

string leerArchivoRLE(const string &direccion);
void guardarArchivoRLE(const string &direccion, const string &texto);
bool verificarRLE(const string &original, const string &recuperado);
void ejecutarRLE(const string &direccion, const string &archivoFinal, int posiciones, unsigned char clave);
char *leerArchivoLZ78(const char *direccion, int &tamanio);
void guardarArchivoLZ78(const char *direccion, const char *texto, int tamanio);
bool verificarLZ78(const char *original, const char *recuperado, int tamanio);


#endif // INTEGRACION_H
