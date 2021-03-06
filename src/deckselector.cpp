#include "../inc/deckselector.h"
#include "../inc/buildtab.h"

DeckSelector::DeckSelector(QObject* parent){

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setObjectName("DeckSelector");

    mainLayout = new QGridLayout;
    mainLayout -> setContentsMargins(0,0,0,0);
    mainLayout -> setSpacing(0);
    mainLayout -> setMargin(0);

    if(NBR_DECK > 0)
    {
        tabDeckButton.reserve(NBR_DECK);
        if(NBR_DECK > 1)
            tabSep.reserve(NBR_DECK-1);
    }

    int i = 0;
    int last = deckList.size();

    if(!deckList.empty())
    {
        foreach (QString str, deckList){

            std::vector<Carte*> * deckCourant = parserAllMighty.deck(deckRep + str);

            // deck button

            QString image = imgPreviewDeck(deckCourant);

            if(image.isNull())
                image = defaultImage;

            tabRadio.push_back(new QRadioButton);
            tabRadio[i] -> setObjectName("selectRad");
            tabRadio[i] -> setToolTip(tr("Utiliser ce deck en duel"));
            tabRadio[i] -> setFocusPolicy(Qt::NoFocus);

            tabDeckButton.push_back(new DeckPreview(str, image));
            tabDeckButton[i] -> setObjectName("selectButt");

            mainLayout->addWidget(tabDeckButton[i],i*2,0,1,1);
            mainLayout->addWidget(tabRadio[i],i*2,1,1,1);

            if (i != last-1){

                tabSep.push_back(new QFrame);
                tabSep[i]->setFixedHeight(1);
                tabSep[i]->setObjectName("selectSep");

                mainLayout->addWidget(tabSep[i], (i*2)+1,0,1,2);
            }

            connect(tabDeckButton[i], SIGNAL(isClick(QString)), this, SLOT(openDeck(QString)));
            connect(tabRadio[i], SIGNAL(clicked()), this, SLOT(setCourant()));

            i++;
        }
        QString nomDeck = getCurrentDeck().toString();
        unsigned int indice=0;
        for(; indice < tabDeckButton.size(); indice++)
        {
            if(tabDeckButton[indice]->nomDeck == nomDeck )
            {
                tabRadio[indice]->toggle();
                break;
            }
        }
        posOldCheck = indice;
    }


    shortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
    shortcut->setContext(Qt::WidgetWithChildrenShortcut);
    connect(shortcut, SIGNAL(activated()), this, SLOT(activeRadio()));

    BuildTab* par= static_cast<BuildTab*>(parent);
    QSpacerItem * spacerButt = new QSpacerItem(2,1,
            QSizePolicy::Preferred,QSizePolicy::Expanding);
    mainLayout -> addItem(spacerButt, last*2, 0);
    connect(par,SIGNAL(nousFocus()),this,SLOT(getsFocus()));
    connect(par,SIGNAL(focusDeck()),this,SLOT(abandonFocus()));

    setLayout(mainLayout);
}


DeckSelector::~DeckSelector(){
    
    int last = deckList.size() - 1;
    int i = last;

    foreach (QString str, deckList){
 
        if (i != last){
            delete tabSep[i];
        }

        delete tabRadio[i];
        delete tabDeckButton[i];

        i --;
    }
    delete shortcut;
    delete mainLayout;
}

QString DeckSelector::imgPreviewDeck(std::vector<Carte*> *deck){
    return deck->empty() ? nullptr : deck->at(0)->image;
}

QVariant DeckSelector::getCurrentDeck()
{
    QSettings settings;
    return settings.value("deckUtilise",  deckRep+"sans_Nom0.deck");
    // TODO ICI on peut mettre un deck par default
}

void DeckSelector::openDeck(QString nomDeck){

    emit popDeck(nomDeck);
}

/* Focus */
void DeckSelector::abandonFocus(){
    DeckPreview* temp2;
    int i=0;
    foreach (QString str, deckList){;
        temp2=tabDeckButton[i];
        temp2->setFocusPolicy(Qt::NoFocus);
        i++;
    }
}

void DeckSelector::getsFocus(){
    DeckPreview* temp2;
    int i=0;
    foreach (QString str, deckList){
        temp2=tabDeckButton[i];
        temp2->setFocusPolicy(Qt::StrongFocus);
        i++;
    }
}

void DeckSelector::setCourant()
{
    size_t pos;
    QRadioButton* senderObj = qobject_cast<QRadioButton*>(sender());
    std::vector<QRadioButton *>::iterator it = std::find(tabRadio.begin(),
                                         tabRadio.end(), senderObj);
    pos = it - tabRadio.begin();

    qDebug() << deckRep + tabDeckButton[pos]->nomDeck;

    if(parserAllMighty.deck(deckRep + tabDeckButton[pos]->nomDeck)->size() != 40)
    {
        QMessageBox::information(this, tr("Deck Invalide"),
                                 tr("Impossible d'utiliser ce deck:"
                                    " Il ne contient pas 40 cartes"),
                                     QMessageBox::Ok);


        tabRadio[posOldCheck]->toggle();
        return;
    }


    QSettings settings;
    settings.setValue("deckUtilise",  tabDeckButton[(int)pos]->nomDeck);
}

void DeckSelector::activeRadio(){
    QRadioButton* temp;
    DeckPreview* temp2;
    QSettings settings;
    int i=0;
    if(QString(qApp->focusObject()->metaObject()->className())=="DeckPreview"){
        foreach (QString str, deckList){
            temp=tabRadio[i];
            temp2=tabDeckButton[i];
            if(static_cast<DeckPreview*>(qApp->focusObject())==temp2){
                temp->toggle();
                settings.setValue("deckUtilise",  tabDeckButton[i]->nomDeck);
            }
            i++;
        }
    }
}
