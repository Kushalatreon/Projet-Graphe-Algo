#include "../Headers/GrapheNonOriente.h"

GrapheNonOriente::GrapheNonOriente() : Graphe()
{}

GrapheNonOriente::GrapheNonOriente(vector<vector<int>> adj) : Graphe(adj)
{}

// a modifier
void GrapheNonOriente::adj_2_fs_aps(vector<int> &fs, vector<int> &aps) const
{
    //Graphe::adj_2_fs_aps(fs, aps);
}

// a modifier
vector<int> GrapheNonOriente::det_ddi(const vector<int> &fs, const vector<int> &aps) const {
    vector<int> v;
    return v;
}
