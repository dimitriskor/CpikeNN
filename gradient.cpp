#include "neuron.h"
#include "gradient.h"
#include "SNN_class.h"

using namespace std;


vector<vector<double>> matrix_mul(vector<vector<double>> A, vector<vector<double>> B){
    int A_x = A.size();
    int A_y = A[0].size();
    int B_x = B.size();
    int B_y = B[0].size();
/*   
 *  if (A_y != B_x)
 *      return A;
*/         
    vector<vector<double>> C;
    
    for (int i = 0; i < A_x; i++){
        vector<double> temp;
        for (int j = 0; j < B_y; j++){
            double value = 0;
            for (int k = 0; k < A_y; k++)
                value += A[i][k] * B[k][j];
            temp.push_back(value);
        }
        C.push_back(temp);
    }
    
    return C;
}


vector<vector<vector<double>>> partial_mult(vector<vector<vector<double>>> weights){
    
    vector<vector<vector<double>>> ret;
    
    vector<vector<double>> I_m;
    for (int i = 0; i < weights[0].size(); i++){
        vector<double> temp;
        for (int j = 0; j < weights[0].size(); j++){
            if (i == j)
                temp.push_back(1.0);
            else
                temp.push_back(0.0);
        }
        I_m.push_back(temp);
    }
    
    ret.push_back(I_m);
    ret.push_back(weights[0]);
    
    for (int i = 0; i < weights.size() - 2; i++){
        vector<vector<double>> temp = ret[ret.size()-1];
        vector<vector<double>> to_add = matrix_mul(temp, weights[i]);
        ret.push_back(to_add);
    }
    
    ret.push_back(weights[weights.size()-1]);
    
    for (int i = weights.size() - 2; i > 0; i--){
        vector<vector<double>> temp = ret[ret.size()-1];
        vector<vector<double>> to_add = matrix_mul(weights[i], temp);
        ret.push_back(to_add);
    }
    
    return ret;
}
    
    
vector<vector<double>> grad_calc(vector<vector<double>> left, vector<vector<double>> right, pair<int,int> coord){
    double multiplier = right[coord.second][0];
    vector<vector<double>> ret;
    for (int i = 0; i < left.size(); i++){
        vector<double> temp;
        temp.push_back(left[i][coord.first]*multiplier);
        ret.push_back(temp);
    }
    return ret;
}


vector<double> grad (vector<vector<vector<double>>> weights, vector<int> loss, vector<int> input){
    
    vector<vector<vector<double>>> sub_weights = partial_mult(weights);
    vector<double> ret;
    
    for (int i = 0; i < weights.size(); i++){
         for (int j = 0; j < weights[i].size(); j++){
             for (int k = 0; k < weights[i][j].size(); k++){
                 vector<vector<double>> grad_val = grad_calc(sub_weights[i], sub_weights[sub_weights.size() - i - 1], make_pair(j,k));
                 double dw = 0;
                 vector<vector<double>> temp;
                 vector<double> t;
                 for (int val : input)
                     t.push_back(val*1.0);
                 temp.push_back(t);
                 vector<vector<double>> mult = matrix_mul(temp, grad_val);
                 for (int n = 0; n < mult[0].size(); n++){
                    dw += (mult[0][n]*loss[n]);
                 }
                 ret.push_back(dw);
             }
         }
    }
    return ret;
}
        


Adam::Adam(){
    this->learning_rate = 0.01;
    this->beta1 = 0.99;
    this->beta2 = 0.999;
    this->time = 0;
    this->tolerance = 100;
    this->loops = 100;
}

Adam::Adam(vector<vector<vector<double>>> *weights, double learning_rate, double beta1, double beta2, int time, double tolerance, int loops){
    this->learning_rate = learning_rate;
    this->beta1 = beta1;
    this->beta2 = beta2;
    this->time = time;
    this->weights = weights;
    this->tolerance = tolerance;
    this->loops = loops;
    int size = 0;
    for (vector<vector<double>> w : *weights)
        size += w.size()*w[0].size();
    for (int i = 0; i < size; i++){
        m.push_back(0.0);
        u.push_back(0.0);
    }
}
    


void Adam::Adam_loop (vector<int> loss_vec, double loss, vector<int> input, int time){
    this->time = time;
    vector<double> gradient = grad(*weights, loss_vec, input);
    int x = 0, y = 0, z = 0;
    for (int i = 0; i < m.size(); i++){
        m[i] = beta1*m[i] + (1 - beta1)*gradient[i]*loss;
        u[i] = beta2*u[i] + (1 - beta2)*pow(gradient[i]*loss,2);
        if (x >= (*weights)[z][y].size()){
            if (y+1 >= (*weights)[z].size()){
                z += 1;
                x = y = 0;
            }
            else{
                y += 1;
                x = 0;
            }
            i -= 1;
        }
        else{
            double dd =learning_rate*m[i]/(1-pow(beta1,time+1))/((sqrt(u[i]+1)/1-pow(beta2,time+1))+1);
            (*weights)[z][y][x] -= dd;
            x += 1;
        }
    }
}




