#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int particiona(int v[], int esq, int dir);
int quickSelect(int v[], int esq, int dir, int k);

int main(int argc, char *argv[]){
    int k, numero, *valores = NULL, capacidade = 10, tamanho = 0;

    if(argc != 3 || strcmp(argv[1], "-k") != 0){
        printf("Uso correto: %s -k <valor>\n", argv[0]);
        return 1;
    }

    k = atoi(argv[2]);

    valores = malloc(capacidade * sizeof(int));
    if(valores == NULL){
        printf("Erro ao alocar memória inicial.\n");
        return 1;
    }

    while(scanf("%d", &numero) == 1){
        if(tamanho == capacidade){
            capacidade *= 2;
            int *novo = realloc(valores, capacidade * sizeof(int));
            if(novo == NULL){
                printf("Erro ao realocar memória.\n");
                free(valores);
                return 1;
            }
            valores = novo;
        }
        valores[tamanho++] = numero;
    }

    if(k < 1 || k > tamanho){
        printf("Valor de k inválido. Deve estar entre 1 e %d.\n", tamanho);
        free(valores);
        return 1;
    }

    int resultado = quickSelect(valores, 0, tamanho - 1, k - 1);  // Subtrai 1 de k, pois é 1-based
    printf("%d", resultado);

    free(valores);
    return 0;
}

int particiona(int v[], int esq, int dir){
    int pivo = v[dir];
    int i = esq;
    int aux;

    for(int j = esq; j < dir; j++){
        if(v[j] < pivo){
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
        }
    }
    aux = v[i];
    v[i] = v[dir];
    v[dir] = aux;

    return i;
}

int quickSelect(int v[], int esq, int dir, int k){
    if(esq == dir) return v[esq];

    int posicaoPivo = particiona(v, esq, dir);

    if(k == posicaoPivo) return v[k];
    else if(k < posicaoPivo) return quickSelect(v, esq, posicaoPivo - 1, k);
    else return quickSelect(v, posicaoPivo + 1, dir, k);
}