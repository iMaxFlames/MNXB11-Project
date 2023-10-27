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

    //TH1D* graph = new TH1D("graph", "Data; T; Data Count", 50, -20, 30);

    //double x[Date.size()];
    //double y[Date.size()];
    for (int i=0; i < Date.size(); i++) {
        //x[i] = i;
        //y[i] = i;
        //graph->Fill(Air_Temp[i]);
    }
    int size_date = Date.size();
    //auto g = new TGraph(size_date, x, y);
    TCanvas* c1 = new TCanvas("c1", "Plot", 900, 600);
    //graph->SetMarkerStyle(20);
    //graph->Draw();
    //g->Draw();

    //int j[Date.size()/1000];
    //for (int i=0; i < Date.size()/1000; i++) {
    //    j[i] = i;
    //}

    vector<double> Avg_Temp;
    double Temp_Temp{0};
    int prev_j{0};
    for (int j=1; j < Date.size(); j++) {
        Temp_Temp += Air_Temp[j];
        if (Date[j][3] != Date[j-1][3]) {
            Avg_Temp.push_back(Temp_Temp/(j-prev_j));
            Temp_Temp = 0;
            prev_j = j;
        }
    }

    TH2D* ggraph = new TH2D("ggraph", "Data; Date; Temp", Avg_Temp.size(), 0, Avg_Temp.size(), 50, 2, 8);

    for (int i=0; i < Avg_Temp.size(); i++) {
        ggraph->Fill(i, Avg_Temp[i]);
    }

    ggraph->SetMarkerStyle(20);
    ggraph->Draw();

    for (unsigned int i=0; i < Avg_Temp.size(); i++)
        cout << Avg_Temp[i] << endl;
    //    cout << Air_Temp[i] << endl;
        //cout << Date[i] << endl;
    //    cout << Quality[i] << endl;
};

//#endif /*Uppsala_Guard*/