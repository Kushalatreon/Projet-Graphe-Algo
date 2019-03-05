#ifndef GRAPHES_GRAPHE_H
#define GRAPHES_GRAPHE_H


#include <vector>
#include <istream>

using std::vector;

class Graphe
{

public:

    /**
     * Destructeur virtuel de Graphe (car methodes virtuelles)
     */
    virtual ~Graphe();

    /**
     * Constructeur de Graphe par defaut : cree un graphe avec une matrice d'adjacence vide
     */
    Graphe();

    /**
     * Constructeur de Graphe avec une matrice d'adjacence en parametre
     * @param [in] adj
     */
    Graphe(const vector<vector<int>> &adj);




    // ---------------------------- CHARGEMENT -----------------------------

    /**
     * Charge un graphe depuis un objet istream
     * Les fichiers permettant de sauvegarder un graphe sont au format txt. Il faut passer un istream en parametre, deja initialise sur un fichier
     * @param ist - objet istream permettant le remplissage du graphe (la matrice d'adjacence)
     */
    void charger(const std::istream &ist);



    // ----------------------------- Methodes d'acces et modification des attributs prives -----------------------------
    /**
     * Retourne la matrice d'adjacence
     * @return tableau 2D : matrice d'adjacence
     */
    vector<vector<int>> matriceAdj() const;

    /**
     * Retourne un tableau a une certaine ligne de la matrice d'adjacence
     * @param [in] i - ligne de la matrice
     * @return tableau 1D : ligne i de la matrice d'adjacence
     */
    vector<int> tableauMatrice(int i) const;

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
    void setMatrice(const vector<vector<int>> &adj);


    // ----------------------------- Methodes de classe (par rapport au graphe)  -----------------------------

    /**
     * Determine la tableau des premiers successeurs (aps)
     * Utilise l'attribut prive d_adj (on pourrait le passer en parametre)
     * @return tableau 1D : aps
     */
    vector<int> detAps() const;

    /**
     * Determine aps
     * Utilise fs
     * Fonction void car elle est utilisee quand un tableau est deja declare ailleurs dans le code. detAps remplit ce tableau
     * @param [out] aps : tableau aps a remplir
     */
    void detAps(vector<int> &aps) const;

    /**
     * Determine fs et aps
     * @param [out] fs : tableau fs a remplir
     * @param [out] aps : tableau aps a remplir
     */
    virtual void adj_2_fs_aps(vector<int> &fs, vector<int> &aps) const;

    /**
     * Determine la tableau des distance pour un sommet donne
     * Correspond a une ligne de la matrice des distances
     * Utilise fs, aps
     * @param [in] fs : tableau fs const (pas modifie dans la methode)
     * @param [in] aps : tableau aps const (pas modifie dans la methode)
     * @param [in] s : numero du sommet dont il faut determine la tableau des distances
     * @return tableau 1D : tableau des distance d'un sommet
     */
    vector<int> distance(const vector<int> &fs, const vector<int> &aps, int s) const;

    /**
     * Determine la matrice des distances
     * Utilise la matrice d'adj (d_adj)
     * @param [in] fs : tableau fs const
     * @param [in] aps : tableau aps const
     * @return tableau 2D : matrice des distances
     */
    vector<vector<int>> m_distances(const vector<int> &fs, const vector<int> &aps) const;

    /**
     * Determine le rang d'un sommet s
     * @param [in] fs : tableau fs
     * @param [in] aps : tableau aps
     * @param [in] s : numero du sommet
     * @return int : rang du sommet
     */
    int rang(const vector<int> &fs, const vector<int> &aps, int s) const;

    /**
     * Determine le rang de tous les sommets du graphe
     * @param [in] fs : tableau fs
     * @param [in] aps : tableau aps
     * @return tableau 1D : rang de tous les sommets
     */
    vector<int> m_rangs(const vector<int> &fs, const vector<int> &aps) const;

    /**
     * Determine le nombre de predecesseurs de chaque sommet
     * @param [in] fs
     * @param [in] aps
     * @return tableau 1D : ddi
     */
    virtual vector<int> det_ddi(const vector<int> &fs, const vector<int> &aps) const;

private:
    vector<vector<int>> d_adj;
};


#endif //GRAPHES_GRAPHE_H
