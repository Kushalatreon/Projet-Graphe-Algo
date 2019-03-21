#include "../Headers/Graphe.h"

Graphe::Graphe() : d_adj{}
{}

Graphe::Graphe(int** adj) : d_adj{adj}
{}

Graphe::Graphe(int nbSommets) : d_adj{}
{
    d_adj = new int*[nbSommets];
    d_adj[0][0] = nbSommets;
    for (int i = 0; i < nbSommets; i++)
        d_adj[i] = new int [nbSommets];

}

Graphe::~Graphe() {

}

void Graphe::charger(const std::istream &ist)
{

}

void Graphe::initAdj()
{
    for (int i = 1; i < d_adj[0][0]; i++)
    {
        for (int j = 1; j < d_adj[0][0]; j++)
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

int** Graphe::matriceAdj() const {
    return nullptr;
}

int* Graphe::tableauMatrice(int i) const {
    return d_adj[i];
}

int Graphe::valMatrice(int i, int j) const {
    return 0;
}

void Graphe::setMatrice(int **&adj) {

}

void Graphe::detAps(const int* fs, int* &aps) const {
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

void Graphe::adj_2_fs_aps(int *&fs, int *&aps) const {

}

void Graphe::fs_aps_2_adj(const int *fs, const int *aps)
{

}

void Graphe::distance(const int* fs, const int* aps, int* &dist, int s) const {

}

void Graphe::m_distances(const int* fs, const int* aps, int** &m_dist) const {

}

int Graphe::rang(const int* fs, const int* aps, int s) const {
    return 0;
}

void Graphe::m_rangs(const int* fs, const int* aps, int** &m_rangs) const {

}


