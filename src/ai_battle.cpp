#include "../inc/ai_main.h"


//##CONSTRUCTOR DESTRUCTOR/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//the neural network
/*neural netwrok
 * 4 layers: 1 input layer, 2 hidden layers, 1 output layer
 * synaps are the weights between neurons layer
 */

//constructor: neural network initialisation
//mode = 1 => file ai.data
//mode = 2 => file learning_ai.data
Ai_main::Ai_main(Noyau * noyau, int mode, int joueur)
{
    srand (time(NULL));
    nb_hidden_layer = 2;
    this->mode = mode;
    this->noyau = noyau;
    this->joueur = joueur;
    load_ai();
}



//destructor
Ai_main::~Ai_main()
{
    if(mode==2) //learning_ai
        save_ai();
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//##LOAD AND SAVE AI///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//save the ai in a file according to the chosen mode
void Ai_main::save_ai()
{
    int i,j,k;
    ofstream ai_file;
    switch(mode)
    {
        case 2:
            ai_file.open("../IA/learning_battle_ai.data");
            break;
        case 1:
        default:
            ai_file.open("../IA/battleai.data");
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
        //save deltas
        for(i=0;i<NB_INPUT;i++)
        {
            for(j=0;j<NB_HIDDEN;j++)
            {
                ai_file << input_delta(i,j) << " ";
            }
            ai_file << endl;
        }
        ai_file << endl;
        //save values
        for(i=0;i<NB_HIDDEN;i++)
        {
            ai_file << input_layer_values(0,i) << " ";
        }
        ai_file << endl;
        ai_file << endl;
        //save test values
        for(i=0;i<NB_HIDDEN;i++)
        {
            ai_file << test_input_layer_values(0,i) << " ";
        }
        ai_file << endl;
        ai_file << endl;
        //save gains
        for(i=0;i<NB_HIDDEN;i++)
        {
            ai_file << input_layer_gains(0,i) << " ";
        }
        ai_file << endl;
        ai_file << endl;
        //save wgains
        for(i=0;i<NB_HIDDEN;i++)
        {
            ai_file << input_layer_wgains(0,i) << " ";
        }
        ai_file << endl;
        ai_file << endl;

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
            //save gains
            for(i=0;i<NB_HIDDEN;i++)
            {
                ai_file << hidden_layers_gains.at(k)(0,i) << " ";
            }
            ai_file << endl;
            ai_file << endl;
            //save wgains
            for(i=0;i<NB_HIDDEN;i++)
            {
                ai_file << hidden_layers_wgains.at(k)(0,i) << " ";
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
        //save deltas
        for(i=0;i<NB_HIDDEN;i++)
        {
            for(j=0;j<NB_OUTPUT;j++)
            {
                ai_file << output_delta(i,j) << " ";
            }
            ai_file << endl;
        }
        ai_file << endl;
        //save values
        for(i=0;i<NB_OUTPUT;i++)
        {
            ai_file << output_layer_values(0,i) << " ";
        }
        ai_file << endl;
        ai_file << endl;
        //save test values
        for(i=0;i<NB_OUTPUT;i++)
        {
            ai_file << test_output_layer_values(0,i) << " ";
        }
        ai_file << endl;
        ai_file << endl;
        //save values
        for(i=0;i<NB_OUTPUT;i++)
        {
            ai_file << output_layer_gains(0,i) << " ";
        }
        ai_file << endl;
        ai_file << endl;
        //save test values
        for(i=0;i<NB_OUTPUT;i++)
        {
            ai_file << output_layer_wgains(0,i) << " ";
        }

        //////////////
        ai_file.close();
    }else{
        cout << "ERROR: open ai file" << endl;
    }
}



//load a trained AI from a file, according to the chosen difficulty
void Ai_main::load_ai()
{
    int i,j,k;
    float number;
    ifstream ai_file;
    switch(mode)
    {
        case 2:
            ai_file.open("../IA/learning_battle_ai.data");
            break;
        case 1:
        default:
            ai_file.open("../IA/battle_ai.data");
            break;
    }
    if(ai_file)
    {
        ////////////input layer//////////////
        //load weights
        for(i=0;i<NB_INPUT;i++)
        {
            for(j=0;j<NB_HIDDEN;j++)
            {
                ai_file >> number;
                input_weight(i,j) = number;
            }
        }
        //load deltas
        for(i=0;i<NB_INPUT;i++)
        {
            for(j=0;j<NB_HIDDEN;j++)
            {
                ai_file >> number;
                input_delta(i,j) = number;
            }
        }
        //load values
        for(i=0;i<NB_HIDDEN;i++)
        {
            ai_file >> number;
            input_layer_values(0,i) = number;
        }
        //load test values
        for(i=0;i<NB_HIDDEN;i++)
        {
            ai_file >> number;
            test_input_layer_values(0,i) = number;
        }
        //load gains
        for(i=0;i<NB_HIDDEN;i++)
        {
            ai_file >> number;
            input_layer_gains(0,i) = number;
        }
        //load wgains
        for(i=0;i<NB_HIDDEN;i++)
        {
            ai_file >> number;
            input_layer_wgains(0,i) = number;
        }

        ////////////hidden layers//////////////
        for(k=0;k<nb_hidden_layer;k++)
        {
            //load weights
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
            //load deltas
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
            //load values
            Matrix<float,1,200> new_values_m;
            for(i=0;i<NB_HIDDEN;i++)
            {
                ai_file >> number;
                new_values_m(0,i) = number;
            }
            hidden_layers_values.push_back(new_values_m);
            //load test values
            Matrix<float,1,200> new_test_values_m;
            for(i=0;i<NB_HIDDEN;i++)
            {
                ai_file >> number;
                new_test_values_m(0,i) = number;
            }
            test_hidden_layers_values.push_back(new_test_values_m);
            //load gains
            Matrix<float,1,200> new_gains_m;
            for(i=0;i<NB_HIDDEN;i++)
            {
                ai_file >> number;
                new_gains_m(0,i) = number;
            }
            hidden_layers_gains.push_back(new_gains_m);
            //load test values
            Matrix<float,1,200> new_wgains_m;
            for(i=0;i<NB_HIDDEN;i++)
            {
                ai_file >> number;
                new_wgains_m(0,i) = number;
            }
            hidden_layers_wgains.push_back(new_wgains_m);

        }
        ////////////output layer//////////////
        //load weights
        for(i=0;i<NB_HIDDEN;i++)
        {
            for(j=0;j<NB_OUTPUT;j++)
            {
                ai_file >> number;
                output_weight(i,j) = number;
            }
        }
        //load deltas
        for(i=0;i<NB_HIDDEN;i++)
        {
            for(j=0;j<NB_OUTPUT;j++)
            {
                ai_file >> number;
                output_delta(i,j) = number;
            }
        }
        //load values
        for(i=0;i<NB_OUTPUT;i++)
        {
            ai_file >> number;
            output_layer_values(0,i) = number;
        }
        //load test values
        for(i=0;i<NB_OUTPUT;i++)
        {
            ai_file >> number;
            test_output_layer_values(0,i) = number;
        }
        //load gains
        for(i=0;i<NB_OUTPUT;i++)
        {
            ai_file >> number;
            output_layer_gains(0,i) = number;
        }
        //load wgains
        for(i=0;i<NB_OUTPUT;i++)
        {
            ai_file >> number;
            output_layer_wgains(0,i) = number;
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


//##INITIALISE/////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//start a new not trained AI
void Ai_main::initialise_random_ai()
{
    int i,j,k;
    /////////////input layer////////////////
    //initialise weights
    for(i=0;i<NB_INPUT;i++)
    {
        for(j=0;j<NB_HIDDEN;j++)
        {
            input_weight(i,j) =
                randomFloat(-1/sqrt(NB_INPUT),1/sqrt(NB_INPUT));
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
    //initialise gain
    for(i=0;i<NB_HIDDEN;i++)
    {
        input_layer_gains(0,i) = 1;
    }
    //initialise wgain
    for(i=0;i<NB_HIDDEN;i++)
    {
        input_layer_wgains(0,i) = 0;
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
        //initialise gain
        Matrix<float,1,200> new_gain_m;
        for(i=0;i<NB_HIDDEN;i++)
        {
            new_gain_m(0,i) = 1;
        }
        hidden_layers_gains.push_back(new_gain_m);
        //initialise wgain
        Matrix<float,1,200> new_wgain_m;
        for(i=0;i<NB_HIDDEN;i++)
        {
            new_wgain_m(0,i) = 0;
        }
        hidden_layers_wgains.push_back(new_wgain_m);
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
    //initialise gain
    for(i=0;i<NB_OUTPUT;i++)
    {
        output_layer_gains(0,i) = 1;
    }
    //initialise wgain
    for(i=0;i<NB_OUTPUT;i++)
    {
        output_layer_wgains(0,i) = 0;
    }
    //////////////
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//##INTERNAL FUNCTIONS/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/*
 * ReLU
 * activation function
 * if the neuron value is positiv, then activate them, else send 0
 * return the vector this neuron activate or not for the next layer
 */
Matrix<float,1,Dynamic> Ai_main::ReLU(Matrix<float,1,Dynamic> layer_values)
{
    Matrix <float,1,Dynamic> next_layer_input(1,layer_values.cols());
    int i;
    for(i=0;i<layer_values.cols();i++)
    {
        next_layer_input(0,i) = max((float) 0,layer_values(0,i));
    }
    return next_layer_input;
}


/*
 * compute the actions' q_values vector
 * takes in input the game state
 * and outputs the vector of the actions do to
 */
void Ai_main::forward_propagation(Matrix<float,1,434> game_state)
{
    input_layer_input = game_state;

    ////input layer////
    input_layer_values = input_layer_input * input_weight;
    input_layer_values += input_layer_wgains;
    hidden_layers_input.at(0) = ReLU(input_layer_values);
    
    ////hidden layer 1////
    hidden_layers_values.at(0) = input_layer_values * hidden_weights.at(0);
    hidden_layers_values.at(0) += hidden_layers_wgains.at(0);
    hidden_layers_input.at(1) = ReLU(hidden_layers_values.at(0));

    ////hidden layer 2////
    hidden_layers_values.at(1) = hidden_layers_values.at(0) * hidden_weights.at(1);
    hidden_layers_values.at(1) += hidden_layers_wgains.at(0);
    output_layer_input = ReLU(hidden_layers_values.at(1));

    ////output layer////
    output_layer_values = hidden_layers_values.at(1) * output_weight;
    output_layer_values += output_layer_wgains;
}



/*
 * compute test actions' q_values vector
 * takes in input the future possible state
 * and outputs the vector of the actions it will be able to do
 */
void Ai_main::test_forward_propagation(Matrix<float,1,434> game_state)
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
int Ai_main::choose_action(Matrix<float,1,135> actions)
{
    srand (time(NULL));
    float choice = rand()%1;

    int action=0;
    while(choice>0)
    {
        if(action==135)
        {
            action=rand()%135;
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
void Ai_main::backward_propagation(float q_targets[135])
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
        output=output_layer_values(0,i);
        local_cost=( q_targets[i] - output_layer_values(0,i) ) *
            output_layer_values(0,i) * (1 - output_layer_values(0,i));
        global_cost += pow(q_targets[i] - output_layer_values(0,i),2);
        
        //update the weights comming into this neuron from the previous
        //layer
        //for each synaps comming into the neuron
        for(j=0;j<output_weight.cols();j++)
        {
            //update the weight, according to the local cost and the
            //update delta at the previous backpropagation
            //update the delta value, etc
            delta=output_delta(i,j);
            udelta = local_cost * output_layer_input(0,i) + delta;
            output_weight(i,j) += udelta;
            output_delta(i,j) = udelta;
            sum += output_weight(i,j) * local_cost;
        }
        
        output_layer_wgains(0,i) += local_cost * output_layer_gains(0,i);
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
        for(j=0;j<hidden_weights.at(i).rows();j++)
        {
            output = hidden_layers_values.at(i)(0,j);
            local_cost = output * (1-output) * sum;
            for(k=0;k<hidden_weights.at(i).cols();k++)
            {
                delta = hidden_deltas.at(i)(j,k);
                udelta = local_cost * hidden_layers_input.at(i)(0,j) + delta;
                hidden_weights.at(i)(j,k) += udelta;
                hidden_deltas.at(i)(j,k) = udelta;
                local_sum += hidden_weights.at(i)(j,k) * local_cost;
            }
            hidden_layers_wgains.at(i)(0,j) += local_cost * hidden_layers_gains.at(i)(0,j);
        }
        sum = local_sum;
        local_sum=0;
    }

    /*
     * do the same as for the hidden layers, but now for the input layer
     */
    for(i=0;i<input_weight.rows();i++)
    {
        output = input_layer_values(0,j);
        local_cost = output * (1 - output) * sum;
        
        for(j=0;j<input_weight.cols();j++)
        {
            delta = input_delta(i,j);
            udelta = local_cost * input_layer_input(0,i) + delta;
            //update weights
            input_weight(i,j) += udelta;
            input_delta(i,j) = udelta;
        }
        //and update the gain weight
        input_layer_wgains(0,i) += local_cost * input_layer_gains(0,i);
    }
}



/*
 * test if the game state is a winning state, a losing state
 * or a neutral state
 */
int Ai_main::test_win(Matrix<float,1,434> state)
{
    if(state(0,0)<=0.5)
        return -1;
    if(state(0,1)<=0.5)
        return 1;
    return 0;
}



//give the maximun q_value of the tested next state
float Ai_main::max_output_test()
{
    float max_value=0;
    int i;
    for(i=0;i<NB_OUTPUT;i++)
    {
        max_value = max(max_value,test_output_layer_values(0,i));
    }
    return max_value;
}



//give the next game state, if the action is played
Matrix<float,1,434> Ai_main::play_simulation(Matrix<float,1,434> game_state,
        int action)
{
    //TODO: connect to "Moteur"
    if(action)
    {
    }
    return game_state;
}



//function to calculate a random float between two floats
float Ai_main::randomFloat(float a, float b)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}


//##NOYAU COMMUNICATION////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//function that read the "noyau", and put the game state in a matrix
Matrix<float,1,434> Ai_main::read_noyau()
{
    int i,j;
    Matrix<float,1,434> game_state;

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

    Carte * tmp_card;

    j=0;

    //chaque carte sur le terrain
    for(i=0;i<20;i++)
    {
        //placement sur le terrain
        if(i==0)
            j=1;
        if(i==5)
            j=8;
        if(i==135)
            j=76;
        if(i==15)
            j=83;
        
        //lecture de la carte
        tmp_card = noyau->trouver(j);
        
        //stockage dans la base de l'ia
        if(joueur == 1){
            if(j<=5)
                terrain_s_monstre[i%5]=tmp_card;
            else if(j<=12)
                terrain_s_magie[i%5]=tmp_card;
            else if(j<=80)
                terrain_a_monstre[i%5]=tmp_card;
            else if(j<=87)
                terrain_a_monstre[i%5]=tmp_card;
        }
        else if(joueur == 2){
            if(j<=5)
                terrain_a_monstre[i%5]=tmp_card;
            else if(j<=12)
                terrain_a_magie[i%5]=tmp_card;
            else if(j<=80)
                terrain_s_monstre[i%5]=tmp_card;
            else if(j<=87)
                terrain_s_monstre[i%5]=tmp_card;
        }
        
        // stocker dans le vecteur d'entrée du réseau neuronnal
        if(tmp_card!=NULL) {
            game_state(0,135+i*4) = tmp_card->atk;
            game_state(0,135+i*4+1) = tmp_card->def;
            game_state(0,135+i*4+2) = tmp_card->etat;
            game_state(0,135+i*4+3) = tmp_card->niveau;
        } else {
            game_state(0,135+i*4) = -1;
            game_state(0,135+i*4+1) = -1;
            game_state(0,135+i*4+2) = -1;
            game_state(0,135+i*4+3) = -1;
        }
        j++;
    }

    //chaque carte dans son propre deck
    for(i=0;i<60;i++)
    {
        if(noyau->d1->at(i)!=NULL) {
            game_state(0,94+i*5) = noyau->d1->at(i)->atk;
            game_state(0,94+i*5+1) = noyau->d1->at(i)->def;
            game_state(0,94+i*5+2) = noyau->d1->at(i)->niveau;
            game_state(0,94+i*5+3) = noyau->d1->at(i)->position_deck;
            game_state(0,94+i*5+4) = noyau->d1->at(i)->genre;
        } else {
            game_state(0,94+i*5) = -1;
            game_state(0,94+i*5+1) = -1;
            game_state(0,94+i*5+2) = -1;
            game_state(0,94+i*5+3) = -1;
            game_state(0,94+i*5+4) = -1;
        }
    }

    //chaque carte dans sa main
    for(i=0;i<7;i++)
    {
        if(joueur==1)
        {
            if(i==0)
                j=14;
        }
        else if(joueur==2)
        {
            if(i==0)
                j=89;
        }
        tmp_card = noyau->trouver(j);
        main[i]=tmp_card;
        if(tmp_card!=NULL) {
            game_state(0,399+i*4) = tmp_card->atk;
            game_state(0,399+i*4+1) = tmp_card->def;
            game_state(0,399+i*4+2) = tmp_card->niveau;
            game_state(0,399+i*4+3) = tmp_card->genre;
        } else {
            game_state(0,399+i*4) = -1;
            game_state(0,399+i*4+1) = -1;
            game_state(0,399+i*4+2) = -1;
            game_state(0,399+i*4+3) = -1;
        }
        j++;
    }

    //derniere carte du cimetiere
    game_state(0,431) = noyau->cimetiere1->back()->atk;
    game_state(0,432) = noyau->cimetiere1->back()->def;
    game_state(0,433) = noyau->cimetiere1->back()->niveau;

    return game_state;
}

//correspondance ID/terrein

int Ai_main::main_id_to_x(int main_id)
{
    if(joueur==1)
        return main_id+14;
    if(joueur==2)
        return main_id+89;
    else
        return -1;
}

int Ai_main::monstre_id_to_x(int monstre_id)
{
    if(joueur==1)
        return monstre_id+1;
    if(joueur==2)
        return monstre_id+76;
    else
        return -1;
}

int Ai_main::magie_piege_id_to_x(int magie_piege_id)
{
    if(joueur==1)
        return magie_piege_id+8;
    if(joueur==2)
        return magie_piege_id+83;
    else
        return -1;
}

//##SIGNALS////////////////////////////////////////////////////////////////////


//put monster in atk position
//return EXIT_SUCCESS if it work and send signal
//return EXIT_FAILURE else
int Ai_main::poser_atk(int main_id)
{
    int i;
    if(main[main_id]!=NULL)
        if(main[main_id]->niveau<5)
            for(i=0;i<5;i++)
                if(terrain_s_monstre[i]==NULL)
                {
                    signal_poser(main_id_to_x(main_id),monstre_id_to_x(i),false,true);
                    return EXIT_SUCCESS;
                }
    return EXIT_FAILURE;
}

//put monster in defense position
int Ai_main::poser_def(int main_id)
{
    int i;
    if(main[main_id]!=NULL)
        if(main[main_id]->niveau<5)
            for(i=0;i<5;i++)
                if(terrain_s_monstre[i]==NULL)
                {
                    signal_poser(main_id_to_x(main_id),monstre_id_to_x(i),true,false);
                    return EXIT_SUCCESS;
                }
    return EXIT_FAILURE;
}

//switch the position of the monster atk/def
int Ai_main::switch_atk_def(int monstre_id)
{
    if(terrain_s_monstre[monstre_id]!=NULL)
    {
        signal_switch_position(monstre_id_to_x(monstre_id));
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int Ai_main::sacrifier_poser(int monstre_id,int main_id)
{
    if(main[main_id]!=NULL)
        if(main[main_id]->niveau<7)
            if(terrain_s_monstre[monstre_id]!=NULL)
            {
                signal_sacrifier_poser(monstre_id_to_x(monstre_id),
                        main_id_to_x(main_id),monstre_id_to_x(monstre_id));
                return EXIT_SUCCESS;
            }
    return EXIT_FAILURE;
}

int Ai_main::sacrifier_sacrifier_poser(int monstre_id_1,int monstre_id_2,int main_id)
{
    if(main[main_id]!=NULL)
        if(main[main_id]->niveau<7)
            if(terrain_s_monstre[monstre_id_1]!=NULL)
                if(terrain_s_monstre[monstre_id_2]!=NULL)
                {
                    signal_sacrifier_sacrifier_poser(monstre_id_to_x(monstre_id_1),monstre_id_to_x(monstre_id_2),
                            main_id_to_x(main_id),monstre_id_to_x(monstre_id_1));
                    return EXIT_SUCCESS;
                }
    return EXIT_FAILURE;
}

int Ai_main::poser_magie_piege(int main_id)
{
    return EXIT_FAILURE;
    int i;
    if(main[main_id]!=NULL)
        if(main[main_id]->niveau<5)
            for(i=0;i<5;i++)
                if(terrain_s_magie[i]==NULL)
                {
                    signal_poser(main_id_to_x(main_id),magie_piege_id_to_x(i),false,false);
                    return EXIT_SUCCESS;
                }
    return EXIT_FAILURE;
}

int Ai_main::activer_magie_piege(int magie_id)
{
    return EXIT_FAILURE;
    if(terrain_s_magie[magie_id]!=NULL)
    {
        signal_activate(magie_piege_id_to_x(magie_id));
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}


//emit signal appropriate to the action chosen by the ai if it works
//returns EXIT_SUCCESS if ti works
//else returns EXIT_FAILURE
int Ai_main::perform_action(int chosen_action)
{
    switch(chosen_action)
    {
        case 0://passer
            return EXIT_SUCCESS;
            //poser atk
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            return poser_atk(chosen_action-1);
            //poser def
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            return poser_def(chosen_action-8);
            //switch atk/def
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            return switch_atk_def(chosen_action-15);
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            //sacrifier poser
            return sacrifier_poser(chosen_action-20,0);
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
            return sacrifier_poser(chosen_action-25,1);
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
            return sacrifier_poser(chosen_action-30,2);
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
            return sacrifier_poser(chosen_action-35,3);
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
            return sacrifier_poser(chosen_action-40,4);
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
            return sacrifier_poser(chosen_action-45,5);
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
            return sacrifier_poser(chosen_action-50,6);
            //sacrifier sacrifier poser
            //poser 0
        case 55:
        case 56:
        case 57:
        case 58:
            return sacrifier_sacrifier_poser(0,chosen_action-54,0);
        case 59:
        case 60:
        case 61:
            return sacrifier_sacrifier_poser(1,chosen_action-57,0);
        case 62:
        case 63:
            return sacrifier_sacrifier_poser(2,chosen_action-59,0);
        case 64:
            return sacrifier_sacrifier_poser(3,4,0);
            //poser 1
        case 65:
        case 66:
        case 67:
        case 68:
            return sacrifier_sacrifier_poser(0,chosen_action-64,1);
        case 69:
        case 70:
        case 71:
            return sacrifier_sacrifier_poser(1,chosen_action-67,1);
        case 72:
        case 73:
            return sacrifier_sacrifier_poser(2,chosen_action-69,1);
        case 74:
            return sacrifier_sacrifier_poser(3,4,1);
            //poser 2
        case 75:
        case 76:
        case 77:
        case 78:
            return sacrifier_sacrifier_poser(0,chosen_action-74,2);
        case 79:
        case 80:
        case 81:
            return sacrifier_sacrifier_poser(1,chosen_action-77,2);
        case 82:
        case 83:
            return sacrifier_sacrifier_poser(2,chosen_action-79,2);
        case 84:
            return sacrifier_sacrifier_poser(3,4,2);
            //poser 3
        case 85:
        case 86:
        case 87:
        case 88:
            return sacrifier_sacrifier_poser(0,chosen_action-84,3);
        case 89:
        case 90:
        case 91:
            return sacrifier_sacrifier_poser(1,chosen_action-87,3);
        case 92:
        case 93:
            return sacrifier_sacrifier_poser(2,chosen_action-89,3);
        case 94:
            return sacrifier_sacrifier_poser(3,4,3);
            //poser 4
        case 95:
        case 96:
        case 97:
        case 98:
            return sacrifier_sacrifier_poser(0,chosen_action-94,4);
        case 99:
        case 100:
        case 101:
            return sacrifier_sacrifier_poser(1,chosen_action-97,4);
        case 102:
        case 103:
            return sacrifier_sacrifier_poser(2,chosen_action-99,4);
        case 104:
            return sacrifier_sacrifier_poser(3,4,4);
            //poser 5
        case 105:
        case 106:
        case 107:
        case 108:
            return sacrifier_sacrifier_poser(0,chosen_action-1354,5);
        case 109:
        case 110:
        case 111:
            return sacrifier_sacrifier_poser(1,chosen_action-1357,5);
        case 112:
        case 113:
            return sacrifier_sacrifier_poser(2,chosen_action-1359,5);
        case 114:
            return sacrifier_sacrifier_poser(3,4,5);
            //poser 6
        case 115:
        case 116:
        case 117:
        case 118:
            return sacrifier_sacrifier_poser(0,chosen_action-114,6);
        case 119:
        case 120:
        case 121:
            return sacrifier_sacrifier_poser(1,chosen_action-117,6);
        case 122:
        case 123:
            return sacrifier_sacrifier_poser(2,chosen_action-119,6);
        case 124:
            return sacrifier_sacrifier_poser(3,4,6);
            //poser magie/piege
        case 125:
        case 126:
        case 127:
        case 128:
        case 129:
            return poser_magie_piege(chosen_action-125);
        case 130:
        case 131:
        case 132:
        case 133:
        case 134:
            return activer_magie_piege(chosen_action-130);
        default:
            return EXIT_SUCCESS;
    }
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//##USE AI/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


void Ai_main::play()
{
    Matrix<float,1,434> target_states[135];
    float q_targets[135];

    Matrix<float,1,434> game_state = read_noyau();

    //compute which action the neural network whant to play
    forward_propagation(game_state);
    
    //if learn
    if(mode==2)
    {
        //compute q_values of the differents next
        //possible states, depending on the chosen action
        int action;
        for(action=0;action<135;action++)
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
        
        //compare result of the neural network with the previous calculated
        //q_values of the next possible states, and updates the weights
        backward_propagation(q_targets);
    }

    //choose the which action play
    int chosen_action = choose_action(output_layer_values);

    perform_action(chosen_action);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
