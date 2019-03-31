#include <iostream>
#include <fstream>
#include "Headers/GrapheOriente.h"
#include "Headers/GrapheNonOriente.h"


/**
 * Cette fonction créer un graphe (voir schema testGrapheOrienté1) qui va nous permettre de tester les fonctions vu en cours
 * Ces methodes serviront aussi pour la creation dynamique souris et clavier
 */
void creerGrapheOriente(){

    GrapheOriente *g = new GrapheOriente(4);
    g->ajouterLisaison(1,2);
    g->ajouterLisaison(1,3,1);
    g->ajouterLisaison(1,4,1);
    g->ajouterLisaison(2,4,1);
    g->ajouterLisaison(4,3,1);


    /** commenter cette ligne pour pouvoir tester, non commenter ici pour ne pas oublie de liberer l'espace memoir */
    delete g;
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
        std::cout << "Sommet pere " << std::endl;
        std::cin >> sommet1;
        std::cout << "sommet fils ? " << std::endl;
        std::cin >> sommet2;

        if (value) {
            std::cout << "Entrer le poid : " << std::endl;
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
        std::cout << "Sommet pere " << std::endl;
        std::cin >> sommet1;
        std::cout << "sommet fils ? " << std::endl;
        std::cin >> sommet2;

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

void testKruskal(GrapheNonOriente *g)
{
    GrapheNonOriente *h = new GrapheNonOriente();
    g->Kruskal(*h);
    h->afficher();
}

int main() {
//    creerGrapheOriente();
//    creerGrapheClavier();

   // testPrufer();



    std::ifstream f ("../Data/GrapheNonOriente1.txt");

    bool type = 1;
    f >> type;

    if(type)
    {
        GrapheOriente *g = new GrapheOriente();
    }
    else
    {
        GrapheNonOriente *g = new GrapheNonOriente();

        charger(f, g);



        g->afficher();



        testKruskal(g);
    }





    std::cout << "Hello, World!" << std::endl;
    return 0;
}