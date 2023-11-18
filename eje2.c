#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaro estructuras
typedef struct {
    int dia, mes, anio;
} fechas;

typedef struct
{
    char ape[15], nombre[15];
    long int dni;
} guias;

typedef struct
{
    char destino[15];
    guias guia;
    fechas fechaSalida;
    fechas fechaRegreso;
    float costo;
    int cantHabRes;
    int *listHabRes;
} viajes;

// Declaro funciones
void cargarFecha(fechas *fecha);
void cargarFecha(fechas *fecha) {
    int bandera = 0;
    // Control dia
    do {
        printf("Ingrese el anio: \n");
        scanf("%d", &fecha->anio);
        if (fecha->anio < 2023 || fecha->anio > 2025) {
            printf("El anio debe estar entre 2023 y 2025\n");
        }
    } while (fecha->anio < 2023 || fecha->anio > 2025);
    // Mes
    do {
        printf("Ingrese el mes: \n");
        scanf("%d", &fecha->mes);
        if (fecha->mes < 1 || fecha->mes > 12) {
            printf("El mes debe ser un numero entre 1 y 12\n");
        }
    } while (fecha->mes < 1 || fecha->mes > 12);
    // Año
    do {
        printf("Ingrese el dia: \n");
        scanf("%d", &fecha->dia);
        if (fecha->mes == 2) {
            if (fecha->dia >= 1 && fecha->dia <= 28) {
                bandera = 1;
            } else {
                printf("El dia debe estar entre 1 y 28, intente nuevamente: \n");
            }
        } else {
            if ((fecha->mes == 4 || fecha->mes == 6 || fecha->mes == 9 || fecha->mes == 11)) {
                if (fecha->dia >= 1 && fecha->dia <= 30) {
                    bandera = 1;
                } else {
                    printf("El dia debe estar entre 1 y 30, intente nuevamente: \n");
                }
            } else {
                if (fecha->dia >= 1 && fecha->dia <= 31) {
                    bandera = 1;
                } else {
                    printf("El dia debe estar entre 1 y 31, intente nuevamente: \n");
                }
            }
        }

    } while (bandera == 0);
}

void modCosto(viajes *viaje);
void modCosto(viajes *viaje) {
    float aumento = 0;
    printf("Ingrese el porcentaje de aumento: \n");
    scanf("%f", &aumento);
    viaje->costo = viaje->costo + (viaje->costo * aumento) / 100;
}

void cargarDatosViaje(viajes *viaje);
void cargarDatosViaje(viajes *viaje) {
    //==DESTINO==
    printf("Ingrese el lugar de destino: \n");
    fflush(stdin);
    gets(viaje->destino);
    //==GUIA==
    // nombre
    printf("Ingrese el nombre del guia: \n");
    fflush(stdin);
    gets(viaje->guia.nombre);
    // apellido
    printf("Ingrese el apellido del guia: \n");
    fflush(stdin);
    gets(viaje->guia.ape);
    // dni
    printf("Ingrese el dni del guia: \n");
    scanf("%ld", &viaje->guia.dni);
    //==FECHAS==
    // Salida
    printf("== Fecha de salida ==\n");
    cargarFecha(&viaje->fechaSalida);
    // Regreso
    printf("== Fecha de regreso ==\n");
    cargarFecha(&viaje->fechaRegreso);
    //==COSTO==
    printf("Ingrese el costo del viaje: \n");
    scanf("%f", &viaje->costo);
    //==HABITACIONES==
    // Cant de habitaciones
    printf("Ingrese la cantidad de habitaciones a reservar: \n");
    scanf("%d", &viaje->cantHabRes);
    // Lista de habitaciones
    // creo el arreglo dinamico
    viaje->listHabRes = (int *)malloc(viaje->cantHabRes * sizeof(int));
    // igreso los numeros de habitaciones
    int duplicado = 0;
    for (size_t i = 0; i < viaje->cantHabRes; i++) {
        printf("Ingrese el numero de la %d habitacion a reservar: \n", i + 1);
        scanf("%d", &viaje->listHabRes[i]);
        for (int j = 0; j < i; j++)
        {
            if(viaje->listHabRes[j] == viaje->listHabRes[i]){
                printf("Este numero de habitacion ya fue ingresado. Ingrese otro.\n");
                i--; // para repetir la iteración actual y permitir que se ingrese otro número.
                break;
            }
        }
        
    }
}

void mostrarDatos(viajes viaje);
void mostrarDatos(viajes viaje) {
    printf("==== DATOS VIAJE ====\n");
    printf("\n");
    printf("DESTINO: %s \n", viaje.destino);
    printf("NOMBRE GUIA: %s %s \n", viaje.guia.ape, viaje.guia.nombre);
    printf("FECHA DE SALIDA: %d/%d/%d \n", viaje.fechaSalida.dia, viaje.fechaSalida.mes, viaje.fechaSalida.anio);
    printf("FECHA DE REGRESO: %d/%d/%d \n", viaje.fechaRegreso.dia, viaje.fechaRegreso.mes, viaje.fechaRegreso.anio);
    printf("COSTO: $%2.f \n", viaje.costo);
    printf("CANT HABITACIONES RES: %d \n", viaje.cantHabRes);
    printf("LISTA DE HABITACIONES RES: ");
    for (int i = 0; i < viaje.cantHabRes; i++) {
        printf("%d ", viaje.listHabRes[i]);
    }
    printf("\n");
}

int main() {
    viajes viaje;
    cargarDatosViaje(&viaje);
    mostrarDatos(viaje);
    return 0;
}