#ifndef _AI_H
#define _AI_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "../IA/lib_eigen/Eigen/Core"
#include <vector>

#include <QString>
#include <QWidget>
#include <QEvent>

using namespace Eigen;
using namespace std;

class Ai : public QWidget
{

    Q_OBJECT

    public:

        //matrix of weights
        vector<Matrix<float,60,60>> hidden_weights;
        Matrix<float,60,10> output_weight;

        //matrix of deltas, which are the difference between the current weight,
        //and the previous weight, at each iteration
        vector<Matrix<float,60,60>> hidden_deltas;
        Matrix<float,60,10> output_delta;

        //row-matrix of current neurons values
        vector<Matrix<float,1,60>> hidden_layers_values;
        Matrix<float,1,10> output_layer_values;

        //matrix of next possible neurons values, according to the chosen action
        vector<Matrix<float,1,60>> test_hidden_layers_values;
        Matrix<float,1,10> test_output_layer_values;

        //the number of neurons layer
        int nb_hidden_layer;

        //mode: 1 = fixed_ai, 2 = learning_ai
        int mode;

    public:

        Ai(int mode);
        ~Ai();
        void save_ai();
        void initialise_random_ai();
        void load_ai();
        void forward_propagation(Matrix<float,1,60> game_state);
        void test_forward_propagation(Matrix<float,1,60> game_state);
        int choose_action(Matrix<float,1,10> actions);
        int play(Matrix<float,1,60> game_state);
        void backward_propagation(float q_targets[10]);
        Matrix<float,1,60> play_simulation(Matrix<float,1,60> game_state, int action);
        int test_win(Matrix<float,1,60> state);
        float max_output_test();
        int play_learn(Matrix<float,1,60> game_state);

    signals:
        void attaquer(int,int);
};

float randomFloat(float a, float b);

#endif
