#include <iostream>
#include <stdlib.h>
#include <time.h>
//#include <Eigen/Core>
#include <eigen-git-mirror/Eigen/Core>
#include <vector>
#include <tuple>

#define NB_INPUT 26
#define NB_LAYER1 60
#define NB_LAYER2 20
#define NB_OUTPUT 10

using namespace Eigen;
using namespace std;

int main()
{
    return 0;
}

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

class Network
{
    public:
        
        /*neural netwrok
         * 4 layers: 1 input layer, 2 hidden layers, 1 output layer
         * synaps are the weights between neurons layer
         */
        vector<Matrix<float,Dynamic,Dynamic>> hidden_weights;
        Matrix<float,Dynamic,10> output_weight;

        vector<Matrix<float,Dynamic,Dynamic>> hidden_deltas;
        Matrix<float,Dynamic,10> output_delta;
        
        vector<Matrix<Neuron,1,Dynamic>> hidden_layers;
        Matrix<Neuron,1,10> output_layer;

        vector<Matrix<float,1,Dynamic>> hidden_layers_values;
        Matrix<float,1,10> output_layer_values;
        
        int nb_hidden_layer;
        /*memory of the neural network
         * matrix associated with his previous computated Q_value
         */
        vector<tuple<Matrix<float,1,20>,float>> memory;


        //neural network weights initialisation
        Network(int nb_hidden_layer)
        {
            int i,j,k;
            srand (time(NULL));
            this->nb_hidden_layer = nb_hidden_layer;
            
            //hidden layers
            for(k=0;k<nb_hidden_layer;k++)
            {
                //initialyse weights
                Matrix<float,60,60> new_weights_m;
                hidden_weights.push_back(new_weights_m);
                for(i=0;i<20;i++)
                {
                    for(j=0;j<60;j++)
                    {
                        new_weights_m(i,j) = rand()%2;
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
                
                //initialyse neurons
                Matrix<Neuron,1,60> new_neurons_m;
                hidden_layers.push_back(new_neurons_m);
                for(i=0;i<60;i++)
                {
                    Neuron new_neuron;
                    new_neurons_m(1,i) = new_neuron;
                }
                
                //initialyse values
                Matrix<float,1,60> new_values_m;
                hidden_layers_values.push_back(new_values_m);
                for(i=0;i<60;i++)
                {
                    new_values_m(1,i) = 0;
                }

            }
            
            //output layer
            //initialyse weights
            for(i=0;i<60;i++)
            {
                for(j=0;j<10;j++)
                {
                    output_weight(i,j) = rand()%2;
                }
            }
            
            //initialyse deltas
            for(i=0;i<60;i++)
            {
                for(j=0;j<10;j++)
                {
                    output_delta(i,j) = 0;
                }
            }
            
            //initialyse neurons
            for(i=0;i<10;i++)
            {
                Neuron new_neuron;
                output_layer(1,i) = new_neuron;
            }
            
            //initialyse values
            for(i=0;i<10;i++)
            {
                output_layer_values(1,i) = 0;
            }
            
        }
        
        
        //compute the vector of actions q_values
        void forward_propagation(Matrix<float,1,20> game_state)
        {
            Matrix<float,1,10> actions;
            
            hidden_layers_values.at(0) = game_state * hidden_weights.at(0);
            hidden_layers_values.at(1) = hidden_layers_values.at(0) * hidden_weights.at(1);
            output_layer_values = hidden_layers_values.at(1) * output_weight;
        }
        
        
        /*choose the action to do, function of the actions' q_value calculated
         * much an action has a big q_value, much more it has chance to be
         * chosen
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
        
        
        int play(Matrix<float,1,20> game_state)
        {
            forward_propagation(game_state);
            int action = choose_action(output_layer_values);
            return action;
        }


        void backward_propagation(float q_targets[10])
        {
            int i,j,k;
            float local_cost=0;
            float global_cost=0;
            float delta, udelta;
            float output;
            float sum=0,local_sum=0;
            
            
            //output_layer
            for(i=0;i<output_weight.rows();i++)
            {
                //calcul local cost of this neuron
                output=output_layer_values(1,i);
                local_cost=( q_targets[i] - output_layer_values(1,i) ) *
                    output_layer_values(1,i) * (1 - output_layer_values(1,i));
                global_cost += pow(q_targets[i] - output_layer_values(1,i),2);
                
                //update the weights comming into this neuron
                for(j=0;j<output_weight.cols();j++)
                {
                    delta=output_delta(i,j);
                    udelta = local_cost * output_weight(i,j) + delta;
                    output_weight(i,j) += udelta;
                    output_delta(i,j) = udelta;
                    sum += output_weight(i,j) * local_cost;
                }
                output_layer(1,i).wgain = local_cost * output_layer(1,i).gain;
            }
            
            
            //hidden_layers
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
        
        
        
        
        int play_learn(Matrix<float,1,20> game_state)
        {
            Matrix<float,1,20> target_states[10];
            float q_targets[10];
            
            int action;
            for(action=0;action<20;action++)
            {
                //compute the next state if this action in chosen
                //TODO: target_states[action] = play_simulation(game_state, action);
                
                //compute the q_value of these states, in function of the memory
                //and futures possibles actions
                //TODO: q_targets[action] = compute_q_value(target_states[action]);
            }
            
            
            int played_action = choose_action(output_layer_values);
            return played_action;
        }
        
        
        
        /*
        void upatde(last_reward, signal)
        {
            float new_state = tensor(signal);
            memory.push(last_state,new_state,last_action,last_reward)
        }
        */


};
