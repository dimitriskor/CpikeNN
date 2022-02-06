#ifndef WFSP_H
#define WFSP_H

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

class SNN;

void WFSP (SNN *Network, vector<int> expected);

void WFSP (SNN *Network, vector<vector<bool>> expected);


double dw (vector<bool> fire, vector<bool> desired, vector<bool> input, double w, bool enable);

double df (vector<double> dw);


vector<bool> Neuron_des (vector<bool> spiketrain, vector<double> dw);

vector<vector<double>> Layer_dw (vector<vector<bool>> in_spikes, vector<vector<bool>> out_spikes, vector<vector<double>> weights, vector<vector<bool>> desired, bool enable);

vector<vector<bool>> Layer_df (vector<vector<bool>> spikes, vector<vector<double>> d_weights);


#endif
