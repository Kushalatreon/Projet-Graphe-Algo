#ifndef GRAPHES_GRAPHEORIENTE_H
#define GRAPHES_GRAPHEORIENTE_H


#include "Graphe.h"

class GrapheOriente : public Graphe
{
private:
    void numerotation(std::vector<int> &num, std::vector<int> &cfc, std::vector<int> &prem, std::vector<int> &pilch, int sommet, int &nNum, int &numCfc) const;
    int sommet_accessible(int sommet, const std::vector<int> &num) const;
    void det_ro(const std::vector<int> &prem, const std::vector<int> &pilch, const std::vector<int> &num, std::vector<int> &ro) const;
    int frondeMin(int s, const std::vector<int> &num) const;
public:

    GrapheOriente();

    GrapheOriente(std::vector<std::vector<int>> adj);


    /**
     * constructeur avec un nombre de sommet en parametre qui va permettre d'initialiser la taille de la matrice
     * @param [in] nbSommets
     */
    explicit GrapheOriente(int nbSommets);

    /**
     * Algorithme de tarjan ### AJOUTER PARAMETRES GRAVE ERREUR ###
     */
     void tarjan(std::vector<int> &num, std::vector<int> &prem, std::vector<int> &pilch, std::vector<int> &ro, std::vector<int> &cfc, int sommet)  const;

    /**
    *
    * @param [in] fp - file de predecesseur
    * @param [in] app - adresses des premiers predecesseurs
    * @param [in] d - distance
    * @param [in, out] lc - longueur critique, chemin le plus court pour tout finir
    * @param [in, out] fpc - file des premiers critiques
    * @param [in, out] appc - adresses des premiers critiques
    */
     void ordonnancement(std::vector<int> fp, std::vector<int> app, std::vector<int> d, std::vector<int> &lc, std::vector<int> &fpc, std::vector<int> &appc) const;

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
    void graphe_reduit(std::vector<int> fs, std::vector<int> aps, std::vector<int> prem, std::vector<int> pilch, std::vector<int> cfc, std::vector<int> &fsr, std::vector<int> & apsr);

    /**
     *
     * @param [in] dist
     * @param [in] prem
     * @param [in, out] pilch
     * @param [in, out] cfc
     */
    void det_cfc(std::vector<std::vector<int>> dist, std::vector<int> &prem, std::vector<int> &pilch, std::vector<int> &cfc);

    virtual void adj_2_fs_aps(std::vector<int> &fs, std::vector<int> &aps) const override;


    bool m_rangs(std::vector<int> fs, std::vector<int> aps, int& r, std::vector<int> &m_rangs/*std::vector<int>& prem, std::vector<int>& num*/) const;


};


#endif //GRAPHES_GRAPHEORIENTE_H
