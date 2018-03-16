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
    srand(time(NULL));

    spinAttaque = new QSpinBox;
    spinDefense = new QSpinBox;
    niveau = new QSpinBox;
    genreCarte = new QComboBox;
    typePrimaire = new QComboBox;
    typeSecondaire = new QComboBox;
    attribut = new QComboBox;
    nom = new QLineEdit;
    image = new QPushButton;
    addComboBox = new QPushButton;
    deleteComboBox = new QPushButton;
    imageUrl = new QLineEdit;
    comboBoxList = new Qlist;

    QStringList imgList = QDir(imgRep).entryList();

    QStringList typePrimaireList;
    typePrimaireList << "Aqua" << "Bete" << "Bete Ailee" << "Bete-Divine" << "Bete-Guerrier" << "Demon" << "Dinosaure" <<"Dragon"  << "Elfe"
             << "Guerrier" << "Insecte" << "Machine" << "Magicien" << "Plante" << "Poisson" << "Pyro" << "Rocher" << "Reptile"
             << "Serpent de Mer" << "Tonnerre" << "Wyrm" <<"Zombie";

    QStringList typeSecondaireList;
    typeSecondaireList << "Effet" << "Normal" << "Fusion" << "Toon" << "Rituel";

    QCompleter *completerImg = new QCompleter(imgList, this);
    completerImg->setCaseSensitivity(Qt::CaseInsensitive);

    image->setFlat(true);
    image->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    imageUrl->setCompleter(completerImg);

    nom->setText("Magicien Blanc aux Yeux Rouge du Lustre Noir");

    ID = new QSpinBox;
    ID->setSingleStep(1);
    ID->setAccelerated(true);
    ID->setMaximum(100000);
    ID->setValue(rand()%100000);

    nrSet = new QComboBox;
    vector<QString> extension;
    extension.push_back("Legende du Dragon Blanc aux yeux bleus");
    extension.push_back("Metal Raider");

    for(unsigned i=0; i<extension.size(); i++)
    {
        nrSet->addItem(extension.at(i), i);
    }
    nrSet->addItem("Custom", 666);
    nrSet->setCurrentIndex(0);


    genreCarte->addItem("Monstre", 0);
    genreCarte->addItem("Magie", 1);
    genreCarte->addItem("Piege", 2);

    genreCarte->setItemIcon(0, QIcon(imgRep + "Level"));
    genreCarte->setItemIcon(1, QIcon(imgRep + "SPELL"));
    genreCarte->setItemIcon(2, QIcon(imgRep + "TRAP"));

    genreCarte->setItemData(1, QBrush(Qt::darkCyan), Qt::TextColorRole);
    genreCarte->setItemData(2, QBrush(Qt::magenta), Qt::TextColorRole);

    for(int i=0; i<typePrimaireList.size(); i++)
    {
        typePrimaire->addItem(typePrimaireList.at(i), i);
    }

//    typePrimaire->setEditable(true);
//    typePrimaire->setCompleter(completerTypePrimaire);

    for(int i=0; i<typeSecondaireList.size(); i++)
    {
        typeSecondaire->addItem(typeSecondaireList.at(i), i);
    }



    QObject::connect(genreCarte, SIGNAL(currentIndexChanged(int)), this,SLOT(slotAttribut()));
    slotAttribut();
    genreCarte->setCurrentIndex(rand()%3);

