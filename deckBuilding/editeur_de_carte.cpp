#include "editeur_de_carte.h"

#define name "editeur de carte V1"

editeur_de_carte::editeur_de_carte()
{
    createMenu();
    createFormGroupBox();

    bigEditor = new QTextEdit;
    bigEditor->setPlainText(QString::fromUtf8("Description / Effet de la carte..."));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(sauvegarder()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(bigEditor);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    setWindowTitle(tr("Basic Layouts"));
}

void editeur_de_carte::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(sauvegarder()));
}

void editeur_de_carte::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Form layout"));

    int i = 0;

    nom = new QLineEdit;
    nom->setText("Magicien Blanc aux Yeux Rouge du Lustre Noir");


    spinAttaque = new QSpinBox;
    spinAttaque -> setSingleStep(500);
    spinAttaque -> setAccelerated(true);
    spinAttaque -> setMaximum(5000);
    spinAttaque -> setMinimum(0);

    spinDefense = new QSpinBox;
    spinDefense -> setSingleStep(500);
    spinDefense -> setAccelerated(true);
    spinDefense -> setMaximum(5000);
    spinDefense -> setMinimum(0);

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(new QLabel("Nom:"), i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(nom, i, 2, 1, 22);

    layout->addWidget(new QLabel("Attaque:"), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(spinAttaque, i, 2, 1, 10);
    layout->addWidget(new QLabel("Defense:"), i, 12, 1, 2, Qt::AlignCenter);
    layout->addWidget(spinDefense, i, 14, 1, 10);

    formGroupBox->setLayout(layout);
}

void editeur_de_carte::sauvegarder()
{
    using namespace std;
    QString yolo = "guilg";
    QString file = QFileDialog::getSaveFileName();
    qDebug() << (file);


    QFile *myfile = new QFile(file);
    myfile->open(QFile::WriteOnly | QFile::Text);

    QTextStream in(myfile);
    in << yolo << endl;
    in << spinAttaque->value() << endl;


    myfile->close();
}

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    editeur_de_carte w;
    w.resize(500, 700);
    w.setWindowTitle(name);

    w.show();


    return app.exec();
}
