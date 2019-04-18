#ifndef OPENFILEDIALOG_H
#define OPENFILEDIALOG_H

#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QPushButton>
#include <QWidget>
#include <QLabel>

//#include "interface.h"
//#include "grapheoriente.h"
//#include "graphenonoriente.h"


class OpenFileDialog : public QWidget
{

Q_OBJECT

public:
    OpenFileDialog();
    std::string getFileName() const;

public slots:
    void openFile();
    void valider();

private:
    QPushButton *d_openFileButton;
    QPushButton *d_okButton;
    QLabel *d_fileLabel;
    QString d_fileName;
};

#endif // OPENFILEDIALOG_H
