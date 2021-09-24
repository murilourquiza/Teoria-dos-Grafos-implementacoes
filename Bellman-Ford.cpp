#include <iostream>
#include <climits>

using namespace std;

// Struct para representar uma aresta com peso em um grafo
struct Aresta {
    int posicao, dest, peso;
};
 
// Struct para representar um grafo conectado com peso e direção
struct Grafo {
    // V-> Nº de vertices, E-> Nº de Arestas
    int V, E;
 
    struct Aresta* Aresta;
};
 
// Cria um grafo com V vertices e E arestas
struct Grafo* criarGrafo(int V, int E)
{
    struct Grafo* grafo = new Grafo;
    grafo->V = V;
    grafo->E = E;
    grafo->Aresta = new Aresta[E];
    return grafo;
}
 
// Função pra printar a solução
void printArr(int dist[], int n)
{
    printf("Vértice | Distância da origem\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
// Função que acha as menores distâncias entre posicao para todos os outros vértices usando o algoritmo de Bellman-Ford
void BellmanFord(struct Grafo* grafo, int posicao)
{
    int V = grafo->V;
    int E = grafo->E;
    int dist[V];
 
    // Inicializa as distâncias de posicao para todos os outros vértices como máximo
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[posicao] = 0;
 
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = grafo->Aresta[j].posicao;
            int v = grafo->Aresta[j].dest;
            int peso = grafo->Aresta[j].peso;
            if (dist[u] != INT_MAX && dist[u] + peso < dist[v])
                dist[v] = dist[u] + peso;
        }
    }
 
    // Busca ciclos de peso negativo
    for (int i = 0; i < E; i++) {
        int u = grafo->Aresta[i].posicao;
        int v = grafo->Aresta[i].dest;
        int peso = grafo->Aresta[i].peso;
        if (dist[u] != INT_MAX && dist[u] + peso < dist[v]) {
            printf("Grafo contém ciclo de peso negativo");
            return; // Se um ciclo negativo for identificado, retornar
        }
    }
 
    printArr(dist, V);
 
    return;
}
 
int main()
{
    int V, E;
    cout << "Insira o número de vértices no grafo: ";
    cin >> V;
    cout << "Insira o número de arestas no grafo: ";
    cin >> E;
    struct Grafo* grafo = criarGrafo(V, E);
 
    grafo->Aresta[0].posicao = 0;
    grafo->Aresta[0].dest = 1;
    grafo->Aresta[0].peso = -1;

    grafo->Aresta[1].posicao = 0;
    grafo->Aresta[1].dest = 2;
    grafo->Aresta[1].peso = 4;

    grafo->Aresta[2].posicao = 1;
    grafo->Aresta[2].dest = 2;
    grafo->Aresta[2].peso = 3;
 
    grafo->Aresta[3].posicao = 1;
    grafo->Aresta[3].dest = 3;
    grafo->Aresta[3].peso = 2;
 
    grafo->Aresta[4].posicao = 1;
    grafo->Aresta[4].dest = 4;
    grafo->Aresta[4].peso = 2;
 
    grafo->Aresta[5].posicao = 3;
    grafo->Aresta[5].dest = 2;
    grafo->Aresta[5].peso = 5;
 
    grafo->Aresta[6].posicao = 3;
    grafo->Aresta[6].dest = 1;
    grafo->Aresta[6].peso = 1;
 
    grafo->Aresta[7].posicao = 4;
    grafo->Aresta[7].dest = 3;
    grafo->Aresta[7].peso = -3;
 
    BellmanFord(grafo, 0);
 
    return 0;
}