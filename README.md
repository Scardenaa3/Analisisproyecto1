# Sistema de Gestión y Análisis Algorítmico de Paquetes Logísticos

Aplicación ejecutable en consola desarrollada en C para la simulación, ordenamiento y búsqueda de paquetes en un centro de distribución utilizando **listas enlazadas simples**. El proyecto realiza una evaluación empírica comparando algoritmos de **Fuerza Bruta** y **Dividir y Conquistar** sobre un volumen masivo de datos ($50.000+$ elementos).

---

##  Tecnologías y Estructura Base

* **Lenguaje:** C (Estándar C99 / C11)
* **Entorno de Ejecución:** Linux / WSL (Windows Subsystem for Linux)[cite: 1]
* **Compilador:** GCC (`gcc`)[cite: 1]
* **Estructura de Datos Base:** `struct Nodo` que almacena un `Paquete` (ID único, peso y prioridad) y un puntero al siguiente elemento.
* **Medición de Tiempo:** Librería estándar `<time.h>` para métricas en milisegundos (`ms`).

---

##  Instalación y Ejecución en WSL

1. **Clonar el repositorio:**
   ```bash
   git clone [https://github.com/tu-usuario/tu-repositorio.git](https://github.com/tu-usuario/tu-repositorio.git)
   cd tu-repositorio
