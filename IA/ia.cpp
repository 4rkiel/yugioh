#include <iostream>
#include <stdlib.h>
#include <time.h>
//#include <Eigen/Core>
#include <lib_eigen/Eigen/Core>
#include <vector>
#include <tuple>


using namespace Eigen;
using namespace std;



//function to calculate a random float between two floats
float randomFloat(float a, float b)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}



//main function, which does nothing
int main()
{
    return 0;
}



//a neuron
class Neuron
{
    public:
        
        float gain;
        float wgain;
        
        Neuron()
        {
            gain = 1;
            wgain = 0;
        }
};



//the neural network
/*neural netwrok
 * 4 layers: 1 input layer, 2 hidden layers, 1 output layer
 * synaps are the weights between neurons layer
 */
class Network
{
    public:
        
        //matrix of weights
        vector<Matrix<float,Dynamic,Dynamic>> hidden_weights;
        Matrix<float,Dynamic,10> output_weight;
        
        //matrix of deltas, which are the difference between the current weight,
        //and the previous weight, at each iteration
        vector<Matrix<float,Dynamic,Dynamic>> hidden_deltas;
        Matrix<float,Dynamic,10> output_delta;
        
        //row-matrix of neurons (gain ang wgain)
        vector<Matrix<Neuron,1,Dynamic>> hidden_layers;
        Matrix<Neuron,1,10> output_layer;
        
        //row-matrix of current neurons values
        vector<Matrix<float,1,Dynamic>> hidden_layers_values;
        Matrix<float,1,10> output_layer_values;
        
        //matrix of next possible neurons values, according to the chosen action
        vector<Matrix<float,1,Dynamic>> test_hidden_layers_values;
        Matrix<float,1,10> test_output_layer_values;
        
        //the number of neurons layer
        int nb_hidden_layer;
        
        
        //constructor: neural network initialisation
        Network(int nb_hidden_layer)
        {
            int i,j,k;
            srand (time(NULL));
            this->nb_hidden_layer = nb_hidden_layer;
            
            //hidden layers
            ///////////////
            for(k=0;k<nb_hidden_layer;k++)
            {
                //initialise weights
                Matrix<float,60,60> new_weights_m;
                hidden_weights.push_back(new_weights_m);
                for(i=0;i<20;i++)
                {
                    for(j=0;j<60;j++)
                    {
                        new_weights_m(i,j) =
                            randomFloat(-1/sqrt(60),1/sqrt(60));
                    }
                }
                //initialise deltas
                Matrix<float,60,60> new_deltas_m;
                hidden_deltas.push_back(new_deltas_m);
                for(i=0;i<20;i++)
                {
                    for(j=0;j<60;j++)
                    {
                        new_deltas_m(i,j) = 0;
                    }
                }
                //initialise neurons
                Matrix<Neuron,1,60> new_neurons_m;
                hidden_layers.push_back(new_neurons_m);
                for(i=0;i<60;i++)
                {
                    Neuron new_neuron;
                    new_neurons_m(1,i) = new_neuron;
                }
                //initialise values
                Matrix<float,1,60> new_values_m;
                hidden_layers_values.push_back(new_values_m);
                for(i=0;i<60;i++)
                {
                    new_values_m(1,i) = 0;
                }
                //initialise test values
                Matrix<float,1,60> new_test_values_m;
                hidden_layers_values.push_back(new_test_values_m);
                for(i=0;i<60;i++)
                {
                    new_test_values_m(1,i) = 0;
                }
            }
            //////////////
            
            //output layer
            //////////////
            //initialise weights
            for(i=0;i<60;i++)
            {
                for(j=0;j<10;j++)
                {
                    output_weight(i,j) =
                            randomFloat(-1/sqrt(60),1/sqrt(60));
                }
            }
            //initialise deltas
            for(i=0;i<60;i++)
            {
                for(j=0;j<10;j++)
                {
                    output_delta(i,j) = 0;
                }
            }
            //initialise neurons
            for(i=0;i<10;i++)
            {
                Neuron new_neuron;
                output_layer(1,i) = new_neuron;
            }
            //initialise values
            for(i=0;i<10;i++)
            {
                output_layer_values(1,i) = 0;
            }
            //initialise test values
            for(i=0;i<10;i++)
            {
                test_output_layer_values(1,i) = 0;
            }
            //////////////
        }
        
        
        
        /*
         * compute the actions' q_values vector
         * takes in input the game state
         * and outputs the vector of the actions do to
         */
        void forward_propagation(Matrix<float,1,20> game_state)
        {
            hidden_layers_values.at(0) = game_state * hidden_weights.at(0);
            hidden_layers_values.at(1) = hidden_layers_values.at(0) * hidden_weights.at(1);
            output_layer_values = hidden_layers_values.at(1) * output_weight;
        }
        
        
        
        /*
         * compute test actions' q_values vector
         * takes in input the future possible state
         * and outputs the vector of the actions it will be able to do
         */
        void test_forward_propagation(Matrix<float,1,20> game_state)
        {
            test_hidden_layers_values.at(0) = game_state * hidden_weights.at(0);
            test_hidden_layers_values.at(1) = test_hidden_layers_values.at(0) * hidden_weights.at(1);
            test_output_layer_values = test_hidden_layers_values.at(1) * output_weight;
        }
        
        
        
