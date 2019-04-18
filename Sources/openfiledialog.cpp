#include "../Headers/openfiledialog.h"

OpenFileDialog::OpenFileDialog() : QWidget (), d_fileName{}
{
    setFixedSize(400, 300);

    d_openFileButton = new QPushButton("Choisir un graphe à charger", this);
    d_openFileButton->move(150,100);

    d_okButton = new QPushButton("Valider", this);
    d_okButton->move(150, 200);

    d_fileLabel = new QLabel{this};
    d_fileLabel->move(50, 150);
    d_fileLabel->setFixedWidth(300);
    d_fileLabel->show();

    QObject::connect(d_openFileButton, SIGNAL(clicked()), this, SLOT(openFile()));
    QObject::connect(d_okButton, SIGNAL(clicked()), this, SLOT(valider()));
}


void OpenFileDialog::openFile()
{
    QString filename =  QFileDialog::getOpenFileName(
          this,
          "Open Document",
          QDir::currentPath(),
          "All files (*.*) ;; Document files (*.doc *.rtf);; PNG files (*.png)");

    if( !filename.isNull() )
    {
      qDebug() << "selected file path : " << filename.toUtf8();

    }

    d_fileName = filename;
    d_fileLabel->setText(d_fileName);
}

void OpenFileDialog::valider()
{
//    Graphe *g;
//    interface in{g, g->matriceAdj()[0][0]};
//    in.process();
    close();
}

std::string OpenFileDialog::getFileName() const
{
    return d_fileName.toStdString();
}
