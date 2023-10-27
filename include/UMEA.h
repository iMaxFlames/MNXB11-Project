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
#include <TH2D.h>
#include <TMultiGraph.h>

using namespace std;

void Data() {
    string line;
    vector<string> DataStore;
    vector<string> Date;
    vector<string> Time;
    vector<double> Air_Temp;
    vector<string> Quality;

    ifstream file{"../datasets/rawdata_smhi-opendata_1_140480_20231007_155326_Umea.csv"};

    while( getline(file, line, '\n') ) {
        
        istringstream sline(line);
        string word;

        while( getline(sline, word, ' ') ) {
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

    TH1D* graph = new TH1D("graph", "Data; T; Data Count", 50, -20, 30);

    
    
    for (int i=0; i < Date.size(); i++) {
        graph->Fill(Air_Temp[i]);
    }

    int size_date = Date.size();
    /*TCanvas* c1 = new TCanvas("c1", "Plot", 900, 600);
    graph->SetMarkerStyle(20);
    graph->Draw();
    */
    
    vector<double> avg_temp;
    double temp_temp = 0;
    vector<string> year_avg;
    vector<int> indices;
    int prev_j = 0;
    for (int j = 1; j < Date.size(); j++) {
        temp_temp += Air_Temp[j];
        if (Date[j][3] != Date[j-1][3]) {
            avg_temp.push_back(temp_temp/(j-prev_j));
            year_avg.push_back(Date[j]);
            indices.push_back(j);
            temp_temp = 0;
            prev_j = j;
        }
    }

    TH2D* hist2D = new TH2D("hist2D", "2D Plot; Year; Average Temp", year_avg.size(), 0, year_avg.size(), 50, 0, 6);

    for (int i = 0; i < avg_temp.size(); i++) {
        // Convert Date to a numerical value for the x-axis (e.g., you can use the index i here)
        double xValue = i;
        // Air_Temp is used for the y-axis
        double yValue = avg_temp[i];

        // Fill the 2D histogram
        hist2D->Fill(xValue, yValue);
    }

    // Create a canvas and draw the 2D histogram
    TCanvas* c2 = new TCanvas("c2", "2D Plot", 900, 600);
    gStyle->SetPalette(1); // Set color palette (optional)

    hist2D->Draw("colz"); // "colz" indicates to draw a 2D color plot

    delete graph;
/*
    for (unsigned int i=0; i < avg_temp.size(); i++) {
        cout << avg_temp[i] << endl;
        cout << year_avg[i] << endl;
        cout << Air_Temp[i] << endl;
        cout << Date[i] << endl;
        cout << Quality[i] << endl;
    }*/
};

//#endif /*Uppsala_Guard*/