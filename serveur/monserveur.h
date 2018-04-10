#ifndef MONSERVEUR_H
#define MONSERVEUR_H
#include <QApplication>
#include <QFrame>

#include <QGridLayout>
#include <QVBoxLayout>

#include <QGraphicsDropShadowEffect>

#include <QPushButton>
#include <QString>
#include <QShortcut>
#include <sstream>
#include <QUdpSocket>
#include <iostream>

#include <QObject>

class MonServeur : public QObject
{
    Q_OBJECT
public:
    explicit MonServeur(QObject *parent = 0);

private:
    QUdpSocket* socket;

signals:

public slots:
    void readyRead();
};

#endif // MONSERVEUR_H
