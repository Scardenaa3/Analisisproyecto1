from reportlab.lib.pagesizes import letter
from reportlab.lib import colors
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Table, TableStyle
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.units import cm

def crear_pdf_informe(nombre_archivo="Informe_Analisis_Algoritmico.pdf"):
    # Configuración del documento con márgenes de 2.5 cm
    doc = SimpleDocTemplate(
        nombre_archivo,
        pagesize=letter,
        rightMargin=2.5 * cm,
        leftMargin=2.5 * cm,
        topMargin=2.5 * cm,
        bottomMargin=2.5 * cm
    )

    story = []

    # --- ESTILOS (Arial, 12pt, Negritas) ---
    styles = getSampleStyleSheet()

    # Título Principal (Arial 18pt Negrita)
    estilo_titulo = ParagraphStyle(
        'TituloPrincipal',
        parent=styles['Normal'],
        fontName='Helvetica-Bold',
        fontSize=18,
        leading=22,
        alignment=1, # Centrado
        spaceAfter=15
    )

    # Subtítulos Sección (Arial 12pt Negrita)
    estilo_subtitulo = ParagraphStyle(
        'SubtituloSeccion',
        parent=styles['Normal'],
        fontName='Helvetica-Bold',
        fontSize=12,
        leading=16,
        spaceBefore=12,
        spaceAfter=6
    )

    # Sub-subtítulos (Arial 12pt Negrita)
    estilo_subsubtitulo = ParagraphStyle(
        'SubSubtituloSeccion',
        parent=styles['Normal'],
        fontName='Helvetica-Bold',
        fontSize=12,
        leading=16,
        spaceBefore=8,
        spaceAfter=4
    )

    # Texto General (Arial 12pt)
    estilo_texto = ParagraphStyle(
        'TextoBase',
        parent=styles['Normal'],
        fontName='Helvetica',
        fontSize=12,
        leading=16,
        spaceAfter=6,
        alignment=4 # Justificado
    )

    # Texto para Tablas y Listas (Arial 12pt)
    estilo_tabla_encabezado = ParagraphStyle(
        'TablaEncabezado',
        parent=styles['Normal'],
        fontName='Helvetica-Bold',
        fontSize=12,
        leading=14,
        alignment=1
    )

    estilo_tabla_celda = ParagraphStyle(
        'TablaCelda',
        parent=styles['Normal'],
        fontName='Helvetica',
        fontSize=12,
        leading=14,
        alignment=0
    )

    estilo_tabla_celda_centro = ParagraphStyle(
        'TablaCeldaCentro',
        parent=styles['Normal'],
        fontName='Helvetica',
        fontSize=12,
        leading=14,
        alignment=1
    )

    # --- CONTENIDO DEL INFORME ---

    # Título Principal
    story.append(Paragraph("Informe de Análisis Algorítmico y Empírico: Sistema de Gestión de Paquetes Logísticos", estilo_titulo))
    story.append(Spacer(1, 10))

    # Encabezado de Datos
    p_meta = Paragraph(
        "<b>Asignatura:</b> Análisis de Algoritmos<br/>"
        "<b>Institución:</b> Universidad EAFIT<br/>"
        "<b>Plataforma de Entrega:</b> EAFIT Interactiva<br/>"
        "<b>Repositorio de GitHub:</b> https://github.com/Scardenaa3/Analisisproyecto1",
        estilo_texto
    )
    story.append(p_meta)
    story.append(Spacer(1, 10))

    # Integrantes
    story.append(Paragraph("Integrantes y Distribución de Responsabilidades", estilo_subtitulo))
    
    data_integrantes = [
        [Paragraph("Integrante", estilo_tabla_encabezado), Paragraph("Rol y Responsabilidades", estilo_tabla_encabezado)],
        [Paragraph("Santiago Cárdenas", estilo_tabla_celda), Paragraph("Diseñador Principal y Desarrollador — Implementación del algoritmo Merge Sort Iterativo (Bottom-Up), arquitectura del módulo de medición de tiempos (<time.h>) e integración general.", estilo_tabla_celda)],
        [Paragraph("Viliam Sofía Mesa", estilo_tabla_celda), Paragraph("Analista de Datos y Desarrolladora — Implementación del módulo de Búsqueda Lineal, manejo de escenarios de prueba (casos borde) y validación de la generación aleatoria de paquetes.", estilo_tabla_celda)],
        [Paragraph("Mariana Cardona", estilo_tabla_celda), Paragraph("Desarrolladora de Estructuras — Implementación del algoritmo Selection Sort intercambiando enlaces nativos sobre listas enlazadas simples y elaboración de pruebas unitarias.", estilo_tabla_celda)]
    ]
    
    t_integrantes = Table(data_integrantes, colWidths=[4.5*cm, 12*cm])
    t_integrantes.setStyle(TableStyle([
        ('BACKGROUND', (0,0), (1,0), colors.HexColor('#EAEAEA')),
        ('GRID', (0,0), (-1,-1), 0.5, colors.grey),
        ('VALIGN', (0,0), (-1,-1), 'TOP'),
        ('BOTTOMPADDING', (0,0), (-1,-1), 6),
        ('TOPPADDING', (0,0), (-1,-1), 6),
    ]))
    story.append(t_integrantes)
    story.append(Spacer(1, 12))

    # Sección 1
    story.append(Paragraph("1. Introducción y Descripción del Problema", estilo_subtitulo))
    story.append(Paragraph(
        "El proyecto aborda la simulación y gestión eficiente de paquetes en un centro de distribución logístico "
        "mediante listas enlazadas simples en lenguaje C. El objetivo fundamental es evaluar el rendimiento de dos "
        "paradigmas de diseño algorítmico (Fuerza Bruta vs. Dividir y Conquistar) al procesar volúmenes masivos de "
        "datos (N = 50.000 paquetes), así como analizar las limitaciones estructurales en las operaciones de búsqueda "
        "sobre estructuras dinámicas de acceso secuencial.",
        estilo_texto
    ))

    # Sección 2
    story.append(Paragraph("2. Modelado de Datos y Algoritmos Implementados", estilo_subtitulo))
    
    story.append(Paragraph("2.1. Estructura de Datos Base", estilo_subsubtitulo))
    story.append(Paragraph(
        "Cada paquete en el sistema se modela con la estructura Paquete (que contiene identificador único ID, peso en "
        "kilogramos y prioridad de envío del 1 al 5) y se almacena dinámicamente mediante punteros en un Nodo de lista enlazada.",
        estilo_texto
    ))

    story.append(Paragraph("2.2. Algoritmos de Ordenamiento", estilo_subsubtitulo))
    story.append(Paragraph(
        "<b>Selection Sort por Enlaces Nativos (Fuerza Bruta):</b> Busca iterativamente el nodo con el menor ID dentro de la "
        "sublista no ordenada y ajusta los punteros siguiente de los nodos involucrados para reposicionarlo. No intercambia los "
        "valores contenidos en la estructura, sino la memoria física mediante la reconfiguración estricta de sus enlaces. Complejidad: O(N^2).",
        estilo_texto
    ))
    story.append(Paragraph(
        "<b>Merge Sort Iterativo Bottom-Up (Dividir y Conquistar):</b> Evita la recursión para controlar el uso del call stack. "
        "Inicia fusionando sublistas de tamaño 1, 2, 4, 8, etc., cortando los enlaces y mezclándolas de forma ordenada en una lista "
        "auxiliar mediante una función iterativa de combinación. Opera nativamente sobre la lista simple sin requerir arreglos auxiliares. Complejidad: O(N log N).",
        estilo_texto
    ))

    story.append(Paragraph("2.3. Algoritmo de Búsqueda y Análisis de Limitación Estructural", estilo_subsubtitulo))
    story.append(Paragraph(
        "<b>Búsqueda Lineal:</b> Recorre secuencialmente la lista nodo por nodo desde la cabeza (head) hasta hallar el ID o alcanzar NULL, con complejidad O(N).<br/>"
        "<b>Análisis de Limitación de Búsqueda Binaria en Listas Enlazadas:</b> Aunque la lista se encuentre perfectamente ordenada mediante Merge Sort, "
        "no es viable implementar una Búsqueda Binaria de orden O(log N) de manera nativa y eficiente. Esto se debe a que las listas simples carecen "
        "de acceso aleatorio por índice O(1). Acceder al elemento medio requiere recorrer N/2 nodos, lo que transforma la ecuación de recurrencia en "
        "T(N) = T(N/2) + O(N), degradando la complejidad de la búsqueda a O(N).",
        estilo_texto
    ))

    # Sección 3
    story.append(Paragraph("3. Experimentos Empíricos y Tiempos de Ejecución", estilo_subtitulo))
    story.append(Paragraph(
        "La simulación se ejecutó sobre un entorno Linux / WSL con una muestra masiva de 50.000 paquetes generados aleatoriamente.",
        estilo_texto
    ))

    data_exp = [
        [Paragraph("Operación", estilo_tabla_encabezado), Paragraph("Algoritmo / Método", estilo_tabla_encabezado), Paragraph("Paradigma / Complejidad", estilo_tabla_encabezado), Paragraph("Tiempo Medido (ms)", estilo_tabla_encabezado)],
        [Paragraph("Ordenamiento", estilo_tabla_celda), Paragraph("Merge Sort Iterativo", estilo_tabla_celda), Paragraph("Dividir y Conquistar — O(N log N)", estilo_tabla_celda), Paragraph("<b>6.50 ms</b>", estilo_tabla_celda_centro)],
        [Paragraph("Ordenamiento", estilo_tabla_celda), Paragraph("Selection Sort por Enlaces", estilo_tabla_celda), Paragraph("Fuerza Bruta — O(N^2)", estilo_tabla_celda), Paragraph("<b>5198.58 ms</b> (~5.2 s)", estilo_tabla_celda_centro)],
        [Paragraph("Búsqueda Individual", estilo_tabla_celda), Paragraph("Búsqueda Lineal (Elemento Existente)", estilo_tabla_celda), Paragraph("Recorrido Secuencial — O(N)", estilo_tabla_celda), Paragraph("< 0.5 ms", estilo_tabla_celda_centro)],
        [Paragraph("Búsqueda Individual", estilo_tabla_celda), Paragraph("Búsqueda Lineal (ID Inexistente -9999)", estilo_tabla_celda), Paragraph("Recorrido Secuencial — O(N)", estilo_tabla_celda), Paragraph("< 0.5 ms", estilo_tabla_celda_centro)],
        [Paragraph("Búsqueda Masiva", estilo_tabla_celda), Paragraph("1000 Rondas (50% Éxito / 50% Fallo)", estilo_tabla_celda), Paragraph("Recorrido Secuencial — O(N)", estilo_tabla_celda), Paragraph("<b>356.78 ms</b>", estilo_tabla_celda_centro)]
    ]

    t_exp = Table(data_exp, colWidths=[3.5*cm, 4.5*cm, 5.0*cm, 3.5*cm])
    t_exp.setStyle(TableStyle([
        ('BACKGROUND', (0,0), (-1,0), colors.HexColor('#EAEAEA')),
        ('GRID', (0,0), (-1,-1), 0.5, colors.grey),
        ('VALIGN', (0,0), (-1,-1), 'MIDDLE'),
        ('BOTTOMPADDING', (0,0), (-1,-1), 5),
        ('TOPPADDING', (0,0), (-1,-1), 5),
    ]))
    story.append(t_exp)
    story.append(Spacer(1, 12))

    # Sección 4
    story.append(Paragraph("4. Discusión de Resultados y Hallazgos", estilo_subtitulo))
    story.append(Paragraph(
        "<b>1. Eficiencia en Ordenamiento:</b> La medición empírica valida plenamente la teoría algorítmica: Merge Sort (6.50 ms) fue aproximadamente "
        "800 veces más rápido que Selection Sort (5198.58 ms) sobre un conjunto de 50.000 elementos. La diferencia entre un crecimiento cuadrático N^2 "
        "(~2.5 x 10^9 comparaciones) y un crecimiento logarítmico N log2 N (~7.8 x 10^5 comparaciones) es abrumadora en entornos de volumen masivo.",
        estilo_texto
    ))
    story.append(Paragraph(
        "<b>2. Costo de Modificación de Enlaces vs. Arreglos:</b> La implementación de Selection Sort intercambiando punteros directamente en la lista "
        "evita copias en memoria de las estructuras completas, pero introduce operaciones adicionales de punteros que acentúan la degradación temporal a medida que N crece.",
        estilo_texto
    ))
    story.append(Paragraph(
        "<b>3. Inviabilidad de Búsqueda Binaria Secuencial:</b> Las mediciones en el módulo de búsqueda masiva (356.78 ms para 1000 consultas) confirman que "
        "el costo de búsqueda acumulado en listas secuenciales depende del recorrido de enlaces. Para lograr consultas O(log N) en sistemas de paquetes "
        "dinámicos, se requeriría migrar hacia estructuras jerárquicas avanzadas (como Árboles Binarios de Búsqueda AVL / Red-Black) o Tablas Hash O(1).",
        estilo_texto
    ))

    # Sección 5
    story.append(Paragraph("5. Conclusiones", estilo_subtitulo))
    story.append(Paragraph(
        "<b>Rendimiento Algorítmico:</b> El paradigma Dividir y Conquistar (Merge Sort) es el estándar recomendado para el procesamiento masivo en sistemas de logística "
        "industrial, demostrando una escalabilidad superior frente a alternativas de Fuerza Bruta.<br/>"
        "<b>Elección de Estructuras de Datos:</b> Las listas enlazadas simples son ideales para operaciones dinámicas de inserción y eliminación sin reorganización de memoria fija O(1) al inicio, "
        "pero presentan severas restricciones en rendimiento para operaciones de búsqueda masiva debido a su naturaleza de acceso secuencial.<br/>"
        "<b>Gestión de Memoria:</b> El desarrollo en C exige un control riguroso de memoria dinámica (malloc / free), garantizando la liberación total de los nodos clonados y procesados en cada simulación.",
        estilo_texto
    ))

    # Construir PDF
    doc.build(story)
    print(f"PDF generado exitosamente: {nombre_archivo}")

if __name__ == "__main__":
    crear_pdf_informe()
