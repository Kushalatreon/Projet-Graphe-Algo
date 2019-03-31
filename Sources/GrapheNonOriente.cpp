#include "../Headers/GrapheNonOriente.h"

GrapheNonOriente::GrapheNonOriente() : Graphe()
{}

GrapheNonOriente::GrapheNonOriente(std::vector<std::vector<int>> adj) : Graphe(adj)
{}

GrapheNonOriente::GrapheNonOriente(int nbSommets) : Graphe(nbSommets)
{
    initAdj();
}

// a modifier
void GrapheNonOriente::adj_2_fs_aps(std::vector<int> &fs, std::vector<int> &aps) const
{
    int n = d_adj[0][0], m = d_adj[0][1];
    /*int m = 0;
     *for (int i = 1; i <= d_adj[0][0]; i++) //Si l'on utilise la première ligne/colonne
     *  if(d_adj[i][0] > 0)
     *      m += d_adj[i][0]; */
    fs.resize(n + m*2 + 1); // m*2 car pour le cas non oriente on duplique tous les arcs
    fs[0] = n + m;

    aps.resize(n + 1);
    aps[0] = n;

    int k =1;
    for(int i = 1 ; i <= n ; i++)
    {
        aps[i] = k;
        for(int j = 1 ; j <= n ; j++)
        {
            if(d_adj[i][j] >= 1)
                fs[k++] = j;
        }
        fs[k++] = 0;
    }
}


void GrapheNonOriente::triAretes_ParBulle(std::vector<GrapheNonOriente::arete> &_a, int taille) const
{
    bool estTrie = false;
    while(!estTrie)
    {
        estTrie = true;
        for(int i = 0 ; i < taille-1 ; i++)
        {
            if(_a[i].p > _a[i+1].p)
            {
                std::swap(_a[i], _a[i+1]);
                estTrie = false;
            }
        }

        --taille;
    }
}

void GrapheNonOriente::getAretesTrieesParPoids(std::vector<GrapheNonOriente::arete> &_a, int taille) const
{
    // remplissage du tableau d'aretes
    for(int i = 1 ; i <= d_adj[0][0] ; ++i)
    {
        for (int j = 1; j <= d_adj[0][0] ; ++j)
        {
            if(d_adj[i][j] != 0)
            {
                _a[i].t = i;
                _a[i].s = j;
                _a[i].p = d_adj[i][j];
            }
        }
    }

    // tri du tableau d'aretes
    triAretes_ParBulle(_a, taille);
}

void GrapheNonOriente::setAretes(GrapheNonOriente &h, const std::vector<GrapheNonOriente::arete> &_a, int taille)
{
    for ( int i = 0 ; i < taille ; ++i)
    {
        int s = _a[i].s;
        int t = _a[i].t;
        int p = _a[i].p;

        if(_a[i].p != 0)
        {
            h.d_adj[t][s] = p;
        }
    }
}

void GrapheNonOriente::fusion(int i, int j, std::vector<int> prem, std::vector<int> &pilch, std::vector<int> &cfc) const
{
    // i et j sont des numeros de composantes
    // i != j

    int s = prem[i];

    while ( pilch[s] != 0 ) s = pilch[s];

    pilch[s] = prem[j];

    while ( pilch[s] != 0 )
    {
        s = pilch[s];
        cfc[s] = i;
    }
}

void GrapheNonOriente::Kruskal(GrapheNonOriente &h)
{
    // nombre de sommets
    int n = d_adj[0][0];

    // nombre d'aretes
    int m = d_adj[0][1];

    // Appel au constructeur par recopie pour creer l'arbe h avec le nombre de sommets du graphe courant
    h = {n};

    // Le nombre d'aretes, dans un arbre de Kruskal, est egal au nombre de sommets - 1
    h.d_adj[0][1] = h.d_adj[0][0] - 1;  // <=> = d_adj[0][0]

    // d_adj[0][1] = nb aretes du graphe courant
    // aretes de l'arbre recouvrant minimal
    std::vector<arete> aretesARM(m);      // <=> h.a dans l'algorithme du cours

    // aretes du graphe courant triees par ordre croissant selon leur poids
    std::vector<arete> aretesGCT(m);      // <=> g.a dans l'algorithme du cours

    // remplissage du tableau d'arete du  graphe courant
    getAretesTrieesParPoids ( aretesGCT, m ) ;


    /*
     * A partir de la, aretesGCT represente les aretes du graphe courant (celui sur lequel on applique l'algorithme de Kruskal).
     * Les aretes sont triees par ordre croissant de leur poids et possedent :
     * - un predecesseur (t)
     * - un successeur   (s)
     * - un poids        (p)
     */




    std::vector<int> prem(n + 1);
    std::vector<int> pilch(n + 1);
    std::vector<int> cfc(n + 1);

    // initialisation de prem, pilch et cfc
    for ( int i = 1 ; i <= n ; ++i)
    {
        prem[i] = i;
        pilch[i] = 0;
        cfc[i] = i;
    }

    for ( int i = 1, k = 0 ; i <= n && k < n ; ++i)
    {
        arete e = aretesGCT[i];

        if(cfc[e.s] != cfc[e.t])
        {
            aretesARM[k++] = e;
            fusion ( cfc[e.s], cfc[e.t], prem, pilch, cfc);
        }
    }

    setAretes(h, aretesARM, m);

    //delete[] aretesARM;
    //delete[] aretesGCT;

}

void GrapheNonOriente::codagePrufer(std::vector<std::vector<int>> A, std::vector<int> &C) {
    int n = A[0][0] - 2; //nombre de sommets - 2

    C.resize(n + 1); //nombre de sommets - 2, + 1 case pour le nombre de cases de C
    C[0] = n;




    for (int i = 1 ; i <= n + 2 ; ++i)
        A[i][0] = 0;

    for (int i = 1 ; i <= n + 2 ; ++i)
        for (int j = 1 ; j <= n + 2 ; ++j)
            if (A[i][j] == 1)
            {
                ++A[i][0];
            }


    for (int k = 1 ; k <= n ; ++k)
    {
        int i = 1, j = 1;

        for (; A[i][0] != 1 ; ++i);
        for (; A[i][j] != 1 ; ++j);

        C[k] = j;
        A[i][j] = 0;
        A[j][i] = 0;
        --A[i][0];
        --A[j][0];
    }
}

void GrapheNonOriente::decodagePrufer(std::vector<int> &C) {
    //C[0] = l'indice du dernier élément
    int n = C[0] + 2;
    bool* I = new bool[n + 1];
    std::vector<int> nbOcc (n + 1);
    nbOcc[0] = n;

    for (int i = 1 ; i <= n ; ++i)
    {
        I[i] = true;
        nbOcc[i] = 0;
    }

    for (int i = 1 ; i < n - 1 ; ++i)
        nbOcc[C[i]]++;

    for (int i = 1 ; i < n - 1 ; ++i)
    {
        int s = C[i];
        std::cout<<'('<<s<<',';

        int t = 1;
        while (!I[t] || nbOcc[t] > 0) {++t;}
        std::cout<<t<<')'<<std::endl;
        I[t] = false;
        --nbOcc[s];
    }

    int s = 1;

    for (; !I[s] ; ++s);
    std::cout<<'('<<s<<',';
    ++s;

    for (; !I[s] ; ++s);
    std::cout<<s<<')'<<std::endl;


    delete[] I;

}






