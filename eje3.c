#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMA 10
// Declaro estructuras
typedef struct {
    int dia, mes, anio;
} Fecha;

typedef struct {
    char tipo[20];  // depósito, retiro, transferencia, etc.
    float monto;
    Fecha fechaMov;
} Movimiento;

typedef struct
{
    long int cbu;
    float saldo;
    Movimiento *movUsu;  // (Movimiento *)malloc(TAMA * sizeof(Movimiento));
} DatosCB;

typedef struct {
    char ape[15];
    char nombre[15];
    long int dni;
    Fecha fechaNac;
    char contra[15];
    int cantMov;
    DatosCB datosCbUsu;
} Cliente;

void cambiarContra(Cliente *usu);
void cambiarContra(Cliente *usu) {
    char contraActual[15];
    char contraNueva[15];
    printf("==== Cambio de contrasenia ====\n");
    printf("\n");
    printf("Ingrese la contrasenia actual\n");
    fflush(stdin);
    gets(contraActual);
    // controlar si la contra actual es igual a la registrada
    if (strcmp(contraActual, usu->contra) == 0) {
        printf("Ingrese la nueva contrasenia:\n");
        fflush(stdin);
        gets(contraActual);
        printf("Repita la nueva contrasenia:\n");
        fflush(stdin);
        gets(contraNueva);
        if (contraActual == contraNueva) {
            strcpy(usu->contra, contraNueva);
            printf("Cambio de contrasenia exitoso!\n");
        } else {
            printf("Las contrasenias no coinciden \n");
        }
    } else {
        printf("Contrasenia incorrecta \n");
    }
}

void menuPrincipal() {
    printf("\n");
    printf("==== Menu principal ====\n");
    printf("\n");
    printf("1. Ver lista de clientes registrados.\n");
    printf("2. Elegir un cliente.\n");
    printf("3. Registrar nuevo cliente.\n");
    printf("4. Salir.\n");
    printf("\n");
}

void menuOpciones() {
    printf("\n");
    printf("==== Menu de usuario ====\n");
    printf("\n");
    printf("1. Cambiar contrasenia.\n");
    printf("2. Depositar monto.\n");
    printf("3. Retirar dinero.\n");
    printf("4. Consultar saldo.\n");
    printf("5. Mostrar datos de la cuenta.\n");
    printf("6. Mostrar historial de movimientos.\n");
    printf("7. Volver al menu clientes.\n");
    printf("\n");
}

