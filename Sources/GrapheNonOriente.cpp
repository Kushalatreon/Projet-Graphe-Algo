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
int* GrapheNonOriente::det_ddi(const int* &fs, const int* &aps) const {
    int*v;
    return v;
}
