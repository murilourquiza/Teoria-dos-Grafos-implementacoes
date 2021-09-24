#include <stdio.h>
#include <stdlib.h>

typedef struct grafo{
    int nro_vertices;
    int grau_max;
    int** arestas;
    float** pesos;
    int* grau;
}Grafo;

Grafo* cria_Grafo(int nro_vertices, int grau_max);
void libera_Grafo(Grafo* gr);
int insereAresta(Grafo* gr, int orig, int dest, float peso);
void algPRIM(Grafo *gr, int orig, int *pai);

void libera_Grafo(Grafo* gr){
    if(gr != NULL){
        int i;
        for(i=0; i<gr->nro_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);

        for(i=0; i<gr->nro_vertices; i++)
            free(gr->pesos[i]);
        free(gr->pesos);
        free(gr->grau);
        free(gr);
    }
}

Grafo* cria_Grafo(int nro_vertices, int grau_max){
    Grafo *gr=(Grafo*)malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->nro_vertices = nro_vertices;
        gr->grau_max = grau_max;
        gr->grau = (int*)calloc(nro_vertices, sizeof(int));
        gr->arestas=(int**)malloc(nro_vertices*sizeof(int*));
        for(i=0; i<nro_vertices; i++)
            gr->arestas[i] = (int*)malloc(grau_max*sizeof(int));
        gr->pesos=(float**)malloc(nro_vertices*sizeof(float*));
        for(i=0; i<nro_vertices; i++){
            gr->pesos[i]=(float*)malloc(grau_max*sizeof(float));
        }
        return gr;
    }
}

int insereAresta(Grafo* gr, int orig, int dest, float peso){
    if(gr ==  NULL)
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    gr->arestas[orig][gr->grau[orig]] = dest;
    gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;

    return 1;
}

int main(){
    int vert, arest, v1, v2, x, y;
    float peso;
    printf("Seja bem-vindo(a) ao Algoritmo de Prim!\n\n");
    printf("Digite o numero total de vertices e arestas do seu grafo: ");
    scanf("%i %i", &vert, &arest);

    int pai[vert];

    Grafo *gr;
    gr = cria_Grafo(vert, arest);

    printf("\nIremos encontrar a arvore geradora minima com ponto de origem em v1=0\n");

    for(int i=0; i<arest; i++){
        printf("\nDigite v1 e v2 da aresta %i: ", i+1);
        scanf("%i %i", &v1, &v2);
        printf("Digite o peso: ");
        scanf("%f", &peso);
        x = insereAresta(gr, v1, v2, peso);
        y = insereAresta(gr, v2, v1, peso);
        if(x == 0 || y == 0){
            printf("Aresta inserida incorretamente\ntente novamente\n");
            i--;
        }
    }
    algPRIM(gr, 0, pai);

    printf("\n");

    for(int m=0; m<vert; m++){
        printf("%d eh pai do filho %d\n", pai[m], m);
    }
    printf("\n");
    for(int m=0; m<vert; m++){
        if(pai[m] != m){
            printf("Aresta %i - %i presenta na Arvore\n", pai[m], m);
        }
    }

    libera_Grafo(gr);
    return 0;
}

void algPRIM(Grafo *gr, int orig, int *pai){
    int i, j, dest, primeiro, NV = gr->nro_vertices;
    double menorPeso;
    for(i=0; i<NV; i++)
        pai[i] = -1;
    pai[orig] = orig;
    while(1){
        primeiro = 1;
        for(i=0; i<NV; i++){
            if(pai[i] != -1){
                for(j=0; j<gr->grau[i]; j++){
                    if(pai[gr->arestas[i][j]] == -1){
                        if(primeiro){
                            menorPeso = gr->pesos[i][j];
                            orig = i;
                            dest = gr->arestas[i][j];
                            primeiro = 0;
                        } else{
                            if(menorPeso > gr->pesos[i][j]){
                                menorPeso = gr->pesos[i][j];
                                orig = i;
                                dest = gr->arestas[i][j];
                            }
                        }
                    }
                }
            }
        }
        if(primeiro == 1)
            break;

        pai[dest] = orig;
    }
}