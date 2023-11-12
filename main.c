#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main()
{
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL)
    {
        printf("Falha ao criar o arquivo de saída.\n");
        return 1;
    }

    // Substitua o bloco de código relacionado ao redirecionamento e à impressão por este
    fprintf(outputFile, "Iniciando programa...\n");

    FILE *arquivoA = fopen("matrizA.txt", "r");
    if (arquivoA == NULL)
    {
        fprintf(outputFile, "Falha ao abrir o arquivo matrizA.txt.\n");
        return 1;
    }

    fprintf(outputFile, "Abrindo arquivo matrizA.txt...\n");

    Matriz A = leMatriz(arquivoA);
    fprintf(outputFile, "Matriz A:\n");
    imprimeMatriz(A);
    fclose(arquivoA);

    FILE *arquivoB = fopen("matrizB.txt", "r");
    if (arquivoB == NULL)
    {
        fprintf(outputFile, "Falha ao abrir o arquivo matrizB.txt.\n");
        return 1;
    }

    fprintf(outputFile, "Abrindo arquivo matrizB.txt...\n");

    Matriz B = leMatriz(arquivoB);
    fprintf(outputFile, "Matriz B:\n");
    imprimeMatriz(B);
    fclose(arquivoB);

    fprintf(outputFile, "Chamando somaMatrizes...\n");
    Matriz C = somaMatrizes(A, B);
    fprintf(outputFile, "Matriz C (soma de A e B):\n");
    imprimeMatriz(C);

    fprintf(outputFile, "Chamando multiplicaMatrizes...\n");
    Matriz D = multiplicaMatrizes(A, B);
    fprintf(outputFile, "Matriz D (multiplicação de A e B):\n");
    imprimeMatriz(D);

    fprintf(outputFile, "Programa concluido.\n");

    fclose(outputFile);

    return 0;
}
