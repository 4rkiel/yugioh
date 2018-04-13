#ifndef _AI_TRAINER_H
#define _AI_TRAINER_H

#include <iostream>
#include <QMainWindow>

#include "../inc/noyau.h"
#include "../inc/ai.h"
#include "../inc/parser.h"
#include "../inc/reseau.h"


class AiTrainer : public QMainWindow
{
    Q_OBJECT

    public:
        void train_ai();
        
        Ai * ai;
        Noyau * noyau;
        Reseau * reseau;
        Carte * carte;
        Parser * parser;

};

#endif
