#ifndef INTERFACE_H
#define INTERFACE_H

#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QPushButton>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVector>

#include "graphe.h"

class interface : public QWidget
{

public:

    /**
     * @brief interface
     * Constructeur d'une interface. Cela cree une fenetre de dimension 1200*800.
     * L'interface prend en parametres un graphe (pour l'afficher) et une taille (utile pour initialiser les donnees)
     * @param[in] g - graphe a afficher
     * @param[in] taille - nombre de sommets du graphe : utile pour initialiser les vecteurs
     */
    interface(Graphe *g, int taille);

    /**
     * @brief interface
     * Constructeur d'une interface. Cela cree une fenetre de dimension 1200*800.
     * L'interface prend en parametres un graphe (pour l'afficher) et une taille (utile pour initialiser les donnees)
     * @param[in] g - graphe a afficher
     * @param[in] taille - nombre de sommets du graphe : utile pour initialiser les vecteurs
     * @param[in] labels - noms des labels au-dessus de chaque sommet du graphe g
     */
    interface(Graphe *g, int taille, std::vector<std::string> labels);

    /**
     * @brief process
     * Methode permettant de lancer l'affichage des differentes parties du graphe : sommets, aretes, labels au-dessus des sommets
     * Cette methode appelle : determinationDesPositions(), affichageLabels() et show()
     */
    void process();



private:

    /**
     * @brief paintEvent
     * Redefinition de paintEvent permettant d'afficher le graphe (sommets + aretes)
     * @param event
     */
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    /**
     * @brief affichageLabels
     * Methode permettant d'afficher des labels au-dessus de chaque sommet du graphe
     */
    void affichageLabels();

    /**
     * @brief determinationDesPositions
     * Methode permettant de determiner les positions des differents sommets selon le nombre de somemts
     */
    void determinationDesPositions();

    // Passage de degres en radians
    static const double deg2rad;

    // Position du "pinceau"
    QPoint d_pos;

    // Rotation du pinceau : simplifie le calcul de position
    int d_heading;

    // Graphe a afficher
    Graphe *d_g;

    // Positions des sommets du graphe
    QVector<QPoint*> d_sommets;

    // Labels au-dessus des sommets (noms de villes par exemple)
    std::vector<std::string> d_labels;
};

#endif // INTERFACE_H
