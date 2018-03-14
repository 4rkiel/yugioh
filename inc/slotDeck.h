#ifndef SLOTDECK
#define SLOTDECK

#include <QFrame>

#include <QString>

class SlotDeck : public QFrame {

    Q_OBJECT

    public: 
    SlotDeck();
    ~SlotDeck();
    void changeState(int sz);
    void draw();

    private:
    int size;
};


#endif
