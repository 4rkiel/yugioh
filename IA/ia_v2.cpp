#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <eigen-git-mirror/Eigen/Core>
#include <vector>
#include <tuple>

using namespace Eigen;
using namespace std;

class Network
{
    public:
        
        /*neural netwrok
         * 4 layers: 1 input layer, 2 hidden layers, 1 output layer
         * synaps are the weights between the neurons layer
         */
        Matrix<float,20,60> input_synaps;
        Matrix<float,60,60> hidden_synaps;
        Matrix<float,60,10> output_synaps;
        
        /*memory of the neural network
         * matrix associated with his previous computated Q_value
         */
        vector<tuple<Matrix<float,1,20>,float>> memory;
        
        
        //neural network weights initialisation
        void init()
        {
            int i,j;
            srand (time(NULL));
            
            for(i=0;i<20;i++)
            {
                for(j=0;j<60;j++)
                {
                    input_synaps(i,j)= rand()%2;
                }
            }
            for(i=0;i<60;i++)
            {
                for(j=0;j<60;j++)
                {
                    hidden_synaps(i,j)= rand()%2;
                }
            }
            for(i=0;i<60;i++)
            {
                for(j=0;j<10;j++)
                {
                    output_synaps(i,j)= rand()%2;
                }
            }
        }
        
        
        //compute the vector of actions q_values
        Matrix<float,1,10> compute_choices(Matrix<float,1,20> game_state)
        {
            Matrix<float,1,10> actions;
            
            Matrix<float,1,60> hidden_layer1 = game_state * input_synaps;
            Matrix<float,1,60> hidden_layer2 = hidden_layer1 * hidden_synaps;
            Matrix<float,1,10> output_layer = hidden_layer2 * output_synaps;
            
            int i;
            float sum=0;
            
            for(i=0;i<10;i++)
            {
                sum += output_layer(1,i);
            }
            
            for(i=0;i<10;i++)
            {
                actions(1,i)=output_layer(1,i)/sum;
            }
            return actions;
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
            Matrix<float,1,10> actions = compute_choices(game_state);
            
            int action = choose_action(actions);
            
            return action;
        }
        
        
        int play_learn(Matrix<float,1,20> game_state)
        {
            Matrix<float,1,20> target_states[20];
            float q_targets[20];
            Matrix<float,1,10> q_values = compute_choices(game_state);

            int action;
            for(action=0;action<20;action++)
            {
                //compute the next state if this action in chosen
                target_states[action] = play_simulation(game_state, action);
                //compute the q_value of this state, function of the memory
                q_targets[action] = compute_q_value(target_states[action]);
            }

            int i;
            float td_loss=0;
            for(i=0;i<20;i++)
                td_loss += pow(q_targets[i]-q_values(i),2);

            //stochastic gradient descent, reinitialize at each iteration
            //backward function, backpropagation
            //update the weight
            
            int played_action = choose_action(q_values);
            return played_action;
        }
        
        
        void upatde(last_reward, signal)
        {
            float new_state = tensor(signal);
            memory.push(last_state,new_state,last_action,last_reward)
        }




};
