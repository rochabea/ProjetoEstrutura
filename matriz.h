#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Celula
{
    struct Celula *direita, *abaixo;
    int linha, coluna;
    float valor;
} Celula;

typedef struct
{
    Celula *cabeca;
    int nlin, ncol;
} Matriz;

Matriz leMatriz(FILE *arquivo);
void imprimeMatriz(Matriz A);
Matriz somaMatrizes(Matriz A, Matriz B);
Matriz multiplicaMatrizes(Matriz A, Matriz B);

#endif /* MATRIZ_H */
