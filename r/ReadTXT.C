#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "TH1D.h"
#include "TGraph.h"
#include "TDatime.h"
#include "TProfile.h"

void ReadData(const char* FileName)
{
    std::ifstream TXTFile(FileName);

    std::string line;
    double rate;

    std::vector<double> rateData;
    std::vector<double> timeData;

    TDatime iTime(2020,04,01,02,29,54);
    double t0 = iTime.Convert();
    t0-=3600*6; // UTC-6

    TH1D *DataHist = new TH1D("dh","Rates histogram",20,0,0);

    TProfile *aProfile = new TProfile("ap","A Profile",24,t0,t0+86400,"s");


    while( std::getline(TXTFile,line) )
    {
        try
        {
            rate = std::stod(line);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Non numeric value found. Skipping line" << '\n';
            continue;
        }

        DataHist->Fill(rate);
        aProfile->Fill(t0+=60,rate);
        rateData.push_back(rate);
        timeData.push_back(t0);
    }

    TGraph *aGraph = new TGraph(timeData.size(),timeData.data(),rateData.data());

    // DataHist->Draw();
    aProfile->GetXaxis()->SetTimeDisplay(1);
    aProfile->Draw();
    // aGraph->GetXaxis()->SetTimeDisplay(1);
    // aGraph->Draw();

}