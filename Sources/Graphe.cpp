#include "../Headers/Graphe.h"

Graphe::Graphe() : d_adj{}
{}

Graphe::Graphe(const vector<vector<int>> &adj) : d_adj{adj}
{}

Graphe::Graphe(const int nbSommets) : d_adj{(unsigned int)nbSommets+1, std::vector<int>(nbSommets+1)}
{

}

Graphe::~Graphe() {

}

void Graphe::initAdj()
{
    for (int i = 1; i < d_adj.size(); i++)
    {
        for (int j = 1; j < d_adj.size(); j++)
        {
            d_adj[i][j] = -1;
            if ( i == j ) d_adj[i][j] = 0;

        }
    }
}

void Graphe::ajouterLisaison(int predecesseur, int successeur, int valeur)
{
    d_adj[predecesseur][successeur] = valeur;
}

vector<vector<int>> Graphe::matriceAdj() const {
    return vector<vector<int>>();
}

vector<int> Graphe::tableauMatrice(int i) const {
    return vector<int>();
}

int Graphe::valMatrice(int i, int j) const {
    return 0;
}

void Graphe::setMatrice(const vector<vector<int>> &adj) {

}

vector<int> Graphe::detAps() const {
    return vector<int>();
}

void Graphe::detAps(vector<int> &aps) const {

}

void Graphe::adj_2_fs_aps(vector<int> &fs, vector<int> &aps) const {

}

vector<int> Graphe::distance(const vector<int> &fs, const vector<int> &aps, int s) const {
    return vector<int>();
}

vector<vector<int>> Graphe::m_distances(const vector<int> &fs, const vector<int> &aps) const {
    return vector<vector<int>>();
}

int Graphe::rang(const vector<int> &fs, const vector<int> &aps, int s) const {
    return 0;
}

vector<int> Graphe::m_rangs(const vector<int> &fs, const vector<int> &aps) const {
    return vector<int>();
}

vector<int> Graphe::det_ddi(const vector<int> &fs, const vector<int> &aps) const {
    return vector<int>();
}


