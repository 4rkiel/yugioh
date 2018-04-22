#include "../inc/ai_battle.h"


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
Ai_battle::Ai_battle(Noyau * noyau, int mode, int joueur)
{
    int i;
    srand (time(NULL));
    nb_hidden_layer = 2;
    this->mode = mode;
    this->noyau = noyau;
    this->joueur = joueur;
    load_ai();
    for(i=0;i<5;i++)
    {
        terrain_s_monstre[i]=NULL;
        terrain_a_monstre[i]=NULL;
        terrain_s_magie[i]=NULL;
        terrain_a_magie[i]=NULL;
        main[i]=NULL;
    }
    main[5]=NULL;
    main[6]=NULL;
}



//destructor
Ai_battle::~Ai_battle()
{
    if(mode==2) //learning_ai
        save_ai();
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//##LOAD AND SAVE AI///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//save the ai in a file according to the chosen mode
void Ai_battle::save_ai()
{
    int i,j,k;
    ofstream ai_file;
    switch(mode)
    {
        case 2:
            switch(joueur)
            {
                case 1:
                    ai_file.open("IA/learning_battle_ai_1.data");
                    break;
                case 2:
                    ai_file.open("IA/learning_battle_ai_2.data");
                    break;
            }
            break;
        case 1:
        default:
            switch(joueur)
            {
                case 1:
                    ai_file.open("IA/battle_ai_1.data");
                    break;
                case 2:
                    ai_file.open("IA/battle_ai_2.data");
                    break;
            }
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
            for(j=0;j<NB_OUTPUT_B;j++)
            {
                ai_file << output_weight(i,j) << " ";
            }
            ai_file << endl;
        }
        ai_file << endl;
        //save deltas
        for(i=0;i<NB_HIDDEN;i++)
        {
            for(j=0;j<NB_OUTPUT_B;j++)
            {
                ai_file << output_delta(i,j) << " ";
            }
            ai_file << endl;
        }
        ai_file << endl;
        //save values
        for(i=0;i<NB_OUTPUT_B;i++)
        {
            ai_file << output_layer_values(0,i) << " ";
        }
        ai_file << endl;
        ai_file << endl;
        //save test values
        for(i=0;i<NB_OUTPUT_B;i++)
        {
            ai_file << test_output_layer_values(0,i) << " ";
        }
        ai_file << endl;
        ai_file << endl;
        //////////////
        ai_file.close();
    }else{
        cout << "ERROR: open ai file" << endl;
    }
}



