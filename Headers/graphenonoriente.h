#ifndef GRAPHENONORIENTE_H
#define GRAPHENONORIENTE_H

#include "Graphe.h"

class GrapheNonOriente : public Graphe
{
public:
    GrapheNonOriente();

    GrapheNonOriente(std::vector<std::vector<int>> adj);

    GrapheNonOriente(int nbSommets);

    virtual void adj_2_fs_aps(std::vector<int> &fs, std::vector<int> &aps) const override;

    void Kruskal(GrapheNonOriente *&h);

    /**
     * Créé un codage de Prüfer à partir d'une matrice d'adjacence
     * @param [in] A - la matrice d'adjacence
     * @param [out] C - le tableau qui accueillera le codage
     */
    void codagePrufer (std::vector<std::vector<int>> A, std::vector<int> &C );

    /**
     * Affiche le codage de Prüfer contenu dans C
     * @param [in] C - tableau qui contient le codage
     */
    void decodagePrufer (std::vector<int> &C);

    /**
     * Sauvegarde le GrapheNonOriente actuel dans un fichier
     * Avant de sauvegarder, veillez à fermer le fichier dans lequel vous souhaitez sauvegarder si celui-ci existe déjà.
     * @param [out] nomFichier - le fichier dans lequel le graphe sera sauvegardé
     */
    void sauvegarder(const std::string &nomFichier) const;


private:

    /*
     * Le principe de l'algorithme consiste a creer un tableau d'arete (struct) qui contiendra les differentes aretes du graphe courant
     * Ensuite, uniquement certaines aretes seront retenues pour faire parie de l'abre recouvrant de poids minimal
     */
    // represente une arete
    typedef struct
    {
        int s,t;
        int p;
    } arete;

    void fusion(int i, int j, std::vector<int> prem, std::vector<int> &pilch, std::vector<int> &cfc) const;

    void triAretes_ParBulle(std::vector<GrapheNonOriente::arete> &_a, int taille) const;

    void getAretesTrieesParPoids(std::vector<GrapheNonOriente::arete> &_a, int taille) const;

    void setAretes(GrapheNonOriente *&h, const std::vector<GrapheNonOriente::arete> &_a, int taille);
};

#endif // GRAPHENONORIENTE_H
