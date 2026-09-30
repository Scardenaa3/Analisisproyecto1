# 📦 Sistema de Gestión y Análisis Algorítmico de Paquetes Logísticos

Aplicación ejecutable en consola desarrollada en **C** para la simulación, gestión, ordenamiento y búsqueda de paquetes en un centro de distribución utilizando **listas enlazadas simples**. 

El proyecto realiza un análisis y evaluación empírica comparando algoritmos de **Fuerza Bruta ($O(n^2)$)** y **Dividir y Conquistar ($O(n \log n)$)** sobre un volumen masivo de datos ($50.000+$ elementos), midiendo los tiempos reales de ejecución mediante la librería `<time.h>`.

---

## 🛠 Tecnologías y Estructura Base

* **Lenguaje:** C (Estándar C99 / C11)
* **Compilador:** GCC (`gcc`)
* **Entorno de Ejecución:** Linux / WSL (Windows Subsystem for Linux) / macOS
* **Estructura de Datos Base:** Lista enlazada simple basada en punteros dinámicos (`malloc` / `free`).
* **Medición de Tiempo:** Librería estándar `<time.h>` para métricas en milisegundos (`ms`).

### 📐 Modelo de Datos (`struct`)
```c
typedef struct Paquete {
    int id;           // ID único (entero)
    float peso;       // Peso en kg (flotante)
    int prioridad;    // Nivel de prioridad (1 a 5)
} Paquete;

typedef struct Nodo {
    Paquete dato;
    struct Nodo* siguiente;
} Nodo;
