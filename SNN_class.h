#ifndef SNN_CLASS_H
#define SNN_CLASS_H

#include <string.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "gradient.h"
#include "neuron.h"
#include "WFSP.h"

using namespace std;

class Adam;

class SNN{
public:

    void set();

    vector<vector<bool>> run_spikes (vector<vector<bool>> input);


    vector<int> run_values (vector<vector<bool>> input);


    void Loss_calc (vector<int> expected);


    void train_STDP (vector<vector<bool>> desired);

    void train_Adam (vector<int> loss_vec, double loss, vector<int> input, int time);

    void train_WFSP (vector<int> exp);

    void train_WFSP(vector<vector<bool>> exp);

    void train(vector<vector<int>> dataset, int epochs, vector<vector<int>> *exp = nullptr, vector<vector<vector<bool>>> *des = nullptr);

    vector<Layer> *get_layers();

    void set_optimizer (string opt);

    vector<vector<vector<double>>> *get_weights();

    vector<int> get_result();

    vector<vector<vector<bool>>> get_network_spikes();


private:
    vector<Layer> layers;
    vector<vector<vector<double>>> weights;
    vector<vector<vector<bool>>> network_spikes;
    vector<int> result;
    double loss;
    vector<int> loss_vec;
    string optimizer;
};

#endif
