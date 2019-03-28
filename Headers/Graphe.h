#ifndef GRAPHES_GRAPHE_H
#define GRAPHES_GRAPHE_H


#include <vector>
#include <iostream>

using std::vector;

class Graphe
{
protected:
    int** d_adj;

public:

    /**
     * Constructeur de Graphe par defaut : cree un graphe avec une matrice d'adjacence vide
     */
    Graphe();

    /**
     * Destructeur virtuel de Graphe (car methodes virtuelles)
     */
    virtual ~Graphe();

    /**
     * Constructeur de Graphe avec une matrice d'adjacence en parametre
     * @param [in] adj
     */
    Graphe(int** adj);


    /**
     * Constructeur de Graphe avec le nombre de sommets et le nombres d'arcs/aretes
     * @param nbSommets
     * @param nbLiaison
     */
    Graphe(int nbSommets);




    // ---------------------------- CHARGEMENT -----------------------------

    /**
     * Charge un graphe depuis un objet istream
     * Les fichiers permettant de sauvegarder un graphe sont au format txt. Il faut passer un istream en parametre, deja initialise sur un fichier
     * @param ist - objet istream permettant le remplissage du graphe (la matrice d'adjacence)
     */
    void charger(const std::istream &ist);




    // ---------------------------- MANIPULATION ----------------------------

    /**
     * Methode qui permet d'initialiser la matrice d'adjacence
     */
    void initAdj();


    /**
     * méthode qui permet de rajouter une arete ou un arc dans la matrice d'adjacence
     * @param [in] predecesseur - sommet pere
     * @param [in] successeur - sommet fils
     * @param [in] valeur - valeur de la liaison
     */
    void ajouterLisaison(int predecesseur, int successeur, int valeur = 1);


    // ----------------------------- Methodes d'acces et modification des attributs prives -----------------------------
    /**
     * Retourne la matrice d'adjacence
     * @return tableau 2D : matrice d'adjacence
     */
    int** matriceAdj() const;

    /**
     * Retourne un tableau a une certaine ligne de la matrice d'adjacence
     * @param [in] i - ligne de la matrice
     * @return tableau 1D : ligne i de la matrice d'adjacence
     */
    int* tableauMatrice(int i) const;

    /**
     * Retourne une valeur a une certaine case de la matrivce d'adjacence
     * @param [in] i - ligne de la matrice
     * @param [in] j - colonne de la matrice
     * @return int : valeur a la case (i,i) de la matrice d'adjacence
     */
    int valMatrice(int i, int j) const;

    /**
     * Permet d'affecter d_adj a une autre matrice
     * @param [in] adj : nouvelle matrice d'adjacence
     */
    void setMatrice(int** &adj);


    // ----------------------------- Methodes de classe (par rapport au graphe)  -----------------------------

    /**
     * Determine aps
     * Utilise fs
     * Fonction void car elle est utilisee quand un tableau est deja declare ailleurs dans le code. detAps remplit ce tableau
     * @param [in] fs : tableau des successeurs
     * @param [out] aps : tableau aps a remplir
     */
    void detAps(int* fs, int* &aps) const;

    /**
     * Determine fs et aps. Adj est attribut prive
     * @param [out] fs : tableau fs a remplir
     * @param [out] aps : tableau aps a remplir
     */
    virtual void adj_2_fs_aps(int* &fs, int* &aps) const = 0;

    /**
     * Remplit la matrice d'adjacence (d_adj) depuis fs et aps
     * @param fs : tableau fs
     * @param aps : teableau aps
     */
    void fs_aps_2_adj(int* fs, int* aps);

    /**
     * Détermine la file des premiers prédécesseurs
     * @param [in] ddi : tableau ddi
     * @param [out] app : tableau app, adresses des premiers prédécesseurs
     */
    void det_app(int* ddi, int* &app) const ;

    /**
     * Passage de fs aps à fp app
     * @param fs : tableau fs
     * @param aps : tableau aps
     * @param fp : tableau fp, file des prédécesseurs
     * @param app : tableau app
     */
     void fs_aps_2_fp_app(int* fs, int* aps, int* &fp, int* &app) const;

    /**
     * Determine la tableau des distance pour un sommet donne
     * Correspond a une ligne de la matrice des distances
     * Utilise fs, aps
     * @param [in] fs : tableau fs const (pas modifie dans la methode)
     * @param [in] aps : tableau aps const (pas modifie dans la methode)
     * @param [out] dist : tableau des distances
     * @param [in] s : numero du sommet dont il faut determine la tableau des distances
     */
    void distance(int* fs, int* aps, int* &dist, int s) const;


    /**
     * Determine la matrice des distances
     * Utilise la matrice d'adj (d_adj)
     * @param [in] fs : tableau fs const
     * @param [in] aps : tableau aps const
     * @param [out] m_dist : matrice des distances
     */
    void m_distances(int* fs, int* aps, int** &m_dist) const;

    /**
     * Determine le rang d'un sommet s
     * @param [in] fs : tableau fs
     * @param [in] aps : tableau aps
     * @param [in] s : numero du sommet
     * @return int : rang du sommet
     */
    int rang(int* fs, int* aps, int s) const;

    /**
     * Determine le rang de tous les sommets du graphe
     * @param [in] fs : tableau fs
     * @param [in] aps : tableau aps
     * @param [out] m_rangs : matrice des rangs
     */
    void m_rangs(int* fs, int* aps, int** &m_rangs) const;

    /**
     * Algorithme de Dijkstra : plus court chemin
     * @param [in] fs - tableau fs
     * @param [in] aps - tableau aps
     * @param [in] s - sommet pour lequel on veut calculer le plus court chemin
     * @param [in,out] d -
     * @param [in,out] pred -
     */
    void dijkstra(int* fs, int* aps, int s, int* &d, int* &pred) const;

    /**
     * Determine le nombre de predecesseurs de chaque sommet
     * @param [in] fs : tableau fs
     * @param [in] aps : tableau aps
     * @param [out] ddi : tableau des successeurs
     */
    void det_ddi(int* fs, int* aps, int* &ddi) const ;


    void afficher();
};


#endif //GRAPHES_GRAPHE_H
