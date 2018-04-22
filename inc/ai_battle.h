#ifndef _AI_BATTLE_H
#define _AI_BATTLE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

#define EIGEN_STACK_ALLOCATION_LIMIT 1000000
#include "../IA/lib_eigen/Eigen/Core"
#include "../inc/noyau.h"

#include <QString>
#include <QWidget>
#include <QEvent>

#define NB_INPUT 434
#define NB_HIDDEN 200
#define NB_OUTPUT_B 3


using namespace Eigen;
using namespace std;

class Ai_battle : public QWidget
{

    Q_OBJECT

    private:

        //matrix of weights
        Matrix<float,434,200> input_weight;
        vector<Matrix<float,200,200>> hidden_weights;
        Matrix<float,200,3> output_weight;
        
        //matrix of deltas, which are the difference between the current weight,
        //and the previous weight, at each iteration
        Matrix<float,434,200> input_delta;
        vector<Matrix<float,200,200>> hidden_deltas;
        Matrix<float,200,3> output_delta;
        
        //row-matrix of current neurons input
        Matrix<float,1,434> input_layer_input;
        vector<Matrix<float,1,200>> hidden_layers_input;
        Matrix<float,1,200> output_layer_input;

        //row-matrix of current neurons input
        Matrix<float,1,434> test_input_layer_input;
        vector<Matrix<float,1,200>> test_hidden_layers_input;
        Matrix<float,1,200> test_output_layer_input;
       
        //row-matrix of current neurons values
        Matrix<float,1,200> input_layer_values;
        vector<Matrix<float,1,200>> hidden_layers_values;
        Matrix<float,1,3> output_layer_values;
        
        //matrix of next possible neurons values, according to the chosen action
        Matrix<float,1,200> test_input_layer_values;
        vector<Matrix<float,1,200>> test_hidden_layers_values;
        Matrix<float,1,3> test_output_layer_values;
        
        
        //the number of neurons layer
        int nb_hidden_layer;
        
        //mode: 1 = fixed_ai, 2 = learning_ai
        int mode;
        
        //noyau
        Noyau * noyau;
        
        //jeu
        
        Carte * terrain_s_monstre[5];
        Carte * terrain_s_magie[5];
        
        Carte * terrain_a_monstre[5];
        Carte * terrain_a_magie[5];
        
        Carte * main[7];
        
        //coté du terrain 1 ou 2;
        int joueur;


    public:
        
        //public functions
        
        //constructor, noyau de jeu, mode d'ia: basique=1 ou évolutive=2
        //joueur : couté de terrain 1 ou 2:
        //1 étant de 0 à 74
        //et 2 étant de 75 à 149
        Ai_battle(Noyau * noyau, int mode, int joueur);
        
        //destructor
        ~Ai_battle();
        

    private:
        
        ////internal functions/////
        
        //save, init, load
        void save_ai();
        void initialise_random_ai();
        void load_ai();
        
        //propagation, chose action
        void forward_propagation(Matrix<float,1,434> game_state);
        void test_forward_propagation(Matrix<float,1,434> game_state);
        int choose_action(Matrix<float,1,3> actions);
        void backward_propagation(float q_targets[3]);
        Matrix<float,1,434> play_simulation(Matrix<float,1,434> game_state, int action);
        int test_win(Matrix<float,1,434> state);
        float max_output_test();
        Matrix<float,1,200> ReLU(Matrix<float,1,200> layer_values);
        Matrix<float,1,3> softmax(Matrix<float,1,3> layer_values);
        float randomFloat(float a, float b);
        
        //communication to noyau, correspondance id/terrain_x
        Matrix<float,1,434> read_noyau();
        int main_id_to_x(int main_id);
        int monstre_id_s_to_x(int monstre_id);
        int monstre_id_a_to_x(int monstre_id);
        int magie_piege_id_to_x(int magie_piege_id);
        
        //function that 
        int perform_action(int chosen_action);
        
        //tests before sending signal to noyau
        //returns EXIT_SUCCES if it send the signal to noyau
        //returns EXIT_FAILURE else
        int attaquer();
        int activer_magie_piege();

    public slots:
        void play(int iter=0);

    signals:
        
        //attanquant : position_carte
        //adversaire : position_carte ou -1 si attaque directe vers le joueur
        void signal_attaquer(int attaquant ,int adversaire);
        
        //activer une marte magie ou piege
        void signal_activate(int terrain);

};

float randomFloat(float a, float b);

#endif
