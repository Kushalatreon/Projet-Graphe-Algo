#include "../Headers/GrapheNonOriente.h"

GrapheNonOriente::GrapheNonOriente() : Graphe()
{}

GrapheNonOriente::GrapheNonOriente(int** adj) : Graphe(adj)
{}

// a modifier
void GrapheNonOriente::adj_2_fs_aps(int* &fs, int* &aps) const
{
    //Graphe::adj_2_fs_aps(fs, aps);
}

// a modifier
void GrapheNonOriente::det_ddi(const int* fs, const int* aps, int* &ddi) const {

}
