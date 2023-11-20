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
    int **historialUsuarios;
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
    // cargo los prestamos mensuales
    printf("Ingrese la cantidad de préstamos mensuales para cada mes:\n");
    for (int i = 0; i < 12; ++i) {
        printf("Mes %d: ", i + 1);
        scanf("%d", &librito->prestamos[i]);
    }
    // cargar información del historiaal de usuarios
    librito->historialUsuarios = (int **)malloc(12 * sizeof(int *));
    for (int i = 0; i < 12; ++i) {
        librito->historialUsuarios[i] = (int *)malloc(50 * sizeof(int));
        for (int j = 0; j < 50; ++j) {
            librito->historialUsuarios[i][j] = 0;
        }
    }
}
int main() {
    Libro librito1;
    cargarLibro(&librito1);
    for (int i = 0; i < 12; ++i) {
        free(librito1.historialUsuarios[i]);
    }
    free(librito1.historialUsuarios);
    return 0;
}