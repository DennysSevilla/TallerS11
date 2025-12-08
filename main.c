#include "funciones.h"

int main() {
    Libro biblioteca[MAX_LIBROS];
    int cantidadLibros = 0;
    int opcion;

    do {
        menu();
        opcion = leerEnteroPositivo();

        switch (opcion) {
            case 1:
                registrarLibro(biblioteca, &cantidadLibros);
                break;
            case 2:
                mostrarLibros(biblioteca, cantidadLibros);
                break;
            case 3:
                buscarLibro(biblioteca, cantidadLibros);
                break;
            case 4:
                actualizarEstado(biblioteca, cantidadLibros);
                break;
            case 5:
                eliminarLibro(biblioteca, &cantidadLibros);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 6);

    return 0;
}