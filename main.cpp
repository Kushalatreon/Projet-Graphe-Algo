#include <iostream>
#include <fstream>
#include "Headers/GrapheOriente.h"
#include "Headers/GrapheNonOriente.h"
//#include "Sources/menuClavier.cpp"

/**
 * Cette fonction créer un graphe (voir schema testGrapheOrienté1) qui va nous permettre de tester les fonctions vu en cours
 * Ces methodes serviront aussi pour la creation dynamique souris et clavier
 */
void creerGrapheOriente(){

    GrapheOriente *g = new GrapheOriente(4);
    g->ajouterLisaison(1,2,2);
    g->ajouterLisaison(1,3,1);
    g->ajouterLisaison(1,4,3);
    g->ajouterLisaison(2,4,1);
    g->ajouterLisaison(4,3,5);


    /** commenter cette ligne pour pouvoir tester, non commenter ici pour ne pas oublie de liberer l'espace memoir */
    delete g;
}

void charger(std::ifstream &is, Graphe *g)
{
    if( !is) return;

    int n;  // nb sommets
    int m;  // nb aretes


    is >> n >> m;
    std::vector<std::vector<int>> tmp (n+1, std::vector<int>(n+1));

    tmp[0].reserve(2);
    tmp[0][0] = n;
    tmp[0][1] = m;
    for(int i = 1 ; i <= n ; ++i)
    {
        tmp[i].reserve(n+1);
    }

    int val;
    while(!is.eof())
    {
        for(int i = 1 ; i <= n ; i++)
        {
            for(int j = 1 ; j <= n ; j++)
            {
                is >> val;
                tmp[i][j] = val;
            }
        }
    }

    g->setMatrice(tmp);

}


void testCreationGraphe()
{
    //Graphe par défaut (vide)
    GrapheOriente gVide;

    //Graphe dont on passe une matrice en paramètre
    std::vector<std::vector<int>> adj;
    int n=4;
    adj.resize(n+1);
    for(int i = 0; i<=n;i++)
        adj[i].resize(n+1);
    adj[0][0] = n;
    for(int i = 1; i<=n; i++)
        for(int j = 1; j<=n; j++)
            adj[i][j] = i+j;
    GrapheOriente gAdjDonne(adj);

    //Graphe dont on ne donne que le nombre de sommet en paramètre
    GrapheOriente gNbSommet(4);

    std::cout<<std::endl;

}

void testAccesGraphe()
{
    //Accès à la ligne i du Graphe g via la méthode g[i]
    GrapheOriente g(4);
    std::vector<int> ligne = g[2];


    //Accès à la matrice d'adjacence du Graphe g
    std::vector<std::vector<int>> adj = g.matriceAdj();

    //Accès à une valeur de la matrice d'adjacence du Graphe g
    int val = g[2][3];

    //Affichage du Graphe g
    g.afficher();

    std::cout<<std::endl;

}

void testSetMatrice()
{
    GrapheOriente g(4);

    std::vector<std::vector<int>> adj;
    int n=4;
    adj.resize(n+1);
    for(int i = 0; i<=n;i++)
        adj[i].resize(n+1);
    adj[0][0] = n;
    for(int i = 1; i<=n; i++)
        for(int j = 1; j<=n; j++)
            adj[i][j] = i+j;

    g.setMatrice(adj);
    std::cout<<std::endl;
}

void testadj_fs_aps_Oriente()
{
    std::vector<int> fs;
    std::vector<int> aps;

    GrapheOriente *g = new GrapheOriente();
    std::ifstream f ("../Data/GrapheOriente1.txt");
    bool type;
    f >> type;
    charger(f, g);

    g->adj_2_fs_aps(fs,aps);


}

void testDetAps()
{
    GrapheOriente *g = new GrapheOriente(4);
    g->ajouterLisaison(1,2,2);
    g->ajouterLisaison(1,3,1);
    g->ajouterLisaison(1,4,3);
    g->ajouterLisaison(2,4,1);
    g->ajouterLisaison(4,3,5);

    std::vector<int> fs, aps;
    g->adj_2_fs_aps(fs, aps);
    for(int i = 0; i>aps.size();i++)
        aps[i] = 0;
    g->detAps(fs,aps);

    std::cout<<std::endl;
}

