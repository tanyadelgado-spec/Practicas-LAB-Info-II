#include <iostream>

using namespace std;

/*
//Ejercio 1. Escriba un programa que identifique si un caracter ingresado es una vocal, una consonante o
//              ninguna de las dos e imprima un mensaje segun el caso.

int main(){
    char C;
    cout << "Ingrese un caracter: ";
    cin >> C;

    if ((C >= 'a' && C <= 'z' ) || (C >= 'A' && C <= 'Z')) {
        if (C == 'a' || C == 'e' || C == 'i' || C == 'o' || C == 'u' ||
            C == 'A' || C == 'E' || C == 'I' || C == 'O' || C == 'U'){
            cout << C << " es una vocal." << endl;

        }
        else {
            cout << C << " es una constante." << endl;
        }
    }
    else {
        cout << C << " no es una letra." << endl;

    }
    return 0;
}
*/

/*
//Ejercicio 2.Escriba un programa que determine la combinacion minima de billetes y monedas para una cantidad
//              dada. Los billetes disponibles son: $50.000, $20.000, $10.000, $5.000, $2.000, $1.000; las monedas:
//              500, 200, 100, 50. Si no es posible distribuir la cantidad exacta entre las denominaciones disponibles,
//              mostrar el faltante
int main(){
    int monto, b50, b20, b10, b5, b2, b1, m500, m200, m100, m50, res;

    cout << "Ingrese la cantidad deseada:";
    cin >> monto;
    res=monto;

    b50=res/50000;
    res=res%50000;

    b20=res/20000;
    res=res%20000;

    b10=res/10000;
    res=res%10000;

    b5=res/5000;
    res=res%5000;

    b2=res/2000;
    res=res%2000;

    b1=res/1000;
    res=res%1000;

    m500=res/500;
    res=res%500;

    m200=res/200;
    res=res%200;

    m100=res/100;
    res=res%100;

    m50=res/50;
    res=res%50;

    cout << "50.000 : " << b50 << endl;
    cout << "20.000: " << b20 << endl;
    cout << "10.000: " << b10 << endl;
    cout << "5.000: " << b5 << endl;
    cout << "2.000: " << b2 << endl;
    cout << "1.000: " << b1 << endl;

    cout << "500: " << m500 << endl;
    cout << "200: " << m200 << endl;
    cout << "100: " << m100 << endl;
    cout << "50: " << m50 << endl;

    cout << "Faltante : $" << res << endl;

    return 0;
}
*/

/*
//Ejercicio 3.Escriba un programa que reciba un mes y un dıa e indique si la fecha es valida. Para 29/2, indicar:
//              “es valida en a˜nos bisiestos”

int main(){
    int mes, dia;

    cout << "Ingrese un numero de mes: ";
    cin >> mes;
    cout << "Ingrese un numero de dia: ";
    cin >> dia;

    if (mes<1 || mes>12){
        cout << mes << " es un mes invalido." << endl;
    }
    else{
        int dm;

        switch (mes){
        case 2:
            if (dia==29){
                cout << dia << "/" << mes << " es valido en un año bisiesto." << endl;
            }
            else if(dia>=1 && dia<=28){
                cout << dia << "/" << mes << " es una fecha valida." << endl;
            }
            else{
                cout << dia << "/" << mes << " es una fecha invalida." << endl;
            }
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            dm=30;
            if (dia>=1 && dia<=dm){
                cout << dia << "/" << mes << " es una fecha valida." << endl;
            }
            else{
                cout << dia << "/" << mes << " es una fecha invalida." << endl;
            }
            break;

        default:
            dm=31;
            if (dia>=1 && dia<=dm){
                cout << dia << "/" << mes << " es una fecha valida." << endl;
            }
            else{
                cout << dia << "/" << mes << " es una fecha invalida." << endl;
            }
        }
    }
    return 0;
}
*/

