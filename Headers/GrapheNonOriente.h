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



private:
};


#endif //GRAPHES_GRAPHENONORIENTE_H
