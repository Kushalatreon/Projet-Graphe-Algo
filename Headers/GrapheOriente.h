#ifndef GRAPHES_GRAPHEORIENTE_H
#define GRAPHES_GRAPHEORIENTE_H


#include "Graphe.h"

class GrapheOriente : public Graphe
{
public:

    GrapheOriente();

    GrapheOriente(int** adj);


    /**
     * constructeur avec un nombre de sommet en parametre qui va permettre d'initialiser la taille de la matrice
     * @param [in] nbSommets
     */
    explicit GrapheOriente(int nbSommets);

    /**
     * Algorithme de tarjan ### AJOUTER PARAMETRES GRAVE ERREUR ###
     */
     void tarjan()  const;

    /**
    *
    * @param [in] fp - file de predecesseur
    * @param [in] app - adresses des premiers predecesseurs
    * @param [in] d - distance
    * @param [in, out] lc - longueur critique, chemin le plus court pour tout finir
    * @param [in, out] fpc - file des premiers critiques
    * @param [in, out] appc - adresses des premiers critiques
    */
     void ordonnancement(int* fp, int* app, int *d, int *&lc, int *&fpc, int *&appc) const;

    /**
     * Permet de creer le graphe reduit a partir des composantes fortement connexes
     * @param [in] fs
     * @param [in] aps
     * @param [in] prem
     * @param [in] pilch
     * @param [in] cfc
     * @param [in, out] fsr
     * @param [in, out] apsr
     */
    void graphe_reduit(int *fs, int *aps, int *prem, int *pilch, int *cfc, int *&fsr, int *& apsr);

    /**
     *
     * @param [in] dist
     * @param [in] prem
     * @param [in, out] pilch
     * @param [in, out] cfc
     */
    void det_cfc(int **dist, int *&prem, int *&pilch, int *&cfc);

    virtual void adj_2_fs_aps(int* &fs, int* &aps) const override;


    bool m_rangs(int* fs, int* aps, int& r, int* &m_rangs/*int*& prem, int*& num*/) const;

private:

};


#endif //GRAPHES_GRAPHEORIENTE_H
