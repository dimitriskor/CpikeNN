#include "WFSP.h"
#include "SNN_class.h"
#include "neuron.h"
#include "Layer.h"

using namespace std;

double l_r_w = 0.0001;
double l_r_f = 1;

void WFSP (SNN *Network, vector<int> expected){
    WFSP(Network, encode_rate(expected));
}

void WFSP (SNN *Network, vector<vector<bool>> expected){
    vector<vector<bool>> temp_df;
    vector<vector<vector<double>>> Net_dw;
    bool enable = true;                                                                                             //enable var controls if the last input spikes contribute. Should be set true only for last layer
    for (int i = Network->get_weights()->size() - 1; i >= 0; i--){
        Net_dw.push_back(Layer_dw(Network->get_network_spikes()[i], Network->get_network_spikes()[i+1], (*Network->get_weights())[i], expected, enable));
        temp_df = Layer_df(Network->get_network_spikes()[i], Net_dw[Net_dw.size()-1]);
        expected = temp_df;
        enable = false;
    }
    std::reverse(Net_dw.begin(), Net_dw.end());
    for (int i = 0; i < (*Network).get_weights()->size(); i++)
        for (int j = 0; j < (*(*Network).get_weights())[i].size(); j++)
            for (int k = 0; k < (*(*Network).get_weights())[i][j].size(); k++)
                (*(*Network).get_weights())[i][j][k] += Net_dw[i][j][k];
}



double dw (vector<bool> fire, vector<bool> desired, vector<bool> input, double w, bool enable){                              //maybe to consider input spikes after the last spike
    double ret = 0;
    int last_f = 0;
    for (int i = 0; i < desired.size(); i++){
        if (desired[i]){
            for (int j = last_f; j < fire.size(); j++){
                if (fire[j] || j+1 == fire.size()){
                    for (int k = last_f; k <= j; k++){
                        if (input[k]){
                            if (j+1 == fire.size() && !fire[j])
                                ret += exp(k-j-1)*w*(j+1-i);
                            else
                                ret += exp(k-j)*w*(j-i);
                        }
                    }
                    last_f = j+1;
                    break;
                }
            }
        }
    }
    if (last_f < fire.size()){
        for (int i = last_f; i < fire.size(); i++){
            if (fire[i]){
                for (int j = last_f; j <= i; j++){
                    if (input[j]){
                        ret -= exp(j-i)*w;
                    }
                }
                last_f = i+1;
            }
        }
        if (last_f < fire.size() && enable){
            for (int i = last_f; i < input.size(); i++){
                if (input[i]){
                    int d = i - input.size();                                                                   //g++ bug
                    ret -= exp(d)*w;
                }
            }
        }
    }
    return tanh(ret*l_r_w);
}


double df (vector<double> dw){
    double ret = 0;
    for (double w : dw)
        ret -= w;
    return l_r_f*ret;
}



vector<bool> Neuron_des (vector<bool> spiketrain, vector<double> dw){
    double d_freq = df(dw);
    vector<bool> ret;
    for (int i = 0; i < spiketrain.size(); i++)
        ret.push_back(0);
    for (int i = 0; i < spiketrain.size(); i++){
        if (spiketrain[i]){
            if (round(i*(1+0.9*d_freq)) >= spiketrain.size())
                continue;
            ret[round(i*(1+0.9*d_freq))] = true;
        }
    }
    return ret;
}



vector<vector<double>> Layer_dw (vector<vector<bool>> in_spikes, vector<vector<bool>> out_spikes, vector<vector<double>> weights, vector<vector<bool>> desired, bool enable){
    vector<vector<double>> ret;
    for (int i = 0; i < in_spikes.size(); i++){
        vector<double> temp;
        for (int j = 0; j < out_spikes.size(); j++){
            temp.push_back(dw(out_spikes[j], desired[j], in_spikes[i], weights[i][j], enable));
        }
        ret.push_back(temp);
    }
    return ret;
}


vector<vector<bool>> Layer_df (vector<vector<bool>> spikes, vector<vector<double>> d_weights){
    vector<vector<bool>> ret;
    for (int i = 0; i < spikes.size(); i++){
        ret.push_back(Neuron_des(spikes[i], d_weights[i]));
    }
    return ret;
}
