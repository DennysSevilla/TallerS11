#include <stdio.h>
#include <string.h>

#define MAX_LIBROS 10
#define LEN_TITULO 100
#define LEN_AUTOR 50
#define LEN_ESTADO 15

typedef struct {
    int id;
    char titulo[LEN_TITULO];
    char autor[LEN_AUTOR];
    int anio;
    char estado[LEN_ESTADO]; 
} Libro;

void menu();
int leerEnteroPositivo();
void limpiarBuffer();
void eliminarSaltoLinea(char* cadena);

void registrarLibro(Libro biblioteca[], int *cantidad);
void mostrarLibros(Libro biblioteca[], int cantidad);
void buscarLibro(Libro biblioteca[], int cantidad);
void actualizarEstado(Libro biblioteca[], int cantidad);
void eliminarLibro(Libro biblioteca[], int *cantidad);
