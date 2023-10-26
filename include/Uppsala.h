//#ifndef Uppsala_Guard
//#define Uppsala_Guard

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>

#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TGraph.h>
#include <TMultiGraph.h>

using namespace std;

void Data() {
    string line;
    vector<string> DataStore;
    vector<string> Date;
    vector<string> Time;
    vector<double> Air_Temp;
    vector<string> Quality;

    ifstream file{"../datasets/rawdata_smhi-opendata_1_97530_20231007_155803_Uppsala.csv"};

    while( getline(file, line, '\n') ) {
        
        istringstream sline(line);
        string word;

        while( getline(sline, word, ',') ) {
            DataStore.push_back(word);
        }
    }

    int i{0};
    while (i < DataStore.size()/4) {
        Date.push_back(DataStore[4*i]);
        Time.push_back(DataStore[4*i + 1]);
        auto Temp = atof(DataStore[4*i + 2].c_str());
        Air_Temp.push_back(Temp);
        Quality.push_back(DataStore[4*i + 3]);
        i += 1;
    }

    TH1D* graph = new TH1D("graph", "Data; T; Data Count", 100, -20, 30);

    double x[Date.size()];
    double y[Air_Temp.size()];
    for (int i=0; i < Date.size(); i++) {
        x[i] = i;
        y[i] = i;
        graph->Fill(Air_Temp[i]);
    }

    //auto g = new TGraph(100, Air_Temp, Air_Temp);
    TCanvas* c1 = new TCanvas("c1", "Plot", 900, 600);
    graph->SetMarkerStyle(20);
    graph->Draw();

    //for (unsigned int i=0; i < Date.size(); i++)
    //    cout << Air_Temp[i] << endl;
        //cout << Date[i] << endl;
    //    cout << Quality[i] << endl;
};

//#endif /*Uppsala_Guard*/