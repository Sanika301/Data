#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
#include <stdexcept>

using namespace std;
double newmax,newmin;

vector<vector<string>> read_file(string &csv_file)
{
    ifstream csv(csv_file);
    vector<vector<string>> vec;
    string line;
    while(getline(csv,line))
    {
        stringstream ss(line);
        string word;
        vector<string> row;

        while(getline(ss,word,','))
        {
            row.push_back(word);
        }
        vec.push_back(row);
    }
    return vec;
}

void display_csv_file_content(vector<vector<string>> &vec)
{
    for(int i=0;i<vec.size();i++)
    {
        for(int j=0;j<vec[i].size();j++)
        {
            cout<<vec[i][j]<<"\t";
        }
        cout<<endl;
    }
}

vector<double> Min_Max_normalization(vector<double> &fnlwgt)
{
    vector<double> fnlwgt_normalized;
    double mini=numeric_limits<double>::max();
    double maxi=numeric_limits<double>::lowest();

    for(int i=0;i<fnlwgt.size();i++)
    {
        mini= fnlwgt[i]<mini? fnlwgt[i]:mini;
        maxi= fnlwgt[i]>maxi? fnlwgt[i]:maxi;
    }

    for(int i=0;i<fnlwgt.size();i++)
    {
        double normalized_value=((fnlwgt[i]-mini)/(maxi-mini))*(newmax-newmin)+newmin;
        fnlwgt_normalized.push_back(normalized_value);
    }

    return fnlwgt_normalized;
}

int main()
{
    double newMax,newMin;
    cout<<"Enter the range to which you want to normalize:NewMin: ";
    cin>>newMin;
    cout<<"NewMax: ";
    cin>>newMax;
    newmin=newMin;
    newmax=newMax;
    string csv_file="data.csv";
    vector<vector<string>> vec=read_file(csv_file);
    cout << "CSV Data:" << endl;
    display_csv_file_content(vec);
    vector<double> fnlwgt;
    for(int i=1;i<vec.size();i++)
    {
        double wgt=stod(vec[i][1]);
        fnlwgt.push_back(wgt);
    }
    cout<<endl;
    vector<double> normalized_column=Min_Max_normalization(fnlwgt);
    for(int i=1;i<vec.size();i++)
    {
        vec[i][1]=to_string(normalized_column[i-1]);
    }

    display_csv_file_content(vec);
    return 0;
}
