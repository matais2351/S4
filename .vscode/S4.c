
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  

#define MAX_PRODUCTOS 10  
#define LARGO_NOMBRE  50

void quitarSaltoLinea(char texto[]) {
    int i = 0;
    while (texto[i] != '\0') {
        if (texto[i] == '\n') {
            texto[i] = '\0';
        }
        i++;
    }
}

void aMinusculas(char origen[], char destino[]) {
    int i = 0;
    while (origen[i] != '\0') {
        if (origen[i] >= 'A' && origen[i] <= 'Z') {
            destino[i] = origen[i] + ('a' - 'A');
        } else {
            destino[i] = origen[i];
        }
        i++;
    }
    destino[i] = '\0';
}

int leerEntero(char mensaje[]) {
    char buffer[LARGO_NOMBRE];
    printf("%s", mensaje);
    fgets(buffer, LARGO_NOMBRE, stdin);
    return atoi(buffer);
}

float leerPrecio(char mensaje[]) {
    char buffer[LARGO_NOMBRE];
    float valor;
    do {
        printf("%s", mensaje);
        fgets(buffer, LARGO_NOMBRE, stdin);
        valor = (float) atof(buffer);
        if (valor < 0) {
            printf("  Precio inválido. Debe ser mayor o igual a 0.\n");
        }
    } while (valor < 0);
    return valor;
}

void ingresarProductos(char nombres[][LARGO_NOMBRE], float precios[], int cantidad) {
    int i;
    for (i = 0; i < cantidad; i++) {
        printf("\nProducto %d\n", i + 1);
        printf("  Nombre: ");
        fgets(nombres[i], LARGO_NOMBRE, stdin);
        quitarSaltoLinea(nombres[i]);
        precios[i] = leerPrecio("  Precio: $");
    }
}

float calcularTotal(float precios[], int cantidad) {
    float total = 0;
    int i;
    for (i = 0; i < cantidad; i++) {
        total += precios[i];
    }
    return total;
}

int indiceMasCaro(float precios[], int cantidad) {
    int mayor = 0;
    int i;
    for (i = 1; i < cantidad; i++) {
        if (precios[i] > precios[mayor]) {
            mayor = i;
        }
    }
    return mayor;
}

int indiceMasBarato(float precios[], int cantidad) {
    int menor = 0;
    int i;
    for (i = 1; i < cantidad; i++) {
        if (precios[i] < precios[menor]) {
            menor = i;
        }
    }
    return menor;
}

float calcularPromedio(float precios[], int cantidad) {
    return calcularTotal(precios, cantidad) / cantidad;
}

int buscarProducto(char nombres[][LARGO_NOMBRE], int cantidad, char buscado[]) {
    char a[LARGO_NOMBRE];
    char b[LARGO_NOMBRE];
    int i;
    aMinusculas(buscado, a);
    for (i = 0; i < cantidad; i++) {
        aMinusculas(nombres[i], b);
        if (strcmp(a, b) == 0) {
            return i;
        }
    }
    return -1;
}

/* ---------- Mostrar inventario ---------- */
void mostrarInventario(char nombres[][LARGO_NOMBRE], float precios[], int cantidad) {
    int i;
    printf("\n%-4s %-30s %10s\n", "N°", "PRODUCTO", "PRECIO");
    printf("-----------------------------------------------\n");
    for (i = 0; i < cantidad; i++) {
        printf("%-4d %-30s %10.2f\n", i + 1, nombres[i], precios[i]);
    }
}

int main(void) {
    char  nombres[MAX_PRODUCTOS][LARGO_NOMBRE];
    float precios[MAX_PRODUCTOS];

    int cantidad;
    int opcion;
    int pos;
    char buscado[LARGO_NOMBRE];
    char buffer[LARGO_NOMBRE];

    printf("=== GESTIÓN DE INVENTARIO ===\n");

    do {
        cantidad = leerEntero("¿Cuántos productos desea ingresar? (1-10): ");
        if (cantidad < 1 || cantidad > MAX_PRODUCTOS) {
            printf("Cantidad inválida. Debe estar entre 1 y %d.\n", MAX_PRODUCTOS);
        }
    } while (cantidad < 1 || cantidad > MAX_PRODUCTOS);

    ingresarProductos(nombres, precios, cantidad);

    do {
        printf("\n========== MENÚ ==========\n");
        printf("1. Mostrar inventario\n");
        printf("2. Precio total del inventario\n");
        printf("3. Producto más caro y más barato\n");
        printf("4. Precio promedio\n");
        printf("5. Buscar producto por nombre\n");
        printf("0. Salir\n");
        opcion = leerEntero("Seleccione una opción: ");

        switch (opcion) {
            case 1:
                mostrarInventario(nombres, precios, cantidad);
                break;

            case 2:
                printf("\nPrecio total del inventario: $%.2f\n",
                       calcularTotal(precios, cantidad));
                break;

            case 3:
                pos = indiceMasCaro(precios, cantidad);
                printf("\nProducto más caro:   %s ($%.2f)\n", nombres[pos], precios[pos]);
                pos = indiceMasBarato(precios, cantidad);
                printf("Producto más barato: %s ($%.2f)\n", nombres[pos], precios[pos]);
                break;

            case 4:
                printf("\nPrecio promedio: $%.2f\n", calcularPromedio(precios, cantidad));
                break;

            case 5:
                printf("\nNombre del producto a buscar: ");
                fgets(buffer, LARGO_NOMBRE, stdin);
                quitarSaltoLinea(buffer);
                strcpy(buscado, buffer);
                pos = buscarProducto(nombres, cantidad, buscado);
                if (pos >= 0) {
                    printf("Encontrado: %s - Precio: $%.2f\n", nombres[pos], precios[pos]);
                } else {
                    printf("El producto \"%s\" no existe en el inventario.\n", buscado);
                }
                break;

            case 0:
                printf("\nHasta luego.\n");
                break;

            default:
                printf("\nOpción inválida.\n");
        }
    } while (opcion != 0);

    return 0;
}

