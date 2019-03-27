#include <iostream>
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


    /** commenter cette ligne pour pouvoir tester, non commenté ici pour ne pas oublie de liberer l'espace memoir */
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
    std::cout << "combien voulez vous de lien ? " << std::endl;
    std::cin >> i;
    return i;
}

void creerGrapheOrienteClavier()
{
    GrapheOriente *go;
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

void creerGrapheNonOrienteClavier()
{
    GrapheNonOriente *gno;
    int nbSommet, liaison, cpt = 0;
    bool value;
    nbSommet = entrerNbSommets();
    liaison = entrerNbLiaison();
    value = creerGrapheValueOuNon();
   // gno = new GrapheNonOriente(nbSommet);

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

    if (choix == 1)
    {
        creerGrapheOrienteClavier();
    }
    else if ( choix == 2)
    {
        creerGrapheNonOrienteClavier();
    }
    else
    {
        std::cout << "entree invalide" << std::endl;
    }
}


int main() {
    creerGrapheOriente();
//    creerGrapheClavier();


    std::cout << "Hello, World!" << std::endl;
    return 0;
}