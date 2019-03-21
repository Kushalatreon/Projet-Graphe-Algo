#ifndef GRAPHES_GRAPHENONORIENTE_H
#define GRAPHES_GRAPHENONORIENTE_H

#include "Graphe.h"

class GrapheNonOriente : public Graphe
{
public:
    GrapheNonOriente();

    GrapheNonOriente(int** adj);

    virtual void adj_2_fs_aps(int* &fs, int* &aps) const override;

    virtual void det_ddi(const int* fs, const int* aps, int* &ddi) const override;

private:
};


#endif //GRAPHES_GRAPHENONORIENTE_H
