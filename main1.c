#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ==========================================
// 3.1. ESTRUCTURA DE DATOS BASE
// ==========================================

typedef struct Paquete {
    int id;           // ID único (entero)
    float peso;       // Peso (flotante)
    int prioridad;    // Prioridad (1 a 5)
} Paquete;

typedef struct Nodo {
    Paquete dato;
    struct Nodo* siguiente;
} Nodo;

// --- Funciones Básicas de Gestión ---

void insertar_inicio(Nodo** cabeza, int id, float peso, int prioridad) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo) return;
    nuevo->dato.id = id;
    nuevo->dato.peso = peso;
    nuevo->dato.prioridad = prioridad;
    nuevo->siguiente = *cabeza;
    *cabeza = nuevo;
}

void imprimir_muestra(Nodo* cabeza, int limite) {
    Nodo* actual = cabeza;
    int contador = 0;
    while (actual != NULL && contador < limite) {
        printf("  [ID: %7d | Peso: %5.2f kg | Prioridad: %d]\n",
               actual->dato.id, actual->dato.peso, actual->dato.prioridad);
        actual = actual->siguiente;
        contador++;
    }
}

void liberar_memoria(Nodo** cabeza) {
    Nodo* actual = *cabeza;
    Nodo* siguiente = NULL;
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    *cabeza = NULL;
}

Nodo* duplicar_lista(Nodo* fuente) {
    if (fuente == NULL) return NULL;
    Nodo* nueva_cabeza = NULL;
    Nodo** ultimo = &nueva_cabeza;

    for (Nodo* actual = fuente; actual != NULL; actual = actual->siguiente) {
        Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
        nuevo->dato = actual->dato;
        nuevo->siguiente = NULL;
        *ultimo = nuevo;
        ultimo = &(nuevo->siguiente);
    }
    return nueva_cabeza;
}

// ==========================================
// 3.2. DISEÑO DE ALGORITMOS DE ORDENAMIENTO
// ==========================================

// 1. Fuerza Bruta: Selection Sort intercambiando enlaces nativamente
void ordenamiento_fuerza_bruta_enlaces(Nodo** cabeza) {
    if (*cabeza == NULL || (*cabeza)->siguiente == NULL) return;

    Nodo** p_actual = cabeza;
    while (*p_actual != NULL) {
        Nodo** p_min = p_actual;
        Nodo** p_cursor = &((*p_actual)->siguiente);

        while (*p_cursor != NULL) {
            if ((*p_cursor)->dato.id < (*p_min)->dato.id) {
                p_min = p_cursor;
            }
            p_cursor = &((*p_cursor)->siguiente);
        }

        if (p_min != p_actual) {
            Nodo* nodo_min = *p_min;
            Nodo* nodo_act = *p_actual;

            if (nodo_act->siguiente == nodo_min) {
                nodo_act->siguiente = nodo_min->siguiente;
                nodo_min->siguiente = nodo_act;
                *p_actual = nodo_min;
            } else {
                Nodo* temp = nodo_act->siguiente;
                nodo_act->siguiente = nodo_min->siguiente;
                nodo_min->siguiente = temp;
                *p_actual = nodo_min;
                *p_min = nodo_act;
            }
        }
        p_actual = &((*p_actual)->siguiente);
    }
}

// 2. Dividir y Conquistar: Merge Sort Iterativo Bottom-Up (Altamente Optimizado)
Nodo* mezclar_listas(Nodo* l1, Nodo* l2, Nodo** cola) {
    Nodo dummy;
    Nodo* actual = &dummy;

    while (l1 && l2) {
        if (l1->dato.id <= l2->dato.id) {
            actual->siguiente = l1;
            l1 = l1->siguiente;
        } else {
            actual->siguiente = l2;
            l2 = l2->siguiente;
        }
        actual = actual->siguiente;
    }
    actual->siguiente = l1 ? l1 : l2;
    while (actual->siguiente) {
        actual = actual->siguiente;
    }
    *cola = actual;
    return dummy.siguiente;
}

void merge_sort_iterativo(Nodo** cabeza_ref) {
    if (!*cabeza_ref || !(*cabeza_ref)->siguiente) return;

    Nodo* cabeza = *cabeza_ref;
    int tamano = 1;
    int largo = 0;

    for (Nodo* curr = cabeza; curr != NULL; curr = curr->siguiente) largo++;

    Nodo dummy;
    dummy.siguiente = cabeza;

    while (tamano < largo) {
        Nodo* prev = &dummy;
        Nodo* curr = dummy.siguiente;

        while (curr) {
            Nodo* left = curr;
            Nodo* right = NULL;
            Nodo* next_sub = NULL;

            // Cortar primera sublista
            int count = 1;
            while (count < tamano && curr->siguiente) {
                curr = curr->siguiente;
                count++;
            }
            right = curr->siguiente;
            curr->siguiente = NULL;
            curr = right;

            // Cortar segunda sublista
            if (right) {
                count = 1;
                while (count < tamano && curr->siguiente) {
                    curr = curr->siguiente;
                    count++;
                }
                next_sub = curr->siguiente;
                curr->siguiente = NULL;
                curr = next_sub;
            }

            // Mezclar ambas sublistas
            Nodo* cola = NULL;
            prev->siguiente = mezclar_listas(left, right, &cola);
            prev = cola;
        }
        tamano *= 2;
    }
    *cabeza_ref = dummy.siguiente;
}

