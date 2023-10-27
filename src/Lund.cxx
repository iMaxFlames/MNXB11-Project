#include "../include/Lund.h"
void Lund() {
    
    // ================== The following code reads the cleaned CSV file =========================
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
    // ==========================================================================================

    // Seeing what the different vector look like
    // for (int j = 0; j < 5; j++) {
    //     cout << Date[j] << " " << Time[j] << " " << Air_Temp[j] << " " <<  Quality[j] << endl;
    // }

    // ===================== Extract data correspoinding to year 1986 =============================

    vector<string> year_1986; // This is where we want to store all the dates for the year 1986
    int length = Date.size(); 
    double temp_temp = 0; // Temparary varible used for taking averages of daily temp.
    int target_year = 1986;
    vector<double> avg_temp; // This is where we want to store all the daily avg temperatures
    
    // Loops through the Date vector (which contains all the dates) and takes the avg of the daily temperatures
    // if that day is in the year 1986. For each day we have three measurements thus the avg divides by 3.
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
    int chernobyl_index; // The index in our extracted data that corresponds to day of Chernobyl disaster
    // Testing the extracted data for year 
    for (int j = 0; j < data_length; j++) {
        // cout << "Date " << year_1986[j] << " Avg Temp for that day " << avg_temp[j] << endl;
        if (year_1986[j] == "1986-04-26"){
            chernobyl_index = j;
        }
    }
    // ============================================================================================


    // ============================== Making the plot ===============================================
    
    // Creating empty histogram
    TH2D* hist2D = new TH2D("hist2D", "Daily Temperature of Year 1986; Day of year; Temperature [#circC]", data_length, 0, 357, 50, -20, 30);

    // Filling the histogram with extracted data
    for (int j = 0; j < 358; j++) {
        hist2D->Fill(j, avg_temp[j]);
    }

    // Plotting the histogram on a canvas
    TCanvas* c2 = new TCanvas("c2", "2D Plot", 900, 600);
    gStyle->SetOptStat(0); //Removes the histogram info
    hist2D->SetMarkerStyle(20);
    hist2D->Draw();

    // ===============================================================================================
}