#include "../Headers/Graphe.h"

Graphe::Graphe() : d_adj{}
{}

Graphe::Graphe(const vector<vector<int>> &adj) : d_adj{adj}
{}