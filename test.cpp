#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include "gradient.h"
#include "neuron.h"
#include "SNN_class.h"
#include "STDP.h"
#include "WFSP.h"
#include "Layer.h"

using namespace std;

int main() {
    vector<int> in = {220,52,200,1,2,10,24,15,1,2};
    vector<int> in1 = {255};
    vector<int> out = {2,2,1,1,9,10,2,185,200,200};
    vector<int> out1 = {10};
    SNN test;
    Layer l1(10,1,1);
    //Layer l3(6,4,3);
    //Layer l4(2,2,3);

    test.get_layers()->push_back(l1);
    //test.get_layers()->push_back(l2);
    //test.get_layers()->push_back(l3);
    //test.layers.push_back(l4);

    test.set_optimizer("STDP");
    test.set();
    vector<vector<int>> dts;
    vector<vector<vector<bool>>> exp;
    vector<vector<bool>> in11 = encode(in1);
    vector<vector<bool>> out11 = encode(out1);
    dts.push_back(in);
    dts.push_back(out);
    exp.push_back(in11);
    exp.push_back(out11);
    for(vector<double> res : (*test.get_weights())[0]){
            for (double r : res)
                cout << r << " ";

            cout << endl;
        }
    cout << endl;

    while(1){
        test.train(dts,100,nullptr,&exp);
        /*for(vector<double> res : (*test.get_weights())[0]){
           for (double r : res)
               cout << r << " ";

           cout << endl;
        }*/
        cout << endl;
        test.train(dts,100,nullptr,&exp);

        test.run_values(encode_rate(dts[0]));
        for(double res : test.get_result())
           cout << res << " ";
        cout << endl;
        test.run_values(encode_rate(dts[1]));
        for(double res : test.get_result())
        cout << res << " ";
        cout << endl;
        cout << endl;

    }

}
