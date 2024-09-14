#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FIL 4  //filas
#define COL 4  //columnas
#define LIM 3  //limites del tablero
#define FIN 10 // fin del bucle (tableros)

void LlenaTalero(int tablero[FIL][COL]);
void elegirDificultad(int *opdif, int *dif);
void intercambiaPosiciones(int tablero[FIL][COL], int *fila_vacia, int *columna_vacia, int dificultad);
void funcApuestaMovimientos(int *apMov);
void imprimeTablero(int tablero [FIL][COL]);
void realizaMovimientos(char mov, int tablero[FIL][COL], int *filv, int *colv, int *movJugador);
int compruebaEstadoTablero(int tablero[FIL][COL]);
void muestraPuntajesApuestas(int *movJug, int *apMov, int *puntosPartida);
void guardaApuestasPuntajes(int puntaje[FIN], int apuesta[FIN], int mov[FIN], int *puntosPartida, int *apuestaMovimientos, int *movimientosJugador, int *x);
void HistApuestasPuntajes(int *x, int apuesta[FIN], int movimientos[FIN], int puntaje[FIN]);
void seguirJugando(int *cierre, char *seguirJugando);

int main() {

    int cierre;

    int x = 0;
    int puntaje[FIN]={0};
    int apuesta[FIN]={0};
    int movimientos[FIN]={0};

    int opciones_dificultad=0;  //opcion agregada (linea 47 hasta 71)
    int dificultad=0;

    printf("Bienvenido al solitario del 15!");  //antes se repetia en el bucle si seguia jugando.

    for(cierre = 0; cierre < FIN; cierre++){

        int tablero[FIL][COL], i, j;
        int fila_vacia = LIM;
        int columna_vacia = LIM;
        int movimientos_jugador = 0;
        int apuesta_movimientos = 0;

        int puntos_partida = 0;

        char seguir_jugando;

        srand(time(NULL));// generador de numeros aleatorios


        LlenaTalero(tablero);

        elegirDificultad(&opciones_dificultad, &dificultad);

        intercambiaPosiciones(tablero, &fila_vacia, &columna_vacia, dificultad);

        funcApuestaMovimientos(&apuesta_movimientos);

        while (1) {

            printf("\nMovimientos: %i.\n",movimientos_jugador);

        //tablero
            imprimeTablero(tablero);

        // Leer movimiento del jugador
            char movimiento;

            printf("Ingresa una direccion (w/a/s/d para mover o Q para salir): ");
            scanf(" %c", &movimiento);

            system ("cls");

        // Realizar el movimiento del jugador
            realizaMovimientos(movimiento, tablero, &fila_vacia, &columna_vacia, &movimientos_jugador);

        // Comprobar si se ha ganado el juego
            if (compruebaEstadoTablero(tablero)) {   //algoritmo nuevo con retorno, por eso lo uso directamente en la validacion. algoritmo viejo comentado arriba.
                printf("\nGanaste el juego!\n");
                printf("\nMovimientos totales: %i.\n",movimientos_jugador);

        //vuelvo a mostrar tablero, pero terminado.
            imprimeTablero(tablero);

        //mostrar puntaje obtenido
            muestraPuntajesApuestas(&movimientos_jugador, &apuesta_movimientos, &puntos_partida);

            break; // Salir del bucle si se ordena el tablero.
            }

        }
    //guardo apuestas y puntajes en arreglos.
        guardaApuestasPuntajes(puntaje, apuesta, movimientos, &puntos_partida, &apuesta_movimientos, &movimientos_jugador, &x);

    //mostrar historial de apuestas  y puntajes. (muy importante la condicion del for)
        HistApuestasPuntajes(&x, apuesta, movimientos, puntaje);

        //Quedarse/salir del juego.
        seguirJugando(&cierre, &seguir_jugando);

    }//cierre de bucle for que permite jugar 10 veces pero todavía no corta, DATO: si tocan q sale del todo.

    printf("\nGracias por jugar :)\nAtte: Juli.");

    return 0;
}

LlenaTalero(int tablero[FIL][COL]){

    // Llenar el tablero del 1 al 15 en orden incrementando el contador "valor=1"
        int valor = 1, i, j;

        for (i = 0; i < FIL; i++) {
            for (j = 0; j < COL; j++) {  //FIL*COL = 16 -> posicion 16 vale 0
                tablero[i][j] = valor;
                valor++;
            }
        }
}

