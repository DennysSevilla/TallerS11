#include "funciones.h"

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void eliminarSaltoLinea(char* cadena) {
    size_t len = strlen(cadena);
    if (len > 0 && cadena[len - 1] == '\n') {
        cadena[len - 1] = '\0';
    }
}

int leerEnteroPositivo() {
    int valor;
    int resultado;
    
    do {
        resultado = scanf("%d", &valor);
        
        if (resultado != 1) {
            printf("Error: Entrada no valida (no es un numero). Intente de nuevo: ");
            limpiarBuffer(); 
        } else if (valor < 0) {
            printf("Error: El numero no puede ser negativo. Intente de nuevo: ");
        } else {            
            limpiarBuffer(); 
            return valor;
        }
    } while (1);
}

void menu() {
    printf("\n--- GESTION DE BIBLIOTECA ---\n");
    printf("1. Registrar libro\n");
    printf("2. Mostrar lista de libros\n");
    printf("3. Buscar libro\n");
    printf("4. Actualizar estado\n");
    printf("5. Eliminar libro\n");
    printf("6. Salir\n");
    printf("Seleccione una opcion: ");
}

void registrarLibro(Libro biblioteca[], int *cantidad) {
    if (*cantidad >= MAX_LIBROS) {
        printf("Error: La biblioteca esta llena (Max %d libros).\n", MAX_LIBROS);
        return;
    }

    printf("\n--- REGISTRAR LIBRO ---\n");
    
    int idTemp;
    int unico = 0;

    do {
        unico = 1;
        printf("Ingrese ID del libro (Entero unico): ");
        idTemp = leerEnteroPositivo();

        for (int i = 0; i < *cantidad; i++) {
            if (biblioteca[i].id == idTemp) {
                printf("Error: Ya existe un libro con el ID %d.\n", idTemp);
                unico = 0;
                break;
            }
        }
    } while (unico == 0);

    biblioteca[*cantidad].id = idTemp;

    printf("Ingrese Titulo: ");
    fgets(biblioteca[*cantidad].titulo, LEN_TITULO, stdin);
    eliminarSaltoLinea(biblioteca[*cantidad].titulo);

    printf("Ingrese Autor: ");
    fgets(biblioteca[*cantidad].autor, LEN_AUTOR, stdin);
    eliminarSaltoLinea(biblioteca[*cantidad].autor);

    printf("Ingrese Anio de publicacion: ");
    biblioteca[*cantidad].anio = leerEnteroPositivo();
    strcpy(biblioteca[*cantidad].estado, "Disponible");
    (*cantidad)++; 
    printf("Libro registrado exitosamente.\n");
}

void mostrarLibros(Libro biblioteca[], int cantidad) {
    if (cantidad == 0) {
        printf("\nNo hay libros registrados.\n");
        return;
    }

    printf("\n%-5s %-30s %-20s %-6s %-15s\n", "ID", "TITULO", "AUTOR", "ANIO", "ESTADO");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%-5d %-30s %-20s %-6d %-15s\n", 
            biblioteca[i].id, 
            biblioteca[i].titulo, 
            biblioteca[i].autor, 
            biblioteca[i].anio, 
            biblioteca[i].estado);
    }
}

void buscarLibro(Libro biblioteca[], int cantidad) {
    if (cantidad == 0) {
        printf("\nNo hay libros para buscar.\n");
        return;
    }

    int opcion;
    printf("\nBuscar por:\n1. ID\n2. Titulo\nOpcion: ");
    opcion = leerEnteroPositivo();

    int encontrado = 0;

    if (opcion == 1) {
        printf("Ingrese ID a buscar: ");
        int idBusq = leerEnteroPositivo();
        for (int i = 0; i < cantidad; i++) {
            if (biblioteca[i].id == idBusq) {
                printf("\n--- LIBRO ENCONTRADO ---\n");
                printf("ID: %d\nTitulo: %s\nAutor: %s\nAnio: %d\nEstado: %s\n",
                    biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autor,
                    biblioteca[i].anio, biblioteca[i].estado);
                encontrado = 1;
                break;
            }
        }
    } else if (opcion == 2) {
        char tituloBusq[LEN_TITULO];
        printf("Ingrese Titulo a buscar: ");
        fgets(tituloBusq, LEN_TITULO, stdin);
        eliminarSaltoLinea(tituloBusq);

        for (int i = 0; i < cantidad; i++) {
            if (strcmp(biblioteca[i].titulo, tituloBusq) == 0) {
                printf("\n--- LIBRO ENCONTRADO ---\n");
                printf("ID: %d\nTitulo: %s\nAutor: %s\nAnio: %d\nEstado: %s\n",
                    biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autor,
                    biblioteca[i].anio, biblioteca[i].estado);
                encontrado = 1;
            }
        }
    } else {
        printf("Opcion invalida.\n");
        return;
    }

    if (!encontrado) {
        printf("Libro no encontrado.\n");
    }
}

void actualizarEstado(Libro biblioteca[], int cantidad) {
    printf("\nIngrese ID del libro para cambiar estado: ");
    int idBusq = leerEnteroPositivo();
    int encontrado = 0;

    for (int i = 0; i < cantidad; i++) {
        if (biblioteca[i].id == idBusq) {
            if (strcmp(biblioteca[i].estado, "Disponible") == 0) {
                strcpy(biblioteca[i].estado, "Prestado");
            } else {
                strcpy(biblioteca[i].estado, "Disponible");
            }
            printf("Estado actualizado a: %s\n", biblioteca[i].estado);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) printf("Libro con ID %d no encontrado.\n", idBusq);
}

void eliminarLibro(Libro biblioteca[], int *cantidad) {
    printf("\nIngrese ID del libro a eliminar: ");
    int idBusq = leerEnteroPositivo();
    int encontrado = 0;

    for (int i = 0; i < *cantidad; i++) {
        if (biblioteca[i].id == idBusq) {
            for (int j = i; j < *cantidad - 1; j++) {
                biblioteca[j] = biblioteca[j + 1]; 
            }
            (*cantidad)--; 
            printf("Libro eliminado exitosamente.\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) printf("Libro con ID %d no encontrado.\n", idBusq);
}