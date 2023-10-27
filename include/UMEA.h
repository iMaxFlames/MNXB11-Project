//#ifndef Uppsala_Guard
//#define Uppsala_Guard

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>

#include <TF1.h> // 1d function class
#include <TH2D.h>
#include <TMultiGraph.h>

using namespace std;

void Data() {
    string line;
    vector<string> DataStore;
    vector<string> Date;
    vector<string> Time;
    vector<double> Air_Temp;

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
        i += 1;
    }

    int size_date = Date.size();
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

    Double_t minYear = stod(year_avg[0]);
    Double_t maxYear = stod(year_avg[year_avg.size() - 1]);
    int size = avg_temp.size();

    TH2D* hist2D = new TH2D("hist2D", "Average temperature each year; Year; Average Temp", size, minYear, maxYear, 50, 0, 6);

    for (int i = 0; i < size; i++) {
        int year = std::stoi(year_avg[i]);
        if (i%10 == 0) {
            hist2D->GetXaxis()->SetBinLabel(i+1, Form("%d", year));
        }
        double yValue = avg_temp[i];
        hist2D->Fill(year, yValue);
    }

    vector<Double_t> year_values;
    for (const auto& year : year_avg) {
        year_values.push_back(stod(year));
    }

    TGraphErrors* linearFitGraph = new TGraphErrors(size, year_values.data(), &avg_temp[0]);
    TF1* linearFit = new TF1("linearFit", "[0]+[1]*x", minYear, maxYear);


    linearFitGraph->Fit(linearFit, "Q");

    double intercept = linearFit->GetParameter(0);
    double slope = linearFit->GetParameter(1);

    cout << "Linear Fit Results:" << endl;
    cout << "Intercept: " << intercept << endl;
    cout << "Slope: " << slope << endl;

    for (int i = 0; i < size; i++) {
        double x = stod(year_avg[i]);
        double y = linearFit->Eval(x);
        linearFitGraph->SetPoint(i, x, y);
    }

    // Create a canvas and draw the 2D histogram
    TCanvas* c2 = new TCanvas("c2", "2D Plot", 900, 600);
    gStyle->SetOptStat(0); //Removes the histogram info
    hist2D->SetMarkerStyle(20);
    hist2D->Draw();

    linearFitGraph->SetLineColor(kRed);
    linearFitGraph->Draw("L");

};

//#endif /*Uppsala_Guard*/