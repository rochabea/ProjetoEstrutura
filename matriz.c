#include "matriz.h"

Matriz leMatriz(FILE *arquivo)
{
    printf("Iniciando leitura da matriz...\n");

    int nlin, ncol;
    fscanf(arquivo, "%d %d", &nlin, &ncol);
    printf("Dimensoes da matriz: %d linhas x %d colunas\n", nlin, ncol);

    Matriz matriz;
    matriz.nlin = nlin;
    matriz.ncol = ncol;

    matriz.cabeca = (Celula *)malloc(sizeof(Celula));
    matriz.cabeca->linha = -1;
    matriz.cabeca->coluna = -1;
    matriz.cabeca->valor = 0;
    matriz.cabeca->direita = matriz.cabeca;
    matriz.cabeca->abaixo = matriz.cabeca;

    for (int i = 0; i < nlin; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            float valor;
            fscanf(arquivo, "%f", &valor);
            printf("Lendo valor %.6f na posicao (%d, %d)\n", valor, i, j);

            if (valor != 0)
            {
                Celula *novo_elem = (Celula *)malloc(sizeof(Celula));
                novo_elem->linha = i;
                novo_elem->coluna = j;
                novo_elem->valor = valor;

                Celula *linha_cabecal = matriz.cabeca;
                while (linha_cabecal->abaixo != matriz.cabeca && linha_cabecal->abaixo->linha < i)
                    linha_cabecal = linha_cabecal->abaixo;

                Celula *coluna_cabecal = linha_cabecal;
                while (coluna_cabecal->direita != linha_cabecal && coluna_cabecal->direita->coluna < j)
                    coluna_cabecal = coluna_cabecal->direita;

                novo_elem->abaixo = linha_cabecal->abaixo;
                linha_cabecal->abaixo = novo_elem;

                novo_elem->direita = coluna_cabecal->direita;
                coluna_cabecal->direita = novo_elem;
            }
        }
    }

    printf("Leitura da matriz concluida...\n");

    return matriz;
}

void imprimeMatriz(Matriz A)
{
    printf("Imprimindo matriz...\n");

    Celula *linha_cabecal = A.cabeca->abaixo;
    while (linha_cabecal != A.cabeca)
    {
        Celula *atual = linha_cabecal->direita;

        printf("Linha %d: ", linha_cabecal->linha);

        while (atual != linha_cabecal)
        {
            printf("(%d,%d) = %.6f ", atual->linha, atual->coluna, atual->valor);
            atual = atual->direita;
        }

        printf("\n");
        linha_cabecal = linha_cabecal->abaixo;
    }

    printf("Impressao da matriz concluída...\n");
}

