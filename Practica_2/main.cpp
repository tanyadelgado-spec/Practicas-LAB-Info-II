#include <iostream>
#include <cstring>

using namespace std;

/*Ejercicio 1. Desarrolle un programa que permita determinar la mınima combinacion de billetes y monedas para
una cantidad de dinero determinada. Los billetes en circulacion son de $50.000, $20.000, $10.000,
$5.000, $2.000 y $1.000, y las monedas son de $500, $200, $100 y $50. Si por medio de los billetes
y monedas disponibles no se puede lograr la cantidad deseada, el sistema deber´a decir lo que resta
para lograrla. Use arreglos y ciclos para realizar el programa.
*/
/*
int main(){
    int dinero[10] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50};
    int cantidad, resto;

    cout << "Ingrese la cantidad de dinero: ";
    cin >> cantidad;

    resto = cantidad;

    for (size_t i = 0; i < size(dinero); ++i) {
        int cantD = resto / dinero[i];

        cout << dinero[i] << ": " << cantD << endl;
        resto = resto % dinero[i];

    }
    cout << "Faltante: " << resto;

    return 0;
}
*/

/*Ejercicio 3. Esciba un programa que compare 2 cadenas de caracteres y retorne verdadero si son iguales y falso
en caso contrario. Utilice arreglos de char. Tenga en cuenta la longitud del arreglo y el caracter
que indica la finalizacion de una cadena de caracteres.
*/
/*
//Funcion para pasar un caracter en mayuscula a minuscula
char minusculas (char C){
    if(C >='A' && C<='Z'){
        C=C+('a'-'A');
    }
    return C;
}

int main(){
    char cad_1[80];
    char cad_2[80];
    bool igual=false;

    //Apuntadores
    char *ptr1=cad_1;
    char *ptr2=cad_2;

    cout << "Ingrese la primer cadena: ";
    cin.getline(cad_1, 80);
    cout << "Ingrese la segunda cadena: ";
    cin.getline(cad_2, 80);

    //Recorre los apuntadores para pasar de mayusculas a minusculas
    for (size_t i = 0; i < strlen(cad_1); ++i) {
        ptr1[i] = minusculas(ptr1[i]);
    }
    for (size_t i = 0; i < strlen(cad_2); ++i) {
        ptr2[i] = minusculas(ptr2[i]);
    }

    //Evalua que ninguna de las dos cadenas haya llegado al final y que ambos caracteres sean iguales
    while (*ptr1 != '\0' && *ptr2 != '\0' && *ptr1 == *ptr2) {
        ptr1++;
        ptr2++;
    }

    if (*ptr1 == *ptr2){
        igual = true;
    }

    cout << boolalpha << igual;

    return 0;
}
*/

/*Ejercicio 5. Haga una funcion que reciba un numero entero (int) y lo convierta a cadena de caracteres. Use
parametros por referencia para retornar la cadena. Escriba un programa de prueba que utilice dicha funcion.
*/
/*
void convertir (int num, char (&cadena)[50]){
    int i = 0;

    //Para el 0
    if (num == 0){
        cadena[0]='0';
        cadena[1] = '\0';
        return;
    }

    //Para negativos
    if (num < 0){
        cadena[i] = '-';
        i++;
        num = -num;
    }

    int inicio = i;

    //Extraer digitos
    while (num > 0){
        int digito = num % 10;
        //Convertir a caracter correspondiente
        cadena[i] = digito + '0';
        i++;
        num = num / 10;
    }
    cadena[i] = '\0';

    //Invertir caracteres
    int final = i - 1;

    while (inicio < final) {
        char trans = cadena[inicio];
        cadena[inicio] = cadena[final];
        cadena[final] = trans;

        inicio++;
        final--;
    }

}

int main(){
    int numero;
    char cadena[50];

    cout << "Ingrese numero entero: ";
    cin >> numero;

    convertir(numero, cadena);
    cout << "El numero convertido a cadena es: " << cadena << endl;

    return 0;
}
*/

