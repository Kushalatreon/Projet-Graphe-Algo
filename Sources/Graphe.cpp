#include "../Headers/Graphe.h"

Graphe::Graphe() : d_adj{}
{}

Graphe::Graphe(const vector<vector<int>> &adj) : d_adj{adj}
{}

Graphe::Graphe(const int nbSommets) : d_adj{(unsigned int)nbSommets+1, std::vector<int>(nbSommets+1)}
{

}

Graphe::~Graphe() {

}

void Graphe::initAdj()
{
    for (int i = 1; i < d_adj.size(); i++)
    {
        for (int j = 1; j < d_adj.size(); j++)
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
