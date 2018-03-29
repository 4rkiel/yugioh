#ifndef FLATEXPBUTT
#define FLATEXPBUTT

#include <QPushButton>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QLabel>


class FlatExpButt : public QPushButton {

    Q_OBJECT

    public: 
    FlatExpButt(QString icoStr, QString txtStr);
    ~FlatExpButt();

    private:
	QVBoxLayout * vlay;
	QWidget * wid;
	QHBoxLayout * layout;
    QLabel * ico;
    QLabel * txt;
};


#endif
