#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ==========================================
// ESTRUCTURAS Y TIPOS DE DATOS
// ==========================================
typedef struct Paquete {
    int id;
    float peso;
    int prioridad; // Entre 1 y 5
} Paquete;

typedef struct Nodo {
    Paquete dato;
    struct Nodo* siguiente;
} Nodo;

// ==========================================
// FUNCIONES DE GESTIÓN DE LISTA
// ==========================================

// Inserción al inicio de la lista
void insertar_inicio(Nodo** cabeza, int id, float peso, int prioridad) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo) {
        printf("Error: Memoria insuficiente.\n");
        return;
    }
    nuevo->dato.id = id;
    nuevo->dato.peso = peso;
    nuevo->dato.prioridad = prioridad;
    nuevo->siguiente = *cabeza;
    *cabeza = nuevo;
}

// Liberación completa de memoria
void liberar_lista(Nodo** cabeza) {
    Nodo* actual = *cabeza;
    Nodo* siguiente = NULL;
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    *cabeza = NULL;
}

// Mostrar los primeros N elementos
void mostrar_primeros_n(Nodo* cabeza, int n) {
    Nodo* actual = cabeza;
    int contador = 0;
    while (actual != NULL && contador < n) {
        printf("  [ID: %6d | Peso: %5.2f kg | Prioridad: %d]\n", 
               actual->dato.id, actual->dato.peso, actual->dato.prioridad);
        actual = actual->siguiente;
        contador++;
    }
}

// ==========================================
// ALGORITMOS DE ORDENAMIENTO
// ==========================================

// 1. Fuerza Bruta: Bubble Sort (Intercambio de datos)
void ordenamiento_fuerza_bruta(Nodo* cabeza) {
    if (cabeza == NULL) return;
    int intercambiado;
    Nodo* ptr1;
    Nodo* lptr = NULL;

    do {
        intercambiado = 0;
        ptr1 = cabeza;

        while (ptr1->siguiente != lptr) {
            if (ptr1->dato.id > ptr1->siguiente->dato.id) {
                Paquete temp = ptr1->dato;
                ptr1->dato = ptr1->siguiente->dato;
                ptr1->siguiente->dato = temp;
                intercambiado = 1;
            }
            ptr1 = ptr1->siguiente;
        }
        lptr = ptr1;
    } while (intercambiado);
}

// 2. Dividir y Conquistar: Merge Sort para listas enlazadas
Nodo* combinar(Nodo* a, Nodo* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    Nodo* resultado = NULL;
    if (a->dato.id <= b->dato.id) {
        resultado = a;
        resultado->siguiente = combinar(a->siguiente, b);
    } else {
        resultado = b;
        resultado->siguiente = combinar(a->siguiente, b->siguiente); // Ajuste de enlace
    }
    return resultado;
}

void dividir_lista(Nodo* fuente, Nodo** frente, Nodo** atras) {
    Nodo* rapido;
    Nodo* lento;
    lento = fuente;
    rapido = fuente->siguiente;

    while (rapido != NULL) {
        rapido = rapido->siguiente;
        if (rapido != NULL) {
            lento = lento->siguiente;
            rapido = rapido->siguiente;
        }
    }
    *frente = fuente;
    *atras = lento->siguiente;
    lento->siguiente = NULL;
}

void merge_sort(Nodo** cabeza_ref) {
    Nodo* cabeza = *cabeza_ref;
    Nodo* a;
    Nodo* b;

    if ((cabeza == NULL) || (cabeza->siguiente == NULL)) {
        return;
    }

    dividir_lista(cabeza, &a, &b);

    merge_sort(&a);
    merge_sort(&b);

    *cabeza_ref = combinar(a, b);
}

// ==========================================
// ALGORITMOS DE BÚSQUEDA
// ==========================================

// Búsqueda Lineal
Nodo* busqueda_lineal(Nodo* cabeza, int id_buscado) {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        if (actual->dato.id == id_buscado) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

// ==========================================
// FUNCIÓN PRINCIPAL / SIMULACIÓN
// ==========================================
int main() {
    srand((unsigned int)time(NULL));
    Nodo* lista_fuerza_bruta = NULL;
    Nodo* lista_merge_sort = NULL;

    int total_paquetes = 50000;
    printf("====================================================\n");
    printf(" SISTEMA DE GESTIÓN Y ANÁLISIS DE PAQUETES LOGÍSTICOS \n");
    printf("====================================================\n\n");

    printf("Generando %d paquetes aleatorios...\n", total_paquetes);
    for (int i = 0; i < total_paquetes; i++) {
        int id = rand() % 1000000 + 1;
        float peso = (float)(rand() % 5000) / 100.0f + 0.1f;
        int prioridad = rand() % 5 + 1;

        insertar_inicio(&lista_fuerza_bruta, id, peso, prioridad);
        insertar_inicio(&lista_merge_sort, id, peso, prioridad);
    }
    printf("Poblacion de datos completada.\n\n");

    // --- EXPERIMENTACIÓN DE ORDENAMIENTO ---
    printf("--- MEDICION DE TIEMPOS DE ORDENAMIENTO ---\n");
    
    clock_t inicio = clock();
    merge_sort(&lista_merge_sort);
    clock_t fin = clock();
    double tiempo_merge = ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000.0;
    printf("1. Merge Sort (Dividir y Conquistar) : %.2f ms\n", tiempo_merge);

    printf("2. Ejecutando Bubble Sort (Fuerza Bruta)... Por favor espere...\n");
    inicio = clock();
    ordenamiento_fuerza_bruta(lista_fuerza_bruta);
    fin = clock();
    double tiempo_bubble = ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000.0;
    printf("   Bubble Sort (Fuerza Bruta)          : %.2f ms\n\n", tiempo_bubble);

    // --- EXPERIMENTACIÓN DE BÚSQUEDA ---
    printf("--- MEDICION DE TIEMPOS DE BUSQUEDA ---\n");
    int rondas_busqueda = 1000;
    inicio = clock();
    for (int i = 0; i < rondas_busqueda; i++) {
        int target_id = rand() % 1000000 + 1;
        busqueda_lineal(lista_merge_sort, target_id);
    }
    fin = clock();
    double tiempo_busqueda = ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000.0;
    printf("Tiempo total para %d busquedas lineales masivas: %.2f ms\n\n", rondas_busqueda, tiempo_busqueda);

    // Muestra de los primeros 5 elementos ordenados
    printf("Muestra de los primeros 5 paquetes ordenados por ID (Merge Sort):\n");
    mostrar_primeros_n(lista_merge_sort, 5);

    // Liberación de memoria
    liberar_lista(&lista_fuerza_bruta);
    liberar_lista(&lista_merge_sort);
    printf("\nMemoria liberada correctamente. Programa finalizado.\n");

    return 0;
}