int main() {
    Cliente clientesReg[TAMA];
    int opcion = 0, bandera = 0;
    float montoNuevo = 0;
    Fecha fechaHoy = {25, 11, 2023};

    // Inicializo 2 clientes
    clientesReg[0] = (Cliente){
        .ape = "Apellido1",
        .nombre = "Nombre1",
        .dni = 123456789,
        .fechaNac = {1, 1, 2000},
        .contra = "cliente1",
        .cantMov = 0,
        .datosCbUsu = {
            .cbu = 987654321,
            .saldo = 1000.0,
            .movUsu = (Movimiento *)malloc(TAMA * sizeof(Movimiento)),
        },
    };
    clientesReg[1] = (Cliente){
        .ape = "Apellido2",
        .nombre = "Nombre2",
        .dni = 987654321,
        .fechaNac = {2, 2, 1990},
        .contra = "cliente2",
        .cantMov = 0,
        .datosCbUsu = {
            .cbu = 123456789,
            .saldo = 1500.0,
            .movUsu = (Movimiento *)malloc(TAMA * sizeof(Movimiento)),
        },
    };

    do {
        // Muestro menu principal
        menuPrincipal();
        // Ingreso de opcion
        do {
            printf("Ingrese el nro de opcion: \n");
            scanf("%d", &opcion);
            if (opcion < 1 || opcion > 4) {
                printf("Opcion incorrecta, intente de nuevo \n");
            }
        } while (opcion < 1 || opcion > 4);

        // Trabajo con la opcion ingresada
        switch (opcion) {
            case 1:
                for (int i = 0; i < TAMA; i++) {
                    if (strlen(clientesReg[i].nombre) > 3 && strlen(clientesReg[i].ape) > 3) {
                        printf("Cliente %d: %s, %s, %ld \n", i + 1, clientesReg[i].ape, clientesReg[i].nombre, clientesReg[i].dni);
                    }
                }
                break;
            case 2:
                // Elijo al cliente
                printf("Ingrese el nro de cliente: \n");
                scanf("%d", &bandera);
                if (clientesReg[bandera].dni == 0) {
                    printf("La opcion elegida no corresponde con ningun cliente \n");
                    break;
                } else {
                    menuOpciones();
                    // Ingreso de opcion
                    do {
                        printf("Ingrese el nro de opcion: \n");
                        scanf("%d", &opcion);
                        if (opcion < 1 || opcion > 7) {
                            printf("Opcion incorrecta, intente de nuevo \n");
                        }
                    } while (opcion < 1 || opcion > 7);
                    // Trabajo con la opcion ingresada
                    switch (opcion) {
                        case 1:  // cambiar contra
                            cambiarContra(&clientesReg[bandera]);
                            break;
                        case 2:  // depo monto
                            printf("Ingrese el monto que desea depositar");
                            scanf("%f", &montoNuevo);
                            if (montoNuevo < 0) {
                                printf("El monto no puede ser 0 o menos\n");
                            } else {
                                clientesReg[bandera].datosCbUsu.saldo = clientesReg[bandera].datosCbUsu.saldo + montoNuevo;
                            }
                            // registro el movimiento
                            // fecha
                            clientesReg[bandera].datosCbUsu.movUsu[clientesReg[bandera].cantMov].fechaMov.anio = fechaHoy.anio;
                            clientesReg[bandera].datosCbUsu.movUsu[clientesReg[bandera].cantMov].fechaMov.mes = fechaHoy.mes;
                            clientesReg[bandera].datosCbUsu.movUsu[clientesReg[bandera].cantMov].fechaMov.dia = fechaHoy.dia;
                            // monto
                            clientesReg[bandera].datosCbUsu.movUsu[clientesReg[bandera].cantMov].monto = montoNuevo;
                            // tipo
                            strcpy(clientesReg[bandera].datosCbUsu.movUsu[clientesReg[bandera].cantMov].tipo, "deposito");
                            // aumento la cantidad de mov del usuario
                            clientesReg[bandera].cantMov++;
                            break;
                        case 3:  // retirar dinero
                            printf("Ingrese el monto que desea depositar");
                            scanf("%f", &montoNuevo);
                            if (montoNuevo < 0) {
                                printf("El monto no puede ser 0 o menos\n");
                            } else {
                                clientesReg[bandera].datosCbUsu.saldo = clientesReg[bandera].datosCbUsu.saldo - montoNuevo;
                            }
                            // registro el movimiento
                            // fecha
                            clientesReg[bandera].datosCbUsu.movUsu[clientesReg[bandera].cantMov].fechaMov.anio = fechaHoy.anio;
                            clientesReg[bandera].datosCbUsu.movUsu[clientesReg[bandera].cantMov].fechaMov.mes = fechaHoy.mes;
                            clientesReg[bandera].datosCbUsu.movUsu[clientesReg[bandera].cantMov].fechaMov.dia = fechaHoy.dia;
                            // monto
                            clientesReg[bandera].datosCbUsu.movUsu[clientesReg[bandera].cantMov].monto = montoNuevo;
                            // tipo
                            strcpy(clientesReg[bandera].datosCbUsu.movUsu[clientesReg[bandera].cantMov].tipo, "retiro");
                            // aumento la cantidad de mov del usuario
                            clientesReg[bandera].cantMov++;
                            break;
                        case 4:  // consultar saldo
                            printf("Saldo actual: %f", clientesReg[bandera].datosCbUsu.saldo);
                            break;
                        case 5:  // mostrar datos
                            printf("Cliente: %s, %s\n", clientesReg[bandera].ape, clientesReg[bandera].nombre);
                            printf("DNI: %ld \n", clientesReg[bandera].dni);
                            printf("Fecha de nacimiento: %d/%d/%d", clientesReg[bandera].fechaNac.dia, clientesReg[bandera].fechaNac.mes, clientesReg[bandera].fechaNac.anio);
                            printf("Contrasenia: %s\n", clientesReg[bandera].contra);
                            printf("CBU: %ld\n", clientesReg[bandera].datosCbUsu.cbu);
                            printf("Saldo: $%2.f\n", clientesReg[bandera].datosCbUsu.saldo);
                            break;
                        case 6:  // historial de mov
                            printf("== Movimientos ==\n");
                            for (int i = 0; i < clientesReg[bandera].cantMov; i++) {
                                printf("=== Mov: %d\n", i + 1);
                                printf("Tipo %s\n", clientesReg[bandera].datosCbUsu.movUsu[i].tipo);
                                printf("Fecha %d/%d/%d \n", clientesReg[bandera].datosCbUsu.movUsu[i].fechaMov.dia = fechaHoy.dia, clientesReg[bandera].datosCbUsu.movUsu[i].fechaMov.mes = fechaHoy.mes, clientesReg[bandera].datosCbUsu.movUsu[i].fechaMov.mes = fechaHoy.anio);
                                printf("Monto: $%2.f \n", clientesReg[bandera].datosCbUsu.movUsu[i].monto);
                                printf("====\n");
                            }
                            break;
                        default:
                            break;
                    }
                }
                break;
            case 3:
                printf("Esta opcion aun no esta lista \n");
                getchar();
                break;
            case 4:
                printf("Saliendo :D \n");
                break;
            default:
                printf("Opcion incorrecta \n");
                break;
        }

    } while (opcion != 4);
    free(clientesReg[0].datosCbUsu.movUsu);
    free(clientesReg[1].datosCbUsu.movUsu);
    return 0;
}

