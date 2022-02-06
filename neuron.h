#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <unistd.h>

using namespace std;

class Neuron{
public:
    Neuron (double state, double threshold, pair<int,int> id, int input_size, vector<double> weights, int last_spike);

    Neuron ();


    void set_id(pair<int,int> id);

    void set_input_size(int size);

    vector<bool> response(vector<vector<bool>> spiketrain);

    pair<int,int> get_id();

    vector<bool> get_action_potential();

    vector<double> *get_weight();

private:
    double state;
    double threshold;
    pair<int,int> id;
    int input_size;
    vector<double> weight;
    int last_spike;
    vector<bool> action_potential;
};



class Layer{
public:
    Layer(int input_size = 10, int size = 2, int id = 1);

    void out_spikes(vector<vector<bool>> input_spikes);

    vector<vector<bool>> get_spikes();

    void print();

    int get_input_size();

    vector<Neuron> *get_neurons();

    int get_id();

    int get_size();


private:
    int size;
    int input_size;
    int id;
    vector<Neuron> neurons;
    vector<vector<bool>> spiketrain;

};



vector<vector<bool>> encode(vector<int> input);

vector<vector<bool>> encode_rate(vector<int> input);

vector<int> decode(vector<vector<bool>> input);


#endif