void testDetDdi()
{
    GrapheOriente *g = new GrapheOriente(4);
    g->ajouterLisaison(1,2,2);
    g->ajouterLisaison(1,3,1);
    g->ajouterLisaison(1,4,3);
    g->ajouterLisaison(2,4,1);
    g->ajouterLisaison(4,3,5);

    std::vector<int> fs, aps, ddi;
    g->adj_2_fs_aps(fs, aps);

    g->det_ddi(fs, aps, ddi);

    std::cout<<std::endl;
}

void testDetApp()
{
    GrapheOriente *g = new GrapheOriente(4);
    g->ajouterLisaison(1,2,2);
    g->ajouterLisaison(1,3,1);
    g->ajouterLisaison(1,4,3);
    g->ajouterLisaison(2,4,1);
    g->ajouterLisaison(4,3,5);

    std::vector<int> fs, aps, ddi, app;
    g->adj_2_fs_aps(fs, aps);

    g->det_ddi(fs, aps, ddi);
    g->det_app(ddi, app);

    std::cout<<std::endl;
}

void testFsAps2FpApp()
{
    GrapheOriente *g = new GrapheOriente(4);
    g->ajouterLisaison(1,2,2);
    g->ajouterLisaison(1,3,1);
    g->ajouterLisaison(1,4,3);
    g->ajouterLisaison(2,4,1);
    g->ajouterLisaison(4,3,5);

    std::vector<int> fs, aps, fp, app;
    g->adj_2_fs_aps(fs, aps);

    g->fs_aps_2_fp_app(fs, aps, fp, app);

    std::cout<<std::endl;
}

void testFsAps2Adj()
{
    GrapheOriente *g = new GrapheOriente(4);
    g->ajouterLisaison(1,2,2);
    g->ajouterLisaison(1,3,1);
    g->ajouterLisaison(1,4,3);
    g->ajouterLisaison(2,4,1);
    g->ajouterLisaison(4,3,5);
    g->ajouterLisaison(1,1,1);

    std::vector<int> fs, aps;
    g->adj_2_fs_aps(fs, aps);

    for(int i = 0; i<g->matriceAdj().size(); i++)
        for(int j = 0; j < g->matriceAdj()[1].size();j++)
            g->matriceAdj()[i][j] = 0;
    g->fs_aps_2_adj(fs, aps);
    //Fonctionne mais si i != j et ne sont pas reliés, adj[i][j] = -1 alors que adj[i][i] = 0 si il n'y a pas de boucle
    std::cout<<std::endl;
}

void testDistance()
{
    GrapheOriente *g = new GrapheOriente(4);
    g->ajouterLisaison(1,2,2);
    g->ajouterLisaison(1,3,1);
    g->ajouterLisaison(1,4,3);
    g->ajouterLisaison(2,4,1);
    g->ajouterLisaison(4,3,5);


    std::vector<int> fs, aps, dist;
    g->adj_2_fs_aps(fs, aps);
    g->distance(fs, aps, dist, 2);
    //Renvoie -1 en dist[i] si i inaccessible depuis le sommet en paramètre
    std::cout<<std::endl;
}

void testMatriceDistance()
{
    GrapheOriente *g = new GrapheOriente(4);
    g->ajouterLisaison(1,2,2);
    g->ajouterLisaison(1,3,1);
    g->ajouterLisaison(1,4,3);
    g->ajouterLisaison(2,4,1);
    g->ajouterLisaison(4,3,5);


    std::vector<int> fs, aps;
    std::vector<std::vector<int>> m_dist;
    g->adj_2_fs_aps(fs, aps);
    g->m_distances(fs, aps, m_dist);
    //Renvoie -1 en m_dist[i][j] si j inaccessible depuis i
    std::cout<<std::endl;
}

void testDetCfc()
{
    GrapheOriente *g = new GrapheOriente(4);
    g->ajouterLisaison(1,2,2);
    g->ajouterLisaison(1,3,1);
    g->ajouterLisaison(1,4,3);
    g->ajouterLisaison(2,4,1);
    g->ajouterLisaison(4,3,5);


    std::vector<int> fs, aps, prem, pilch, cfc;
    std::vector<std::vector<int>> m_dist;
    g->adj_2_fs_aps(fs, aps);
    g->m_distances(fs, aps, m_dist);
    g->det_cfc(m_dist, prem, pilch, cfc);

    std::cout<<std::endl;
}



