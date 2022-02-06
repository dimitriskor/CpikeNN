#include "neuron.h"
#include "SNN_class.h"
#include "STDP.h"
#include "gradient.h"

using namespace std;

void SNN::set(){
    for (Layer l : layers){
        vector<vector<double>> array;
        for (int i = 0; i < l.get_input_size(); i++){
            vector<double> row;
            for (Neuron cell : *l.get_neurons()){
                row.push_back((*cell.get_weight())[i]);
            }
            array.push_back(row);
        }
        weights.push_back(array);
    }
}

vector<vector<bool>> SNN::run_spikes (vector<vector<bool>> input){
    vector<vector<bool>> spikes = input;
    network_spikes.clear();
    network_spikes.push_back(spikes);
    for (Layer frw : layers){
        frw.out_spikes(spikes);
        spikes = frw.get_spikes();
        network_spikes.push_back(spikes);
    }
    return spikes;
}


vector<int> SNN::run_values (vector<vector<bool>> input){
    vector<vector<bool>> spikes = run_spikes(input);
    result = decode(spikes);
    return result;
}


void SNN::Loss_calc (vector<int> expected){
    double sum = 0;
    vector<int> ret;
    for (int i = 0; i < expected.size(); i++){
        sum += pow((result[i] - expected[i]),2);
        ret.push_back(result[i] - expected[i]);
    }
    loss = sqrt(sum);
    loss_vec = ret;
}


void SNN::train_STDP(vector<vector<bool>> desired){
    STDP(this, desired);
}

void SNN::train_Adam (vector<int> loss_vec, double loss, vector<int> input, int time){
    Adam ADAM(&weights);
    ADAM.Adam_loop(loss_vec, loss, input, time);
}

void SNN::train_WFSP(vector<int> exp){
    WFSP(this, exp);
}

void SNN::train_WFSP(vector<vector<bool>> exp){
    WFSP(this, exp);
}

void SNN::train(vector<vector<int>> dataset, int epochs, vector<vector<int>> *exp, vector<vector<vector<bool>>> *des){
    for (int i = 0; i < epochs; i++){
        int rnd = rand()%dataset.size();
        vector<int> input = dataset[rnd];
        if (optimizer == "Adam"){
            run_values(encode_rate(input));
            Loss_calc((*exp)[rnd]);
            train_Adam(loss_vec, loss, input, i);
        }
        else if (optimizer == "STDP"){
            run_spikes(encode(input));
            train_STDP((*des)[rnd]);
        }
        else if (optimizer == "WFSP"){
            run_spikes(encode_rate(input));
            train_WFSP((*exp)[rnd]);
        }
        for (int n = 0; n < layers.size(); n++)
            for (int j = 0; j < layers[n].get_input_size(); j++)
                for (int k = 0; k < layers[n].get_size(); k++)
                    (*(*layers[n].get_neurons())[k].get_weight())[j] = weights[n][j][k];
    }
}

vector<Layer> *SNN::get_layers(){
    return &layers;
}

void SNN::set_optimizer (string opt){
    optimizer = opt;
}

vector<vector<vector<double>>> *SNN::get_weights(){
    return &weights;
}

vector<int> SNN::get_result(){
    return result;
}

vector<vector<vector<bool>>> SNN::get_network_spikes(){
    return network_spikes;
}
