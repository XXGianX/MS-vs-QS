# Informe: Laboratorio Quicksort vs Merge Sort

## Implementación de la partición

Se implementó la partición de Lomuto en `src/quicksort.c`, usando `arr[right]` como pivote.
El índice `i` avanza cada vez que se encuentra un elemento `≤ pivote`, intercambiándolo
hacia la izquierda. Al finalizar, el pivote se coloca en `i+1` y se devuelve esa posición.

```c
static int partition(int arr[], int left, int right){
  int pivot = arr[right];
  int i = left - 1;
  for(int j = left; j < right; j++){
    if(arr[j] <= pivot){
      i++;
      swapInt(&arr[i], &arr[j]);
    }
  }
  swapInt(&arr[i + 1], &arr[right]);
  return i + 1;
}
```

---

## Respuestas a las preguntas del informe

### 1. ¿Quicksort ordenó correctamente todos los casos ejecutados?

Sí. Ninguna línea del archivo `results/results.csv` contiene `sorted=0`.
Todos los 280 casos (7 tamaños × 4 tipos × 5 semillas × 2 algoritmos) terminaron con `sorted=1`.

---

### 2. Para entradas aleatorias, ¿qué algoritmo fue más rápido en promedio?

Quicksort fue más rápido en todos los tamaños probados. La razón R(n) = T_merge / T_quick
se mantuvo por encima de 1 en todo momento (ver gráfico `ratio_random.png`):

| n       | T_quick (s)   | T_merge (s)   | R(n)  |
|---------|---------------|---------------|-------|
| 1 000   | 0.0000439     | 0.0000640     | 1.46  |
| 10 000  | 0.000591      | 0.000724      | 1.22  |
| 100 000 | 0.00684       | 0.00919       | 1.34  |

Quicksort resultó aproximadamente **1.2–1.5× más rápido** que merge sort en entradas aleatorias.

---

### 3. ¿La razón R(n) aumenta, disminuye o se mantiene estable cuando crece n?

R(n) cae levemente al pasar de n=1 000 a n=2 000 (~1.46 → ~1.15), luego **sube y se
estabiliza** alrededor de 1.3–1.35 para n ≥ 10 000. En general, la ventaja de quicksort
se mantiene relativamente estable a escala grande, sin crecer indefinidamente ni desaparecer.

---

### 4. ¿Qué ocurrió con las entradas ordenadas e inversamente ordenadas?

Quicksort exhibió su **peor caso O(n²)** en ambas situaciones. Con el pivote igual al último
elemento, una entrada ya ordenada (o invertida) produce particiones completamente desbalanceadas
(0 elementos a un lado, n−1 al otro), degradando la recursión a n niveles de profundidad.

| n       | T_quick sorted (s) | T_merge sorted (s) |
|---------|--------------------|--------------------|
| 10 000  | 0.039              | 0.000231           |
| 50 000  | 0.978              | 0.00116            |
| 100 000 | **3.93**           | 0.00236            |

Para n=100 000, quicksort tardó casi **4 segundos** frente a los **2 ms** de merge sort;
merge sort fue ~1 600× más rápido. El comportamiento con entrada invertida fue idéntico.

---

### 5. ¿Qué ocurrió con las entradas con muchos elementos repetidos?

Con la partición de Lomuto los elementos iguales al pivote van todos al mismo lado,
produciendo también particiones desbalanceadas cuando hay muchos repetidos. Sin embargo,
como los valores repetidos son aleatorios (rango 0–99) y no están concentrados en el pivote,
el desbalance es moderado. Quicksort fue **más rápido** que merge sort para todos los tamaños,
pero su ventaja fue menor que con entradas aleatorias:

| n       | T_quick (s) | T_merge (s) |
|---------|-------------|-------------|
| 10 000  | 0.000794    | 0.000660    |
| 100 000 | 0.0427      | 0.00680     |

Para n=100 000, merge sort ya aventajó a quicksort en este tipo de entrada (~6.3×),
lo que anticipa que con más repeticiones la situación empeoraría para quicksort.

---

### 6. ¿Qué detalles de implementación podrían cambiar los resultados?

- **Elección del pivote**: usar la mediana de tres (primero, medio, último) o un pivote
  aleatorio elimina el peor caso O(n²) en entradas ordenadas/invertidas, siendo la mejora
  más impactante posible.
- **Partición de Hoare vs. Lomuto**: Hoare hace menos intercambios en promedio (~n/3 vs. ~n/2),
  lo que reduce la constante oculta de quicksort.
- **Manejo de elementos repetidos (3-way partition / Dutch Flag)**: con la partición de
  Bentley-McIlroy se agrupan todos los iguales al pivote en un solo bloque, convirtiendo
  el caso de repetidos de O(n²) a O(n·k) donde k es la cantidad de valores distintos.
- **Corte a insertion sort para subarreglos pequeños**: para n < ~16 insertion sort supera
  a quicksort por su menor overhead; esta optimización reduce el tiempo total en ~10–15%.
- **Límite de recursión y versión iterativa**: la recursión sin control puede provocar
  desbordamiento de pila en el peor caso; ordenar siempre el subarreglo menor primero
  (tail-call optimization) acota la profundidad a O(log n).