void traitementGrapheOriente(GrapheOriente *&go)
{

    // Initialisation des tableaux
    std::vector<int> pilch(static_cast<unsigned int>(go->matriceAdj()[0][0] + 1));
    std::vector<int> prem(static_cast<unsigned int>(go->matriceAdj()[0][0] + 1));
    std::vector<int> cfc(static_cast<unsigned int>(go->matriceAdj()[0][0] + 1));
    std::vector<int> ro(static_cast<unsigned int>(go->matriceAdj()[0][0] + 1));
    std::vector<int> num(static_cast<unsigned int>(go->matriceAdj()[0][0] + 1));

    // FS et APS
    std::vector<int> fs;
    std::vector<int> aps;


    int choix;

    std::cout << "Quelle fonction voulez vous utiliser ?" << std::endl;
    std::cout << "1 - Tarjan + graphe reduit" << std::endl;
    std::cout << "2 - Ordonnancement " << std::endl;
    std::cout << "3 - Rang" << std::endl;
    std::cin >> choix;
    if ( choix > 0 && choix < 4)
    {
        if ( choix ==  1)
        {
            for(int i = 1; i <= go->matriceAdj()[0][0]; i++)
            {
                pilch[i] = 0;
                prem[i] = 0;
                cfc[i] = 0;
                ro[i] = 0;
                num[i] = 0;
            }
            int sommetDepart;

            std::cout << "Entrer le sommet de départ (entre 0 et " << go->matriceAdj()[0][0]<< std:: endl;
            std::cin >> sommetDepart;
            go->tarjan(num, prem, pilch, ro, cfc, sommetDepart);

            //Graphe reduit

            go->adj_2_fs_aps(fs,aps);
            std::vector<int> fsr(static_cast<unsigned int>(fs[0]));
            std::vector<int> apsr(static_cast<unsigned int>(aps[0]));

            /*
             * probleme
             */
            go->graphe_reduit(fs,aps,prem, pilch, cfc, fsr, apsr);
        }
        else if( choix ==  2)
        {
            go->adj_2_fs_aps(fs,aps);
            std::vector<int> fp(static_cast<unsigned int>(fs[0]));
            std::vector<int> app(static_cast<unsigned int>(aps[0]));
            std::vector<int> d;

            int sommetDepart;

            std::cout << "Entrer le sommet de départ (entre 0 et " << go->matriceAdj()[0][0]<< std:: endl;
            std::cin >> sommetDepart;

            go->fs_aps_2_fp_app(fs,aps,fp,app);
            go->distance(fs,aps,d,sommetDepart);

            std::vector<int> lc(static_cast<unsigned int>(fs[0]));
            std::vector<int> fpc(static_cast<unsigned int>(fs[0]));
            std::vector<int> appc(static_cast<unsigned int>(aps[0]));

            /*
             * casse, marche pas fs aps 2 fp app, app ou fp ne fini pas par 0
             */
            go->ordonnancement(fp,app,d,lc, fpc,appc);
        }
        else if( choix ==  3)
        {
            std::vector<int> m_rang;

            int sommetDepart;
            std::cout << "Entrer le sommet de départ (entre 0 et " << go->matriceAdj()[0][0]<< std:: endl;
            std::cin >> sommetDepart;
            go->adj_2_fs_aps(fs,aps);
            go->m_rangs(fs,aps,sommetDepart,m_rang);
        }
        else if ( choix == 4 )
        {
            go->adj_2_fs_aps(fs,aps);
            std::vector<int> d;
            std::vector<int> pred;

            int sommetDepart;
            std::cout << "Entrer le sommet de départ (entre 0 et " << go->matriceAdj()[0][0]<< std:: endl;
            std::cin >> sommetDepart;

            go->dijkstra(fs,aps,sommetDepart,d,pred);
        }
        else
        {

        }




    }

}

