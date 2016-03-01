
/*
TODO:
    - import network
    - create trainer
*/

#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "neural_network.hpp"

using namespace std;

int max_rounds = 1;
vector <int> nodes_per_layer = {2,2,2};

vector <double> inputs;
vector <double> outputs;
vector <double> expected_outputs;

// this is for x^2
int train_vals(int in)
{
    return pow(in,2);
}

void generate_values()
{
    inputs.clear();
    expected_outputs.clear();
    for (int a=0; a<nodes_per_layer.at(0); a++) {
        inputs.push_back(a);
    }
    for (int a=0; a<nodes_per_layer.at(nodes_per_layer.size()-1); a++) {
        expected_outputs.push_back(train_vals(a));
    }
}

int main()
{
    srand(time(NULL));
    cout << endl;
    
    network net;
    net.setup(nodes_per_layer);
    generate_values();
    
    int run = 0;
    //while (run < max_rounds) {
        outputs = net.cycle_network();
        net.export_weights_to_file();
        net.mutate();
        
        // find error
        double avg_error = 0;
        for (int a=0; a<outputs.size(); a++) {
            cout << "- out " << a << ": " << outputs.at(a) << endl;
            avg_error += expected_outputs.at(a) - outputs.at(a);
        } avg_error = avg_error/outputs.size();
        cout << "Average Error: " << avg_error << endl;
        cout << endl;
        
        //net.import_weights_from_file("weights.txt");
        outputs = net.cycle_network();
        
        // find error
        avg_error = 0;
        for (int a=0; a<outputs.size(); a++) {
            cout << "- out " << a << ": " << outputs.at(a) << endl;
            avg_error += expected_outputs.at(a) - outputs.at(a);
        } avg_error = avg_error/outputs.size();
        cout << "Average Error: " << avg_error << endl;
        cout << endl;
        
        run++;
    //}
    
    return 0;
}