Matriz somaMatrizes(Matriz A, Matriz B)
{
    printf("Chamando somaMatrizes...\n");

    if (A.nlin != B.nlin || A.ncol != B.ncol)
    {
        printf("As matrizes tem dimensoes diferentes e nao podem ser somadas.\n");
        exit(1);
    }

    Matriz C;
    C.nlin = A.nlin;
    C.ncol = A.ncol;

    C.cabeca = (Celula *)malloc(sizeof(Celula));
    C.cabeca->linha = -1;
    C.cabeca->coluna = -1;
    C.cabeca->valor = 0;
    C.cabeca->direita = C.cabeca;
    C.cabeca->abaixo = C.cabeca;

    Celula *linha_cabecal_A = A.cabeca->abaixo;
    Celula *linha_cabecal_B = B.cabeca->abaixo;
    Celula *linha_cabecal_C = C.cabeca;

    while (linha_cabecal_A != A.cabeca || linha_cabecal_B != B.cabeca)
    {
        Celula *atual_A = (linha_cabecal_A != A.cabeca) ? linha_cabecal_A->direita : NULL;
        Celula *atual_B = (linha_cabecal_B != B.cabeca) ? linha_cabecal_B->direita : NULL;

        if (atual_A && (!atual_B || atual_A->coluna < atual_B->coluna))
        {
            Celula *novo = (Celula *)malloc(sizeof(Celula));
            novo->linha = atual_A->linha;
            novo->coluna = atual_A->coluna;
            novo->valor = atual_A->valor;
            novo->direita = novo;
            novo->abaixo = linha_cabecal_C->abaixo;
            linha_cabecal_C->abaixo = novo;
            linha_cabecal_C = novo;

            linha_cabecal_A = linha_cabecal_A->abaixo;
        }
        else if (atual_B && (!atual_A || atual_A->coluna > atual_B->coluna))
        {
            Celula *novo = (Celula *)malloc(sizeof(Celula));
            novo->linha = atual_B->linha;
            novo->coluna = atual_B->coluna;
            novo->valor = atual_B->valor;
            novo->direita = novo;
            novo->abaixo = linha_cabecal_C->abaixo;
            linha_cabecal_C->abaixo = novo;
            linha_cabecal_C = novo;

            linha_cabecal_B = linha_cabecal_B->abaixo;
        }
        else // atual_A->coluna == atual_B->coluna
        {
            float soma = atual_A->valor + atual_B->valor;
            if (soma != 0)
            {
                Celula *novo = (Celula *)malloc(sizeof(Celula));
                novo->linha = atual_A->linha;
                novo->coluna = atual_A->coluna;
                novo->valor = soma;
                novo->direita = novo;
                novo->abaixo = linha_cabecal_C->abaixo;
                linha_cabecal_C->abaixo = novo;
                linha_cabecal_C = novo;
            }

            linha_cabecal_A = linha_cabecal_A->abaixo;
            linha_cabecal_B = linha_cabecal_B->abaixo;
        }
    }

    printf("somaMatrizes concluida...\n");

    return C;
}

Matriz multiplicaMatrizes(Matriz A, Matriz B)
{
    printf("Chamando multiplicaMatrizes...\n");

    if (A.ncol != B.nlin)
    {
        printf("O numero de colunas de A deve ser igual ao numero de linhas de B para multiplicação de matrizes.\n");
        exit(1);
    }

    Matriz C;
    C.nlin = A.nlin;
    C.ncol = B.ncol;

    C.cabeca = (Celula *)malloc(sizeof(Celula));
    C.cabeca->linha = -1;
    C.cabeca->coluna = -1;
    C.cabeca->valor = 0;
    C.cabeca->direita = C.cabeca;
    C.cabeca->abaixo = C.cabeca;

    for (int i = 0; i < A.nlin; i++)
    {
        Celula *linha_A = A.cabeca->abaixo;
        while (linha_A->linha != i)
            linha_A = linha_A->abaixo;

        for (int j = 0; j < B.ncol; j++)
        {
            Celula *coluna_B = B.cabeca->direita;
            while (coluna_B->coluna != j)
                coluna_B = coluna_B->direita;

            float soma = 0;
            Celula *elem_A = linha_A->direita;
            Celula *elem_B = coluna_B->abaixo;
            while (elem_A != linha_A && elem_B != coluna_B)
            {
                if (elem_A->coluna == elem_B->linha)
                {
                    soma += elem_A->valor * elem_B->valor;
                    elem_A = elem_A->direita;
                    elem_B = elem_B->abaixo;
                }
                else if (elem_A->coluna < elem_B->linha)
                {
                    elem_A = elem_A->direita;
                }
                else
                {
                    elem_B = elem_B->abaixo;
                }
            }

            if (soma != 0)
            {
                Celula *novo = (Celula *)malloc(sizeof(Celula));
                novo->linha = i;
                novo->coluna = j;
                novo->valor = soma;
                novo->direita = novo;
                novo->abaixo = C.cabeca->abaixo;
                C.cabeca->abaixo = novo;
            }
        }
    }

    printf("multiplicaMatrizes concluída...\n");

    return C;
}
