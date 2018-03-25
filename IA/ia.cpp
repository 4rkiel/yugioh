#include <MiniDNN.h>


#include <Eigen/Core>
#include <vector>
#include <stdexcept>
#include "Config.h"
#include "RNG.h"
#include "Layer.h"
#include "Output.h"
#include "Callback.h"
#include "Utils/Random.h"

using namespace MiniDNN;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::VectorXd Vector;


    template <typename DerivedX, typename DerivedY>    
void play(Network net, Optimizer& opt,
        const Eigen::MatrixBase<DerivedX>& x,
        const Eigen::MatrixBase<DerivedY>& y,
        int batch_size)
{

    typedef typename Eigen::MatrixBase<DerivedX>::PlainObject PlainObjectX;
    typedef typename Eigen::MatrixBase<DerivedY>::PlainObject PlainObjectY;
    typedef Eigen::Matrix<typename PlainObjectX::Scalar, PlainObjectX::RowsAtCompileTime, PlainObjectX::ColsAtCompileTime> XType;
    typedef Eigen::Matrix<typename PlainObjectY::Scalar, PlainObjectY::RowsAtCompileTime, PlainObjectY::ColsAtCompileTime> YType;

    const int nlayer = net.num_layers();
    if(nlayer <= 0)
        return;

    opt.reset();

    std::vector<XType> x_batches;                                           
    std::vector<YType> y_batches;                                           
    const int nbatch = internal::create_shuffled_batches(x, y, batch_size, net.m_default_rng, x_batches, y_batches);

    // Train on each mini-batch
    for(int i = 0; i < nbatch; i++)
    {
        //play
        net.forward(x_batches[i]);
        const Output* output = net.get_output();
        Matrix action = output->backprop_data();

        //learn
        //net->backprop(x_batches[i], y_batches[i]);
        //net->update(opt);
    }

}



int main()
{
    int nb_game_input=50;
    int nb_1layer_neurons=100;
    int nb_2layer_neurons=100;
    int nb_actions_output=10;

    // Predictors -- each column is an observation
    Matrix x = Matrix::Random(100, 100);
    // Response variables -- each column is an observation
    Matrix y = Matrix::Random(100, 100);

    // Construct a network object
    Network net;

    // Create three layers
    // Layer 1 -- fully connected, input size nb_game_input, output size nb_1layer_neurons
    Layer* layer1 = new FullyConnected<ReLU>(nb_game_input, nb_1layer_neurons);
    // Layer 2 -- fully connected, input size nb_1layer_neurons, output size nb_2layer_nneurons
    Layer* layer2 = new FullyConnected<ReLU>(nb_1layer_neurons, nb_2layer_neurons);
    // Layer 3 -- fully connected, input size nb_2layer_neurons, output size nb_actions_output
    Layer* layer3 = new FullyConnected<ReLU>(nb_2layer_neurons, nb_actions_output);

    // Add layers to the network object
    net.add_layer(layer1);
    net.add_layer(layer2);
    net.add_layer(layer3);

    // Set output layer
    net.set_output(new RegressionMSE());

    // Create optimizer object
    RMSProp opt;
    opt.m_lrate = 0.001;

    // (Optional) set callback function object
    ////VerboseCallback callback;
    ////net.set_callback(callback);

    // Initialize parameters with N(0, 0.01^2) using random seed 123
    net.init(0, 0.01, 123);

    // Fit the model with a batch size of 100, running 10 epochs with random seed 123
    ////net.fit(opt, x, y, 100, 10, 123);

    // Obtain prediction -- each column is an observation
    ////Matrix pred = net.predict(x);

    // Layer objects will be freed by the network object,
    // so do not manually delete them
    
    int batch_size = 100;

    play(net,opt,x,y,batch_size);

    return 0;
}
