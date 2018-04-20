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
#define NB_OUTPUT 135


using namespace Eigen;
using namespace std;

class Ai_battle : public QWidget
{

    Q_OBJECT

    private:

        //matrix of weights
        Matrix<float,434,200> input_weight;
        vector<Matrix<float,200,200>> hidden_weights;
        Matrix<float,200,135> output_weight;
        
        //matrix of deltas, which are the difference between the current weight,
        //and the previous weight, at each iteration
        Matrix<float,434,200> input_delta;
        vector<Matrix<float,200,200>> hidden_deltas;
        Matrix<float,200,135> output_delta;
        
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
        Matrix<float,1,135> output_layer_values;
        
        //matrix of next possible neurons values, according to the chosen action
        Matrix<float,1,200> test_input_layer_values;
        vector<Matrix<float,1,200>> test_hidden_layers_values;
        Matrix<float,1,135> test_output_layer_values;
        
        
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
        
    public:
        
        //play without learn
        void play();


    private:
        
        ////internal functions/////
        
        //save, init, load
        void save_ai();
        void initialise_random_ai();
        void load_ai();
        
        //propagation, chose action
        void forward_propagation(Matrix<float,1,434> game_state);
        void test_forward_propagation(Matrix<float,1,434> game_state);
        int choose_action(Matrix<float,1,135> actions);
        void backward_propagation(float q_targets[135]);
        Matrix<float,1,434> play_simulation(Matrix<float,1,434> game_state, int action);
        int test_win(Matrix<float,1,434> state);
        float max_output_test();
        Matrix<float,1,200> ReLU(Matrix<float,1,200> layer_values);
        Matrix<float,1,135> softmax(Matrix<float,1,135> layer_values);
        float randomFloat(float a, float b);
        
        //communication to noyau, correspondance id/terrain_x
        Matrix<float,1,434> read_noyau();
        int main_id_to_x(int main_id);
        int monstre_id_to_x(int monstre_id);
        int magie_piege_id_to_x(int magie_piege_id);

        //function that 
        int perform_action(int chosen_action);
        
        //tests before sending signal to noyau
        //returns EXIT_SUCCES if it send the signal to noyau
        //returns EXIT_FAILURE else
        int poser_atk(int main_id);
        int poser_def(int main_id);
        int switch_atk_def(int monstre_id);
        int sacrifier_poser(int monstre_id, int main_id);
        int sacrifier_sacrifier_poser(int monstre_1_id, int monstre_2_id, int main_id);
        int poser_magie_piege(int magie_id);
        int activer_magie_piege(int magie_id);



    signals:
        
        //attanquant : position_carte
        //adversaire : position_carte ou -1 si attaque directe vers le joueur
        void signal_attaquer(int attaquant ,int adversaire);
        
        //main : position carte a poser
        //terrain : destination
        //def : true si défense, false si attaque
        //vis : true si recto, false si verso
        void signal_poser(int main, int terrain, bool def ,bool vis);

        //sacrifi un monstre et le remplace avec un monstre de niveau 5-6
        void signal_sacrifier_poser(int sacrifice_x, int main_x, int terrain_x);

        //Sacrifie deux monstres et en met un en remplacement de niveau 7 et plus
        void signal_sacrifier_sacrifier_poser(int sacrifice_1_x, int sacrifice_2_x, int main_x, int terrain_x);
        
        //passe de "atk à def" ou de "def à atk"
        //terrain : position de la carte a switcher
        void signal_switch_position(int terrain);
        
        //detruit la carte à la position terrain
        //void signal_detruire(int terrain);

        //activer une marte magie ou piege
        void signal_activate(int terrain);

};

float randomFloat(float a, float b);

#endif
