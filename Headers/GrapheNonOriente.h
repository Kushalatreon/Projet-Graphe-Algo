#ifndef GRAPHES_GRAPHENONORIENTE_H
#define GRAPHES_GRAPHENONORIENTE_H

#include "Graphe.h"

class GrapheNonOriente : public Graphe
{
public:
    GrapheNonOriente();

    GrapheNonOriente(vector<vector<int>> adj);

    virtual void adj_2_fs_aps(vector<int> &fs, vector<int> &aps) const override;

    virtual vector<int> det_ddi(const vector<int> &fs, const vector<int> &aps) const override;

private:
};


#endif //GRAPHES_GRAPHENONORIENTE_H
