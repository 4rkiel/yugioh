#include "../inc/ai.h"


//CONSTRUCTOR DESTRUCTOR///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//the neural network
/*neural netwrok
 * 4 layers: 1 input layer, 2 hidden layers, 1 output layer
 * synaps are the weights between neurons layer
 */
//constructor: neural network initialisation
Ai::Ai(int difficulty)
{
    srand (time(NULL));
    nb_hidden_layer = 2;
    if(difficulty == 15)
    {
        mode = 0;
        initialise_random_ai();
    }
    else
    {
        load_trained_ai(difficulty);
    }
}



//destructor
Ai::~Ai()
{
    if(mode >= 11 && mode <= 14)
        save_ai();
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//LOAD AND SAVE AI/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//save the ai in a file according to the chosen mode
void Ai::save_ai()
{
    int i,j,k;
    ofstream ai_file;
    switch(mode)
    {
        case 1:
            ai_file.open("../IA/easy_ai.data");
            break;
        case 2:
            ai_file.open("../IA/medium_ai.data");
            break;
        case 3:
            ai_file.open("../IA/hard_ai.data");
            break;
        case 4:
            ai_file.open("../IA/learning_ai.data");
            break;
        default:
            break;
    }
    if(ai_file){
        //hidden layers
        ///////////////
        for(k=0;k<nb_hidden_layer;k++)
        {
            //save weights
            for(i=0;i<20;i++)
            {
                for(j=0;j<60;j++)
                {
                    ai_file << hidden_weights.at(k)(i,j);
                }
                ai_file << endl;
            }
            ai_file << endl;
            //save deltas
            for(i=0;i<20;i++)
            {
                for(j=0;j<60;j++)
                {
                    ai_file << hidden_deltas.at(k)(i,j);
                }
                ai_file << endl;
            }
            ai_file << endl;
            //save values
            for(i=0;i<60;i++)
            {
                ai_file << hidden_layers_values.at(k)(1,i);
            }
            ai_file << endl;
            ai_file << endl;
            //save test values
            for(i=0;i<60;i++)
            {
                ai_file << test_hidden_layers_values.at(k)(1,i);
            }
            ai_file << endl;
            ai_file << endl;
        }
        //////////////
        //output layer
        //////////////
        //save weights
        for(i=0;i<60;i++)
        {
            for(j=0;j<10;j++)
            {
                ai_file << output_weight(i,j);
            }
            ai_file << endl;
        }
        ai_file << endl;
        //initialise deltas
        for(i=0;i<60;i++)
        {
            for(j=0;j<10;j++)
            {
                ai_file << output_delta(i,j);
            }
            ai_file << endl;
        }
        ai_file << endl;
        //initialise values
        for(i=0;i<10;i++)
        {
            ai_file << output_layer_values(1,i);
        }
        ai_file << endl;
        ai_file << endl;
        //initialise test values
        for(i=0;i<10;i++)
        {
            ai_file << test_output_layer_values(1,i);
        }
        //////////////
        ai_file.close();
    }else{
        cout << "ERROR: open ai file" << endl;
    }
}



//load a trained AI from a file, according to the chosen difficulty
void Ai::load_trained_ai(int difficulty)
{
    int i,j,k;
    float number;
    ifstream ai_file;
    switch(difficulty)
    {
        case 11:
            mode=1;
            ai_file.open("../IA/easy_ai.data");
            break;
        case 12:
            mode=2;
            ai_file.open("../IA/medium_ai.data");
            break;
        case 13:
            mode=3;
            ai_file.open("../IA/hard_ai.data");
            break;
        case 14:
            mode=4;
            ai_file.open("../IA/learning_ai.data");
            break;
        default:
            cout << "Error: no difficulty/mode selected" << endl;
            break;
    }
    if(ai_file)
    {
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
                    ai_file >> number;
                    new_weights_m(i,j) = number;
                }
            }
            //initialise deltas
            Matrix<float,60,60> new_deltas_m;
            hidden_deltas.push_back(new_deltas_m);
            for(i=0;i<20;i++)
            {
                for(j=0;j<60;j++)
                {
                    ai_file >> number;
                    new_deltas_m(i,j) = number;
                }
            }
            //initialise values
            Matrix<float,1,60> new_values_m;
            hidden_layers_values.push_back(new_values_m);
            for(i=0;i<60;i++)
            {
                ai_file >> number;
                new_values_m(1,i) = number;
            }
            //initialise test values
            Matrix<float,1,60> new_test_values_m;
            hidden_layers_values.push_back(new_test_values_m);
            for(i=0;i<60;i++)
            {
                ai_file >> number;
                new_test_values_m(1,i) = number;
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
                ai_file >> number;
                output_weight(i,j) = number;
            }
        }
        //initialise deltas
        for(i=0;i<60;i++)
        {
            for(j=0;j<10;j++)
            {
                ai_file >> number;
                output_delta(i,j) = number;
            }
        }
        //initialise values
        for(i=0;i<10;i++)
        {
            ai_file >> number;
            output_layer_values(1,i) = number;
        }
        //initialise test values
        for(i=0;i<10;i++)
        {
            ai_file >> number;
            test_output_layer_values(1,i) = number;
        }
        //////////////
        ai_file.close();
    }
    else
    {
        cout << "ERROR: cannot open ai file" << endl;
    }
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//INITIALISE///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//start a new not trained AI
void Ai::initialise_random_ai()
{
    int i,j,k;
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


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//INTERNAL FUNCTIONS///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/*
 * compute the actions' q_values vector
 * takes in input the game state
 * and outputs the vector of the actions do to
 */
void Ai::forward_propagation(Matrix<float,1,20> game_state)
{
    hidden_layers_values.at(0) = game_state * hidden_weights.at(0);
    hidden_layers_values.at(1) = hidden_layers_values.at(0)
        * hidden_weights.at(1);
    output_layer_values = hidden_layers_values.at(1) * output_weight;
}



/*
 * compute test actions' q_values vector
 * takes in input the future possible state
 * and outputs the vector of the actions it will be able to do
 */
void Ai::test_forward_propagation(Matrix<float,1,20> game_state)
{
    test_hidden_layers_values.at(0) = game_state * hidden_weights.at(0);
    test_hidden_layers_values.at(1) = test_hidden_layers_values.at(0)
        * hidden_weights.at(1);
    test_output_layer_values = test_hidden_layers_values.at(1) * output_weight;
}



/*
 * Choose the action to do, according to the actions' q_value calculated.
 * More an action has a big q_value, more it has chance to be chosen
 */
int Ai::choose_action(Matrix<float,1,10> actions)
{
    srand (time(NULL));
    float choice = rand()%1;

    int action=0;
    while(choice>0)
    {
        if(action==10)
        {
            action=rand()%10;
            break;
        }
        choice -= actions(1,action);
        action++;
    }

    return action;
}



/*
 * compare the output of the neural network with the q_values of the
 * different next possible state, and update the weights of the neural
 * network
 */
void Ai::backward_propagation(float q_targets[10])
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
        }
        sum = local_sum;
        local_sum=0;
    }
}



/*
 * test if the game state is a winning state, a losing state
 * or a neutral state
 */
int Ai::test_win(Matrix<float,1,20> state)
{
    return state(1,1);
}



//give the maximun q_value of the tested next state
float Ai::max_output_test()
{
    float max_value=0;
    int i;
    for(i=0;i<20;i++)
    {
        max_value = max(max_value,test_output_layer_values(1,i));
    }
    return max_value;
}



//give the next game state, if the action is played
Matrix<float,1,20> Ai::play_simulation(Matrix<float,1,20> game_state,
        int action)
{
    //TODO: connect to "Moteur"
    if(action)
    {
    }
    return game_state;
}



//function to calculate a random float between two floats
float randomFloat(float a, float b)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//USE AI///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//play without learn
int Ai::play(Matrix<float,1,20> game_state)
{
    forward_propagation(game_state);
    int action = choose_action(output_layer_values);
    return action;
}



int Ai::play_learn(Matrix<float,1,20> game_state)
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


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
