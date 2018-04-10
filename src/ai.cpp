#include "../inc/ai.h"


//CONSTRUCTOR DESTRUCTOR///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//the neural network
/*neural netwrok
 * 4 layers: 1 input layer, 2 hidden layers, 1 output layer
 * synaps are the weights between neurons layer
 */

//constructor: neural network initialisation
//mode = 1 => file ai.data
//mode = 2 => file learning_ai.data
Ai::Ai(Noyau * noyau,int mode)
{
    srand (time(NULL));
    nb_hidden_layer = 2;
    this->mode = mode;
    this->noyau = noyau;
    load_ai();
}



//destructor
Ai::~Ai()
{
    if(mode==2) //learning_ai
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
        case 2:
            ai_file.open("../IA/learning_ai.data");
            break;
        case 1:
        default:
            ai_file.open("../IA/ai.data");
            break;
    }
    if(ai_file){
        //////////////input layer///////////////
        //save weights
        for(i=0;i<NB_INPUT;i++)
        {
            for(j=0;j<NB_HIDDEN;j++)
            {
                ai_file << input_weight(i,j) << " ";
            }
            ai_file << endl;
        }
        ai_file << endl;
        //initialise deltas
        for(i=0;i<NB_INPUT;i++)
        {
            for(j=0;j<NB_HIDDEN;j++)
            {
                ai_file << input_delta(i,j) << " ";
            }
            ai_file << endl;
        }
        ai_file << endl;
        //initialise values
        for(i=0;i<NB_HIDDEN;i++)
        {
            ai_file << input_layer_values(0,i) << " ";
        }
        ai_file << endl;
        ai_file << endl;
        //initialise test values
        for(i=0;i<NB_HIDDEN;i++)
        {
            ai_file << test_input_layer_values(0,i) << " ";
        }

        ////////////hidden layers//////////////
        for(k=0;k<nb_hidden_layer;k++)
        {
            //save weights
            for(i=0;i<NB_HIDDEN;i++)
            {
                for(j=0;j<NB_HIDDEN;j++)
                {
                    ai_file << hidden_weights.at(k)(i,j) << " ";
                }
                ai_file << endl;
            }
            ai_file << endl;
            //save deltas
            for(i=0;i<NB_HIDDEN;i++)
            {
                for(j=0;j<NB_HIDDEN;j++)
                {
                    ai_file << hidden_deltas.at(k)(i,j) << " ";
                }
                ai_file << endl;
            }
            ai_file << endl;
            //save values
            for(i=0;i<NB_HIDDEN;i++)
            {
                ai_file << hidden_layers_values.at(k)(0,i) << " ";
            }
            ai_file << endl;
            ai_file << endl;
            //save test values
            for(i=0;i<NB_HIDDEN;i++)
            {
                ai_file << test_hidden_layers_values.at(k)(0,i) << " ";
            }
            ai_file << endl;
            ai_file << endl;
        }
        //////////////output layer///////////////
        //save weights
        for(i=0;i<NB_HIDDEN;i++)
        {
            for(j=0;j<NB_OUTPUT;j++)
            {
                ai_file << output_weight(i,j) << " ";
            }
            ai_file << endl;
        }
        ai_file << endl;
        //initialise deltas
        for(i=0;i<NB_HIDDEN;i++)
        {
            for(j=0;j<NB_OUTPUT;j++)
            {
                ai_file << output_delta(i,j) << " ";
            }
            ai_file << endl;
        }
        ai_file << endl;
        //initialise values
        for(i=0;i<NB_OUTPUT;i++)
        {
            ai_file << output_layer_values(0,i) << " ";
        }
        ai_file << endl;
        ai_file << endl;
        //initialise test values
        for(i=0;i<NB_OUTPUT;i++)
        {
            ai_file << test_output_layer_values(0,i) << " ";
        }
        //////////////
        ai_file.close();
    }else{
        cout << "ERROR: open ai file" << endl;
    }
}



