#include <iostream>
#include <integracion.h>
#include <LZ78.h>
using namespace std;

int main(){

    int opcion, posiciones;;
    string direccion, archivoFinal;
    unsigned char clave = 'K';

    while(true){
        //Menu
        cout << "-_-_-_- Compresion de Archivos -_-_-_-\n";
        cout <<"1.RLE\n";
        cout <<"2.LZ78\n";
        cout <<"3. Salir\n";
        cout << "\nIngrese una opcion: ";
        cin >> opcion;
        if(opcion == 3) break;


        //Direcciones de los archivos
        cout << "Ingrese la direccion del archivo a comprimir:\n";
        cin >> direccion;

        cout << "Ingrese la direccion del archivo donde se guardara el resultado:\n";
        cin >> archivoFinal;


        //Posiciones para la encriptacion
        do{
            cout << "Ingrese el numero de posiciones a rotar (1-7) para la encriptacion: ";
            cin >> posiciones;

            if(posiciones < 1 || posiciones > 7){
                cout << "Elije un valor entre 1 y 7.\n";
            }

        }while(posiciones < 1 || posiciones > 7);

        //Casos de compresion
        switch (opcion){

        case 1: //5.1 Compresion y descompresion RLE

            cout << "-_-_- Compresion con RLE -_-_-\n";
            ejecutarRLE(direccion, archivoFinal, posiciones, clave);
            break;

        case 2: //5.2 Compresion y descompresion LZ78

            cout << "-_-_- Compresion con LZ78 -_-_-\n";
            //ejecutarLZ78(direccion, archivoFinal, posiciones, clave);

            break;

        default:
            cout << "Opcion invalida" << endl;
            break;}
        }


    cout << "\nSalida exitosa.\n";
    return 0;
}

/*
    switch (opcion){

    case 1 :{
    //5.1 Compresion y descompresion RLE
    string cadena;
    cout << "Ingrese la cadena a comprimir: " << endl;
    cin >> cadena;
    string compressed = comprimir_RLE(cadena);
    string original = descomprimir_RLE(compressed);

    cout << "La cadena comprimida es : \n" << compressed << endl;

    cout << "La cadena descomprimida es : \n" << original << endl;

    break;
    }
    //---------------------
    case 2 :{
        char cadena[1000];
        cout << "Ingrese la cadena a comprimir : " << endl;
        cin >> cadena ;
        int* lista_prefi = nullptr;
        char* lista_cade = nullptr;
        int num_parejas = 0;

        compresion_LZ78(cadena,lista_prefi, lista_cade, num_parejas);

        //se muestra el par (indice, caracter)
        for(int i = 1; i < num_parejas; i++){
            cout << "Se agrego al diccionario : (" << lista_prefi[i] << ", "<< lista_cade[i] <<"), " << endl ;
        }

        delete[] lista_prefi;
        delete[] lista_cade;

        break;
    }

    default :{
        cout << "Opcion invalida" << endl;
    }
    break;
    }
*/

