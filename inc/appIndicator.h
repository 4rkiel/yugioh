#ifndef APPINDICATOR
#define APPINDICATOR

#include <QGraphicsDropShadowEffect>
#include <QColor>

#include <QLabel>


class AppIndicator : public QLabel {

    Q_OBJECT

    public: 
    AppIndicator();
    ~AppIndicator();

    private:
    QGraphicsDropShadowEffect * effect;

};


#endif
