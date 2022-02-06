#ifndef GRADIENT_H
#define GRADIENT_H

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

vector<vector<double>> matrix_mul(vector<vector<double>> A, vector<vector<double>> B);

vector<vector<vector<double>>> partial_mult(vector<vector<vector<double>>> weights);
    
    
vector<vector<double>> grad_calc(vector<vector<double>> left, vector<vector<double>> right, pair<int,int> coord);


vector<double> grad (vector<vector<vector<double>>> weights, vector<int> loss, vector<int> input);

        

class Adam{
public:
    
    Adam();
    
    Adam(vector<vector<vector<double>>> *weights, double learning_rate = 0.1, double beta1 = 0.99, double beta2 = 0.999, int time = 0, double tolerance = 100, int loops = 100);
    
    void Adam_loop (vector<int> loss_vec, double loss, vector<int> input, int time = 0);
    
    
private:
    vector<vector<vector<double>>> *weights;
    vector<double> m;
    vector<double> u;
    double learning_rate;
    double beta1;
    double beta2;
    int time;
    double tolerance;
    int loops;
};


#endif