/*
//Ejercicio 4. Escriba un programa que sume dos tiempos en formato HHMM, donde el primer entero representa
//             una hora (p.ej., 1245 = 12:45) y el segundo entero representa una duracion (2570=25 horas y 70
//             minutos). El programa debe imprimir la hora final, que es el resultado de sumar al primer entero
//             la duracion representada por el segundo. El primer entero debe ser una hora valida y debe ser
//             verificada por el programa.
int main(){
    int hora, duracion, h, min, h_d, min_d;

    cout << "Ingrese la hora (HHMM): ";
    cin >> hora;
    cout << "Ingrese la duracion (HHMM): ";
    cin >> duracion;

    //Separo las horas y los minutos
    h = hora/100;
    min = hora%100;
    h_d = duracion/100;
    min_d = duracion%100;

    if (h<0 || h>=23 || min<0 || min>59){
        cout << hora << " es un tiempo invalido." <<endl;
        return 0;
    }

    min+=min_d;
    h+=h_d+min/60;
    min=min%60;

    h=h%24;
    hora=h*100+min;

    cout << "La hora resultante es " << hora << endl;

    return 0;
}
*/

/*
//Ejrcicio 5. Escriba un programa que reciba un numero impar e imprima el patron mostrado a continuacion.I>
int main(){
    int n;

    cout << "Ingrese un numero impar: ";
    cin >> n;

    if(n%2==0){
        cout << "El numero debe ser impar." << endl;
        return 0;
    }

    for (int i=1; i<=n; i+=2 ){
        for (int j=1; j<=i; j++){
            cout << "*";
        }
        cout << endl;
    }

    for (int i=n; i>=1; i-=2){
        for (int j=1; j<=i; j++){
            cout << "*";
        }
        cout << endl;
    }
    return 0;
}
*/

/*
//Ejercicio 6. Escriba un programa que aproxime e segun la serie infinita. El usuario debe ingresar el numero de terminos.
int main(){
    int n;
    double e=0.0, factorial=1.0;

    cout << "Ingrese el numero de terminos: ";
    cin >> n;

    for (int i=0; i<n; i++){
        if (i>0){
            factorial *=i;
        }
        e+=1.0/factorial;
    }
    cout << "e es aproximadamente: " << e << endl;

    return 0;
}
*/

/*
//Ejercicio 7. Escriba un programa que pida al usuario que ingrese un numero N. Sume los pares de la serie de
//              Fibonacci menores a N e imprima el resultado en consola. (0, 1, 1, 2, 3, 5, 8, 13, 21, ...)
int main(){
    int n, a=0, b=1, suma=0, sig;

    cout << "Ingrese un numero: ";
    cin >> n;

    while (a<n) {
        if (a%2==0){
            suma+=a;
        }
        sig=a+b;
        a=b;
        b=sig;
    }
    cout << "El resultado de la suma es: " << suma << endl;

    return 0;
}
*/

/*
//Ejercicio 8. . Escriba un programa que solicite al usuario tres numeros a, b y c. Despues de esto, sume todos
//                  los multiplos de a (ma1, ma2 . . . , man) y b (mb1, mb2 . . . , mbn) menores que c,
//                  sin duplicar aquellos que sean comunes entre ambos.
int main(){
    int a, b, c, suma=0;

    cout << "Ingrese tres numeros: ";
    cin >> a;
    cin >> b;
    cin >> c;

    for (int i=1; i<c; i++){
        if (i%a==0 || i%b==0){
            suma+=i;
            cout << i << "+";
        }
    }

    cout << " = " << suma << endl;


    return 0;
}
*/

/*
//Ejercicio 9. Escriba un programa que reciba un numero N y luego sume los dıgitos de N elevados a sı mismos
//              e imprima el resultado en pantalla
int main(){
    int n, suma=0;

    cout << "Ingrese un numero: ";
    cin >> n;

    while (n>0) {
        int digito=n%10, potencia=1;

        for (int i = 0; i < digito; i++) {
            potencia = potencia*digito;
        }

        suma= suma+potencia;
        n=n/10;
    }
    cout << "El resultado de la suma es: " << suma << endl;

    return 0;
}
*/

