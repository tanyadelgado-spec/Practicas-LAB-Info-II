#ifndef DESENCRIPTACION_H
#define DESENCRIPTACION_H

class desencriptacion
{
public:
    desencriptacion();
};

//void mostrarByte(unsigned char byte, const string& mensaje);
unsigned char rotacionIzquierda(unsigned char byte, int posiciones);
unsigned char rotacionDerecha(unsigned char byte, int posiciones);
void encriptar(unsigned char *datos, int cantidad, int posiciones, unsigned char clave);
void desencriptar(unsigned char *datos, int cantidad, int posiciones, unsigned char clave);


#endif // DESENCRIPTACION_H