//load a trained AI from a file, according to the chosen difficulty
void Ai::load_ai()
{
    int i,j,k;
    float number;
    ifstream ai_file;
    switch(mode)
    {
        case 2:
            ai_file.open("../IA/learning_ai.data");
            break;
        case 1:
        default:
            ai_file.open("../IA/ai.data");
            break;
    }
    if(ai_file)
    {
        ////////////input layer//////////////
        //initialise weights
        for(i=0;i<NB_INPUT;i++)
        {
            for(j=0;j<NB_HIDDEN;j++)
            {
                ai_file >> number;
                input_weight(i,j) = number;
            }
        }
        //initialise deltas
        for(i=0;i<NB_INPUT;i++)
        {
            for(j=0;j<NB_HIDDEN;j++)
            {
                ai_file >> number;
                input_delta(i,j) = number;
            }
        }
        //initialise values
        for(i=0;i<NB_HIDDEN;i++)
        {
            ai_file >> number;
            input_layer_values(0,i) = number;
        }
        //initialise test values
        for(i=0;i<NB_HIDDEN;i++)
        {
            ai_file >> number;
            test_input_layer_values(0,i) = number;
        }

        ////////////hidden layers//////////////
        for(k=0;k<nb_hidden_layer;k++)
        {
            //initialise weights
            Matrix<float,200,200> new_weights_m;
            for(i=0;i<NB_HIDDEN;i++)
            {
                for(j=0;j<NB_HIDDEN;j++)
                {
                    ai_file >> number;
                    new_weights_m(i,j) = number;
                }
            }
            hidden_weights.push_back(new_weights_m);
            //initialise deltas
            Matrix<float,200,200> new_deltas_m;
            for(i=0;i<NB_HIDDEN;i++)
            {
                for(j=0;j<NB_HIDDEN;j++)
                {
                    ai_file >> number;
                    new_deltas_m(i,j) = number;
                }
            }
            hidden_deltas.push_back(new_deltas_m);
            //initialise values
            Matrix<float,1,200> new_values_m;
            for(i=0;i<NB_HIDDEN;i++)
            {
                ai_file >> number;
                new_values_m(0,i) = number;
            }
            hidden_layers_values.push_back(new_values_m);
            //initialise test values
            Matrix<float,1,200> new_test_values_m;
            for(i=0;i<NB_HIDDEN;i++)
            {
                ai_file >> number;
                new_test_values_m(0,i) = number;
            }
            test_hidden_layers_values.push_back(new_test_values_m);
        }
        ////////////output layer//////////////
        //initialise weights
        for(i=0;i<NB_HIDDEN;i++)
        {
            for(j=0;j<NB_OUTPUT;j++)
            {
                ai_file >> number;
                output_weight(i,j) = number;
            }
        }
        //initialise deltas
        for(i=0;i<NB_HIDDEN;i++)
        {
            for(j=0;j<NB_OUTPUT;j++)
            {
                ai_file >> number;
                output_delta(i,j) = number;
            }
        }
        //initialise values
        for(i=0;i<NB_OUTPUT;i++)
        {
            ai_file >> number;
            output_layer_values(0,i) = number;
        }
        //initialise test values
        for(i=0;i<NB_OUTPUT;i++)
        {
            ai_file >> number;
            test_output_layer_values(0,i) = number;
        }
        //////////////
        ai_file.close();
    }
    else
    {
        initialise_random_ai();
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
    /////////////input layer////////////////
    //initialise weights
    for(i=0;i<NB_INPUT;i++)
    {
        for(j=0;j<NB_HIDDEN;j++)
        {
            input_weight(i,j) = 1;
        }
    }
    //initialise deltas
    for(i=0;i<NB_INPUT;i++)
    {
        for(j=0;j<NB_HIDDEN;j++)
        {
            input_delta(i,j) = 0;
        }
    }
    //initialise values
    for(i=0;i<NB_HIDDEN;i++)
    {
        input_layer_values(0,i) = 0;
    }
    //initialise test values
    for(i=0;i<NB_HIDDEN;i++)
    {
        test_input_layer_values(0,i) = 0;
    }

    /////////////hidden layers///////////////
    for(k=0;k<nb_hidden_layer;k++)
    {
        //initialise weights
        Matrix<float,200,200> new_weights_m;
        for(i=0;i<NB_HIDDEN;i++)
        {
            for(j=0;j<NB_HIDDEN;j++)
            {
                new_weights_m(i,j) =
                    randomFloat(-1/sqrt(NB_INPUT),1/sqrt(NB_INPUT));
            }
        }
        hidden_weights.push_back(new_weights_m);
        //initialise deltas
        Matrix<float,200,200> new_deltas_m;
        for(i=0;i<NB_HIDDEN;i++)
        {
            for(j=0;j<NB_HIDDEN;j++)
            {
                new_deltas_m(i,j) = 0;
            }
        }
        hidden_deltas.push_back(new_deltas_m);
        //initialise values
        Matrix<float,1,200> new_values_m;
        for(i=0;i<NB_HIDDEN;i++)
        {
            new_values_m(0,i) = 0;
        }
        hidden_layers_values.push_back(new_values_m);
        //initialise test values
        Matrix<float,1,200> new_test_values_m;
        for(i=0;i<NB_HIDDEN;i++)
        {
            new_test_values_m(0,i) = 0;
        }
        test_hidden_layers_values.push_back(new_test_values_m);
    }
    /////////////output layer////////////////
    //initialise weights
    for(i=0;i<NB_HIDDEN;i++)
    {
        for(j=0;j<NB_OUTPUT;j++)
        {
            output_weight(i,j) =
                randomFloat(-1/sqrt(NB_INPUT),1/sqrt(NB_INPUT));
        }
    }
    //initialise deltas
    for(i=0;i<NB_HIDDEN;i++)
    {
        for(j=0;j<NB_OUTPUT;j++)
        {
            output_delta(i,j) = 0;
        }
    }
    //initialise values
    for(i=0;i<NB_OUTPUT;i++)
    {
        output_layer_values(0,i) = 0;
    }
    //initialise test values
    for(i=0;i<NB_OUTPUT;i++)
    {
        test_output_layer_values(0,i) = 0;
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
void Ai::forward_propagation(Matrix<float,1,413> game_state)
{
    input_layer_values = game_state * input_weight;
    hidden_layers_values.at(0) = input_layer_values * hidden_weights.at(0);
    hidden_layers_values.at(1) = hidden_layers_values.at(0)
        * hidden_weights.at(1);
    output_layer_values = hidden_layers_values.at(1) * output_weight;
}



/*
 * compute test actions' q_values vector
 * takes in input the future possible state
 * and outputs the vector of the actions it will be able to do
 */
void Ai::test_forward_propagation(Matrix<float,1,413> game_state)
{
    test_input_layer_values = game_state * input_weight;
    test_hidden_layers_values.at(0) = test_input_layer_values *
        hidden_weights.at(0);
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
int Ai::test_win(Matrix<float,1,413> state)
{
    if(state(0,0)<=0.5)
        return -1;
    if(state(0,1)<=0.5)
        return 1;
    return 0;
}



//give the maximun q_value of the tested next state
float Ai::max_output_test()
{
    float max_value=0;
    int i;
    for(i=0;i<NB_OUTPUT;i++)
    {
        max_value = max(max_value,test_output_layer_values(1,i));
    }
    return max_value;
}



//give the next game state, if the action is played
Matrix<float,1,413> Ai::play_simulation(Matrix<float,1,413> game_state,
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



//function that read the "noyau", and put the game state in a matrix
Matrix<float,1,413> Ai::read_noyau()
{
    int i;
    Matrix<float,1,413> game_state;

    //attributs globaux du terrain
    game_state(0,0) = noyau->selfLife;
    game_state(0,1) = noyau->foeLife;
    game_state(0,2) = noyau->phase;
    game_state(0,3) = noyau->tour;
    game_state(0,4) = -1;
    game_state(0,5) = -1;
    game_state(0,6) = -1;
    game_state(0,7) = -1;
    game_state(0,8) = -1;
    game_state(0,9) = -1;

    //chaque carte sur le terrain
    for(i=0;i<20;i++)
    {
        if(noyau->terrain->at(i)!=NULL) {
            game_state(0,10+i*5) = noyau->terrain->at(i)->atk;
            game_state(0,10+i*5+1) = noyau->terrain->at(i)->def;
            game_state(0,10+i*5+2) = noyau->terrain->at(i)->etat;
            game_state(0,10+i*5+3) = noyau->terrain->at(i)->niveau;
            game_state(0,10+i*5+4) = noyau->terrain->at(i)->position_terrain;
        } else {
            game_state(0,10+i*5) = -1;
            game_state(0,10+i*5+1) = -1;
            game_state(0,10+i*5+2) = -1;
            game_state(0,10+i*5+3) = -1;
            game_state(0,10+i*5+4) = -1;
        }
    }

    //chaque carte dans son propre deck
    for(i=0;i<60;i++)
    {
        if(noyau->d1->at(i)!=NULL) {
            game_state(0,105+i*5) = noyau->d1->at(i)->atk;
            game_state(0,105+i*5+1) = noyau->d1->at(i)->def;
            game_state(0,105+i*5+2) = noyau->d1->at(i)->etat;
            game_state(0,105+i*5+3) = noyau->d1->at(i)->niveau;
            game_state(0,105+i*5+4) = noyau->d1->at(i)->position_deck;
        } else {
            game_state(0,105+i*5) = -1;
            game_state(0,105+i*5+1) = -1;
            game_state(0,105+i*5+2) = -1;
            game_state(0,105+i*5+3) = -1;
            game_state(0,105+i*5+4) = -1;
        }
    }

    //derniere carte du cimetiere
    game_state(0,410) = noyau->cimetiere1->back()->atk;
    game_state(0,411) = noyau->cimetiere1->back()->def;
    game_state(0,412) = noyau->cimetiere1->back()->niveau;

    return game_state;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//USE AI///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//play without learn
int Ai::play()
{
    Matrix<float,1,413> game_state = read_noyau();
    forward_propagation(game_state);
    int action = choose_action(output_layer_values);
    return action;
}



int Ai::play_learn()
{
    Matrix<float,1,413> target_states[10];
    float q_targets[10];

    Matrix<float,1,413> game_state = read_noyau();
    
    
    //compute the previous calculated q_values of the differents next
    //possible states, depending on the chosen action
    int action;
    for(action=0;action<10;action++)
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

    emit attaquer(1,2);
    return chosen_action;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