/*    // Muestro menus
    int opcion = 0;
    do {
        // Menu principal
        menuPrincipal();
        // Elijo opcion
        do {
            scanf("%d", &opcion);
            if (opcion < 1 || opcion > 3) {
                printf("Opcion incorrecta, intente nuevamente:\n");
            }
        } while (opcion < 1 || opcion > 3);
        // Opciones
        switch (opcion) {
            case 1:
                for (int i = 0; i < TAMA; i++) {
                    if (clientesReg[i].dni != 0) {
                        printf("Cliente %d: %s, %s, %ld \n", i + 1, clientesReg[i].ape, clientesReg[i].nombre, clientesReg[i].dni);
                    }
                }
                opcion = 0;
                do {
                    menuOpciones();
                    // Elijo opcion
                    do {
                        scanf("%d", &opcion);
                        if (opcion < 1 || opcion > 7) {
                            printf("Opcion incorrecta, intente nuevamente:\n");
                        }
                    } while (opcion < 1 || opcion > 7);
                    switch (opcion) {
                        //Cambio de contra
                        case 1:
                            printf("Elija el usuario al que desea cambiar la contrasenia: \n");
                            for (int i = 0; i < TAMA; i++) {
                                if (clientesReg[i].dni != 0) {
                                    printf("Cliente %d: %s, %s, %ld \n", i + 1, clientesReg[i].ape, clientesReg[i].nombre, clientesReg[i].dni);
                                }
                            }
                            printf("\n");
                            scanf("%d", &opcion);
                            if (clientesReg[opcion].dni != 0) {
                                cambiarContra(&clientesReg[opcion]);
                            } else {
                                printf("El usuario elegido no existe\n");
                            }
                            break;
                        //Depositar monto
                        case 2:
                            printf("Ingrese el monto a depositar: \n");

                            break;
                        case 3:

                            break;
                        case 4:

                            break;
                        case 5:

                            break;
                        case 6:

                            break;
                        case 7:

                            break;

                        default:
                            printf("Opcion incorrecta \n");
                            break;
                    }
                } while (opcion != 7);
                break;

            case 2:
                printf("Estamos trabajando en esta opcion, elija otra\n");
                break;
            case 3:
                printf("Saliendo \n");
                break;
            default:
                printf("Opcion incorrecta, intente nuevamente\n");
                break;
        }

    } while (opcion != 3);*/