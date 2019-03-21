#include "../Headers/Graphe.h"

Graphe::Graphe() : d_adj{}
{}

Graphe::Graphe(int** adj) : d_adj{adj}
{}

Graphe::Graphe(int nbSommets) : d_adj{}
{
    d_adj = new int*[nbSommets];
    for (int i = 0; i <= nbSommets; i++)
        d_adj[i] = new int [nbSommets];
    d_adj[0][0] = nbSommets;
}

Graphe::~Graphe() {

}

void Graphe::charger(const std::istream &ist)
{

}

void Graphe::initAdj()
{
    for (int i = 1; i <= d_adj[0][0]; i++)
    {
        for (int j = 1; j <= d_adj[0][0]; j++)
        {
            d_adj[i][j] = -1;
            if ( i == j ) d_adj[i][j] = 0;

        }
    }
}

void Graphe::ajouterLisaison(int predecesseur, int successeur, int valeur)
{
    d_adj[predecesseur][successeur] = valeur;
}

int** Graphe::matriceAdj() const
{
    return d_adj;
}

int* Graphe::tableauMatrice(int i) const
{
    return d_adj[i];
}

int Graphe::valMatrice(int i, int j) const
{
    return d_adj[i][j];
}

void Graphe::setMatrice(int **&adj)
{
    d_adj = adj;
}

void Graphe::detAps(int* fs, int* &aps) const {
    int n = fs[0];
    aps = new int[n+1];
    aps[0] = n;
    aps[1] = 1;

    int j = 1;
    for (int i = 2 ; i < n ; ++i)
    {
        while(fs[j] != 0)
        {
            ++j;
        }
        ++j;
        aps[i] = j;
    }
}

void Graphe::adj_2_fs_aps(int *&fs, int *&aps) const
{
    int n = d_adj[0][0], m = d_adj[0][1];

    fs = new int[n + m + 1];
    fs[0] = n + m;

    aps = new int[n + 1];
    aps[0] = n;

    int k =1;
    for(int i = 1 ; i <= n ; i++)
    {
        aps[i] = k;
        for(int j = 1 ; j <= n ; j++)
        {
            if(d_adj[i][j] >= 1) fs[k++] = j;
        }
        fs[k++] = 0;
    }
}

void Graphe::fs_aps_2_adj(int *fs, int *aps)
{
    int n = aps[0], m = fs[0] -n;

    /*
     * Ce sont deux lignes a supprimer selon moi (dorian) car d_adj est cense etre alloue avant d'appeler cette fonction
     * Pour creer d_adj, il faut le nombre de sommets au moins, soit aps[0].
     * Il y a donc redondance.
     * (Allah limite on peut laisser la deuxieme)
     */
    d_adj[0][0] = n;
    d_adj[0][1] = m;

    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = aps[0] ; (j = fs[j]) != 0 ; j++)
        {
            d_adj[i][j] = 1;
        }
    }
}

void Graphe::distance(int* fs, int* aps, int* &dist, int s) const
{
    int t = 0;
    int q = 1;
    int p = 1;
    int d = 0;
    int n = aps[0];

    dist = new int[n + 1];
    dist[0] = n;

    int* fa = new int[n + 1];

    for(int i = 1 ; i <= n ; i++) dist[i] = -1;
    fa[0] = n;
    fa[1] = s;

    while(t < q)
    {
        d++;
        for(int i = t+1 ; i <= q ; i++)
        {
            int suiv = aps[fa[i]];

            while(fs[suiv] != 0)
            {
                if(dist[fs[suiv]] == -1)
                {
                    dist[fs[suiv]] = d;
                    fa[++p] = fs[suiv];
                }
                suiv++;
            }
        }
        t = q;
        q = p;
    }

    delete[] fa;
}

void Graphe::m_distances(int *fs, int *aps, int **&m_dist) const
{
    int n = aps[0];

    m_dist = new int*[n + 1];
    m_dist[0] = new int[1];
    m_dist[0][0] = n;

    for(int s = 1 ; s <= n ; s++)
    {
        distance(fs, aps, m_dist[s], s);
    }
}

int Graphe::rang(int* fs, int* aps, int s) const {

}

void Graphe::m_rangs(int* fs, int* aps, int** &m_rangs) const {

}

void Graphe::dijkstra(int* fs, int* aps, int s, int* &d, int* &pred) const
{
    int n = aps[0], h;

    d = new int[n + 1];
    d[0] = n;

    pred = new int[n + 1];
    pred[0] = n;

    bool *x = new bool[n + 1];

    // initialisation de d a INT32_MAX
    for(int i = 1 ; i <= n ; i++)
    {
        d[i] = INT32_MAX;
    }

    for(int i = 1 ; i <= n ; i++)
    {
        d[i] = d_adj[s][i];
        if(d[i] != INT32_MAX) pred[i] = s;
        else pred[i] = -1;
        x[i] = false;
    }

    pred[s] = 0;
    x[s] = true;
    int cpt = n;

    while(--cpt > 0)
    {
        // calcul du minimum dans d pour les sommets qui ne sont pas dans x

        int minh = INT32_MAX;
        int j = -1;

        for(int i = 1 ; i <= n ; i++)
        {
            if(!x[i])
            {
                if(d[i] < minh)
                {
                    minh = d[i];
                    j = i;
                }
            }
        }

        if(minh == INT32_MAX) break;    // j == -1
        x[j] = true;

        for(int k = aps[j] ; (k = fs[k]) != 0 ; k++)
        {
            if(!x[k])
            {
                int v = d[j] + d_adj[j][h];

                if(v < d[h])
                {
                    d[h] = 0;
                    pred[h] = j;
                }
            }
        }
    }

    delete[] x;
}


