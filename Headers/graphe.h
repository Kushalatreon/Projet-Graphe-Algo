#ifndef GRAPHE_H
#define GRAPHE_H

#include <vector>
#include <iostream>
#include <fstream>

class Graphe
{
protected:
    std::vector<std::vector<int>> d_adj;
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
    Graphe( std::vector<std::vector<int>> &adj);


    /**
     * Constructeur de Graphe avec le nombre de sommets
     * @param nbSommets
     */
    Graphe(int nbSommets);



    // ---------------------------- CHARGEMENT -----------------------------

    /**
     * Charge un graphe depuis un objet istream
     * Les fichiers permettant de sauvegarder un graphe sont au format txt. Il faut passer un istream en parametre, deja initialise sur un fichier
     * @param i - objet istream permettant le remplissage du graphe (la matrice d'adjacence)
     */
    void charger(std::ifstream &i);




    // ---------------------------- MANIPULATION ----------------------------

    /**
     * Permet d'initialiser la matrice d'adjacence
     */
    void initAdj();


    /**
     * Permet de rajouter une arete ou un arc dans la matrice d'adjacence
     * @param [in] predecesseur - sommet pere
     * @param [in] successeur - sommet fils
     * @param [in] valeur - valeur de la liaison
     */
    void ajouterLisaison(int predecesseur, int successeur, int valeur = 1);

    /**
     * Redéfinition de l'opérateur []
     * Permet par exemple d'utiliser std::cout<<g[0][0]
     * @param [in] i - l'indice de la ligne à afficher
     * @return le vecteur de la ligne i
     */
    std::vector<int> operator[](int i) const;

    // ----------------------------- Methodes d'acces et modification des attributs prives -----------------------------


    /**
     * Retourne la matrice d'adjacence
     * @return tableau 2D - matrice d'adjacence
     */
     std::vector<std::vector<int>> matriceAdj() const;

    /**
     * Permet d'affecter d_adj a une autre matrice
     * @param [in] adj - nouvelle matrice d'adjacence
     */
    void setMatrice( std::vector<std::vector<int>> &adj);


    // ----------------------------- Methodes de classe (par rapport au graphe)  -----------------------------

    /**
     * Determine aps
     * Fonction void car elle est utilisee quand un tableau est deja declare ailleurs dans le code. detAps remplit ce tableau
     * @param [in] fs - tableau des successeurs
     * @param [out] aps - tableau aps a remplir
     */
    void detAps(std::vector<int> fs, std::vector<int> &aps) const;

    /**
     * Determine fs et aps. Adj est attribut prive
     * @param [out] fs - tableau fs a remplir
     * @param [out] aps - tableau aps a remplir
     */
    virtual void adj_2_fs_aps(std::vector<int> &fs, std::vector<int> &aps) const = 0;

    /**
     * Remplit la matrice d'adjacence (d_adj) depuis fs et aps
     * @param [in] fs - tableau fs
     * @param [in] aps - tableau aps
     */
    void fs_aps_2_adj(std::vector<int> fs, std::vector<int> aps);

    /**
     * Détermine la file des premiers prédécesseurs
     * @param [in] ddi - tableau ddi
     * @param [out] app - tableau app, adresses des premiers prédécesseurs
     */
    void det_app(std::vector<int> ddi, std::vector<int> &app) const ;

    /**
     * Passage de fs aps à fp app
     * @param [in] fs - tableau fs
     * @param [in] aps - tableau aps
     * @param [out] fp - tableau fp, file des prédécesseurs
     * @param [out] app - tableau app
     */
     void fs_aps_2_fp_app(std::vector<int> fs, std::vector<int> aps, std::vector<int> &fp, std::vector<int> &app) const;

    /**
     * Determine la tableau des distance pour un sommet donne
     * Correspond a une ligne de la matrice des distances
     * @param [in] fs - tableau fs
     * @param [in] aps - tableau aps
     * @param [out] dist - tableau des distances
     * @param [in] s - numero du sommet dont il faut determine la tableau des distances
     */
    void distance(std::vector<int> fs, std::vector<int> aps, std::vector<int> &dist, int s) const;


    /**
     * Determine la matrice des distances
     * @param [in] fs - tableau fs
     * @param [in] aps - tableau aps
     * @param [out] m_dist - matrice des distances
     */
    void m_distances(std::vector<int> fs, std::vector<int> aps,  std::vector<std::vector<int>> &m_dist) const;

    /**
     * Algorithme de Dijkstra : plus court chemin
     * @param [in] fs - tableau fs
     * @param [in] aps - tableau aps
     * @param [in] s - sommet pour lequel on veut calculer le plus court chemin
     * @param [in,out] d - la distance
     * @param [in,out] pred - le tableau des predecesseurs
     */
    void dijkstra(std::vector<int> fs, std::vector<int> aps, int s, std::vector<int> &d, std::vector<int> &pred) const;

    /**
     * Determine le nombre de predecesseurs de chaque sommet
     * @param [in] fs - tableau fs
     * @param [in] aps - tableau aps
     * @param [out] ddi - tableau des successeurs
     */
    void det_ddi(std::vector<int> fs, std::vector<int> aps, std::vector<int> &ddi) const ;

    /**
     * Permet d'afficher la matrice d'adjacence
     */
    void afficher();
};

#endif // GRAPHE_H
