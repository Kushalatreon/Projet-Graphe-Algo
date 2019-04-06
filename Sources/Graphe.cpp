#include <iostream>
#include "../Headers/Graphe.h"

Graphe::Graphe() : d_adj{}
{}

Graphe::Graphe( std::vector<std::vector<int>> &adj) : d_adj{adj}
{}

Graphe::Graphe(int nbSommets) : d_adj{}
{
    std::vector<std::vector<int>> inter (nbSommets+1,std::vector<int>(nbSommets+1));

    d_adj = inter;

//    for (int i = 0; i <= nbSommets; i++)
//        d_adj[i] = new int [nbSommets];

    d_adj[0][0] = nbSommets;
}

Graphe::~Graphe() {

}

void Graphe::charger(const std::istream &ist)
{

}

void Graphe::initAdj()
{
    d_adj[0][1] = 0;
    for (int i = 1; i <= d_adj[0][0]; i++)
    {
        for (int j = 1; j <= d_adj[0][0]; j++)
        {
            d_adj[i][j] = -1;
            if ( i == j ) d_adj[i][j] = 0;

        }
    }
}

void Graphe::ajouterLisaison(int predecesseur, int successeur, int valeur)
{
    d_adj[predecesseur][successeur] = valeur;
    d_adj[0][1]++;
    /*d_adj[0][successeur]++;//Si l'on utilise la première ligne pour stocker le nombre de prédecesseur
     *d_adj[predecesseur][0]++;//Si l'on utilise la première colonne pour stocker le nombre de successeur*/
}


std::vector<int> Graphe::operator[](int i) const
{
    return d_adj[i];
}

 std::vector<std::vector<int>> Graphe::matriceAdj() const
{
    return d_adj;
}

std::vector<int> Graphe::tableauMatrice(int i) const
{
    return d_adj[i];
}

int Graphe::valMatrice(int i, int j) const
{
    return d_adj[i][j];
}

void Graphe::setMatrice(std::vector<std::vector<int>> &adj)
{
    d_adj = adj;
}

void Graphe::detAps(std::vector<int> fs, std::vector<int> &aps) const {
    int n = fs[0];
    aps.resize(n+1);
    aps[0] = n;
    aps[1] = 1;

    int j = 1;
    for (int i = 2 ; i < n ; ++i)
    {
        while(fs[j] != 0)
        {
            ++j;
        }
        ++j;
        aps[i] = j;
    }
}


void Graphe::fs_aps_2_adj(std::vector<int> fs, std::vector<int> aps)
{
    int n = aps[0], m = fs[0] -n;

    /*
     * Ce sont deux lignes a supprimer selon moi (dorian) car d_adj est cense etre alloue avant d'appeler cette fonction
     * Pour creer d_adj, il faut le nombre de sommets au moins, soit aps[0].
     * Il y a donc redondance.
     * (Allah limite on peut laisser la deuxieme)
     */
    d_adj[0][0] = n;
    d_adj[0][1] = m;

    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = aps[i] ; (j = fs[j]) != 0 ; j++)
        {
            d_adj[i][j] = 1;//Fonctionne pour un graphe non valué mais comment on procède dans le cas d'un graphe valué?
        }
    }
}

//Est-ce que la distance fait sens dans un graphe non Orienté? Sinon, déplacer la méthode dans Graphe Orianté
void Graphe::distance(std::vector<int> fs, std::vector<int> aps, std::vector<int> &dist, int s) const
{
    int t = 0;
    int q = 1;
    int p = 1;
    int d = 0;
    int n = aps[0];

    dist.resize(n + 1);
    dist[0] = n;

    std::vector<int> fa(n + 1);

    for(int i = 1 ; i <= n ; i++) dist[i] = -1;
    fa[0] = n;
    fa[1] = s;

    while(t < q)
    {
        d++;
        for(int i = t+1 ; i <= q ; i++)
        {
            int suiv = aps[fa[i]];

            while(fs[suiv] != 0)
            {
                if(dist[fs[suiv]] == -1)
                {
                    dist[fs[suiv]] = d;
                    fa[++p] = fs[suiv];
                }
                suiv++;
            }
        }
        t = q;
        q = p;
    }

}

