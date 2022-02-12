#include "neuron.h"
#include "Layer.h"


using namespace std;

Layer::Layer(int input_size, int size, int id){
    this->input_size = input_size;
    this->size = size;
    this->id = id;
    for (int i = 0; i < size; i++){
        vector<bool> temp;
        for (int i = 0; i < 128; i++)
            temp.push_back(0);
        spiketrain.push_back(temp);
    }
    for (int i = 0; i < size; i++){
        Neuron *cell = new Neuron;
        cell->set_id(make_pair(id,i));
        cell->set_input_size(input_size);
        neurons.push_back(*cell);
    }

}

void Layer::out_spikes(vector<vector<bool>> input_spikes){
    for (int i = 0; i < size; i++){
        spiketrain[i] = neurons[i].response(input_spikes);
    }
}

vector<vector<bool>> Layer::get_spikes(){
    return spiketrain;
}

void Layer::print(){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < 128; j++)
            cout << spiketrain[i][j];
        cout << endl;
    }
}

int Layer::get_input_size(){
    return input_size;
}

vector<Neuron> *Layer::get_neurons(){
    return &neurons;
}

int Layer::get_id(){
    return id;
}

int Layer::get_size(){
    return size;
}
