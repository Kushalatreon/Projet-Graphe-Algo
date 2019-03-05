#ifndef GRAPHES_GRAPHEVALUE_H
#define GRAPHES_GRAPHEVALUE_H


#include "GrapheOriente.h"
#include "GrapheNonOriente.h"

/**
 * La matrice d'adjacence devient une matrice des couts
 */
class GrapheValue : public GrapheOriente, GrapheNonOriente
{
public:
    GrapheValue();

    GrapheValue(vector<vector<int>> couts);
private:

};


#endif //GRAPHES_GRAPHEVALUE_H