/*Ejercicio 7. Escriba un programa que reciba una cadena de caracteres y elimine los caracteres repetidos.
Por ejemplo, si se recibe ”bananas”, debe mostrar ”bans”.
*/
/*
int main(){
    char inicial[50], cadena[50];

    cout << "Ingrese una cadena: ";
    cin.getline(inicial, 50);

    char *ptr = inicial;
    char *c = cadena;

    //Copiar caracter a caracter
    while (*ptr != '\0') {
        *c = *ptr;
        c++;
        ptr++;
    }
    *c = '\0';

    ptr = cadena;

    while (*ptr != '\0') {
        //Revisar caracteres anteriores, ptr recorre cada posicion y c se reinicia en cada vuelta para comparar
        //con los anteriores
        char *c = cadena;
        bool repetido = false;

        //Verificamos si está repetido
        while (c < ptr) {
            if (*c == *ptr){
                repetido = true;
            }
            c++;
        }

        //Eliminar en caso de estar repetido el caracter
        if(repetido){
            char *r = ptr;

            //Desplazar el caracter repetido copiando los caracteres posteriores
            while (*r != '\0') {
                *r = *(r+1);
                r++;

            }
        }
        else{
            ptr++;
        }
    }
    cout << "Original: " << inicial << ". Sin repetidos: " << cadena << "." << endl;

    return 0;
}
*/

/*Ejercicio 9. Escribir un programa que reciba un numero n y una cadena de caracteres numericos; el programa
debe separar la cadena de caracteres en grupos de n cifras, sumarlos e imprimir el resultado. En
caso de no poder dividirse exactamente en grupos de n cifras, se debe rellenar con ceros a la
izquierda del primer numero.
*/
/*
int main(){
    int n;
    char cadena[50];

    cout << "Ingrese un numero: ";
    cin >> n;
    //Para pasar de un cin a cin.getline y que no se tome '\n' como finalizacion de la cadena
    cin.ignore();
    cout << "Ingrese una cadena de caracteres numericos: ";
    cin.getline(cadena, 50);

    //Recorrer cadena para hallar cantidad cifras
    int longitud = 0;
    char *ptr = cadena;

    while (*ptr != '\0') {
        longitud++;
        ptr++;
    }

    //Ceros que se requieren
    int ceros = (n - (longitud % n)) % n;
    int sum=0;
    ptr=cadena;

    //Primer grupo, convertir caracter a numero (*ptr - '0')
    int cifras_1 = n - ceros;
    int numero = 0;

    for (int i = 0; i < cifras_1; ++i) {
        numero = numero * 10 +(*ptr - '0');
        ptr++;
    }
    sum += numero;

    //Demas grupos
    while (*ptr != '\0') {
        numero = 0;
        for (int i = 0; i < n; ++i) {
            numero = numero * 10 +(*ptr - '0');
            ptr++;
        }
        sum += numero;
    }

    cout << "Original: " << cadena << "." << endl;
    cout << "Suma: " << sum << "." << endl;

    return 0;
}
*/

/*Ejercicio 11. Escriba un programa que permita manejar las reservas de asientos en una sala de cine. Los asientos
de la sala de cine estan organizados en 15 filas con 20 asientos cada una. El programa debe mostrar
una representacion de la sala que indique que asientos estan disponibles y cuales se encuentran
reservados. Ademas, debe permitir realizar reservas o cancelaciones al ingresar a la fila (letras
A-O) y el numero del asiento (numeros 1-20).
 */

