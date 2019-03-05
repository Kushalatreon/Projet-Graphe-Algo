#ifndef GRAPHES_GRAPHEORIENTE_H
#define GRAPHES_GRAPHEORIENTE_H


#include "Graphe.h"

class GrapheOriente : public Graphe
{
public:

    GrapheOriente();

    GrapheOriente(vector<vector<int>> adj);

    void tarjan();

    void ordonnancement();
private:

};


#endif //GRAPHES_GRAPHEORIENTE_H
