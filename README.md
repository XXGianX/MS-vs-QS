# Laboratorio: Quicksort en la práctica

Este repositorio contiene una base de código para comparar experimentalmente quicksort y merge sort.

## Compilación

```bash
make
```

## Prueba rápida

```bash
make test
```

## Ejecutar una medición individual

```bash
./experiment quick random 10000 101
./experiment merge random 10000 101
```

El programa imprime una línea CSV con el formato:

```text
algorithm,inputType,n,seed,timeSeconds,sorted
```

## Ejecutar el experimento pequeño del laboratorio

```bash
make run
```

El resultado se guarda en:

```text
results/results.csv
```

## Generar gráficos con gnuplot

```bash
gnuplot scripts/plot.gp
```

Los gráficos se guardan en `results/`.

## Tarea principal

Completar la implementación de quicksort en `src/quicksort.c`.
# MS-vs-QS
