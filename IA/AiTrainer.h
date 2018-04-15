#ifndef _AI_TRAINER_H
#define _AI_TRAINER_H

#include <iostream>
#include <QMainWindow>

#include "../inc/noyau.h"
#include "../inc/ai_main.h"
#include "../inc/ai_battle.h"
#include "../inc/parser.h"
#include "../inc/reseau.h"


class AiTrainer : public QMainWindow
{
    Q_OBJECT

    public:
        void train_ai();
        
        Ai_main * ai_main_1;
        Ai_battle * ai_battle_1;

        Ai_main * ai_main_2;
        Ai_battle * ai_battle_2;

        Noyau * noyau;
        Reseau * reseau;
        Carte * carte;
        Parser * parser;

};

#endif
