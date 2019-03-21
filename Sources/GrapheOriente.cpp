#include "../Headers/GrapheOriente.h"

GrapheOriente::GrapheOriente() : Graphe()
{}

GrapheOriente::GrapheOriente(int** adj) : Graphe(adj)
{}

GrapheOriente::GrapheOriente(int nbSommets) : Graphe(nbSommets)
{
    initAdj();
}

void GrapheOriente::ajouterArete(int predecesseur, int successeur)
{
    ajouterLisaison(predecesseur,successeur, 1);
}

void GrapheOriente::tarjan() const {

}

void GrapheOriente::ordonnancement() const {

}