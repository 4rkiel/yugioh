#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <eigen-git-mirror/Eigen/Core>
#include <vector>

using namespace Eigen;

class Network
{
    public:
        
        
        Matrix<float,20,60> input_synaps;
        Matrix<float,60,60> hidden_synaps;
        Matrix<float,60,10> output_synaps;
        
        
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
};