//load a trained AI from a file, according to the chosen difficulty
void Ai_battle::load_ai()
{
    int i,j,k;
    float number;
    ifstream ai_file;
    switch(mode)
    {
        case 2:
            switch(joueur)
            {
                case 1:
                    ai_file.open("IA/learning_battle_ai_1.data");
                    break;
                case 2:
                    ai_file.open("IA/learning_battle_ai_2.data");
                    break;
            }
            break;
        case 1:
        default:
            switch(joueur)
            {
                case 1:
                    ai_file.open("IA/battle_ai_1.data");
                    break;
                case 2:
                    ai_file.open("IA/battle_ai_2.data");
                    break;
            }
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
        }
        ////////////output layer//////////////
        //load weights
        for(i=0;i<NB_HIDDEN;i++)
        {
            for(j=0;j<NB_OUTPUT_B;j++)
            {
                ai_file >> number;
                output_weight(i,j) = number;
            }
        }
        //load deltas
        for(i=0;i<NB_HIDDEN;i++)
        {
            for(j=0;j<NB_OUTPUT_B;j++)
            {
                ai_file >> number;
                output_delta(i,j) = number;
            }
        }
        //load values
        for(i=0;i<NB_OUTPUT_B;i++)
        {
            ai_file >> number;
            output_layer_values(0,i) = number;
        }
        //load test values
        for(i=0;i<NB_OUTPUT_B;i++)
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


//##INITIALISE/////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//start a new not trained AI
void Ai_battle::initialise_random_ai()
{
    int i,j,k;
    srand(time(nullptr));
    /////////////input layer////////////////
    //initialise weights
    for(i=0;i<NB_INPUT;i++)
    {
        for(j=0;j<NB_HIDDEN;j++)
        {
            input_weight(i,j) = randomFloat(-0.01,0.01);
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
                new_weights_m(i,j) = randomFloat(-0.01,0.01);
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
        for(j=0;j<NB_OUTPUT_B;j++)
        {
            output_weight(i,j) = randomFloat(-0.01,0.01);
        }
    }
    //initialise deltas
    for(i=0;i<NB_HIDDEN;i++)
    {
        for(j=0;j<NB_OUTPUT_B;j++)
        {
            output_delta(i,j) = 0;
        }
    }
    //initialise values
    for(i=0;i<NB_OUTPUT_B;i++)
    {
        output_layer_values(0,i) = 0;
    }
    //initialise test values
    for(i=0;i<NB_OUTPUT_B;i++)
    {
        test_output_layer_values(0,i) = 0;
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
Matrix<float,1,200> Ai_battle::ReLU(Matrix<float,1,200> layer_values)
{
    Matrix <float,1,200> next_layer_input;
    int i;
    for(i=0;i<NB_HIDDEN;i++)
    {
        next_layer_input(0,i) = 1/(1+exp(-layer_values(0,i)));
    }
    return next_layer_input;
}


/*
 * softmax
 * activation function
 */
Matrix<float,1,3> Ai_battle::softmax(Matrix<float,1,3> layer_values)
{
    Matrix <float,Dynamic,Dynamic> next_layer_input(1,layer_values.cols());
    int i,j;
    float sum=0;
    for(j=0;j<NB_OUTPUT_B;j++)
    {
        sum += exp(layer_values(0,j));
    }
    for(i=0;i<NB_OUTPUT_B;i++)
    {
        next_layer_input(0,i) = exp(layer_values(0,i))/sum;
    }
    return next_layer_input;
}



/*
 * compute the actions' q_values vector
 * takes in input the game state
 * and outputs the vector of the actions do to
 */
void Ai_battle::forward_propagation(Matrix<float,1,434> game_state)
{
    input_layer_input = game_state;
    hidden_layers_input.clear();

    ////input layer////
    input_layer_values = input_layer_input * input_weight;
    hidden_layers_input.push_back(ReLU(input_layer_values));
    
    ////hidden layer 1////
    hidden_layers_values.at(0) = hidden_layers_input.at(0) * hidden_weights.at(0);
    hidden_layers_input.push_back(ReLU(hidden_layers_values.at(0)));

    ////hidden layer 2////
    hidden_layers_values.at(1) = hidden_layers_input.at(1) * hidden_weights.at(1);
    output_layer_input = ReLU(hidden_layers_values.at(1));

    ////output layer////
    output_layer_values = output_layer_input * output_weight;
    output_layer_values = softmax(output_layer_values);
}



/*
 * compute test actions' q_values vector
 * takes in input the future possible state
 * and outputs the vector of the actions it will be able to do
 */
void Ai_battle::test_forward_propagation(Matrix<float,1,434> game_state)
{
    test_input_layer_input = game_state;
    test_hidden_layers_input.clear();

    ////input layer////
    test_input_layer_values = test_input_layer_input * input_weight;
    test_hidden_layers_input.push_back(ReLU(test_input_layer_values));
    
    ////hidden layer 1////
    test_hidden_layers_values.at(0) = test_hidden_layers_input.at(0) * hidden_weights.at(0);
    test_hidden_layers_input.push_back(ReLU(test_hidden_layers_values.at(0)));

    ////hidden layer 2////
    test_hidden_layers_values.at(1) = test_hidden_layers_input.at(1) * hidden_weights.at(1);
    test_output_layer_input = ReLU(test_hidden_layers_values.at(1));

    ////output layer////
    test_output_layer_values = test_output_layer_input * output_weight;
    test_output_layer_values = softmax(test_output_layer_values);

}



/*
 * Choose the action to do, according to the actions' q_value calculated.
 * More an action has a big q_value, more it has chance to be chosen
 */
int Ai_battle::choose_action(Matrix<float,1,3> actions)
{
    srand (time(NULL));
    float choice = randomFloat(0,1);

    int action=0;
    while(choice>0)
    {
        if(action==3)
        {
            action=rand()%3;
            break;
        }
        choice -= actions(0,action);
        action++;
    }

    return action;
}



/*
 * compare the output of the neural network with the q_values of the
 * different next possible state, and update the weights of the neural
 * network
 */
void Ai_battle::backward_propagation(float q_targets[3])
{
    int i,j,k;
    float local_cost=0;
    float delta, udelta;
    float output;
    float sum=0,local_sum=0;

    //output_layer
    //for each neuron in the output layer
    for(i=0;i<output_weight.cols();i++)
    {
        //calcul local cost of this neuron
        output = output_layer_values(0,i);
        local_cost = (q_targets[i] - output) *
            output * (1 - output);
        //update the weights comming into this neuron from the previous
        //layer
        //for each synaps comming into the neuron
        for(j=0;j<output_weight.rows();j++)
        {
            //update the weight, according to the local cost and the
            //update delta at the previous backpropagation
            //update the delta value, etc
            delta=output_delta(j,i);
            udelta = local_cost * output_layer_input(0,i) + delta;
            output_weight(j,i) += udelta;
            output_delta(j,i) = udelta;
            sum += output_weight(j,i) * local_cost;
        }
    }

    /*
     * do the same as for the output layer, but now multiplicated by
     * the  sum of the previous localcost time the previous weights,
     * and this for all the neurons in all the hidden layers
     * so the cost is backpropagated to update all the neurons of the
     * network
     */
    for(i=hidden_weights.size()-1;i>=0;i--)
    {
        //cout << endl << "hidden layers ////////////////////////////////////" << endl << endl;
        for(j=0;j<hidden_weights.at(i).cols();j++)
        {
            output = hidden_layers_values.at(i)(0,j);
            local_cost = output * (1 - output) * sum;
            for(k=0;k<hidden_weights.at(i).rows();k++)
            {
                delta = hidden_deltas.at(i)(k,j);
                udelta = local_cost * hidden_layers_input.at(i)(0,j) + delta;
                hidden_weights.at(i)(k,j) += udelta;
                hidden_deltas.at(i)(k,j) = udelta;
                local_sum += hidden_weights.at(i)(k,j) * local_cost;
            }
        }
        sum = local_sum;
        local_sum=0;
    }

    //cout << endl << "output layers ////////////////////////////////////////" << endl << endl;
    //do the same as for the hidden layers, but now for the input layer
    for(i=0;i<input_weight.cols();i++)
    {
        output = input_layer_values(0,i);
        local_cost = output * (1 - output) * sum;
        
        for(j=0;j<input_weight.rows();j++)
        {
            delta = input_delta(j,i);
            udelta = local_cost * input_layer_input(0,i) + delta;
            //update weights
            input_weight(j,i) += udelta;
            input_delta(j,i) = udelta;
        }
    }
}

/*
 * test if the game state is a winning state, a losing state
 * or a neutral state
 */
int Ai_battle::test_win(Matrix<float,1,434> state)
{
    if(state(0,0)<=0.5)
        return -1;
    if(state(0,1)<=0.5)
        return 1;
    return 0;
}



//give the maximun q_value of the tested next state
float Ai_battle::max_output_test()
{
    float max_value=0;
    int i;
    for(i=0;i<NB_OUTPUT_B;i++)
    {
        max_value = max(max_value,test_output_layer_values(0,i));
    }
    return max_value;
}



//give the next game state, if the action is played
Matrix<float,1,434> Ai_battle::play_simulation(Matrix<float,1,434> game_state,
        int action)
{
    //TODO: connect to "Moteur"
    if(action)
    {
    }
    return game_state;
}



//function to calculate a random float between two floats
float Ai_battle::randomFloat(float a, float b)
{
    float random = a + ((float) rand()) / ((float) RAND_MAX / (b-a));
    return random;
}


//##NOYAU COMMUNICATION////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//function that read the "noyau", and put the game state in a matrix
Matrix<float,1,434> Ai_battle::read_noyau()
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
        if(i==10)
            j=76;
        if(i==15)
            j=83;
        
        //lecture de la carte
        tmp_card = noyau->trouver(j);
        
        //stockage dans la base de l'ia
        if(joueur == 1){
            if(i<5)
                terrain_s_monstre[i%5]=tmp_card;
            else if(i<10)
                terrain_s_magie[i%5]=tmp_card;
            else if(i<15)
                terrain_a_monstre[i%5]=tmp_card;
            else if(i<20)
                terrain_a_magie[i%5]=tmp_card;
        }
        else if(joueur == 2){
            if(i<5)
                terrain_a_monstre[i%5]=tmp_card;
            else if(i<10)
                terrain_a_magie[i%5]=tmp_card;
            else if(i<15)
                terrain_s_monstre[i%5]=tmp_card;
            else if(i<20)
                terrain_s_magie[i%5]=tmp_card;
        }
        
        // stocker dans le vecteur d'entrée du réseau neuronnal
        if(tmp_card!=NULL) {
            game_state(0,10+i*4) = tmp_card->atk;
            game_state(0,10+i*4+1) = tmp_card->def;
            game_state(0,10+i*4+2) = tmp_card->etat;
            game_state(0,10+i*4+3) = tmp_card->niveau;
        } else {
            game_state(0,10+i*4) = -1;
            game_state(0,10+i*4+1) = -1;
            game_state(0,10+i*4+2) = -1;
            game_state(0,10+i*4+3) = -1;
        }
        j++;
    }

    j=noyau->d1->size()-1;
    //chaque carte dans son propre deck
    for(i=0;i<60;i++)
    {
        if(j>=0)
        {
            if(noyau->d1!=NULL)
            {
                if(noyau->d1->at(j)!=NULL)
                {
                    game_state(0,94+i*5) = noyau->d1->at(i)->atk;
                    game_state(0,94+i*5+1) = noyau->d1->at(i)->def;
                    game_state(0,94+i*5+2) = noyau->d1->at(i)->niveau;
                    game_state(0,94+i*5+3) = noyau->d1->at(i)->position_deck;
                    game_state(0,94+i*5+4) = noyau->d1->at(i)->genre;
                } else
                {
                    game_state(0,94+i*5) = -1;
                    game_state(0,94+i*5+1) = -1;
                    game_state(0,94+i*5+2) = -1;
                    game_state(0,94+i*5+3) = -1;
                    game_state(0,94+i*5+4) = -1;
                }
            }
        } else {
            game_state(0,94+i*5) = -1;
            game_state(0,94+i*5+1) = -1;
            game_state(0,94+i*5+2) = -1;
            game_state(0,94+i*5+3) = -1;
            game_state(0,94+i*5+4) = -1;
        }
        j--;
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
    /*
    if(noyau->cimetiere1!=NULL && noyau->cimetiere1->back()!=NULL){
        game_state(0,431) = noyau->cimetiere1->back()->atk;
        game_state(0,432) = noyau->cimetiere1->back()->def;
        game_state(0,433) = noyau->cimetiere1->back()->niveau;
    }else{
    */
        game_state(0,431) = -1;
        game_state(0,432) = -1;
        game_state(0,433) = -1;
    //}

    return game_state;
}

//correspondance ID/terrein

int Ai_battle::main_id_to_x(int main_id)
{
    if(joueur==1)
        return main_id+14;
    if(joueur==2)
        return main_id+89;
    else
        return -1;
}

int Ai_battle::monstre_id_s_to_x(int monstre_id)
{
    if(joueur==1)
        return monstre_id+1;
    if(joueur==2)
        return monstre_id+76;
    else
        return -1;
}

int Ai_battle::monstre_id_a_to_x(int monstre_id)
{
    if(joueur==2)
        return monstre_id+1;
    if(joueur==1)
        return monstre_id+76;
    else
        return -1;
}

int Ai_battle::magie_piege_id_to_x(int magie_piege_id)
{
    if(joueur==1)
        return magie_piege_id+8;
    if(joueur==2)
        return magie_piege_id+83;
    else
        return -1;
}

//##SIGNALS////////////////////////////////////////////////////////////////////


int Ai_battle::activer_magie_piege()
{
    return EXIT_FAILURE;
    int magie_id=0;
    if(terrain_s_magie[magie_id]!=NULL)
    {
        signal_activate(magie_piege_id_to_x(magie_id));
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int Ai_battle::attaquer()
{
    int attaquant_id,cible_id;
    for(attaquant_id=0;attaquant_id<5;attaquant_id++)
    {
        for(cible_id=0;cible_id<5;cible_id++)
        {
            if(terrain_s_monstre[attaquant_id]!=NULL)
            {
                if(terrain_s_monstre[attaquant_id]->etat==0)
                {
                    if(terrain_a_monstre[cible_id]!=NULL)
                    {
                        signal_attaquer(monstre_id_s_to_x(attaquant_id),monstre_id_a_to_x(cible_id));
                        return EXIT_SUCCESS;
                    }
                }
            }
        }
    }
    return EXIT_FAILURE;
}


//emit signal appropriate to the action chosen by the ai if it works
//returns EXIT_SUCCESS if ti works
//else returns EXIT_FAILURE
int Ai_battle::perform_action(int chosen_action)
{
    switch(chosen_action)
    {
        case 0://passer
            return EXIT_SUCCESS;
        case 1:
        case 2:
            return attaquer();
        default:
            return EXIT_SUCCESS;
    }
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//##USE AI/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


void Ai_battle::play(int iter)
{
    iter++;
    Matrix<float,1,434> target_states[3];
    float q_targets[3];

    Matrix<float,1,434> game_state = read_noyau();

    //compute which action the neural network whant to play
    forward_propagation(game_state);
    
    //if learn
    if(mode==2)
    {
        //compute q_values of the differents next
        //possible states, depending on the chosen action
        int action;
        for(action=0;action<3;action++)
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
                q_targets[action] = 0; //bad reward
            }
            else
            {
                //compute the q_value of these states, according to th
                //futur possibles actions
                test_forward_propagation(target_states[action]);
                q_targets[action] = 0.007;//max_output_test();
            }
        }
    }

    //choose the which action play
    int chosen_action = choose_action(output_layer_values);

    cout << chosen_action << endl;
    if(perform_action(chosen_action)==EXIT_FAILURE)
    {
        q_targets[chosen_action] = 0;
        
        if(mode==2)
        {
            //compare result of the neural network with the previous calculated
            //q_values of the next possible states, and updates the weights
            backward_propagation(q_targets);
        }
        if(iter<5)
            play(iter);
        else
            perform_action(0);
    } else {
        if(mode==2)
        {
            //compare result of the neural network with the previous calculated
            //q_values of the next possible states, and updates the weights
            backward_propagation(q_targets);
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