int main(){
    char sala[15][20];

    //Inicilizar la sala
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 20; ++j) {
            sala [i][j] = '-';
        }
    }

    int op, asiento, f;
    char fila;
    do{
        cout << "\n****** SALA DE CINE ******" << endl;
        cout << "1. Mostrar sala" << endl;
        cout << "2. Reservar asiento" << endl;
        cout << "3. Cancelar reserva" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> op;

        switch (op) {
        case 1:
            //Asientos 1-20
            cout << "\n   ";
            for (int j = 1; j <= 20; ++j) {
                cout << j << "  ";
            }
            cout << endl;

            //filas A-0
            for (int i = 0; i < 15; ++i) {
                //Pasamos j al equivalente en char
                cout << char('A' + i) << "  ";

                char *ptr = sala [i];
                for (int j = 0; j < 20; ++j) {
                    if(j < 9){
                        cout << *ptr << "  ";
                    }
                    else{
                        cout << *ptr << "   ";
                    }
                    ptr++;

                }
                cout << endl;
            }
            break;

        case 2:
            cout << "Ingrese la fila (A-O): ";
            cin >> fila;
            cout << "Ingrese el numero del asiento (1-20): ";
            cin >> asiento;

            f = fila - 'A';
            if (f >= 0 && f < 15 && asiento >= 1 && asiento <= 20){
                char *ptr= &sala[f][asiento - 1];

                if (*ptr == '-'){
                    *ptr = '+';
                    cout << "Reserva realizada correctamente." << endl;
                }
                else{
                    cout << "El asiento ya esta reservado." << endl;
                }
            }
            else{
                cout << "La fila o el asiento no valido." << endl;
            }

            break;

        case 3:
            cout << "Ingrese la fila (A-O): ";
            cin >> fila;
            cout << "Ingrese el numero del asiento (1-20): ";
            cin >> asiento;

            f = fila - 'A';
            if (f >= 0 && f < 15 && asiento >= 1 && asiento <= 20){
                char *ptr= &sala[f][asiento - 1];

                if (*ptr == '+'){
                    *ptr = '-';
                    cout << "Reserva cancelada correctamente." << endl;
                }
                else{
                    cout << "El asiento no estaba reservado." << endl;
                }
            }
            else{
                cout << "La fila o el asiento no valido." << endl;
            }
            break;

        case 4:
            cout << "Hasta pronto." << endl;
            break;

        default:
            cout << "Opcion no valida.";
            break;
        }

    } while (op != 4);

    return 0;
}


/*Ejercicio 13. Se tiene una fotografıa digitalizada de una porcion de la galaxia NGC 1300 que esta ubicada a
61.000.000 de años luz del planeta Tierra. La representacion digital de la imagen esta constituida
por una matriz de numeros enteros, en la cual cada uno representa la cantidad de luz en ese punto
de la imagen.
Elabore y pruebe una funcion que reciba un puntero a la matriz de enteros como argumento y que
retorne el numero de estrellas encontradas en la imagen. Ignore las estrellas que puedan existir en
los bordes de la matriz.
 */
/*
int contar_Estrellas(int (*ptr)[8], int filas){
    int estrellas = 0;

    //Recorremos la matriz, omitiendo los bordes
    for (int i = 1; i < filas - 1; ++i) {
        for (int j = 1; j < 7; ++j) {
            double promedio = (ptr[i][j] +
                            ptr[i][j-1] +
                            ptr[i][j+1] +
                            ptr[i-1][j] +
                            ptr[i+1][j]) / 5.0;

            if (promedio > 6){
                estrellas++;
            }
        }
    }
    return estrellas;
}

int main(){
    int matriz[6][8] = { {0, 3, 4, 0, 0, 0, 6, 8},
                         {5, 13, 6, 0, 0, 0, 2, 3},
                         {2, 6, 2, 7, 3, 0, 10, 0},
                         {0, 0, 4, 15, 4, 1, 6, 0},
                         {0, 0, 7, 12, 6, 9, 10, 4},
                         {5, 0, 6, 10, 6, 4, 8, 0} };

    int estrellas = contar_Estrellas(matriz, 6);
    cout << "Numero de estrellas encontradas: " << estrellas << endl;

    return 0;
}
*/