//    image->setPixmap( QPixmap(imgRep + "DEFAULT" ) );
//    image->show();

    QLabel *font = new QLabel;
    font->setStyleSheet("border: 2px solid black");
    image->setStyleSheet("border-image: url("+imgRep + "DEFAULT"+"); margin: 2px");

    QObject::connect(image, SIGNAL(clicked()), this,SLOT(selectImg()));


    spinAttaque -> setSingleStep(500);
    spinAttaque -> setAccelerated(true);
    spinAttaque -> setMaximum(5000);
    spinAttaque -> setMinimum(0);


    spinDefense -> setSingleStep(500);
    spinDefense -> setAccelerated(true);
    spinDefense -> setMaximum(5000);
    spinDefense -> setMinimum(0);

    niveau -> setSingleStep(1);
    niveau -> setAccelerated(true);
    niveau -> setMaximum(12);
    niveau -> setMinimum(1);

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(new QLabel("Nom:"), i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(nom, i, 2, 1, 22);
    layout->addWidget(new QLabel("ID:"), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(ID, i, 2, 1, 22);
    layout->addWidget(new QLabel("Set:"), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(nrSet, i, 2, 1, 22);
    layout->addWidget(new QLabel("genre:"), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(genreCarte, i, 2, 1, 7);
    layout->addWidget(typePrimaire, i, 9, 1, 7);
    layout->addWidget(typeSecondaire, i, 16, 1, 8);
    layout->addWidget(new QLabel("attribut:"), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(attribut, i, 2, 1, 10);
    layout->addWidget(font, i, 12, 5, 12);
    layout->addWidget(image, i, 12, 5, 12);
    layout->addWidget(new QLabel("Niveau:"), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(niveau, i, 2, 1, 10);

    layout->addWidget(new QLabel("Attaque:"), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(spinAttaque, i, 2, 1, 10);
    layout->addWidget(new QLabel("Defense:"), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(spinDefense, i, 2, 1, 10);
    layout->addWidget(new QLabel("Image URL:"), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(imageUrl, i, 2, 1, 10);

    layout->addWidget(addComboBox, ++i, 0, 1, 10);
    layout->addWidget(deleteComboBox, ++i, 0, 1, 10);

    formGroupBox->setLayout(layout);
}

void editeur_de_carte::sauvegarder()
{
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

void editeur_de_carte::selectImg()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Selectionner une image"), imgRep,
                                                    tr("Images (*.png *.xpm *.jpg)"));
    qDebug() << (fileName);

    if(!fileName.isNull())
        image->setStyleSheet("border-image: url(" + fileName + "); margin: 2px");
}

void editeur_de_carte::slotAttribut()
{
    attribut->clear();
    switch(genreCarte->currentIndex())
    {
        case MONSTRE:
            attribut->addItem(QString::fromUtf8("Lumière"), 0);
            attribut->addItem("Tenebre", 1);
            attribut->addItem("Terre", 2);
            attribut->addItem("Eau", 3);
            attribut->addItem("Feu", 4);
            attribut->addItem("Vent", 5);
            attribut->addItem("Divin", 6);

            attribut->setItemIcon(0, QIcon(imgRep + "LUMIERE"));
            attribut->setItemIcon(1, QIcon(imgRep + "TENEBRE"));
            attribut->setItemIcon(2, QIcon(imgRep + "TERRE"));
            attribut->setItemIcon(3, QIcon(imgRep + "EAU"));
            attribut->setItemIcon(4, QIcon(imgRep + "FEU"));
            attribut->setItemIcon(5, QIcon(imgRep + "VENT"));
            attribut->setItemIcon(6, QIcon(imgRep + "DIVIN"));

            attribut->setCurrentIndex(rand()%7);

            spinAttaque->setDisabled(false);
            spinDefense->setDisabled(false);
            typePrimaire->setDisabled(false);
            typeSecondaire->setDisabled(false);
            niveau->setDisabled(false);
        break;

        case MAGIE:
            attribut->addItem("Normal", 0);
            attribut->addItem("Continue", 1);
            attribut->addItem("Equipement", 2);
            attribut->addItem("Jeu-Rapide", 3);
            attribut->addItem("Rituelle", 4);
            attribut->addItem("Terrain", 5);

            attribut->setItemIcon(0, QIcon(imgRep + "Normal-N"));
            attribut->setItemIcon(1, QIcon(imgRep + "Continuous"));
            attribut->setItemIcon(2, QIcon(imgRep + "Equip"));
            attribut->setItemIcon(3, QIcon(imgRep + "Quick-Play"));
            attribut->setItemIcon(4, QIcon(imgRep + "Ritual"));
            attribut->setItemIcon(5, QIcon(imgRep + "Field"));

            attribut->setCurrentIndex(rand()%6);

            spinAttaque->setDisabled(true);
            spinDefense->setDisabled(true);
            typePrimaire->setDisabled(true);
            typeSecondaire->setDisabled(true);
            niveau->setDisabled(true);
        break;

        case PIEGE:
            attribut->addItem("Normal", 0);
            attribut->addItem("Continue", 1);
            attribut->addItem("Contre", 2);

            attribut->setItemIcon(0, QIcon(imgRep + "Normal-N"));
            attribut->setItemIcon(1, QIcon(imgRep + "Continuous"));
            attribut->setItemIcon(2, QIcon(imgRep + "Counter"));

            attribut->setCurrentIndex(rand()%3);

            spinAttaque->setDisabled(true);
            spinDefense->setDisabled(true);
            typePrimaire->setDisabled(true);
            typeSecondaire->setDisabled(true);
            niveau->setDisabled(true);
    }
}


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    editeur_de_carte w;
    w.resize(500, 700);
    w.setWindowTitle(name);

    w.show();


    return app.exec();
}
