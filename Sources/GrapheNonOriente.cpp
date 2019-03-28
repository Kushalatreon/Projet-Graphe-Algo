#include "../Headers/GrapheNonOriente.h"

GrapheNonOriente::GrapheNonOriente() : Graphe()
{}

GrapheNonOriente::GrapheNonOriente(int** adj) : Graphe(adj)
{}

GrapheNonOriente::GrapheNonOriente(int nbSommets) : Graphe(nbSommets)
{
    initAdj();
}

// a modifier
void GrapheNonOriente::adj_2_fs_aps(int* &fs, int* &aps) const
{
    int n = d_adj[0][0], m = d_adj[0][1];
    /*int m = 0;
     *for (int i = 1; i <= d_adj[0][0]; i++) //Si l'on utilise la première ligne/colonne
     *  if(d_adj[i][0] > 0)
     *      m += d_adj[i][0]; */
    fs = new int[n + m + 1];
    fs[0] = n + m;

    aps = new int[n + 1];
    aps[0] = n;

    int k =1;
    for(int i = 1 ; i <= n ; i++)
    {
        aps[i] = k;
        for(int j = i ; j <= n ; j++)
        {
            if(d_adj[i][j] >= 1)
                fs[k++] = j;
        }
        fs[k++] = 0;
    }
}

void GrapheNonOriente::fusion(int i, int j, int *prem, int *&pilch, int *&cfc) const
{
    // i et j sont des numeros de composantes
    // i != j

    int s = prem[i];

    while ( pilch[s] != 0 ) s = pilch[s];

    pilch[s] = prem[j];

    while ( pilch[s] != 0 )
    {
        s = pilch[s];
        cfc[s] = i;
    }
}

void GrapheNonOriente::Kruskal(GrapheNonOriente &h) const
{
    // Appel au constructeur par recopie pour creer l'arbe h avec le nombre de sommets du graphe courant
    h = {d_adj[0][0]};

    // Le nombre d'aretes, dans un arbre de Kruskal, est egal au nombre de sommets - 1
    h.d_adj[0][1] = h.d_adj[0][0] - 1;  // <=> = d_adj[0][0]

    int n = d_adj[0][0];
    int *prem = new int[n + 1];
    int *pilch = new int[n + 1];
    int *cfc = new int[n + 1];

    for ( int i = 1 ; i<= n ; ++i)
    {
        prem[i] = i;
        pilch[i] = 0;
        cfc[i] = i;
    }

    for ( int i = 1, k = 0 ; i <= n && k < n ; ++i)
    {
        int *tmp = new int[n + 1];
        for ( int j = 1 ; j <= n ; j++) tmp[j] = d_adj[i][j];

        for ( int j = 1 ; j <= n ; ++j)
        {
            if(cfc[i] != cfc[j])
            {
                h.d_adj[i][k++] = tmp[j];
                fusion ( cfc[i], cfc[j], prem, pilch, cfc);
            }
        }

        delete[] tmp;
    }

    delete[] prem;
    delete[] pilch;
    delete[] cfc;
}

void GrapheNonOriente::codagePrufer(int **A, int *&C) {
    int n = A[0][0] - 2; //nombre de sommets - 2

    C = new int [n + 1]; //nombre de sommets - 2, + 1 case pour le nombre de cases de C
    C[0] = n;


    for (int i = 1 ; i <= n + 2 ; ++i)
        A[i][0] = 0;

    for (int i = 1 ; i <= n + 2 ; ++i)
        for (int j = 1 ; j <= n + 2 ; ++j)
            if (A[i][j] == 1)
            {
                ++A[i][0];
            }


    for (int k = 1 ; k <= n ; ++k)
    {
        int i = 1, j = 1;

        for (; A[i][0] != 1 ; ++i);
        for (; A[i][j] != 1 ; ++j);

        C[k] = j;
        A[i][j] = 0;
        A[j][i] = 0;
        --A[i][0];
        --A[j][0];
    }
}

void GrapheNonOriente::decodagePrufer(int *C) {
    //C[0] = l'indice du dernier élément
    int n = C[0] + 2;
    bool* I = new bool[n + 1];
    int* nbOcc = new int[n + 1];
    nbOcc[0] = n;

    for (int i = 1 ; i <= n ; ++i)
    {
        I[i] = true;
        nbOcc[i] = 0;
    }

    for (int i = 1 ; i < n - 1 ; ++i)
        nbOcc[C[i]]++;

    for (int i = 1 ; i < n - 1 ; ++i)
    {
        int s = C[i];
        std::cout<<'('<<s<<',';

        int t = 1;
        while (!I[t] || nbOcc[t] > 0) {++t;}
        std::cout<<t<<')'<<std::endl;
        I[t] = false;
        --nbOcc[s];
    }

    int s = 1;

    for (; !I[s] ; ++s);
    std::cout<<'('<<s<<',';
    ++s;

    for (; !I[s] ; ++s);
    std::cout<<s<<')'<<std::endl;


    delete[] I;
    delete[] nbOcc;
}
