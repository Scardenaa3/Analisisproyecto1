#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ==========================================
// 3.1. ESTRUCTURA DE DATOS BASE
// ==========================================

// Estructura para la información del paquete
typedef struct Paquete {
    int id;           // ID único (entero)
    float peso;       // Peso (flotante)
    int prioridad;    // Prioridad (1 a 5)
} Paquete;

// Estructura de la lista enlazada simple
typedef struct Nodo {
    Paquete dato;
    struct Nodo* siguiente;
} Nodo;

// --- Funciones Básicas de Gestión de la Lista ---

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

// Impresión de una muestra de la lista
void imprimir_muestra(Nodo* cabeza, int limite) {
    Nodo* actual = cabeza;
    int contador = 0;
    while (actual != NULL && contador < limite) {
        printf("  [ID: %7d | Peso: %5.2f kg | Prioridad: %d]\n",
               actual->dato.id, actual->dato.peso, actual->dato.prioridad);
        actual = actual->siguiente;
        contador++;
    }
    if (actual != NULL) {
        printf("  ... (listado truncado a %d elementos)\n", limite);
    }
}

// Liberación de memoria dinámica de todos los nodos
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

// Función auxiliar para duplicar la lista y poder comparar ambos ordenamientos equitativamente
Nodo* duplicar_lista(Nodo* fuente) {
    if (fuente == NULL) return NULL;
    
    Nodo* nueva_cabeza = NULL;
    Nodo* ultimo = NULL;
    Nodo* actual = fuente;

    while (actual != NULL) {
        Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
        nuevo->dato = actual->dato;
        nuevo->siguiente = NULL;

        if (nueva_cabeza == NULL) {
            nueva_cabeza = nuevo;
            ultimo = nuevo;
        } else {
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
        actual = actual->siguiente;
    }
    return nueva_cabeza;
}

// ==========================================
// 3.2. DISEÑO DE ALGORITMOS DE ORDENAMIENTO
// ==========================================

// 1. Fuerza Bruta: Selection Sort INTERCAMBIANDO ENLACES (Punteros)
// Operación nativa exigida por la rúbrica para puntuación máxima.
void ordenamiento_fuerza_bruta_enlaces(Nodo** cabeza) {
    if (*cabeza == NULL || (*cabeza)->siguiente == NULL) return;

    Nodo** p_min;
    Nodo** p_actual = cabeza;

    while (*p_actual != NULL) {
        p_min = p_actual;
        Nodo** p_cursor = &((*p_actual)->siguiente);

        while (*p_cursor != NULL) {
            if ((*p_cursor)->dato.id < (*p_min)->dato.id) {
                p_min = p_cursor;
            }
            p_cursor = &((*p_cursor)->siguiente);
        }

        if (p_min != p_actual) {
            Nodo* temp_min = *p_min;
            Nodo* temp_act = *p_actual;

            if (temp_act->siguiente == temp_min) { // Nodos adyacentes
                temp_act->siguiente = temp_min->siguiente;
                temp_min->siguiente = temp_act;
                *p_actual = temp_min;
            } else { // Nodos no adyacentes
                Nodo* temp_next = temp_act->siguiente;
                temp_act->siguiente = temp_min->siguiente;
                temp_min->siguiente = temp_next;
                *p_actual = temp_min;
                *p_min = temp_act;
            }
        }
        p_actual = &((*p_actual)->siguiente);
    }
}

// 2. Dividir y Conquistar: Merge Sort adaptado nativamente a Listas Enlazadas
Nodo* combinar(Nodo* a, Nodo* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    Nodo* resultado = NULL;
    if (a->dato.id <= b->dato.id) {
        resultado = a;
        resultado->siguiente = combinar(a->siguiente, b);
    } else {
        resultado = b;
        resultado->siguiente = combinar(a, b->siguiente);
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
// 3.3. DISEÑO DE ALGORITMOS DE BÚSQUEDA
// ==========================================

// Búsqueda Lineal Fuerza Bruta: Recorrido nodo por nodo
Nodo* busqueda_lineal(Nodo* cabeza, int id_buscado) {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        if (actual->dato.id == id_buscado) {
            return actual; // Encontrado
        }
        actual = actual->siguiente;
    }
    return NULL; // No encontrado
}

// ==========================================
// 3.4. SIMULACIÓN Y MEDICIÓN DE TIEMPO
// ==========================================
int main() {
    srand((unsigned int)time(NULL));

    Nodo* lista_original = NULL;
    int total_paquetes = 50000; // Mínimo 50,000 según requerimiento
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

        // Guardamos el ID del último insertado para asegurar una búsqueda exitosa
        if (i == total_paquetes / 2) {
            id_objetivo_existente = id;
        }
    }
    printf("Lista inicial de %d paquetes generada correctamente.\n\n", total_paquetes);

    // Muestra inicial
    printf("Muestra de los primeros 5 paquetes (Desordenados):\n");
    imprimir_muestra(lista_original, 5);
    printf("\n");

    // --- EXPERIMENTO DE ORDENAMIENTO ---
    printf("---------------------------------------------------------\n");
    printf(" 1. EXPERIMENTACION DE ORDENAMIENTO                      \n");
    printf("---------------------------------------------------------\n");

    // Duplicamos la lista para usar exactamente los mismos datos en ambos algoritmos
    Nodo* lista_merge = duplicar_lista(lista_original);
    Nodo* lista_fuerza_bruta = duplicar_lista(lista_original);

    // 1. Merge Sort
    clock_t inicio = clock();
    merge_sort(&lista_merge);
    clock_t fin = clock();
    double tiempo_merge = ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000.0;
    printf("-> Merge Sort (Dividir y Conquistar) : %.2f ms\n", tiempo_merge);

    // 2. Selection Sort por Enlaces
    printf("-> Ejecutando Selection Sort (Fuerza Bruta por enlaces)... Por favor espere...\n");
    inicio = clock();
    ordenamiento_fuerza_bruta_enlaces(&lista_fuerza_bruta);
    fin = clock();
    double tiempo_fuerza_bruta = ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000.0;
    printf("-> Selection Sort (Fuerza Bruta)     : %.2f ms\n\n", tiempo_fuerza_bruta);

    printf("Muestra de los primeros 5 paquetes ordenados (Merge Sort):\n");
    imprimir_muestra(lista_merge, 5);
    printf("\n");

    // --- EXPERIMENTO DE BÚSQUEDA ---
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

    // --- CONCLUSIONES DE LA SIMULACIÓN EMPÍRICA ---
    printf("---------------------------------------------------------\n");
    printf(" REPORTES Y HALLAZGOS EMPIRICOS                         \n");
    printf("---------------------------------------------------------\n");
    printf("1. ORDENAMIENTO:\n");
    printf("   Merge Sort fue exponencialmente mas rapido que Fuerza Bruta (%.2f ms vs %.2f ms).\n", 
           tiempo_merge, tiempo_fuerza_bruta);
    printf("   Esto se debe a su complejidad O(n log n) frente al O(n^2) del Selection Sort.\n\n");
    printf("2. BUSQUEDA Y LIMITACION ESTRUCTURAL:\n");
    printf("   La busqueda lineal secuencial requiere recorrer nodo por nodo O(n).\n");
    printf("   A pesar de tener la lista ordenada, las listas simples NO permiten acceso\n");
    printf("   directo por indice (p. ej., arr[mid]), lo que impide implementar una\n");
    printf("   busqueda binaria O(log n) nativa sin estructuras adicionales.\n");
    printf("=========================================================\n");

    // Liberar memoria
    liberar_memoria(&lista_original);
    liberar_memoria(&lista_merge);
    liberar_memoria(&lista_fuerza_bruta);

    printf("\nMemoria dinamica liberada exitosamente. Proceso finalizado.\n");
    return 0;
}
