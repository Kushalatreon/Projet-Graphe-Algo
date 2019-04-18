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

void Graphe::charger(std::ifstream &i)
{
    if( !i) return;

    int n;  // nb sommets
    int m;  // nb aretes


    i >> n >> m;
    std::vector<std::vector<int>> tmp (n+1, std::vector<int>(n+1));

    tmp[0].reserve(2);
    tmp[0][0] = n;
    tmp[0][1] = m;
    for(int i = 1 ; i <= n ; ++i)
    {
        tmp[i].reserve(n+1);
    }

    int val;
    while(!i.eof())
    {
        for(int i = 1 ; i <= n ; i++)
        {
            for(int j = 1 ; j <= n ; j++)
            {
                i >> val;
                tmp[i][j] = val;
            }
        }
    }

    setMatrice(tmp);
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

void Graphe::setMatrice(std::vector<std::vector<int>> &adj)
{
    d_adj.resize(adj.size());

    for(int i = 0; i < d_adj.size(); i++)
    {
        d_adj[i].resize(adj[i].size());
    }

    d_adj[0][0] = adj[0][0];
    d_adj[0][1] = adj[0][1];

    int n = d_adj[0][0];

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            d_adj[i][j] = adj[i][j];
        }
    }
}

void Graphe::detAps(std::vector<int> fs, std::vector<int> &aps) const {
    int n = 0;
    for(int i = 0; i<fs.size();i++)
        if(fs[i] == 0)
            n++;
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

    int k;
    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = aps[i] ; (k = fs[j]) != 0 ; j++)
        {
            d_adj[i][k] = 1;//Fonctionne pour un graphe non valué mais comment on procède dans le cas d'un graphe valué?
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
    dist[0] = -1;

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
    m_dist[0].resize(n+1);
    m_dist[0][0] = n;

    for(int i = 1; i<=n; i++)
        m_dist[0][i] = -1;
    for(int s = 1 ; s <= n ; s++)
    {
        distance(fs, aps, m_dist[s], s);
    }
}

void Graphe::dijkstra(std::vector<int> fs, std::vector<int> aps, int s, std::vector<int> &d, std::vector<int> &pred) const
{

    std::vector<std::vector<int>> c = d_adj;

    for (int i = 0; i < d_adj.size(); ++i)
    {
        for (int j = 0; j < d_adj.size() ; ++j)
        {
            if (d_adj[i][j] == -1)
            {
                c[i][j]= INT32_MAX;
            }
        }
    }

    int n = aps[0], h;

    d.resize(n + 1);
    d[0] = n;

    pred.resize(n+1);
    pred[0] = n;

    std::vector<bool> x(n+1);

    // initialisation de d a -1
    for(int i = 1 ; i <= n ; i++)
    {
        d[i] = -1;
    }

    for(int i = 1 ; i <= n ; i++)
    {
        d[i] = c[s][i];
        if(d[i] != INT32_MAX) pred[i] = s;
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

        for(int k = aps[j] ; (h = fs[k]) != 0 ; k++)
        {
            if(!x[k])
            {
                int v = d[j] + c[j][h];

                if(v < d[h])
                {
                    d[h] = v;
                    pred[h] = j;
                }
            }
        }
    }
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
    int m = fs[0];
    ddi.resize(n + 1);

    for (int i = 0 ; i <= n ; ++i)
        ddi[i] = 0;

    for (int i = 1 ; i <= m ; ++i)
        ++ddi[fs[i]];
    ddi[0] = n;
}

void Graphe::fs_aps_2_fp_app(std::vector<int> fs, std::vector<int> aps, std::vector<int> &fp, std::vector<int> &app) const
{
    std::vector<int> ddi;
    int n = aps[0];
    int j;
    fp.resize(fs[0]+1);

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


