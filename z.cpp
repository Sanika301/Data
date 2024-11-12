#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
#include <stdexcept>

using namespace std;

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

vector<double> Z_Score_Normalisation(vector<double> &fnlwgt)
{
    vector<double> fnlwgt_normalized;
    double sum=0;
    for(int i=0;i<fnlwgt.size();i++)
    {
       sum+=fnlwgt[i];
    }

    double mean=(sum/fnlwgt.size());
    double sq_sum=0;

    for(int i=0;i<fnlwgt.size();i++)
    {
        sq_sum+=pow(fnlwgt[i]-mean,2);
    }
    double standad_deviation=sqrt(sq_sum/fnlwgt.size());

    for(int i=0;i<fnlwgt.size();i++)
    {
        double normalized_value=((fnlwgt[i]-mean)/(standad_deviation));
        fnlwgt_normalized.push_back(normalized_value);
    }

    return fnlwgt_normalized;
}

int main()
{
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
    vector<double> normalized_column=Z_Score_Normalisation(fnlwgt);
    for(int i=1;i<vec.size();i++)
    {
        vec[i][1]=to_string(normalized_column[i-1]);
    }

    display_csv_file_content(vec);
    return 0;
}
