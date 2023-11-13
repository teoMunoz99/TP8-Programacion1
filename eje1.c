#include <stdio.h>
#include <string.h>
//Declaro estrucutras
typedef struct{
    int dia;
    int mes;
    int anio;
}fecha;

typedef struct{
    char nombre[30];
    long int telefono;
}proveedor;

typedef struct{
    char nombreProducto[30];
    float precioUnitario;
    int ventasMensuales[12];
    proveedor proveedorProd;
    fecha fechaProd;
}producto;

void modificarPrecio(producto prod, float *precio);
void modificarPrecio(producto prod, float *precio){
    float nuevoP;
    printf("Cambiar precio de: %s \n", prod.nombreProducto);
    printf("PRECIO ACTUAL: $%2.f \n", prod.precioUnitario);
    printf("Ingrese el nuevo precio: $");
    scanf("%f", &nuevoP);
    *precio = nuevoP;
    printf("PRECIO NUEVO: $%2.f \n", *precio);
}

producto cargarDatos();
producto cargarDatos(){
    producto prod;
    int opcion = 0;
    printf("Ingrese el nombre del producto:\n");
    fflush(stdin);
    gets(prod.nombreProducto);
    printf("Ingrese el precio del producto: %s \n", prod.nombreProducto);
    scanf("%f", &prod.precioUnitario);
    printf("Desea modificar el precio?\n");
    printf("1. SI\n2. NO\n");
    scanf("%d", &opcion);
    if(opcion == 1){
        modificarPrecio(prod, &prod.precioUnitario);
    }
    printf("Dia de inicio de ventas del producto: \n");
    scanf("%d", &prod.fechaProd.dia);
    printf("Mes de inicio de ventas del producto: \n");
    scanf("%d", &prod.fechaProd.mes);
    printf("Año de inicio de ventas del producto: \n");
    scanf("%d", &prod.fechaProd.anio);
    for(int i = 0; i < 12 - prod.fechaProd.mes; i++){   
        printf("Ingrese la cantidad de ventas del %i mes:\n", i+1);
        scanf("%d", &prod.ventasMensuales[i]);
    }
    printf("Ingrese el nombre del proveedor: \n");
    fflush(stdin);
    gets(prod.proveedorProd.nombre);
    printf("Ingrese el telefono del proveedor: \n");
    scanf("%ld", &prod.proveedorProd.telefono);
    return prod;
}

float montoTotalVentas(producto prod);
float montoTotalVentas(producto prod){
    float total = 0;
    for (int i = 0; i < 12 - prod.fechaProd.mes; i++)
    {
        total = total + prod.ventasMensuales[i]* prod.precioUnitario;
    }
    return total;
}

void mostrarProd(producto prod);
void mostrarProd(producto prod){
    float total;
    printf("\n === MUESTRA DEL PRODUCTO === \n");
    printf("NOMBRE PRODUCTO: %s \n", prod.nombreProducto);
    printf("PRECIO UNITARIO: $%2.f \n", prod.precioUnitario);
    printf("CANT.VENTAS MENSUALES: ");
    for (int i = 0; i < 12 - prod.fechaProd.mes; i++)
    {
        printf("%d-", prod.ventasMensuales[i]);
    }
    printf("\nNOMBRE DEL PROVEEDOR: %s \n", prod.proveedorProd.nombre);
    printf("TEL. DEL PROVEEDOR: %ld \n", prod.proveedorProd.telefono);
    printf("FECHA DE INICIO: %d/%d/%d \n", prod.fechaProd.dia, prod.fechaProd.mes, prod.fechaProd.anio);
    total = montoTotalVentas(prod);
    printf("MONTO TOTAL VENTAS: $%2.f \n", total);
}

void mesConMasVentas(producto prod);
void mesConMasVentas(producto prod){
    int mayor = 0, mes;
    char nombreMes[15];
    for(int i = 0; i < 12 - prod.fechaProd.mes; i++){
        if(prod.ventasMensuales[i] > mayor){
            mayor = prod.ventasMensuales[i];
            mes = prod.fechaProd.mes + i;
        }
    }
    switch(mes) {
        case 1:
            strcpy(nombreMes, "Enero");
            break;
        case 2:
            strcpy(nombreMes, "Febrero");
            break;
        case 3:
            strcpy(nombreMes, "Marzo");
            break;
        case 4:
            strcpy(nombreMes, "Abril");
            break;
        case 5:
            strcpy(nombreMes, "Mayo");
            break;
        case 6:
            strcpy(nombreMes, "Junio");
            break;
        case 7:
            strcpy(nombreMes, "Julio");
            break;
        case 8:
            strcpy(nombreMes, "Agosto");
            break;
        case 9:
            strcpy(nombreMes, "Septiembre");
            break;
        case 10:
            strcpy(nombreMes, "Octubre");
            break;
        case 11:
            strcpy(nombreMes, "Noviembre");
            break;
        case 12:
            strcpy(nombreMes, "Diciembre");
            break;
        default:
        ;
    }
    printf("%s fue el mes con mas ventas\n", nombreMes);
    printf("TOTAL DE VENTAS DEL MES %d: %d \n", mes, mayor);
}

int main(){
    int tama, opcion=0;
    printf("Ingrese la cantiad de productos a cargar: \n");
    scanf("%d", &tama);
    producto prod[tama];
    for (int i = 0; i < tama; i++)
    {   
        printf("=== Producto: %d ===\n", i+1);
        prod[i] = cargarDatos();
    }
    printf("=== Elija un producto para ver sus detalles ===\n");
    for (int i = 0; i < tama; i++)
    {
        printf("%d. %s \n", i+1, prod[i].nombreProducto);
    }
    scanf("%d", &opcion);
    mostrarProd(prod[opcion-1]);
    mesConMasVentas(prod[opcion-1]);
    return 0;
}