/*Ejercicio 15. Elabore un programa que permita hallar la interseccion entre un par de rectangulos. Represente
los rectangulos como arreglos de 4 datos de la siguiente manera:
(a) Los primeros 2 datos corresponden a las coordenadas de la esquina superior izquierda del
rectangulo (x,y).
(b) Los siguientes 2 datos representan el ancho y la altura del rectangulo.
Esto se representa en la Figura 3a. Tenga en cuenta que los valores en el eje vertical aumentan
hacia abajo y en el eje horizontal aumentan hacia la derecha.
El programa debe recibir 2 arreglos que representen los rectangulos A y B. Por referencia, debe
retornar un rectangulo C (con la misma estructura descrita anteriormente) que corresponda a la
interseccion entre A y B. rectangulo = {x, y, ancho, alto}
 */
/*
//Es void para modificar los valores de C directamente
void interseccion(int A[], int B[], int C[]){
    //Coordenada x de interseccion
    if (A[0] > B[0])
        C[0] = A[0];
    else
        C[0] = B[0];

    //Coordenada y de interseccion
    if (A[1] > B[1])
        C[1] = A[1];
    else
        C[1] = B[1];

    //Desplazamiento en x
    int horizontal_A = A[0] + A[2];
    int horizontal_B = B[0] + B[2];

    //Desplazamiento en y
    int vertical_A = A[1] + A[3];
    int vertical_B = B[1] + B[3];

    //Ancho de intrseccion
    int ancho;
    if (horizontal_A < horizontal_B)
        ancho = horizontal_A;
    else
        ancho = horizontal_B;

    C[2] = ancho - C[0];

    //Alto de la interseccion
    int alto;
    if (vertical_A < vertical_B)
        alto = vertical_A;
    else
        alto = vertical_B;

    C[3] = alto - C[1];

}

int main(){
    int A[4], B[4], C[4];

    cout << "Ingrese los valores del rectangulo A:" << endl;
    cout << "Coordenada en x: ";
    cin >> A[0];
    cout << "Coordenada en y: ";
    cin >> A[1];
    cout << "Ancho: ";
    cin >> A[2];
    cout << "Alto: ";
    cin >> A[3];

    cout << "\nIngrese los datos del rectangulo B:" << endl;
    cout << "Coordenada en x: ";
    cin >> B[0];
    cout << "Coordenada en y: ";
    cin >> B[1];
    cout << "Ancho: ";
    cin >> B[2];
    cout << "Alto: ";
    cin >> B[3];

    interseccion(A, B, C);

    cout << "\nInterseccion de los rectangulos A y B: {";

    for (int i = 0; i < 4; ++i) {
        cout << C[i];

        if (i < 3)
            cout << ",";
    }
    cout << "}" << endl;

    return 0;
}
*/

/*Ejercicio 17. Dos numeros a y b (con a ̸= b) son amigables si la suma de los divisores de a (excluyendose a sı
mismo) es igual a b, y al sumar los divisores de b el resultado es a. Ej.: los divisores de 220 son
1, 2, 4, 5, 10, 11, 20, 22, 44, 55 y 110; y suman 284. Los divisores de 284 son 1, 2, 4, 71 y 142 y
suman 220. Entonces, 220 y 284 son amigables. Escriba un programa que reciba un numero y halle
la suma de todos los numeros amigables menores al numero ingresado.
 */
/*
int main(){
    int n;
    cout << "Ingrese un numero: ";
    cin >> n;

    //Asignamos los valores menores a n al arreglo
    int numeros[1000];
    for (int i = 0; i < n; ++i) {
        numeros[i] = i;
    }

    int *ptr = numeros;
    int resultado = 0;

    //Recorrer arreglo con ptr
    for (int i = 1; i < n; ++i) {

        //Divisores de 1er numero (A)
        int suma_A=0;
        for (int j = 1; j < i; ++j) {
            if (*(ptr + i) % j == 0)
                suma_A += j;
        }

        //Virificar A!=B y divisores de B
        int B = suma_A;
        if (B != i && B > 0){
            int suma_B = 0;

            for (int j = 1; j < B; ++j) {
                if (B % j == 0)
                    suma_B += j;
            }

            //Son amigables si
            if (suma_B == i)
                resultado += *(ptr + i);
        }
    }
    cout << "El resultado de la suma es: " << resultado << endl;

    return 0;
}
*/