// ==========================================
// 3.3. DISEÑO DE ALGORITMOS DE BÚSQUEDA
// ==========================================

// Búsqueda Lineal
Nodo* busqueda_lineal(Nodo* cabeza, int id_buscado) {
    for (Nodo* actual = cabeza; actual != NULL; actual = actual->siguiente) {
        if (actual->dato.id == id_buscado) {
            return actual;
        }
    }
    return NULL;
}

// ==========================================
// 3.4. SIMULACIÓN Y MEDICIÓN DE TIEMPO
// ==========================================

int main() {
    srand((unsigned int)time(NULL));

    Nodo* lista_original = NULL;
    int total_paquetes = 50000;
    int id_objetivo_existente = -1;

    printf("=========================================================\n");
    printf(" SISTEMA DE GESTION Y ANALISIS ALGORITMICO DE PAQUETES \n");
    printf("=========================================================\n\n");

    printf("Generando %d paquetes aleatorios...\n", total_paquetes);
    for (int i = 0; i < total_paquetes; i++) {
        int id = rand() % 1000000 + 1;
        float peso = (float)(rand() % 5000) / 100.0f + 0.1f;
        int prioridad = rand() % 5 + 1;

        insertar_inicio(&lista_original, id, peso, prioridad);

        if (i == total_paquetes / 2) {
            id_objetivo_existente = id;
        }
    }
    printf("Lista inicial de %d paquetes generada correctamente.\n\n", total_paquetes);

    printf("Muestra de los primeros 5 paquetes (Desordenados):\n");
    imprimir_muestra(lista_original, 5);
    printf("\n");

    // --- 1. EXPERIMENTACIÓN DE ORDENAMIENTO ---
    printf("---------------------------------------------------------\n");
    printf(" 1. EXPERIMENTACION DE ORDENAMIENTO                      \n");
    printf("---------------------------------------------------------\n");

    Nodo* lista_merge = duplicar_lista(lista_original);
    Nodo* lista_fuerza_bruta = duplicar_lista(lista_original);

    // Medición Merge Sort Iterativo
    clock_t inicio = clock();
    merge_sort_iterativo(&lista_merge);
    clock_t fin = clock();
    double tiempo_merge = ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000.0;
    printf("-> Merge Sort (Dividir y Conquistar) : %.2f ms\n", tiempo_merge);

    // Medición Selection Sort
    printf("-> Ejecutando Selection Sort (Fuerza Bruta por enlaces)... Por favor espere...\n");
    inicio = clock();
    ordenamiento_fuerza_bruta_enlaces(&lista_fuerza_bruta);
    fin = clock();
    double tiempo_fuerza_bruta = ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000.0;
    printf("-> Selection Sort (Fuerza Bruta)     : %.2f ms\n\n", tiempo_fuerza_bruta);

    printf("Muestra de los primeros 5 paquetes ordenados (Merge Sort):\n");
    imprimir_muestra(lista_merge, 5);
    printf("\n");

    // --- 2. EXPERIMENTACIÓN DE BÚSQUEDA MASIVA ---
    printf("---------------------------------------------------------\n");
    printf(" 2. EXPERIMENTACION DE BUSQUEDA MASIVA                   \n");
    printf("---------------------------------------------------------\n");

    int rondas_busqueda = 1000;
    printf("Ejecutando %d rondas de Busqueda Lineal en la lista...\n", rondas_busqueda);

    inicio = clock();
    for (int i = 0; i < rondas_busqueda; i++) {
        int target = (i % 2 == 0) ? id_objetivo_existente : (rand() % 1000000 + 1);
        busqueda_lineal(lista_merge, target);
    }
    fin = clock();
    double tiempo_busqueda = ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000.0;
    printf("-> Tiempo acumulado de %d busquedas lineales: %.2f ms\n\n", rondas_busqueda, tiempo_busqueda);

    // --- REPORTES Y HALLAZGOS EMPÍRICOS ---
    printf("---------------------------------------------------------\n");
    printf(" REPORTES Y HALLAZGOS EMPÍRICOS                         \n");
    printf("---------------------------------------------------------\n");
    
    printf("1. ORDENAMIENTO:\n");
    
    if (tiempo_merge < tiempo_fuerza_bruta) {
        printf("   Merge Sort fue más rápido que Fuerza Bruta (%.2f ms vs %.2f ms).\n", 
           tiempo_merge, tiempo_fuerza_bruta);
    } else {
        printf("   Selection Sort fue mas rapido en esta ejecucion (%.2f ms vs %.2f ms).\n",
           tiempo_fuerza_bruta, tiempo_merge);
    }
    
    printf("   Esto se debe a su complejidad O(n log n) frente al O(n^2) del Selection Sort.\n\n");
    
    printf("2. BÚSQUEDA Y LIMITACIÓN ESTRUCTURAL:\n");
    
    printf("   La búsqueda lineal secuencial requiere recorrer nodo por nodo O(n).\n");
    printf("   A pesar de tener la lista ordenada, las listas simples NO permiten acceso\n");
    printf("   directo por índice (p. ej., arr[mid]), lo que impide implementar una\n");
    printf("   búsqueda binaria O(log n) nativa sin estructuras adicionales.\n");
    printf("=========================================================\n");

    // Liberación de Memoria Dinámica
    liberar_memoria(&lista_original);
    liberar_memoria(&lista_merge);
    liberar_memoria(&lista_fuerza_bruta);

    printf("\nMemoria dinamica liberada exitosamente. Proceso finalizado.\n");
    return 0;
}
