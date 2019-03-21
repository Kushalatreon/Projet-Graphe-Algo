#include <iostream>
#include "Headers/GrapheOriente.h"


/**
 * Cette fonction créer un graphe (voir schema testGrapheOrienté1) qui va nous permettre de tester les fonctions vu en cours
 * Ces methodes serviront aussi pour la creation dynamique souris et clavier
 */
void creerGrapheOriente(){

    GrapheOriente *g = new GrapheOriente(4);
    g->ajouterLisaison(1,2,1);
    g->ajouterLisaison(1,3,1);
    g->ajouterLisaison(1,4,1);
    g->ajouterLisaison(2,4,1);
    g->ajouterLisaison(4,3,1);


    /** commenter cette ligne pour pouvoir tester, non commenté ici pour ne pas oublie de liberer l'espace memoir */
    delete g;
}

void creerGrapheClavier()
{

}



int main() {
    creerGrapheOriente();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}