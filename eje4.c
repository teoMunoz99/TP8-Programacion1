#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dia, mes, anio;
} Fecha;

typedef struct
{
    char nombre[15];
    char ape[15];

} Autor;

typedef struct
{
    char titulo[15];
    Autor autorLibro;
    Fecha fechPubli;
    int id;
    int prestamos[12];
    char **historialPrestamos;
} Libro;

void cargarLibro(Libro *librito);
void cargarLibro(Libro *librito) {
    printf("Ingrese el nombre del libro:\n");
    fflush(stdin);
    gets(librito->titulo);
    printf("Ingrese el nombre del autor:\n");
    fflush(stdin);
    gets(librito->autorLibro.nombre);
    printf("Ingrese el apellido del autor:\n");
    fflush(stdin);
    gets(librito->autorLibro.ape);
    printf("Ingrese el año de publicacion: \n");
    scanf("%d", &librito->fechPubli.anio);
    printf("Ingrese el id del libro: \n");
    scanf("%d", &librito->id);
    printf("Ingrese la cantidad de prestamos que tuvo: \n");
    scanf("%d", &librito->id);
    // redimenciono el arreglo dinamico
    //librito->historialPrestamos = (char **)realloc(librito->historialPrestamos, librito->id * (char **));
    for (int i = 0; i < librito->id; i++) {
        for (int j = 0; j < 2; j++) {
            printf("Ingrese el mes de prestamo: \n");
            fflush(stdin);
        }
    }
}
int main() {
    return 0;
}