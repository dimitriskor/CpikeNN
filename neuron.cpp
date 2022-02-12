#include "neuron.h"

using namespace std;

Neuron::Neuron (double state, double threshold, pair<int,int> id, int input_size, vector<double> weights, int last_spike){
    this->state = state;
    this->threshold = threshold;
    this->id = id;
    this->input_size = input_size;
    this->weight = weights;
    this->last_spike = last_spike;
    for (int i = 0; i < 128; i++){
        this->action_potential.push_back(0);
    }
}

Neuron::Neuron (){
    this->state = 0;
    this->threshold = 1.75;
    this->id = make_pair(1,1);
    this->input_size = 10;
    for (int i = 0; i < 10; i++){
        this->weight.push_back((rand()%1000)/1000.0);
    }
    this->last_spike = 0;
    for (int i = 0; i < 128; i++){
        this->action_potential.push_back(0);
    }
}


void Neuron::set_id(pair<int,int> id){
    this->id = id;
}

void Neuron::set_input_size(int size){
    this->input_size = size;
    this->weight.clear();
    for (int i = 0; i < size; i++){
        this->weight.push_back((rand()%1000)/1000.0);
    }
}

vector<bool> Neuron::response(vector<vector<bool>> spiketrain){
    for (int i = 0; i < 128; i++){
        double sum = 0;
        for (int j = 0; j < input_size; j++){
            sum += spiketrain[j][i]*weight[j];
        }
        if (sum != 0){
            state = state*exp(-(i-last_spike)/2) + sum;
            if (state > threshold){
                state = 0.0;
                last_spike = i;
                action_potential[i] = 1;
            }
            else{
                action_potential[i] = 0;
            }
        }
        else{
            action_potential[i] = 0;
        }
    }
    return action_potential;
}

pair<int,int> Neuron::get_id(){
    return id;
}

vector<bool> Neuron::get_action_potential(){
    return action_potential;
}

vector<double> *Neuron::get_weight(){
    return &weight;
}



vector<vector<bool>> encode(vector<int> input){
    srand(time(nullptr));
    vector<vector<bool>> output;
    for (int i = 0; i < input.size(); i++){
        vector<bool> temp;
        for (int j = 0; j < 128; j++){
            temp.push_back(input[i] + rand()%256 >= 256);
        }
        output.push_back(temp);
    }
    return output;
}

vector<vector<bool>> encode_rate(vector<int> input){
    vector<vector<bool>> output;
    for (int i = 0; i < input.size(); i++){
        vector<bool> temp;
        double rate = 256.0/(input[i]+1);
        double t = 1;
        for (int j = 0; j < 128; j++){
            if (t < rate)
                temp.push_back(0);
            else{
                temp.push_back(1);
                t -= rate;
            }
            t+=1;
        }
        output.push_back(temp);
    }
    return output;
}

vector<int> decode(vector<vector<bool>> input){
    vector<int> output;
    for (int i = 0; i < input.size(); i++){
        int sum = 0;
        for (int j = 0; j < 128; j++){
            sum += 2*input[i][j];
        }
        output.push_back(sum);
    }
    return output;
}
