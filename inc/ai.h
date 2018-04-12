#ifndef _AI_H
#define _AI_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

#define EIGEN_STACK_ALLOCATION_LIMIT 1000000
#include "../IA/lib_eigen/Eigen/Core"
#include "../inc/noyau.h"

#include <QString>
#include <QWidget>
#include <QEvent>

#define NB_INPUT 413
#define NB_HIDDEN 200
#define NB_OUTPUT 10


using namespace Eigen;
using namespace std;

class Ai : public QWidget
{

    Q_OBJECT

    private:

        //matrix of weights
        Matrix<float,413,200> input_weight;
        vector<Matrix<float,200,200>> hidden_weights;
        Matrix<float,200,10> output_weight;
        
        //matrix of deltas, which are the difference between the current weight,
        //and the previous weight, at each iteration
        Matrix<float,413,200> input_delta;
        vector<Matrix<float,200,200>> hidden_deltas;
        Matrix<float,200,10> output_delta;
        
        //row-matrix of current neurons values
        Matrix<float,1,200> input_layer_values;
        vector<Matrix<float,1,200>> hidden_layers_values;
        Matrix<float,1,10> output_layer_values;
        
        //matrix of next possible neurons values, according to the chosen action
        Matrix<float,1,200> test_input_layer_values;
        vector<Matrix<float,1,200>> test_hidden_layers_values;
        Matrix<float,1,10> test_output_layer_values;
        
        //the number of neurons layer
        int nb_hidden_layer;
        
        //mode: 1 = fixed_ai, 2 = learning_ai
        int mode;
        
        //noyau
        Noyau * noyau;


    public:
        
        //public functions
        
        //constructor, noyau de jeu, mode d'ia: basique=1 ou évolutive=2
        Ai(Noyau * noyau, int mode);
        
        //destructor
        ~Ai();
        
    public:
        
        //play without learn
        int play();
        
        //play and learn
        int play_learn();


    private:
        
        //internal functions
        
        void save_ai();
        void initialise_random_ai();
        void load_ai();
        void forward_propagation(Matrix<float,1,413> game_state);
        void test_forward_propagation(Matrix<float,1,413> game_state);
        int choose_action(Matrix<float,1,10> actions);
        void backward_propagation(float q_targets[10]);
        Matrix<float,1,413> play_simulation(Matrix<float,1,413> game_state, int action);
        int test_win(Matrix<float,1,413> state);
        float max_output_test();
        Matrix<float,1,413> read_noyau();


    signals:
        
        //attanquant : position_carte
        //adversaire : position_carte ou -1 si attaque directe vers le joueur
        void attaquer(int attaquant ,int adversaire);
        
        //main : position carte a poser
        //terrain : destination
        //def : true si défense, false si attaque
        //vis : true si recto, false si verso
        void poser(int main, int terrain, bool def ,bool vis);
        
        //passe de "atk à def" ou de "def à atk"
        //terrain : position de la carte a switcher
        void switch_position(int terrain);
        
        //detruit la carte à la position terrain
        void detruire(int terrain);

};

float randomFloat(float a, float b);

#endif