void elegirDificultad(int *opdif, int *dif){

        printf("\nCon que dificultad queres empezar?");
        printf("\n1:Facil.\n2:Intermedio.\n3:Dificil.\n4:Rompecocos.");
        printf("\n>");
        scanf("%i",opdif);

        while(*opdif < 1 || *opdif > 4){
            printf("\nPor favor utilizar alguna de las opciones presentadas.");
            printf("\n1:Facil.\n2:Intermedio.\n3:Dificil.\n4:Rompecocos.");
            printf("\n>");
            scanf("%i",opdif);
        }

        if(*opdif == 1){
            *dif = 5;
        }
        else if(*opdif == 2){
            *dif= 120;
        }
        else if(*opdif == 3){
            *dif = 300;
        }
        else if(*opdif == 4){
            *dif = 1000;
        }
}

void intercambiaPosiciones(int tablero[FIL][COL], int *fila_vacia, int *columna_vacia, int dificultad){
    int i;
    for (i = 0; i < dificultad; i++) {
        int movimiento = rand() % 4;

        switch (movimiento) {
            case 0: // Mover arriba
                if (*fila_vacia < LIM) {
                    tablero[*fila_vacia][*columna_vacia] = tablero[*fila_vacia + 1][*columna_vacia];
                    tablero[*fila_vacia + 1][*columna_vacia] = 0;
                    (*fila_vacia)++;
                }
                break;
            case 1: // Mover abajo
                if (*fila_vacia > 0) {
                    tablero[*fila_vacia][*columna_vacia] = tablero[*fila_vacia - 1][*columna_vacia];
                    tablero[*fila_vacia - 1][*columna_vacia] = 0;
                    (*fila_vacia)--;
                }
                break;
            case 2: // Mover izquierda
                if (*columna_vacia < LIM) {
                    tablero[*fila_vacia][*columna_vacia] = tablero[*fila_vacia][*columna_vacia + 1];
                    tablero[*fila_vacia][*columna_vacia + 1] = 0;
                    (*columna_vacia)++;
                }
                break;
            case 3: // Mover derecha
                if (*columna_vacia > 0) {
                    tablero[*fila_vacia][*columna_vacia] = tablero[*fila_vacia][*columna_vacia - 1];
                    tablero[*fila_vacia][*columna_vacia - 1] = 0;
                    (*columna_vacia)--;
                }
                break;
        }
    }
}

void funcApuestaMovimientos(int *apMov){

        printf("En cuantos movimientos (entre 40 y 200) apostas que podes resolver el puzzle?\n>");
        scanf("%i",apMov);

        while(*apMov <40 || *apMov >200){

            printf("\n\nApuesta no valida, por favor ingresa una apuesta valida (entre 40 y 200).\n");
            printf("En cuantos movimientos apostas que podes resolver el puzzle?\n>");
            scanf("%i",apMov);

        }
}

void imprimeTablero(int tablero[FIL][COL]){

    int i,j;
    printf("\n");
    for (i = 0; i < FIL; i++) {
        for (j = 0; j < COL; j++) {
            if (tablero[i][j] == 0) {
                    printf("[  ]");
            }
            else {
                printf("[%2d]", tablero[i][j]);
            }
        }
        printf("\n");
    }
}

void realizaMovimientos(char mov, int tablero[FIL][COL], int *filv, int *colv, int *movJugador) {
    switch (mov) {
        case 'w': case 'W': // arriba
            if (*filv < LIM) {
                tablero[*filv][*colv] = tablero[*filv + 1][*colv];
                tablero[*filv + 1][*colv] = 0;
                (*filv)++;
                (*movJugador)++;
            }
            break;
        case 'a': case 'A': // izquierda
            if (*colv < LIM) {
                tablero[*filv][*colv] = tablero[*filv][*colv + 1];
                tablero[*filv][*colv + 1] = 0;
                (*colv)++;
                (*movJugador)++;
            }
            break;
        case 's': case 'S': // abajo
            if (*filv > 0) {
                tablero[*filv][*colv] = tablero[*filv - 1][*colv];
                tablero[*filv - 1][*colv] = 0;
                (*filv)--;
                (*movJugador)++;
            }
            break;
        case 'd': case 'D': // derecha
            if (*colv > 0) {
                tablero[*filv][*colv] = tablero[*filv][*colv - 1];
                tablero[*filv][*colv - 1] = 0;
                (*colv)--;
                (*movJugador)++;
            }
            break;
        case 'Q': case 'q': // salir del juego
            printf("Juego abandonado!\n");
            exit(0);
        default:
            printf("Movimiento no valido\n");
    }
}


//me descoqué al pedo.
int compruebaEstadoTablero(int tablero[FIL][COL]){

            int i, j, contador = 0;

            int tableroAuxiliar[FIL][COL] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};

            for (i = 0; i < FIL; i++) {
                for (j = 0; j < COL; j++) {

                    if (tablero[i][j] == tableroAuxiliar[i][j]) { //se evalua 16 veces.
                        contador ++; //si cuenta que el tablero del juego tiene los valores iguales a uno ordenado, entonces incrementa.
                    }
                }

            }
            if(contador==16){ //si incrementa 16 veces, entonces todas las pos coinciden y estan ordenadas.

                //printf("ACA DEBERIA SER 16 : %i",contador);
                return 1;
            }
            else{

                //printf("ACA DEBERIA SER != 15 : %i",contador);
                contador = 0;
                return 0;
            }
}

