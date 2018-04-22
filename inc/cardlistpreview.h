#ifndef CARDLISTPREVIEW_H
#define CARDLISTPREVIEW_H

#include <vector>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QCompleter>
#include <QFileDialog>
#include <QCoreApplication>
#include <QStringList>
#include <algorithm>
#include <QMargins>
#include <QShortcut>
#include <QScrollArea>
#include "carte.h"
#include "cardpreview.h"
#include "parser.h"

class CardListPreview : public QWidget
{
    Q_OBJECT

public:

    void updateSearch(std::vector<Carte *> *cardList);

    CardListPreview(std::vector<Carte *> *cardList2);
    ~CardListPreview();

    QVBoxLayout *mainLayout;

    std::vector<CardPreview *> *cardPreviewList;

};

#endif // CARDLISTPREVIEW_H
