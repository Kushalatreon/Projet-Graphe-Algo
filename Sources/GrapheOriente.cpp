#include "../Headers/GrapheOriente.h"

GrapheOriente::GrapheOriente() : Graphe()
{}

GrapheOriente::GrapheOriente(vector<vector<int>> adj) : Graphe(adj)
{}

GrapheOriente::GrapheOriente(int nbSommets) : Graphe(nbSommets)
{
    initAdj();
}

int GrapheOriente::ajouterArete(int predecesseur, int successeur)
{
    ajouterLisaison(predecesseur,successeur, 1);
}