void muestraPuntajesApuestas(int *movJug, int *apMov, int *puntosPartida){

            if(*movJug == *apMov){

                *puntosPartida = 1000;

                printf("\n\nFelicidades, obtuviste %i puntos por cumplir con tu apuesta de movimientos.\n",*puntosPartida);
                printf("\nApuesta: %i. \nMovimientos: %i.\n",*apMov,*movJug);

            }
            else if(*movJug < *apMov && *movJug > (*apMov - 10) ){

                *puntosPartida = 1200;

                printf("\n\nFelicidades, obtuviste %i puntos por superar tu apuesta de movimientos.\n",*puntosPartida);
                printf("\nApuesta: %i. \nMovimientos: %i\n",*apMov,*movJug);

            }
            else if(*movJug > *apMov && *movJug <(*apMov + 10) ){

                *puntosPartida = 500;

                printf("\n\nFelicidades, obtuviste %i puntos, estuviste cerca de cumplir tu apuesta :).\n",*puntosPartida);
                printf("\nApuesta: %i. \nMovimientos: %i\n",*apMov,*movJug);

            }
            else if(*movJug < (*apMov-10)){

                *puntosPartida = 1500;

                printf("\n\nSuperaste con creces tu apuesta! toma tus merecidos %i puntos.\n",*puntosPartida);
                printf("\nApuesta: %i. \nMovimientos: %i\n",*apMov,*movJug);
            }
            else{

                *puntosPartida = 0;

                printf("\n\nNo conseguiste acercarte a tu apuesta, pero podes seguirlo intentando!\n");
                printf("\nApuesta: %i. \nMovimientos: %i\n",*apMov,*movJug);

            }

}

void guardaApuestasPuntajes(int puntaje[FIN], int apuesta[FIN], int mov[FIN], int *puntosPartida, int *apuestaMovimientos, int *movimientosJugador, int *x){

        puntaje[*x] = *puntosPartida;
        apuesta[*x] = *apuestaMovimientos;
        mov[*x] = *movimientosJugador;
        (*x)++;
}

void HistApuestasPuntajes(int *x, int apuesta[FIN], int movimientos[FIN], int puntaje[FIN]){
        int i;
        if(*x>1){//evito mostrar en primera vuelta.

            for(i=0; i < *x ;i++){

                printf("\nHistorial de apuestas (partida %i):\n",i+1);

                printf("\n>Apuesta: %i.\n",apuesta[i]);

                printf("\n>Resultado: %i.\n",movimientos[i]);

                printf("\n>Puntaje: %i.\n",puntaje[i]);
            }
        }
}

void seguirJugando(int *cierre, char *seguirJugando){

        if(*cierre < FIN-1){  //evito preguntar en la última ronda

            printf("\nQueres seguis jugando?  (s = si n = no)\n>");
            scanf(" %c",seguirJugando);

            if(*seguirJugando == 'n'){ //funciona joya.

                *cierre = FIN-1;
            }
            else if(*seguirJugando != 's'){

                while(*seguirJugando != 's' && *seguirJugando != 'n'){                                                                                       /*Solamente se ejecuta cuando no es ni s ni n, si es cualquiera de los dos la
                                                                                                                                                               condicion deja de ser valida y por ende sale a la mierda. */
                    printf("La respuesta ingresada no es valida, por favor utilizar (s = si n = no)\n> ");
                    scanf(" %c",seguirJugando);

                    if(*seguirJugando == 'n'){ //funciona joya.

                        *cierre = FIN-1;
                    }
                }
            }
        }

}

/////////////////////////////////////////////////////////////////////////////////////////////
/*
            int correcto = 1;                   //El tablero esta ordenado a menos que encuentre lo contrario
            int contador = 1;

            for (i = 0; i < FIL; i++) {
                for (j = 0; j < COL; j++) {
                    if (contador == (FIL*COL) ) {  //rastreo posición [3][3] (unica posicion que no puede ser igual al contador)
                        if (tablero[i][j] != 0) {  //si uso el operador logico && para juntar este if con el de arriba y no entiendo por qué.
                            correcto = 0;
                            break;
                        }
                    }
                    else if (tablero[i][j] != contador) { //se evalua 15 veces.
                        correcto = 0;
                        break;
                }
                    contador++;
                }
                if (correcto == 0) {
                    break;
                }
            }
*/
