#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PRODUCTOS 5
#define MAX_NOMBRE 50

char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
int tiempos[MAX_PRODUCTOS];
int recursos[MAX_PRODUCTOS];
int demandas[MAX_PRODUCTOS];
int total_productos = 0;

void agregarProducto();
void editarProducto();
void eliminarProducto();
void calcularTotales();
void mostrarProductos();
int buscarProducto(const char* nombre);

int main() {
    int opcion;
    do {
        printf("\n--- Menu de Optimizacion de Produccion ---\n");
        printf("1. Agregar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Calcular totales\n");
        printf("5. Mostrar todos los productos\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: agregarProducto(); break;
            case 2: editarProducto(); break;
            case 3: eliminarProducto(); break;
            case 4: calcularTotales(); break;
            case 5: mostrarProductos(); break;
            case 6: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 6);

    return 0;
}

void agregarProducto() {
    if (total_productos >= MAX_PRODUCTOS) {
        printf("No hay espacio para mas productos!\n");
        return;
    }
    printf("Ingrese nombre del producto: ");
    scanf("%s", nombres[total_productos]);
    printf("Ingrese tiempo de fabricacion (minutos): ");
    scanf("%d", &tiempos[total_productos]);
    printf("Ingrese recursos necesarios (unidades): ");
    scanf("%d", &recursos[total_productos]);
    printf("Ingrese demanda (unidades): ");
    scanf("%d", &demandas[total_productos]);
    total_productos++;
    printf("Producto agregado exitosamente.\n");
}

int buscarProducto(const char* nombre) {
    for (int i = 0; i < total_productos; i++) {
        if (strcmp(nombres[i], nombre) == 0) {
            return i;
        }
    }
    return -1;
}

void editarProducto() {
    char nombre[MAX_NOMBRE];
    printf("Ingrese el nombre del producto a editar: ");
    scanf("%s", nombre);
    int idx = buscarProducto(nombre);
    if (idx == -1) {
        printf("Producto no encontrado.\n");
        return;
    }
    printf("Editando producto '%s':\n", nombre);
    printf("Nuevo tiempo de fabricacion (%d actual): ", tiempos[idx]);
    scanf("%d", &tiempos[idx]);
    printf("Nuevos recursos necesarios (%d actual): ", recursos[idx]);
    scanf("%d", &recursos[idx]);
    printf("Nueva demanda (%d actual): ", demandas[idx]);
    scanf("%d", &demandas[idx]);
    printf("Producto actualizado.\n");
}

void eliminarProducto() {
    char nombre[MAX_NOMBRE];
    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombre);
    int idx = buscarProducto(nombre);
    if (idx == -1) {
        printf("Producto no encontrado.\n");
        return;
    }
    for (int i = idx; i < total_productos - 1; i++) {
        strcpy(nombres[i], nombres[i + 1]);
        tiempos[i] = tiempos[i + 1];
        recursos[i] = recursos[i + 1];
        demandas[i] = demandas[i + 1];
    }
    total_productos--;
    printf("Producto eliminado.\n");
}

void calcularTotales() {
    if (total_productos == 0) {
        printf("No hay productos registrados.\n");
        return;
    }
    int tiempo_total = 0;
    int recursos_total = 0;
    for (int i = 0; i < total_productos; i++) {
        tiempo_total += tiempos[i] * demandas[i];
        recursos_total += recursos[i] * demandas[i];
    }
    printf("--- Totales ---\n");
    printf("Tiempo total de fabricacion: %d minutos\n", tiempo_total);
    printf("Recursos totales necesarios: %d unidades\n", recursos_total);

    int tiempo_limite = 480;
    int recursos_limite = 1000;
    if (tiempo_total > tiempo_limite || recursos_total > recursos_limite) {
        printf("Advertencia! No se puede cumplir con la demanda.\n");
        printf("Limites: Tiempo <= %d min, Recursos <= %d unidades\n", tiempo_limite, recursos_limite);
    } else {
        printf("La fabrica puede cumplir con la demanda.\n");
    }
}

void mostrarProductos() {
    if (total_productos == 0) {
        printf("No hay productos registrados.\n");
        return;
    }
    printf("\n--- Lista de Productos ---\n");
    for (int i = 0; i < total_productos; i++) {
        printf("Producto %d:\n", i + 1);
        printf("  Nombre: %s\n", nombres[i]);
        printf("  Tiempo: %d minutos\n", tiempos[i]);
        printf("  Recursos: %d unidades\n", recursos[i]);
        printf("  Demanda: %d unidades\n\n", demandas[i]);
    }
}