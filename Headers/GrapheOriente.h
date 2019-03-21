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
     * permet d'ajouter une arete entre deux dommets
     * @param [in] predecesseur - sommet pere
     * @param [in] successeur - sommet fils
     */
    void ajouterArete(int predecesseur, int successeur);

    /**
     * Algorithme de tarjan ### AJOUTER PARAMETRES GRAVE ERREUR ###
     */
    virtual void tarjan() const override;

    /**
    *
    * @param [in] fp - file de predecesseur
    * @param [in] app - adresses des premiers predecesseurs
    * @param [in] d - distance
    * @param [in, out] lc - longueur critique, chemin le plus court pour tout finir
    * @param [in, out] fpc - file des premiers critiques
    * @param [in, out] appc - adresses des premiers critiques
    */
    virtual void ordonnancement(int fp[], int app[], int *d, int *&lc, int *&fpc, int *&appc) const override;

    /**
     *
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

    /**
     * Redéfinition
     * Determine le nombre de predecesseurs de chaque sommet
     * @param [in] fs
     * @param [in] aps
     */
    virtual void det_ddi(const int* fs, const int* aps, int* &ddi) const override;

    /**
     * Redéfinition
     * Détermine la file des premiers prédécesseurs
     * @param [in] ddi : tableau ddi
     * @param [out] app : tableau app
     */
    virtual void det_app(int* ddi, int* &app) const override;

    /**
     * Redéfinition
     * Passage de fs aps à fp app
     * @param fs : tableau fs
     * @param aps : tableau aps
     * @param fp : tableau fp, file des prédécesseurs
     * @param app : tableau app
     */
    virtual void fs_aps_2_fp_app(int* fs, int* aps, int* &fp, int* &app) const override;

private:

};


#endif //GRAPHES_GRAPHEORIENTE_H
