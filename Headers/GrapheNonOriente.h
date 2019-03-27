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


private:
    void fusion(int i, int j, int* prem, int* &pilch, int* &cfc) const;
};


#endif //GRAPHES_GRAPHENONORIENTE_H