        /*
         * Choose the action to do, according to the actions' q_value calculated.
         * More an action has a big q_value, more it has chance to be chosen
         */
        int choose_action(Matrix<float,1,10> actions)
        {
            srand (time(NULL));
            float choice = rand()%1;
            
            int action=0;
            while(choice>0)
            {
                if(action=10)
                {
                    action=rand()%10;
                    break;
                }
                choice -= actions(1,action);
                action++;
            }
            
            return action;
        }
        
        
        
        //play without learn
        int play(Matrix<float,1,20> game_state)
        {
            forward_propagation(game_state);
            int action = choose_action(output_layer_values);
            return action;
        }
        
        
        
        /*
         * compare the output of the neural network with the q_values of the
         * different next possible state, and update the weights of the neural
         * network
         */
        void backward_propagation(float q_targets[10])
        {
            int i,j,k;
            float local_cost=0;
            float global_cost=0;
            float delta, udelta;
            float output;
            float sum=0,local_sum=0;
            
            
            //output_layer
            //for each neuron in the output layer
            for(i=0;i<output_weight.rows();i++)
            {
                //calcul local and global cost of this neuron
                output=output_layer_values(1,i);
                local_cost=( q_targets[i] - output_layer_values(1,i) ) *
                    output_layer_values(1,i) * (1 - output_layer_values(1,i));
                global_cost += pow(q_targets[i] - output_layer_values(1,i),2);
                
                //update the weights comming into this neuron from the previous
                //layer
                //for each synaps comming into the neuron
                for(j=0;j<output_weight.cols();j++)
                {
                    //update the weight, according to the local cost and the
                    //update delta at the previous backpropagation
                    //update the delta value, etc
                    delta=output_delta(i,j);
                    udelta = local_cost * output_weight(i,j) + delta;
                    output_weight(i,j) += udelta;
                    output_delta(i,j) = udelta;
                    sum += output_weight(i,j) * local_cost;
                }
                output_layer(1,i).wgain = local_cost * output_layer(1,i).gain;
            }
            
            /*
             * do the same as for the output layer, but now multiplicated by
             * the  sum of the previous localcost time the previous weights,
             * and this for all the neurons in all the hidden layers
             * so the cost is backpropagated to update all the neurons of the
             * network
             */
            for(i=hidden_weights.size();i>0;i--)
            {
                for(j=0;j<hidden_weights.at(i).cols();j++)
                {
                    output=hidden_layers_values.at(i)(1,j);
                    local_cost = output * (1-output) * sum;
                    for(k=0;k<hidden_weights.at(i).cols();k++)
                    {
                        delta = hidden_deltas.at(i)(j,k);
                        udelta = local_cost * hidden_weights.at(i)(j,k) + delta;
                        hidden_weights.at(i)(j,k) += udelta;
                        hidden_deltas.at(i)(j,k) = udelta;
                        local_sum += hidden_weights.at(i)(j,k) * local_cost;
                    }
                    hidden_layers.at(i)(1,j).wgain = local_cost * hidden_layers.at(i)(1,j).gain;
                }
                sum = local_sum;
                local_sum=0;
            }
        }
        
        
        
        //give the next game state, if the action is played
        Matrix<float,1,20> play_simulation(Matrix<float,1,20> game_state, int action)
        {
            //TODO: connect to "Moteur"
        }
        
        
        
        /*
         * test if the game state is a winning state, a losing state
         * or a neutral state
         */
        int test_win(Matrix<float,1,20> state)
        {
            return state(1,1);
        }
        
        
        
        //give the maximun q_value of the tested next state
        float max_output_test()
        {
            float max_value=0;
            int i;
            for(i=0;i<20;i++)
            {
                max_value = max(max_value,test_output_layer_values(1,i));
            }
            return max_value;
        }
        
        
        
        int play_learn(Matrix<float,1,20> game_state)
        {
            Matrix<float,1,20> target_states[10];
            float q_targets[10];
            
            //compute the previous calculated q_values of the differents next
            //possible states, depending on the chosen action
            int action;
            for(action=0;action<20;action++)
            {
                //compute the next state if this action in chosen
                target_states[action] = play_simulation(game_state, action);
                
                int test = test_win(target_states[action]);
                if(test == 1)
                {
                    q_targets[action] = 1; //good reward
                }
                else if(test == -1)
                {
                    q_targets[action] = -1; //bad reward
                }
                else
                {
                    //compute the q_value of these states, according to th
                    //futur possibles actions
                    test_forward_propagation(target_states[action]);
                    q_targets[action] = max_output_test();
                }
            }
            
            //compute which action the neural network whant to play
            forward_propagation(game_state);
            
            //compare result of the neural network with the previous calculated
            //q_values of the next possible states, and updates the weights
            backward_propagation(q_targets);
            
            //choose the which action play
            int chosen_action = choose_action(output_layer_values);
            return chosen_action;
        }
        
        
        
};

