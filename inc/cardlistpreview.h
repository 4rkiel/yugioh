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
#include <QDebug>
#include <algorithm>
#include <QMargins>
#include <QShortcut>
#include <QScrollArea>
#include "carte.h"
#include "parser.h"
#include "cardpreview.h"

class CardListPreview : public QWidget
{
    Q_OBJECT

public:
    CardListPreview(std::vector<Carte *> cardList);

    QVBoxLayout *mainLayout;

    std::vector<CardPreview *> *cardPreviewList;

};

#endif // CARDLISTPREVIEW_H