//Même combat que précédemment
void Graphe::m_distances(std::vector<int> fs, std::vector<int> aps,  std::vector<std::vector<int>> &m_dist) const
{
    int n = aps[0];

    m_dist.resize(n + 1);
    m_dist[0].resize(1);
    m_dist[0][0] = n;

    for(int s = 1 ; s <= n ; s++)
    {
        distance(fs, aps, m_dist[s], s);
    }
}

//Ne peut exister que si le graphe est orienté
//Est-ce nécessaire?
int Graphe::rang(std::vector<int> fs, std::vector<int> aps, int s) const {

}

//Ne peut exister que si le graphe est orienté
void Graphe::m_rangs(std::vector<int> fs, std::vector<int> aps,  std::vector<std::vector<int>> &m_rangs) const {

}

void Graphe::dijkstra(std::vector<int> fs, std::vector<int> aps, int s, std::vector<int> &d, std::vector<int> &pred) const
{
    int n = aps[0], h;

    d.resize(n + 1);
    d[0] = n;

    pred.resize(n+1);
    pred[0] = n;

    bool *x = new bool[n + 1];

    // initialisation de d a -1
    for(int i = 1 ; i <= n ; i++)
    {
        d[i] = -1;
    }

    for(int i = 1 ; i <= n ; i++)
    {
        d[i] = d_adj[s][i];
        if(d[i] != -1) pred[i] = s;
        else pred[i] = -1;
        x[i] = false;
    }

    pred[s] = 0;
    x[s] = true;
    int cpt = n;

    while(--cpt > 0)
    {
        // calcul du minimum dans d pour les sommets qui ne sont pas dans x

        int minh = INT32_MAX;
        int j = -1;

        for(int i = 1 ; i <= n ; i++)
        {
            if(!x[i])
            {
                if(d[i] < minh)
                {
                    minh = d[i];
                    j = i;
                }
            }
        }

        if(minh == INT32_MAX) break;    // j == -1
        x[j] = true;

        for(int k = aps[j] ; (k = fs[k]) != 0 ; k++)
        {
            if(!x[k])
            {
                int v = d[j] + d_adj[j][h];

                if(v < d[h])
                {
                    d[h] = 0;
                    pred[h] = j;
                }
            }
        }
    }

    delete[] x;
}

void Graphe::afficher()
{
    for (int i = 1; i <= d_adj[0][0]; i++ )
    {
        for (int j = 1 ; j <= d_adj[0][0]; j++)
            std::cout << d_adj[i][j] << " " ;
        std::cout << std::endl;
    }
}

void Graphe::det_app(std::vector<int> ddi, std::vector<int> &app) const
{
    int n = ddi[0];
    app.resize(n +1);
    app[0] = n;
    app[1] = 1;

    for (int i = 2 ; i <= n ; ++i)
        app[i] = app[i - 1] + ddi[i - 1] + 1;
}

void Graphe::det_ddi(std::vector<int> fs, std::vector<int> aps, std::vector<int> &ddi) const
{
    int n = aps[0];
    ddi.resize(n + 1);

    for (int i = 0 ; i <= n ; ++i)
        ddi[i] = 0;

    for (int i = 1 ; i <= n ; ++i)
        ++ddi[fs[i]];
    ddi[0] = n;
}

void Graphe::fs_aps_2_fp_app(std::vector<int> fs, std::vector<int> aps, std::vector<int> &fp, std::vector<int> &app) const
{
    std::vector<int> ddi;
    int n = aps[0];
    int j;

    det_ddi(fs, aps, ddi);
    det_app(ddi, app);
    fp[0] = fs[0];

    for(int i = 1 ; i <= n ; ++i)
        for (int k = aps[i] ; (j = fs[k]) != 0 ; ++k)
            fp[app[j]++] = i;

    for (int i = 1 ; i <= n ; ++i)
        fp[app[i]] = 0;

    for (int i = n ; i > 1 ; --i)
        app[i] = app[i - 1] + 1;

    app[1] = 1;

}


