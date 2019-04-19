#ifndef GRAPHEORIENTE_H
#define GRAPHEORIENTE_H

#include "Graphe.h"

class GrapheOriente : public Graphe
{
private:
    /**
     * Numerote les sommets selon l'algorithme de Tarjan
     * @param [in, out] num - nouvelle numerotation
     * @param [in, out] cfc - composantes fortement connexes
     * @param [in, out] prem
     * @param [in, out] pilch
     * @param [in, out] sommet
     * @param [in, out] nNum - numéro a affecter
     * @param [in, out] numCfc - numéro de la composante
     */
    void numerotation(std::vector<int> &num, std::vector<int> &cfc, std::vector<int> &prem, std::vector<int> &pilch, int sommet, int &nNum, int &numCfc) const;

    /**
     * Renvoie le numéro d'un sommet accessible
     * @param [in] sommet - sommet de depart
     * @param [in] num - nouvelle numerotation des sommets
     * @return int - numéro du premier sommet accessible
     */
    int sommet_accessible(int sommet, const std::vector<int> &num) const;

    /**
     * Determination de ro
     * @param [in] prem
     * @param [in] pilch
     * @param [in] num
     * @param [in, out] ro - tableau des ro
     * @param [in] cfc
     */
    void det_ro(const std::vector<int> &prem, const std::vector<int> &pilch, const std::vector<int> &num, std::vector<int> &ro, std::vector<int> &cfc) const;

    /**
     * Renvoie la valeur d'une fronde minimale d'un sommet S
     * @param [in] s - sommet de depart
     * @param [in] num
     * @param [in] cfc
     * @return int - la valeur minimale trouvee
     */
    int frondeMin(int s, const std::vector<int> &num, std::vector<int> &cfc) const;

public:

    GrapheOriente();

    GrapheOriente(std::vector<std::vector<int>> adj);


    /**
     * Constructeur avec un nombre de sommets en parametre qui va permettre d'initialiser la taille de la matrice
     * @param [in] nbSommets
     */
    explicit GrapheOriente(int nbSommets);

    /**
     * Application de l'algorithme de Tarjan
     * @param [in, out] num
     * @param [in, out] prem
     * @param [in, out] pilch
     * @param [in, out] ro
     * @param [in, out] cfc
     * @param [in] sommet - sommet de départ
     */
     void tarjan(std::vector<int> &num, std::vector<int> &prem, std::vector<int> &pilch, std::vector<int> &ro, std::vector<int> &cfc, int sommet)  const;

    /**
    * Determination des chemins critiques
    * @param [in] fp - file des predecesseurs
    * @param [in] app - adresses des premiers predecesseurs
    * @param [in] d - distance
    * @param [in, out] lc - longueur critique, chemin le plus court pour tout finir
    * @param [in, out] fpc - file des predecesseurs critiques
    * @param [in, out] appc - adresses des premiers critiques
    */
     void ordonnancement(std::vector<int> fp, std::vector<int> app, std::vector<int> d, std::vector<int> &lc, std::vector<int> &fpc, std::vector<int> &appc) const;

    /**
     * Permet de creer le graphe reduit a partir des composantes fortement connexes
     * @param [in] fs - file des successeurs
     * @param [in] aps - adresses des premiers successeurs
     * @param [in] prem
     * @param [in] pilch
     * @param [in] cfc
     * @param [in, out] fsr
     * @param [in, out] apsr
     */
    void graphe_reduit(std::vector<int> fs, std::vector<int> aps, std::vector<int> prem, std::vector<int> pilch, std::vector<int> cfc, std::vector<int> &fsr, std::vector<int> & apsr);

    /**
     * Permet de determiner les composantes fortement connexes
     * @param [in] dist - tableau des distances
     * @param [in] prem - premier element de la pile
     * @param [in, out] pilch - pile
     * @param [in, out] cfc - composante fortement connexe
     */
    // ################################# CASSE #################################
    void det_cfc(std::vector<std::vector<int>> dist, std::vector<int> &prem, std::vector<int> &pilch, std::vector<int> &cfc);

    /**
     * Cree la matrice des rangs
     * @param [in] fs
     * @param [in] aps
     * @param [in, out] r - rang
     * @param [in, out] m_rangs - matrice des rangs
     * @return bool
     */
    bool m_rangs(std::vector<int> fs, std::vector<int> aps, int& r, std::vector<int> &m_rangs/*std::vector<int>& prem, std::vector<int>& num*/) const;

    /**
     * Cree fs et aps a partir de la matrice d'adjacence
     * @param fs
     * @param aps
     */
    virtual void adj_2_fs_aps(std::vector<int> &fs, std::vector<int> &aps) const override;

    /**
     * Sauvegarde le GrapheOriente actuel dans un fichier
     * Avant de sauvegarder, veillez à fermer le fichier dans lequel vous souhaitez sauvegarder si celui-ci existe déjà.
     * @param [out] nomFichier - le fichier dans lequel le graphe sera sauvegardé
     */
    void sauvegarder(const std::string &nomFichier) const;

};


#endif // GRAPHEORIENTE_H
