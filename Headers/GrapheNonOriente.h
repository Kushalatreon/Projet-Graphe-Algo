#ifndef GRAPHES_GRAPHENONORIENTE_H
#define GRAPHES_GRAPHENONORIENTE_H

#include "Graphe.h"

class GrapheNonOriente : public Graphe
{
public:
    GrapheNonOriente();

    GrapheNonOriente(int** adj);

    GrapheNonOriente(int nbSommets);

    virtual void adj_2_fs_aps(int* &fs, int* &aps) const override;

    void Kruskal(GrapheNonOriente &h) const;

    /**
     * Créé un codage de Prüfer à partir d'une matrice d'adjacence
     * @param [in] A - la matrice d'adjacence
     * @param [out] C - le tableau qui accueillera le codage
     */
    void codagePrufer (int **A, int *&C );

    /**
     * Affiche le codage de Prüfer contenu dans C
     * @param [in] C - tableau qui contient le codage
     */
    void decodagePrufer (int *C);

private:
    void fusion(int i, int j, int* prem, int* &pilch, int* &cfc) const;
};


#endif //GRAPHES_GRAPHENONORIENTE_H
