# Documentacion

## Entrega

La entrega se realiza via **aula.usm.cl** en formato `.zip`.

## Multiplicacion de matrices

### Programa principal
Este programa en C++ implementa y evalua los algoritmos de multiplicacion de matrices cuadradas (metodo iterativo Naive y el algoritmo divide y venceras de Strassen en su version pura). 
Para compilar el codigo, navegue a la carpeta correspondiente y utilice el compilador mediante el comando 'make'. Luego, ejecute el programa principal con './matrix_multiplication'. 
El programa leera los datasets de prueba (tamaños desde 16x16 hasta 1024x1024), medira el tiempo de CPU en milisegundos y el consumo maximo historico de memoria RAM (Peak RSS) para cada ejecucion, y guardara automaticamente todas las metricas en un archivo '.csv' dentro de la subcarpeta 'data/measurements/'.

### Scripts
Contiene el script desarrollado en Python 3 encargado de leer el archivo '.csv' generado por el programa principal y graficar los resultados.
Para ejecutarlo, asegurese de tener instaladas las librerias 'pandas' y 'matplotlib', y corra el comando 'python3 scripts/plot_generator.py' (o el nombre correspondiente de su script). El script procesara los promedios de las mediciones y exportara el grafico en formato '.png' (escala log-log) directamente hacia la carpeta 'data/plots/'.

## Ordenamiento de arreglo unidimensional

Algoritmos: MergeSort, QuickSort, PatienceSort, std::sort.

### Programa principal
Este modulo en C++ evalua el rendimiento empirico de cuatro algoritmos de ordenamiento frente a arreglos de distintos tamaños (desde N=10 hasta N=10.000.000) y diferentes dominios (aleatorios, ascendentes y descendentes).
Para compilar, ingrese a la carpeta correspondiente y ejecute 'make'. Para iniciar el experimento, corra el binario './sorting'. El programa procesara las tres muestras por cada configuracion, registrara el tiempo de ejecucion y la huella de memoria dinamica, consolidando los resultados en el archivo 'sorting_measurements.csv' dentro de 'data/measurements/'.

### Scripts
Contiene el script analitico en Python 3 utilizado para visualizar el comportamiento asintotico de los algoritmos de ordenamiento.
Se ejecuta mediante 'python3 scripts/plot_generator.py'. El script filtra los datos del experimento (por ejemplo, el caso representativo Aleatorio D7) y genera graficos de linea comparativos de tiempo vs. tamaño del arreglo. Las imagenes resultantes se guardan en la carpeta 'data/plots/'


## Adicional
Los codigos C++ de esta tarea fueron sacados de geek for geeks. 