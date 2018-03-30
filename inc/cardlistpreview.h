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

class CardListPreview : public QWidget
{
public:
    CardListPreview(std::vector<Carte *> Card);

    std::vector<Carte *> allCard;

    QVBoxLayout *mainLayout;

    std::vector<QHBoxLayout *> *cardPreviewList;

};

#endif // CARDLISTPREVIEW_H