void traitementGrapheNonOriente(GrapheNonOriente *&gno)
{

    std::vector<int> fs;
    std::vector<int> aps;
    int choix;

    std::cout << "Quelle fonction voulez vous utiliser ?" << std::endl;
    std::cout << "1 - Kruskal" << std::endl;
    std::cout << "2 - Codage Prufer + decodage" << std::endl;
    std::cout << "3 - Dijkstra" << std::endl;
    std::cin >> choix;

    if ( choix > 0 && choix < 4)
    {
        if ( choix ==  1)
        {
            GrapheNonOriente *h;
            gno->Kruskal(h);
            h->afficher();
        }
        else if (choix == 2)
        {
            std::vector<int> C;
            gno->codagePrufer(gno->matriceAdj(), C);
            /*
             * AFFICHER C
             */
            gno->decodagePrufer(C);
        }
        else if (choix == 3 )
        {
            gno->adj_2_fs_aps(fs,aps);
            std::vector<int> d;
            std::vector<int> pred;

            int sommetDepart;
            std::cout << "Entrer le sommet de départ (entre 0 et " << gno->matriceAdj()[0][0]<< std:: endl;
            std::cin >> sommetDepart;

            gno->dijkstra(fs,aps,sommetDepart,d,pred);
        }
        else
        {

        }

    }
}


bool creerGrapheValueOuNon()
{
    char c;
    std::cout << "Voulez vous un graphe value ? " << std::endl;
    std::cout << "o : oui" << std::endl << "n : non" << std::endl;
    std::cin >> c;
    if (c == 'o')
    {
        return true;
    }
    else if (c == 'n')
    {
        return false;
    }
    else
    {
        std::cout << "Entree invalide " << std::endl;
        return false;
    }

}

int entrerNbSommets()
{
    int i;
    std::cout << "combien voulez vous de sommets ? " << std::endl;
    std::cin >> i;
    return i;
}

int entrerNbLiaison()
{
    int i;
    std::cout << "combien voulez vous de liens ? " << std::endl;
    std::cin >> i;
    return i;
}


void saisieSommets(int &pere, int &fils)
{
    std::cout << "Sommet pere ?" << std::endl;
    std::cin >> pere;
    std::cout << "sommet fils ? " << std::endl;
    std::cin >> fils;
}

void creerGrapheOrienteClavier(GrapheOriente *&go)
{
    int nbSommet, liaison, cpt = 0;
    bool value;
    nbSommet = entrerNbSommets();
    liaison = entrerNbLiaison();
    value = creerGrapheValueOuNon();
    go = new GrapheOriente(nbSommet);

    int val;
    while (cpt < liaison)
    {
        int sommet1, sommet2;

        saisieSommets(sommet1,sommet2);

        if (value) {
            std::cout << "Entrer le poids : " << std::endl;
            std::cin >> val;
            go->ajouterLisaison(sommet1,sommet2,val);
        }
        else
        {
           go->ajouterLisaison(sommet1,sommet2);
        }

        cpt++;
    }

    go->afficher();
}

void creerGrapheNonOrienteClavier(GrapheNonOriente *&gno)
{
    int nbSommet, liaison, cpt = 0;
    bool value;
    nbSommet = entrerNbSommets();
    liaison = entrerNbLiaison();
    value = creerGrapheValueOuNon();
    gno = new GrapheNonOriente(nbSommet);

    int val;
    while (cpt < liaison)
    {
        int sommet1, sommet2;

        saisieSommets(sommet1,sommet2);

        if (value) {
            std::cout << "Entrer le poids : " << std::endl;
            std::cin >> val;
            gno->ajouterLisaison(sommet1,sommet2,val);
            gno->ajouterLisaison(sommet2,sommet1,val);
        }
        else
        {
            gno->ajouterLisaison(sommet1,sommet2);
            gno->ajouterLisaison(sommet2,sommet1);
        }
        cpt++;
    }



    gno->afficher();
}



