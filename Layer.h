#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <unistd.h>
#include "neuron.h"

using namespace std;

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

#endif
