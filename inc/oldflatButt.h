#ifndef FLATBUTT
#define FLATBUTT

#include <QPushButton>

#include <QHBoxLayout>
#include <QString>
#include <QLabel>


class FlatButt : public QPushButton {

    Q_OBJECT

    public: 
    FlatButt(QString icoStr, QString txtStr);
    ~FlatButt();

    private:
    QHBoxLayout * layout;
    QLabel * ico;
    QLabel * txt;
};


#endif