void creerGrapheClavier()
{
    int choix ;
    std::cout << "Voulez vous un graphe oriente ou non oriente " << std::endl;
    std::cout << "1 : Oriente " << std::endl << "2 : non oriente" << std::endl;
    std::cin >> choix;

    GrapheOriente *go;
    GrapheNonOriente *gno;

    if (choix == 1)
    {
        creerGrapheOrienteClavier(go);
        traitementGrapheOriente(go);

    }
    else if ( choix == 2)
    {
        creerGrapheNonOrienteClavier(gno);

    }
    else
    {
        std::cout << "entree invalide" << std::endl;
    }
}


void testPrufer()
{
    GrapheNonOriente *gno;
    std::vector<int> C;
    std::cout<<"---------------------------------------------------------------------------------------------------"<<std::endl;
    std::cout<<"Ne fonctionne que sur un graphe non value ! Sinon les poids des aretes sont perdus lors du codage !"<<std::endl;
    std::cout<<"---------------------------------------------------------------------------------------------------"<<std::endl;

    creerGrapheNonOrienteClavier(gno);

    gno->codagePrufer(gno->matriceAdj(), C);


    std::cout<<"Décodage : "<<std::endl;
    gno->decodagePrufer(C);

}


void testKruskal()
{
    std::ifstream f ("../Data/GrapheNonOriente1.txt");

    GrapheNonOriente *g = new GrapheNonOriente();

    bool t;
    f >> t;

    charger(f, g);

    g->afficher();

    GrapheNonOriente *h;
    g->Kruskal(h);
    std::cout << std::endl;
    h->afficher();
}

void testadj_fs_aps_NonOriente()
{
    std::vector<int> fs;
    std::vector<int> aps;

    GrapheNonOriente *g = new GrapheNonOriente();
    std::ifstream f ("../Data/GrapheNonOriente1.txt");
    bool type;
    f >> type;
    charger(f, g);

    g->adj_2_fs_aps(fs,aps);

    for (int i = 0 ; i < fs.size() ; ++i)
    {
        std::cout<< "fs[" << i <<"] : " << fs[i] << std::endl;
    }

    for (int i = 0 ; i < aps.size() ; ++i)
    {
        std::cout<< "aps[" << i <<"] : " << aps[i] << std::endl;

    }


}

void testMRang()
{
    /*GrapheOriente *g = new GrapheOriente(4);
    g->ajouterLisaison(1,2,2);
    g->ajouterLisaison(1,3,1);
    g->ajouterLisaison(1,4,3);
    g->ajouterLisaison(2,4,1);
    g->ajouterLisaison(4,3,5);
    */
    GrapheOriente *g = new GrapheOriente();
    //creerGrapheOrienteClavier(g);

    std::ifstream f ("C:/Users/Thibaud/Desktop/grapheTestRang.txt");
    bool t;
    f >> t;
    charger(f, g);


    int r=0;
    std::vector<int> fs, aps, m_rangs;
    g->adj_2_fs_aps(fs, aps);
    bool test = g->m_rangs(fs, aps, r, m_rangs);

    if (test)
    {
        std::cout << "Tous les sommets ont un rang fini. Le graphe ne contient pas de boucle" << std::endl;
        for (int i = 1 ; i <= m_rangs.size() ; ++i)
            std::cout << "Rang du sommet " << i << " : " << m_rangs[i];
    }
    else
    {
        std::cout << "Le graphe contient une boucle, des sommets n'ont pas de rang fini." << std::endl;
        for (int i = 1 ; i <= m_rangs.size() ; ++i)
            std::cout << "Rang du sommet " << i << " : " << m_rangs[i];
    }
}



void testTarjan()
{
    std::ifstream f ("../Data/GrapheOriente1.txt");
    bool type;
    f >> type;

    GrapheOriente *g = new GrapheOriente();
    charger(f, g);

    std::vector<int> pilch(static_cast<unsigned int>(g->matriceAdj()[0][0] + 1));
    std::vector<int> prem(static_cast<unsigned int>(g->matriceAdj()[0][0] + 1));
    std::vector<int> cfc(static_cast<unsigned int>(g->matriceAdj()[0][0] + 1));
    std::vector<int> ro(static_cast<unsigned int>(g->matriceAdj()[0][0] + 1));
    std::vector<int> num(static_cast<unsigned int>(g->matriceAdj()[0][0] + 1));

    int sommet = 3;

    // initialisation des tableaux à 0
    for(int i = 1; i <= g->matriceAdj()[0][0]; i++)
    {
        pilch[i] = 0;
        prem[i] = 0;
        cfc[i] = 0;
        ro[i] = 0;
        num[i] = 0;
    }

    g->tarjan(num, prem, pilch, ro, cfc, sommet);
}