/*
//Ejercicio 10. Escriba un programa que reciba un numero N e imprima el enesimo primo
int main(){
    int n, contador=0, numero=1;

    cout << "Ingrese un numero: ";
    cin >> n;

    while (contador<n) {
        numero++;
        bool primo=true;

        for (int i = 2; i < numero; i++) {
            if (numero%i==0){
                primo=false;
                break;
            }
        }
        if (primo){
            contador++;
        }
    }
    cout << "El primo numero " << n << " es: " << numero << endl;

    return 0;
}
*/

/*
//Ejercicio 11. Escriba un programa que reciba un numero N y calcule el MCM de los numeros enteros entre 1 y N
int main(){
    int n, mcm=1;
    bool encontrado=false;

    cout << "Ingrese un numero: ";
    cin >> n;

    while (!encontrado) {
        encontrado=true;

        for (int i = 1; i <= n; i++) {
            if(mcm%i != 0){
                encontrado=false;
                break;
            }
        }
        if(!encontrado){
            mcm++;
        }
    }
    cout << "El minimo comun multiplo es: " << mcm << endl;

    return 0;
}
*/

/*
//Ejercicio 12. Escriba un programa que reciba un numero N y calcule el mayor factor primo de N.
int main(){
    int n, N, mFactor=1;

    cout << "Ingrese un numero: ";
    cin >> n;
    N=n;

    //Verificar 2
    while (N%2==0) {
        mFactor=2;
        N=N/2;
    }

    //Primos impares
    for (int i = 3; i*i <= N; i+=2) {
        while (N%i==0) {
            mFactor=i;
            N=N/i;
        }
    }

    if (N>1){
        mFactor=N;
    }

    cout << "El mayor factor primo de " << n << " es: " << mFactor << endl;

    return 0;
}
*/

/*
//Ejercicio 13.Escriba un programa que reciba un numero N y sume todos los primos menores que N.
int main(){
    int n, suma=0;

    cout << "Ingrese un numero: ";
    cin >> n;

    //Recorrer hasta n
    for (int i = 2; i < n; ++i) {
        bool es_Primo=true;

        //Verificamos divisores de i
        for (int j = 2; j < i; ++j) {
            if (i%j == 0){
                es_Primo=false;
                break;
            }
        }
        if (es_Primo){
            suma+=i;
        }
    }

    cout << "El resultado de la suma es: " << suma << endl;

    return 0;
}
*/

/*
//Ejercicio 14. Escriba un programa que encuentre e imprima el numero palındromo mas grande producto de dos
//              numeros de 3 dıgitos.
int main(){
    int mayor=0, num1=0, num2=0;

    for (int i = 100; i <= 999; ++i) {
        for (int j = i; j <= 999; ++j) {
            int producto=i*j;
            int inicial=producto;
            int invertido=0;

            while (producto>0) {
                int digito=producto%10;

                invertido=invertido*10+digito;
                producto=producto/10;

            }
            if (inicial==invertido){
                if (inicial>mayor){
                    mayor=inicial;
                    num1=i;
                    num2=j;
                }
            }
        }
    }

    cout << "El numero palindromo mas grande es: " << mayor << endl;
    cout << "Es producto de " << num1 << " * " << num2 << endl;



    return 0;
}
*/

