#include "neuron.h"
#include "STDP.h"
#include "SNN_class.h"
#include "Layer.h"

using namespace std;


//Learning rate. Should be w dependent
double A = 0.001;

double delta_W (vector<bool> pre_synaptic, vector<bool> post_synaptic){
    double ret = 0;
    for (int i = 0; i < 128; i++){
        if (post_synaptic[i]){
            for (int j = 0; j < 128; j++){
                if (pre_synaptic[j])
                    if (i > j){
                        ret += A*log(1+exp((i-j)/128));
                    }
                    else{
                        ret -= A*log(1+exp((j-i)/128));
                    }
            }
        }
    }
    return ret;
}


vector<vector<double>> dw_neuron (Layer layer, vector<vector<vector<bool>>> network_spikes, vector<vector<bool>> *des){
    vector<vector<double>> ret;
    for (int i = 0; i < layer.get_input_size(); i++){
        vector<double> temp;
        for (Neuron cell : *layer.get_neurons()){
            if (des != nullptr)
                temp.push_back(delta_W(network_spikes[layer.get_id() - 1][i], (*des)[cell.get_id().second]));
            else{
                temp.push_back(delta_W(network_spikes[layer.get_id() - 1][i], cell.get_action_potential()));
                //cout << delta_W(network_spikes[layer.get_id() - 1][i], cell.get_action_potential()) << " " << i << endl;
              }
        }
        ret.push_back(temp);
    }
    return ret;
}


vector<vector<vector<double>>> W_diff (SNN Snn, vector<vector<bool>> desired){
    vector<vector<vector<double>>> ret;
    for (Layer layer : *Snn.get_layers()){
        if (layer.get_id() == Snn.get_layers()->size())
            ret.push_back(dw_neuron(layer, Snn.get_network_spikes(), &desired));
        else
            ret.push_back(dw_neuron(layer, Snn.get_network_spikes()));
    }
    return ret;
}

void STDP(SNN *SpikingN, vector<vector<bool>> desired){
    vector<vector<vector<double>>> d_w = W_diff(*SpikingN, desired);

    for (int i = 0; i < (*SpikingN).get_weights()->size(); i++)
        for (int j = 0; j < (*(*SpikingN).get_weights())[i].size(); j++)
            for (int k = 0; k < (*(*SpikingN).get_weights())[i][j].size(); k++)
                (*(*SpikingN).get_weights())[i][j][k] += d_w[i][j][k];
}