void testDijkstraEtLeResteQuiEstCasse()
{

    GrapheOriente *g = new GrapheOriente(4);
    g->ajouterLisaison(1,2,2);
    g->ajouterLisaison(1,3,1);
    g->ajouterLisaison(1,4,3);
    g->ajouterLisaison(2,4,1);
    g->ajouterLisaison(4,3,5);


    std::vector<int> fs(10);
    std::vector<int> aps(5);
    std::vector<int> d(5);
    std::vector<int> pred(5);
    int s = 2;

    g->adj_2_fs_aps(fs, aps);

    // test dijkstra
    g->dijkstra(fs, aps, s, d, pred);




    std::vector<int> fp(static_cast<unsigned int>(fs[0] + 1));
    std::vector<int> app(static_cast<unsigned int>(aps[0] + 1));

    // test fs_aps_2_fp_app
    g->fs_aps_2_fp_app(fs, aps, fp, app);




    d[1] = 2;
    d[2] = 1;
    d[3] = 7;
    d[4] = 4;
    d[5] = 3;

    std::vector<int> lc(5);
    std::vector<int> fpc(10);
    std::vector<int> appc(5);

    // test ordonnancement
    g->ordonnancement(fp, app, d, lc, fpc, appc);

    delete g;

}

void affecteDuree(GrapheOriente *go, int duree, int sommet)
{
    for ( int i = 1; i <= go->matriceAdj()[0][0]; i++)
    {
        if (go->matriceAdj()[sommet][i] > 0 )
        {
           go->ajouterLisaison(sommet,i,duree);
        }
    }
}


void testOrdonnancement()
{
    int nbSommet, nbLiaison;
    nbSommet = entrerNbSommets();
    nbLiaison = entrerNbLiaison();

    std::vector<std::string> tache ;
    tache.resize(nbSommet+1);
    GrapheOriente *go = new GrapheOriente(nbSommet);

    for ( int i = 1; i <= nbSommet; i++)
    {
        std::cout << "Nom de la tache " << i << std::endl;
        std::cin >> tache[i];
    }

    int cpt = 0;
    while (cpt < nbLiaison)
    {
        int sommet1, sommet2;
        saisieSommets(sommet1,sommet2);
        go->ajouterLisaison(sommet1,sommet2);
        cpt++;
    }

    int duree = 0;
    std::vector<int> d;
    d.resize(nbSommet+1);
    for ( int i = 1; i <= nbSommet; i++)
    {
        std::cout << "Duree de la tache " << i << " : " << tache[i] << std::endl;
        std::cin >> duree;
        affecteDuree(go,duree,i);
        d[i] = duree;
    }

    std::vector<int> fs;
    std::vector<int> aps;
    go->adj_2_fs_aps(fs, aps);

    std::vector<int> fp;
    std::vector<int> app;
    fp.resize(fs.size());
    app.resize(aps.size());
    go->fs_aps_2_fp_app(fs, aps, fp, app);

    std::vector<int> lc;
    std::vector<int> fpc;
    std::vector<int> appc;

    go->ordonnancement(fp,app,d,lc,fpc,appc);





}


int main() {
//    creerGrapheOriente();
//testCreationGraphe();
//testAccesGraphe();
//testSetMatrice();
//testDetAps();
//testDetDdi();
//testDetApp();
//testFsAps2FpApp();
//testFsAps2Adj();
//testDistance();
//testMatriceDistance();
//testDetCfc();
testMRang();
    //creerGrapheClavier();

//    testPrufer();

    //testadj_fs_aps_NonOriente();
    //testadj_fs_aps_Oriente();
    //testKruskal();

    //testTarjan();
    //int sertarien = 2;



//    testDijkstraEtLeResteQuiEstCasse();

    //testOrdonnancement();

    //std::cout << "Hello, World!" << std::endl;
    return 0;
}