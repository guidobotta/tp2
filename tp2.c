#include "heap.h"
#include "hash.h"
#include "abb.h"
#include "lista.h"
#include "strutil.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Para cada archivo nuevo:
    *Guardar en ABB con clave "date"
    *Guardar en hash con clave "flight_number"
    *Guardar en heap de maximos struct vuelo_heap
*/

//SON TODOS CHAR*, VEMOS MAS ADELANTE QUE TIPO DE DATO CONVIENE PARA CADA UNO
//REEMPLAZAR VUELO POR FLIGHT? PASAR TODO A INGLES O A ESPAÑOL? WTF CON "TODO" JAJA

typedef priority_heap{   //Guardamos cada struct vuelo_heap en el heap y con el conseguimos la
    char* priority;      //clave para el hash
    char* flight_number;
}priority_heap_t;

priority_heap_t* crear_priority_heap(char* priority, char* flight_number){
    priority_heap_t* prior_heap 
}

typedef struct vuelo{
    char* flight_number;
    char* airline;
    char* origin_airport;
    char* destination_airport;
    char* tail_number;
    char* priority;
    char* date;
    char* departure_delay;
    char* air_time;
    char* cancelled;
}vuelo_t;

vuelo_t *crear_vuelo(){
    vuelo_t *vuelo = malloc(sizeof(vuelo_t));
    if(!vuelo) return NULL;
    //Pedir memoria para cada uno y luego asignar NULL o 0.
    //Me parece mejor que asignemos los valores a cada campo fuera de esta funcion
    vuelo->flight_number;
    vuelo->airline;
    vuelo->origin_airport;
    vuelo->destination_airport;
    vuelo->tail_number;
    vuelo->priority;
    vuelo->date;
    vuelo->departure_delay;
    vuelo->air_time;
    vuelo->cancelled;
    return vuelo;
}

///
// AGREGAR ARCHIVO
///

void agregar_archivo(char** comando){
    
    FILE* archivo = fopen(nombre_archivo, "r");
    if(!archivo){
        fprintf(stderr, "Error\n");
        return;
    }
    
    fscanf(
        archivo,
        FORMATO_ARCHIVO, //<--- Es una constante que tiene un char* con el formato del .csv
        vuelo->flight_number,
        vuelo->airline
        vuelo->origin_airport
        vuelo->destination_airport
        vuelo->tail_number
        vuelo->priority
        vuelo->date
        vuelo->departure_delay
        vuelo->air_time
        vuelo->cancelled
        );

    vuelo_heap->priority = vuelo->priority;
    vuelo_heap->flight_number = vuelo->flight_number;
    //fscanf se encarga de meter cada valor del archivo en su correspondiente lugar.
    hash_guardar(vuelo->flight_number, vuelo);
    abb_guardar(vuelo->date, vuelo);
    heap_encolar(vuelo->date, vuelo_heap);
    //Parsear cada linea con getline o fscanf y meter dentro del struct
    fclose(archivo);
}

///
// VER TABLERO
///

void ver_tablero(char** comando);

///
// INFO VUELO
///

void info_vuelo(char** comando);

///
// PRIORIDAD VUELOS
///

int priority_comp(const priority_heap_t* vuelo_1, const priority_heap_t* vuelo_2){
    if (atoi(vuelo_1->priority) > atoi(vuelo_2->priority)) return ;
    else if (atoi(vuelo_1->priority) < atoi(vuelo_2->priority)) return ;

    else if (atoi(vuelo_1->flight_number) > atoi(vuelo_2->flight_number)) return ;
    else if (atoi(vuelo_1->flight_number) < atoi(vuelo_2->flight_number)) return ;

    return 0;
}

void prioridad_vuelos(char** comando, hash_t* hash){
    if(!comando[1]){
        fprintf(stderr, "Error\n");
        return;
    }

    heap_t* heap = heap_crear(/*!!FUNCION DE COMPARACIÓN DE FECHAS Y CODIGO DE VUELO¡¡*/); 
    //Debe ser un Heap de Mínimos, por lo que la funcion de comparacion debe estar al reves
    if (!heap){
        fprintf(stderr, "Error\n");
        return;
    }

    int cantidad = atoi(comando[1]);
    int contador = 0;

    hash_iter_t* hash_iter = hash_iter_crear(hash);
    if (!hash_iter){
        heap_destruir(heap);
        fprintf(stderr, "Error\n");
        return;
    }

    while (!hash_iter_al_final(hash_iter)){
        if (contador < cantidad){
            heap_encolar(heap, hash_iter_ver_actual(hash_iter));
            contador++;
        }
        else if (/*LA PRIORIDAD DEL ELEMENTO ES MAYOR AL MENOR DEL HEAP*/){
            heap_desencolar(heap);
            heap_encolar(heap, hash_iter_ver_actual(hash_iter));
        }
        hash_iter_avanzar(hash_iter);
    }

    lista_t* lista = lista_crear();
    if(!lista){
        hash_iter_destruir(hash_iter);
        heap_destruir(heap);
        fprintf(stderr, "Error\n");
        return;
    }

    while(!heap_esta_vacio(heap)){
        lista_insertar_primero(lista, heap_desencolar(heap));
    }

    while(!lista_esta_vacia(lista)){
        char* clave = (char*)lista_borrar_primero(lista);
        printf("%s - %s", hash_obtener(hash, clave)->priority, hash_obtener(hash, clave)->flight_number);
    }

    hash_iter_destruir(hash_iter);
    heap_destruir(heap);
}

///
// BORRAR
///

void borrar(char** comando);

///
// EJECUTADOR
///

void ejecucion(char* linea, hash_t* hash, abb_t* abb){
    char** comando = split(linea, ' ');
    if (!strcmp(comando[0], "agregar_archivo")) agregar_archivo(comando); //EJECUTAR AGREGAR_ARCHIVO
    else if (!strcmp(comando[0], "ver_tablero")) ver_tablero(comando); //EJECUTAR VER_TABLERO
    else if (!strcmp(comando[0], "info_vuelo")) info_vuelo(comando); //EJECUTAR INFO_VUELO
    else if (!strcmp(comando[0], "prioridad_vuelos")) prioridad_vuelos(comando, hash); //EJECUTAR PRIORIDAD_VUELOS
    else if (!strcmp(comando[0], "borrar")) borrar(comando); //EJECUTAR BORRAR
    else {
        fprintf(stderr, "Error");
        return;
    }
    printf("OK\n");
}

/*
Ejecuta el main.c y se queda esperando input del usuario

#agregar_archivo <nombre_archivo>
Llama a la funcion agregar_archivo(nombre_archivo);
#ver_tablero <k cantidad vuelo> <modo: asc/desc> <desde> <hasta>
Llama a la funcion ver_tablero();
#info_vuelo <codigo vuelo>
Llama a la funcion info_vuelo();
#prioridad_vuelos <k cantidad vuelos>
Llama a la funcion prioridad_vuelos();
#borrar <desde> <hasta>
Llama a la funcion borrar();
*/
int main(){

    hash_t* hash = hash_crear(free);
    if(!hash){
        return 1;
    }

    hash_t* abb = abb_crear(free, funcion_comparacion);
    if(!abb){
        free(hash);
        return 1;
    }

    size_t tam = 0;
    char* linea = NULL;
    while (getline(&linea, &tam, stdin) != -1){
        ejecucion(linea, hash, abb);
    }

    return 0;
}
