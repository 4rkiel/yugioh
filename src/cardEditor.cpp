#include "../inc/cardEditor.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>

CardEditor::CardEditor(Parser* parser){

    allCards = parser->all_cards;
    parse = parser;
    
    createFormGroupBox();

    bigEditor = new QTextEdit;
    bigEditor->setPlaceholderText(tr("Description / Effet de la carte..."));

    mainLayout = new QGridLayout;
    mainLayout -> setMargin(0);
    mainLayout -> setSpacing(0);
    mainLayout -> setContentsMargins(0,0,0,0);

        mainLayout->addWidget(formGroupBox, 0, 0);
        mainLayout->addWidget(bigEditor, 1, 0);


    setLayout(mainLayout);
}


CardEditor::~CardEditor (){
    // TODO
    delete layout;
    delete imageUrl;
    delete nom;
    delete effectBox;
    delete attribut;
    delete typeSecondaire;
    delete typePrimaire;
    delete genreCarte;
    delete niveau;
    delete spinDefense;
    delete spinAttaque;
	
}



void CardEditor::createFormGroupBox (){

    formGroupBox = new QGroupBox();

    int i = 0;
    srand(time(NULL));

    spinAttaque = new Spin;
    spinDefense = new Spin;
    niveau = new Spin;
    genreCarte = new Combo;
    genreCarte -> setLayoutDirection(Qt::LeftToRight);
    typePrimaire = new Combo;
    typeSecondaire = new Combo;
    attribut = new Combo;
    attribut -> setLayoutDirection(Qt::LeftToRight);
    effectBox = new Combo;
    nom = new QLineEdit;
    image = new QPushButton;
    image->setDefault(true);
    imageUrl = new QLineEdit;

    ShadowButt *searchImg = new ShadowButt("\uf07c", "");
    searchImg -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    ShadowButt *genRdmName = new ShadowButt("\uf074", "");
    genRdmName -> setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QStringList imgList = QDir(imgRep).entryList();

    QStringList typePrimaireList;
    typePrimaireList << tr("Aqua") << tr("Bete") << tr("Bete Ailee") << tr("Bete-Divine") << tr("Bete-Guerrier") << tr("Demon") << tr("Dinosaure") <<tr("Dragon")  << tr("Elfe")
             << tr("Guerrier") << tr("Insecte") << tr("Machine") << tr("Magicien") << tr("Plante") << tr("Poisson") << tr("Pyro") << tr("Rocher") << tr("Reptile")
             << tr("Serpent de Mer") << tr("Tonnerre") << tr("Wyrm") <<tr("Zombie");

    QStringList typeSecondaireList;
    typeSecondaireList << tr("Effet") << tr("Normal") << tr("Fusion") << tr("Toon") << tr("Rituel");

    QStringList effectList = {tr("Piocher"), tr("Detruire Monstre"), tr("Detruire Magie/piege"), tr("Detruire"), tr("TOUT DETRUIRE !"), tr("gagner 1000 life point"), tr("+1000 attaque")};

    QCompleter *completerImg = new QCompleter(imgList, this);
    completerImg->setCaseSensitivity(Qt::CaseInsensitive);

    image->setFlat(true);
    image->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    imageUrl->setCompleter(completerImg);
    QObject::connect(imageUrl, SIGNAL(returnPressed()), this, SLOT(updateImg()));


    nameRandom();
    QObject::connect(genRdmName, SIGNAL(clicked()), this, SLOT(nameRandom()));

    ID = new Spin;
    ID->setSingleStep(1);
    ID->setAccelerated(true);
    ID->setMaximum(100000000);

    ID->setValue(rand()%100000000);

    bool sortir = true;

    do
    {
        sortir = true;
        for(Carte* carteCourante : *allCards)
        {
            if(carteCourante->id == ID->value())
            {
                sortir = false;
                ID->setValue(rand()%100000000);
                break;
            }
        }
    }while(!sortir);

    nrSet = new Combo;
    vector<QString> extension;
    extension.push_back(tr("Legende du Dragon Blanc aux yeux bleus"));
    extension.push_back(tr("Metal Raider"));

    for(unsigned i=0; i<extension.size(); i++)
    {
        nrSet->addItem(extension.at(i), i);
    }
    nrSet->addItem(tr("Custom"), 666);
    nrSet->setCurrentIndex(0);

    genreCarte->addItem(tr("Monstre"), 0);
    genreCarte->addItem(tr("Magie"), 1);
    genreCarte->addItem(tr("Piege"), 2);

    genreCarte->setItemIcon(0, QIcon(imgRep + "Level"));
    genreCarte->setItemIcon(1, QIcon(imgRep + "SPELL"));
    genreCarte->setItemIcon(2, QIcon(imgRep + "TRAP"));

    genreCarte->setItemData(1, QBrush(Qt::darkCyan), Qt::TextColorRole);
    genreCarte->setItemData(2, QBrush(Qt::magenta), Qt::TextColorRole);

    for(int i=0; i<typePrimaireList.size(); i++)
    {
        typePrimaire->addItem(typePrimaireList.at(i), i);
    }

    for(int i=0; i<typeSecondaireList.size(); i++)
    {
        typeSecondaire->addItem(typeSecondaireList.at(i), i);
    }

    for(int i=0; i<effectList.size(); i++)
    {
        effectBox->addItem(effectList.at(i), i);
    }

    QObject::connect(genreCarte, SIGNAL(currentIndexChanged(int)), this,SLOT(slotAttribut()));
    slotAttribut();

    QObject::connect(typeSecondaire, SIGNAL(currentIndexChanged(int)), this,SLOT(slotNormal()));
    slotAttribut();

    genreCarte->setCurrentIndex(rand()%3);

    image->setStyleSheet("border-image: url("+imgRep + "DEFAULT"+"); margin: 2px");

    QObject::connect(image, SIGNAL(clicked()), this,SLOT(selectImg()));
    QObject::connect(searchImg, SIGNAL(clicked()), this,SLOT(selectImg()));


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

    layout = new QGridLayout;

    // ... placement ...................................................

    layout->addWidget(searchImg, 7, 11, 1, 1);
    layout->addWidget(genRdmName, 0, 23, 1, 1);
    layout->addWidget(new QLabel(tr("Nom:")), i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(nom, i, 2, 1, 21);
    layout->addWidget(new QLabel(tr("Set:")), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(nrSet, i, 2, 1, 22);
    layout->addWidget(new QLabel(tr("genre:")), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(genreCarte, i, 2, 1, 7);
    layout->addWidget(typePrimaire, i, 9, 1, 7);
    layout->addWidget(typeSecondaire, i, 16, 1, 8);
    layout->addWidget(new QLabel(tr("attribut:")), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(attribut, i, 2, 1, 10);
    layout->addWidget(image, i, 12, 6, 12);
    layout->addWidget(new QLabel(tr("Niveau:")), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(niveau, i, 2, 1, 10);

    layout->addWidget(new QLabel(tr("Attaque:")), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(spinAttaque, i, 2, 1, 10);
    layout->addWidget(new QLabel(tr("Defense:")), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(spinDefense, i, 2, 1, 10);
    layout->addWidget(new QLabel(tr("Image URL:")), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(imageUrl, i, 2, 1, 9);
    layout->addWidget(new QLabel(tr("Effet:")), ++i, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(effectBox, i, 2, 1, 10);

    formGroupBox->setLayout(layout);
}

void CardEditor::sauvegarder (){

    string fileName = absoluteUrlImage.toStdString();
    string ext (fileName.substr(fileName.find_last_of(".") + 1));

    QString file = QCoreApplication::applicationDirPath()+"/sets/"+QString::number(nrSet->currentIndex())+".set";

    QString imgURL = QCoreApplication::applicationDirPath()+"/img/cards/"+QString::number(nrSet->currentIndex())+"/"+QString::number(ID->value());

    QFile *myfile = new QFile(file);

    QDir init;
    init.mkpath(QCoreApplication::applicationDirPath()+"/img/cards/"+QString::number(nrSet->currentIndex()));

    if(!myfile->open(QFile::WriteOnly | QFile::Text | QFile::Append))
    {// chemin  corrompue
        QMessageBox *msgError = new QMessageBox();
        msgError->setText(tr("Impossible de sauvegarder"));
        msgError->setStandardButtons(QMessageBox::Ok);
        connect(msgError, SIGNAL(accepted()), this, SLOT(reject()));
    }
    QFile::copy(absoluteUrlImage, imgURL);
    QTextStream in(myfile);

    QString eff = bigEditor->toPlainText();
    if(bigEditor->toPlainText().toStdString() == "")
    {
        eff = "YOLO";
    }

    QString text = QString("##YGO\n") + QString::number(ID->value()) + "\n"+QString::number(genreCarte->currentIndex())
            +"\n"+QString::number(typeSecondaire->currentIndex())+"\n"+nom->text()+"\n"+QString::number(attribut->currentIndex())+"\n"+
            QString::number(niveau->value())+"\n"+QString::number(typePrimaire->currentIndex())+"\n"+eff+"\n{{"+QString::number(effectBox->currentIndex())+"\n"+
            QString::number(spinAttaque->value())+"\n"+QString::number(spinDefense->value())+"\n";

    in << text;

    myfile->close();

    parse->all_cards->push_back(new Carte(ID->value(),spinAttaque->value(),
              spinDefense->value(),true,nom->text(),
              absoluteUrlImage,RECTO,genreCarte->currentIndex(),
              (Type)typePrimaire->currentIndex(),typeSecondaire->currentIndex(),
              (Attribut)attribut->currentIndex(),bigEditor->toPlainText(),
              niveau->value(),
              effectBox->currentIndex(),nrSet->currentIndex(),-1,-1));

    ID->setValue(rand()%100000000);

    bool sortir = true;

    do
    {
        sortir = true;
        for(Carte* carteCourante : *allCards)
        {
            if(carteCourante->id == ID->value())
            {
                sortir = false;
                ID->setValue(rand()%100000000);
                break;
            }
        }
    }while(!sortir);


    QMessageBox::information(this, tr("Sauvegarde"),
                             tr("La carte ")+nom->text()+tr(" a bien été sauvegardé."),
                                 QMessageBox::Ok);

    nameRandom();
}


void CardEditor::nameRandom(){

    vector<QString> one;
    one = {tr("Dragon"), tr("Magicien"), "WizTiger", tr("Guerrier"), tr("Tigre"), tr("Vampire"), tr("Archer"), tr("Serpent"), tr("Soldat"), tr("Singe Mutant")};

    vector<QString> two;
    two ={tr("noir"), tr("rouge"), tr("blanc"), tr("eradicateur"), tr("invincible"), tr("destructeur"), tr("mangeur d'âmes"), tr("scrumMaster"), tr("malefique")};

    vector<QString> tree;
    tree = {tr("du chaos"), tr("des tenebres"), tr("de la lumiere"), tr("invisible"), tr("des landes"), tr("myr"), tr("gobelin"), tr("du ciel"), tr("millenaire"), tr("jeune"), tr("debutant"),                             tr("innofensif")
           , tr("radieu"), tr("grognon"), tr("Json"), tr("DEADJOE"), tr("imperial")};

    nom->setText(one.at(rand()%one.size()) + " " + two.at(rand()%two.size()) + " " + tree.at(rand()%tree.size()));
}


void CardEditor::selectImg(){

    QString fileName = QFileDialog::getOpenFileName(this, tr("Selectionner une image"), imgRep,
                                                    "Images (*.png *.xpm *.jpg)");

    if(!fileName.isNull())
    {
        image->setStyleSheet("border-image: url(" + fileName + "); margin: 2px");
        imageUrl->setText(fileName.section('/', -1));
        absoluteUrlImage = fileName;
    }
}


void CardEditor::updateImg (){
    
    vector<string> extension = {"jpg", "xpm", "png"};
    string fileName = imgRep.toStdString() + imageUrl->text().toStdString();

    if(std::find(extension.begin(), extension.end(), (fileName.substr(fileName.find_last_of(".") + 1))) == extension.end())
    {// extension incorrecte
        imageUrl->setText(imageUrl->text() + "\t extension incorrect");

    }

    else if(!QFileInfo(imgRep + imageUrl->text()).exists())
    {// fichier incorrecte
        imageUrl->setText(imageUrl->text() + tr("\t n'existe pas"));
    }
    else
    {
        image->setStyleSheet("border-image: url(" + imgRep + imageUrl->text() + "); margin: 2px");
        absoluteUrlImage = imgRep + imageUrl->text();
    }
}


void CardEditor::slotAttribut(){

    attribut->clear();
    switch(genreCarte->currentIndex()){

        case MONSTRE:
            attribut->addItem(tr("Lumière"), 0);
            attribut->addItem(tr("Tenebre"), 1);
            attribut->addItem(tr("Terre"), 2);
            attribut->addItem(tr("Eau"), 3);
            attribut->addItem(tr("Feu"), 4);
            attribut->addItem(tr("Vent"), 5);
            attribut->addItem(tr("Divin"), 6);

            attribut->setItemIcon(0, QIcon(imgRep + "LUMIERE"));
            attribut->setItemIcon(1, QIcon(imgRep + "TENEBRE"));
            attribut->setItemIcon(2, QIcon(imgRep + "TERRE"));
            attribut->setItemIcon(3, QIcon(imgRep + "EAU"));
            attribut->setItemIcon(4, QIcon(imgRep + "FEU"));
            attribut->setItemIcon(5, QIcon(imgRep + "VENT"));
            attribut->setItemIcon(6, QIcon(imgRep + "DIVIN"));

            attribut->setCurrentIndex(rand()%7);

            spinAttaque->setVisible(true);
            spinDefense->setVisible(true);
            typePrimaire->setVisible(true);
            typeSecondaire->setVisible(true);
            niveau->setVisible(true);
        break;

        case MAGIE:
            attribut->addItem(tr("Normal"), 0);
            attribut->addItem(tr("Continue"), 1);
            attribut->addItem(tr("Equipement"), 2);
            attribut->addItem(tr("Jeu-Rapide"), 3);
            attribut->addItem(tr("Rituelle"), 4);
            attribut->addItem(tr("Terrain"), 5);

            attribut->setItemIcon(0, QIcon(imgRep + "Normal-N"));
            attribut->setItemIcon(1, QIcon(imgRep + "Continuous"));
            attribut->setItemIcon(2, QIcon(imgRep + "Equip"));
            attribut->setItemIcon(3, QIcon(imgRep + "Quick-Play"));
            attribut->setItemIcon(4, QIcon(imgRep + "Ritual"));
            attribut->setItemIcon(5, QIcon(imgRep + "Field"));

            attribut->setCurrentIndex(rand()%6);

            spinAttaque->setVisible(false);
            spinDefense->setVisible(false);
            typePrimaire->setVisible(false);
            typeSecondaire->setVisible(false);;
            niveau->setVisible(false);
        break;

        case PIEGE:
            attribut->addItem(tr("Normal"), 0);
            attribut->addItem(tr("Continue"), 1);
            attribut->addItem(tr("Contre"), 2);

            attribut->setItemIcon(0, QIcon(imgRep + "Normal-N"));
            attribut->setItemIcon(1, QIcon(imgRep + "Continuous"));
            attribut->setItemIcon(2, QIcon(imgRep + "Counter"));

            attribut->setCurrentIndex(rand()%3);

            spinAttaque->setVisible(false);
            spinDefense->setVisible(false);
            typePrimaire->setVisible(false);
            typeSecondaire->setVisible(false);
            niveau->setVisible(false);
    }
}


void CardEditor::slotNormal(){

    if (typeSecondaire->currentIndex() == 1){ // si monstre normal
    
        effectBox->setVisible(false);
    
    } else {
        
        effectBox->setVisible(true);
    }
}
