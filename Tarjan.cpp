#include <iostream>
#include <list>
#include <stack>
using namespace std;
 
// Classe para representar um grafo direcionado
class Grafo
{
    int V; // Vértices
    list<int> *adj; // Array dinâmico de listas adjacentes
 
    // Função DFS
    void SCCUtil(int u, int desc[], int baixo[],
                stack<int> *st, bool stackMembro[]);
public:
    Grafo(int V); // Construtor
    void addVertice(int v, int w); // Adiciona vértice a um grafo
    void SCC(); // Printa components fortemente conectados
};
 
Grafo::Grafo(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Grafo::addVertice(int v, int w)
{
    adj[v].push_back(w);
}
 
void Grafo::SCCUtil(int u, int desc[], int baixo[], stack<int> *st,
                    bool stackMembro[])
{
    static int tempo = 0;
 
    desc[u] = baixo[u] = ++tempo;
    st->push(u);
    stackMembro[u] = true;
 
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;
 
        if (desc[v] == -1)
        {
            SCCUtil(v, desc, baixo, st, stackMembro);
 
            baixo[u] = min(baixo[u], baixo[v]);
        }
 
        else if (stackMembro[v] == true)
            baixo[u] = min(baixo[u], desc[v]);
    }
 
    int w = 0;
    if (baixo[u] == desc[u])
    {
        while (st->top() != u)
        {
            w = (int) st->top();
            cout << w << " ";
            stackMembro[w] = false;
            st->pop();
        }
        w = (int) st->top();
        cout << w << "\n";
        stackMembro[w] = false;
        st->pop();
    }
}
 
void Grafo::SCC()
{
    int *desc = new int[V];
    int *baixo = new int[V];
    bool *stackMembro = new bool[V];
    stack<int> *st = new stack<int>();
 
    for (int i = 0; i < V; i++)
    {
        desc[i] = -1;
        baixo[i] = -1;
        stackMembro[i] = false;
    }

    for (int i = 0; i < V; i++)
        if (desc[i] == -1)
            SCCUtil(i, desc, baixo, st, stackMembro);
}
 
int main()
{
    // Testando com valores de exemplo
    cout << "\nComponentes fortemente conectados no primeiro grafo: \n";
    Grafo g1(5);
    g1.addVertice(1, 0);
    g1.addVertice(0, 2);
    g1.addVertice(2, 1);
    g1.addVertice(0, 3);
    g1.addVertice(3, 4);
    g1.SCC();
 
    cout << "\nComponentes fortemente conectados no segundo grafo: \n";
    Grafo g2(4);
    g2.addVertice(0, 1);
    g2.addVertice(1, 2);
    g2.addVertice(2, 3);
    g2.SCC();
 
    cout << "\nComponentes fortemente conectados no terceiro grafo: \n";
    Grafo g3(7);
    g3.addVertice(0, 1);
    g3.addVertice(1, 2);
    g3.addVertice(2, 0);
    g3.addVertice(1, 3);
    g3.addVertice(1, 4);
    g3.addVertice(1, 6);
    g3.addVertice(3, 5);
    g3.addVertice(4, 5);
    g3.SCC();
 
    cout << "\nComponentes fortemente conectados no quarto grafo: \n";
    Grafo g4(11);
    g4.addVertice(0,1);g4.addVertice(0,3);
    g4.addVertice(1,2);g4.addVertice(1,4);
    g4.addVertice(2,0);g4.addVertice(2,6);
    g4.addVertice(3,2);
    g4.addVertice(4,5);g4.addVertice(4,6);
    g4.addVertice(5,6);g4.addVertice(5,7);g4.addVertice(5,8);g4.addVertice(5,9);
    g4.addVertice(6,4);
    g4.addVertice(7,9);
    g4.addVertice(8,9);
    g4.addVertice(9,8);
    g4.SCC();
 
    cout << "\nComponentes fortemente conectados no quinto grafo: \n";
    Grafo g5(5);
    g5.addVertice(0,1);
    g5.addVertice(1,2);
    g5.addVertice(2,3);
    g5.addVertice(2,4);
    g5.addVertice(3,0);
    g5.addVertice(4,2);
    g5.SCC();
 
    return 0;
}
