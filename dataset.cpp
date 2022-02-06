#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>  

using namespace std;

class dataset{
public:
    string uid;
    int age;
    bool gender;
    int date;
    string event;
    
    void convert_date(){
        int t = date%100;
        date -= t;
        t = 100*t/12;
        date += t;
    };
};

vector<dataset> read_dts(string filename){
    fstream fin;
    fin.open("train.csv");
    vector<string> row;
    string line, temp, word;
    vector<dataset> ret;
    fin >> temp;
    while (fin >> temp){
        row.clear();
        stringstream s(temp);
        while (getline(s, word,',')) {
            row.push_back(word);
        }
        dataset med;
        med.uid = row[0];
        med.age = stoi(row[1]);
        med.gender = row[2] == "F";
        med.date = stoi(row[3]);
        med.event = row[4];
        med.convert_date();
        ret.push_back(med);
    }
    return ret;
}

template <typename T>
void split_dts(vector<T> dts, float percent){
    int size = dts.size(), test_size = dts.size()*percent;
    vector<T> test, train = dts;
    vector<int> rand_index;
    for (int i = 0; i < test_size; i++)
        rand_index.push_back(rand()/size);
    sort(rand_index.begin(), rand_index.end(), greater<int>());
    for (int i = 0; i < rand_index.size(); i++){
        test.push_back(dts[rand_index[i]]);
        train.erase(train.begin()+rand_index[i]);
    }
    pair<vector<T>, vector<T>> ret(train, test);
    return ret;
}

int main(){
    vector<dataset> dts = read_dts("train.csv");
    for (dataset d : dts)
        cout << d.age << endl;
}