/*
//Ejercicio 15. Escriba un programa que reciba un numero N impar y genere la matriz que sigue una espiral segun
//              el ejemplo a continuacion para los valores N = 5 y N = 3
//              Despues de generada la matriz, sume las diagonales (en rojo) e imprima el resultado.
int main (){
    int N;

    cout << "Ingrese un numero N impar: ";
    cin >> N;

    // Verificar que N sea positivo e impar
    if (N <= 0 || N % 2 == 0)
    {
        cout << "El numero debe ser positivo e impar." << endl;
        return 0;
    }

    // Crear la matriz
    int matriz[100][100];

    // Empezamos en el centro de la matriz
    int fila = N / 2;
    int columna = N / 2;

    // El centro contiene el numero 1
    matriz[fila][columna] = 1;

    int numero = 2;

    // Empezamos moviendonos hacia la derecha
    int pasos = 1;

    while (numero <= N * N)
    {
        // Mover hacia la derecha
        for (int i = 0; i < pasos && numero <= N * N; i++)
        {
            columna++;
            matriz[fila][columna] = numero;
            numero++;
        }

        // Mover hacia abajo
        for (int i = 0; i < pasos && numero <= N * N; i++)
        {
            fila++;
            matriz[fila][columna] = numero;
            numero++;
        }

        // Aumentar la cantidad de pasos
        pasos++;

        // Mover hacia la izquierda
        for (int i = 0; i < pasos && numero <= N * N; i++)
        {
            columna--;
            matriz[fila][columna] = numero;
            numero++;
        }

        // Mover hacia arriba
        for (int i = 0; i < pasos && numero <= N * N; i++)
        {
            fila--;
            matriz[fila][columna] = numero;
            numero++;
        }

        // Aumentar la cantidad de pasos
        pasos++;
    }

    // Imprimir la matriz
    cout << "\nMatriz en espiral:\n";

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matriz[i][j] << "\t";
        }

        cout << endl;
    }

    // Sumar las diagonales
    int suma = 0;

    for (int i = 0; i < N; i++)
    {
        // Diagonal principal
        suma = suma + matriz[i][i];

        // Diagonal secundaria
        suma = suma + matriz[i][N - 1 - i];
    }

    // El centro se sumo dos veces
    suma = suma - matriz[N / 2][N / 2];

    cout << "\nEl resultado de la suma de las diagonales es: "
         << suma << endl;

    return 0;
}
*/

/*
//Ejercicio 16. Sea n ∈ N. Definimos la sucesion de Collatz C(n) como:
//              Escriba un programa que reciba un valor j y calcule las series de Collatz para todas las semillas
//              N < j. Encuentre la semilla que genera la serie de Collatz mas larga y cuantos terminos m tiene.
//              Imprima dicha serie de Collatz, la semilla y la cantidad de terminos.
int main(){
    long long j;

    cout << "Ingrese el valor de j: ";
    cin >> j;

    long long semillaMayor = 0;
    int mayorTerminos = 0;

    // Arreglo para guardar la serie mas larga
    long long mejorSerie[10000];

    // Probar todas las semillas N menores que j
    for (long long N = 1; N < j; N++)
    {
        long long C = N;
        int terminos = 1;

        // Arreglo temporal para la serie de la semilla actual
        long long serie[10000];

        // Guardar el primer termino C0 = N
        serie[0] = C;

        // Generar la serie hasta llegar a 1
        while (C != 1)
        {
            if (C % 2 == 0)
            {
                C = C / 2;
            }
            else
            {
                C = 3 * C + 1;
            }

            serie[terminos] = C;
            terminos++;
        }

        // Comparar con la serie mas larga encontrada
        if (terminos > mayorTerminos)
        {
            mayorTerminos = terminos;
            semillaMayor = N;

            // Copiar la serie actual
            for (int i = 0; i < terminos; i++)
            {
                mejorSerie[i] = serie[i];
            }
        }
    }

    // Imprimir la semilla
    cout << "\nLa semilla es: " << semillaMayor << endl;

    // Imprimir cantidad de terminos
    cout << "La cantidad de terminos es: "
         << mayorTerminos << endl;

    // Imprimir la serie
    cout << "La serie de Collatz es: " << endl;

    for (int i = 0; i < mayorTerminos; i++)
    {
        cout << mejorSerie[i];

        if (i < mayorTerminos - 1)
        {
            cout << " -> ";
        }
    }

    cout << endl;

    return 0;
}
*/

/*
//Ejercicio 17. Escriba un programa que pida al usuario un numero k y encuentre e imprima el primer numero
//              triangular con al menos k divisores. El enesimo triangular es n(n + 1)/2.
int main(){
    int k, n=1, divisores;
    long long triangular;

    cout << "Ingrese un numero: ";
    cin >> k;

    while (true) {
        triangular=(long long)n*(n+1)/2;
        divisores=0;

        for (long long i = 1; i*i <= triangular; ++i) {

            if (triangular%i==0){
                divisores++;

                if(i != triangular/i){
                    divisores++;
                }
            }

        }
        if (divisores>=k){
            cout << "El numero es: " << triangular << ", que tiene " << divisores << " divisores." << endl;
            break;
        }
        n++;
    }

    return 0;
}
*/
