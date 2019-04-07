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

void testadj_fs_aps()
{
    std::vector<int> fs;
    std::vector<int> aps;

    GrapheNonOriente *g = new GrapheNonOriente();
    std::ifstream f ("../Data/GrapheNonOriente1.txt");
    bool type;
    f >> type;
    charger(f, g);

    g->adj_2_fs_aps(fs,aps);


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

void testConstructeurMatriceParam()
{

    std::vector<std::vector<int>> matrice(4, std::vector<int>(4));


    for (int i = 1 ; i < matrice.size() ; ++i)
    {
        for (int j = 1 ; j < matrice[i].size() ; ++j)
        {
            if (i == j)
            {
                matrice[i][j] = 0;
            }
            else
                matrice[i][j] = 1;
        }
    }

    matrice[0][0] = 3;
    matrice[0][1] = 6;
    GrapheNonOriente g{matrice};
    //GrapheOriente g{matrice};


    g.afficher();

}

void testConstructeurNbSommets()
{
    int nbSommets = 3;

    GrapheOriente g{nbSommets};
    g.afficher();
    std::cout<<std::endl;

    std::cout<<g[0][0];
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


int main() {
//    creerGrapheOriente();
    //creerGrapheClavier();

//    testPrufer();

    //testadj_fs_aps();
    //testKruskal();

    //testTarjan();
    //int sertarien = 2;

    //testConstructeurMatriceParam();
    //testConstructeurNbSommets();

    testDijkstraEtLeResteQuiEstCasse();


    //std::cout << "Hello, World!" << std::endl;
    return 0;
}