#ifndef GRAPHES_GRAPHEORIENTE_H
#define GRAPHES_GRAPHEORIENTE_H


#include "Graphe.h"

class GrapheOriente : public Graphe
{
public:

    GrapheOriente();

    GrapheOriente(vector<vector<int>> adj);


    /**
     * constructeur avec un nombre de sommet en parametre qui va permettre d'initialiser la taille de la matrice
     * @param [in] nbSommets
     */
    GrapheOriente(int nbSommets);


    /**
     * permet d'ajouter une arete entre deux dommets
     * @param [in] predecesseur - sommet pere
     * @param [in] successeur - sommet fils
     */
    void ajouterArete(int predecesseur, int successeur);


    void tarjan();

    void ordonnancement();
private:

};


#endif //GRAPHES_GRAPHEORIENTE_H
