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
