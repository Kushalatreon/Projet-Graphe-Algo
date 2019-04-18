#include <cmath>
#include "../Headers/interface.h"

const double interface::deg2rad = 3.14159265358979/180;

const int STEP = 150;

interface::interface(Graphe *g, int taille) : QWidget (), d_pos{600,100}, d_heading{0}, d_g{g}, d_sommets{taille,0}, d_labels{}
{
    setFixedSize(1200, 800);

    for(int i = 0; i < d_sommets.size(); i++)
    {
        d_sommets[i] = new QPoint();
    }
}

interface::interface(Graphe *g, int taille, std::vector<std::string> labels) : QWidget (), d_pos{600,100}, d_heading{0}, d_g{g}, d_sommets{taille,0}, d_labels{labels}
{
    setFixedSize(1200, 800);

    for(int i = 0; i < d_sommets.size(); i++)
    {
        d_sommets[i] = new QPoint();
    }
}


void interface::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    //painter.drawEllipse(QPoint(500.0, 500.0), 50, 50);
    painter.setBrush(Qt::red);

    int nbSommets = d_g->matriceAdj()[0][0];

    int angle = 360/nbSommets;

    // affichage des sommets
    for(int i = 0 ; i < nbSommets ; i++)
    {
        painter.drawEllipse(*d_sommets[i], 20, 20);
    }

    // affichage des arrêtes
    for(int i = 1 ; i <= nbSommets ; i++)
    {
        for(int j = 1 ; j <= nbSommets ; j++)
        {
            if(d_g->matriceAdj()[i][j] > 0)
            {
                painter.drawLine(d_sommets[i-1]->x(), d_sommets[i-1]->y(),
                                 d_sommets[j-1]->x(), d_sommets[j-1]->y());
            }
        }
    }

}

void interface::determinationDesPositions()
{
    int nbSommets = d_g->matriceAdj()[0][0];

    int angle = 360/nbSommets;

    for(int i = 0 ; i < nbSommets ; i++)
    {
        //QPoint* ptmp = new QPoint{d_pos.x(), d_pos.y()};
        d_sommets[i]->setX(d_pos.x());
        d_sommets[i]->setY(d_pos.y());

        double alpha = deg2rad*d_heading;

        QPoint pdest {static_cast<int>(d_pos.x() + STEP * std::cos(alpha)),
                      static_cast<int>(d_pos.y() + STEP * std::sin(alpha))};

        d_pos = pdest;

        d_heading += angle;
    }
    int p;
}

void interface::affichageLabels()
{
    // affichage des noms des sommets

    for(int i = 0 ; i < d_g->matriceAdj()[0][0] ; i++)
    {
        int x = d_sommets[i]->x();
        int y = d_sommets[i]->y();
        //QString text = QString::number(i+1);
        QString text = QString::fromStdString(d_labels[i]);
        QLabel* lab = new QLabel{this};
        //lab->setGeometry(d_sommets[i].x()-10, d_sommets[i].y()-10, d_sommets[i].x()+10, d_sommets[i].y()+10);
        lab->setFont(QFont{"Arial", 12, QFont::Bold});
        lab->move(x-30, y-30);
        lab->setText(text);
        lab->show();
    }
    int p;

}

void interface::process()
{
    determinationDesPositions();
    affichageLabels();
    show();
}
