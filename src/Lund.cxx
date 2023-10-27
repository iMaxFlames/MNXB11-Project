#include "../include/Lund.h"
void Lund() {
    
    // The following code reads the CSV file 
    string line;
    vector<string> DataStore;
    vector<string> Date;
    vector<string> Time;
    vector<double> Air_Temp;
    vector<string> Quality;

    ifstream file{"../datasets/rawdata_smhi-opendata_1_53430_20231007_155558_Lund.csv"};

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
    
    // Seeing what the different vector look like
    // for (int j = 0; j < 5; j++) {
    //     cout << Date[j] << " " << Time[j] << " " << Air_Temp[j] << " " <<  Quality[j] << endl;
    // }

    // Get data for the start and end of year 1986, because that is when Chernoboly disaster occured
    vector<string> year_1986;
    // vector<double> temp_1986;
    int length = Date.size();
    double temp_temp = 0;
    int target_year = 1986;
    vector<double> avg_temp;
    

    for (int j = 0; j < length; j++) {
        int current_year = std::stoi(Date[j]);
        if (current_year == target_year) {
            temp_temp += Air_Temp[j-1];
            if (Date[j][9] != Date[j-1][9]) {
                avg_temp.push_back(temp_temp/3);
                year_1986.push_back(Date[j-1]);
                temp_temp = 0;
        }
        }
    }
    int data_length = year_1986.size();
    int chernobyl_index;
    // Testing the extracted data for year 
    for (int j = 0; j < data_length; j++) {
        // cout << "Date " << year_1986[j] << " Avg Temp for that day " << avg_temp[j] << endl;
        if (year_1986[j] == "1986-04-26"){
            chernobyl_index = j;
        }
    }


    TH2D* hist2D = new TH2D("hist2D", "Daily Tempreature of Year 1986; Day of year; Temperature [#circC]", data_length, 0, 357, 50, -20, 30);

    for (int j = 0; j < 358; j++) {
        // if (i%30 == 0) {
        //     hist2D->GetXaxis()->SetBinLabel(i+1, Form("%d", date));
        // }
        hist2D->Fill(j, avg_temp[j]);
    }

    //vector<string> months{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    TCanvas* c2 = new TCanvas("c2", "2D Plot", 900, 600);
    gStyle->SetOptStat(0); //Removes the histogram info
    hist2D->SetMarkerStyle(20);
    hist2D->Draw();

    //cout << chernobyl_index << " " << year_1986[chernobyl_index] << " " << avg_temp[chernobyl_index] << endl;

}