#ifndef STDP_H
#define STDP_H

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <unistd.h>
#include "neuron.h"

using namespace std;


class SNN;


//Learning rate. Should be w dependent
double delta_W (vector<bool> pre_synaptic, vector<bool> post_synaptic);


vector<vector<double>> dw_neuron (Layer layer, vector<vector<vector<bool>>> network_spikes, vector<vector<bool>> *des = nullptr);


vector<vector<vector<double>>> W_diff (SNN Snn, vector<vector<bool>> desired);

void STDP(SNN *SpikingN, vector<vector<bool>> desired);

#endif
