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

double find_median(vector<double> &arr)
{
    int size=arr.size();
    double median= size%2==0 ? (arr[(size/2)-1]+arr[(size/2)])/2:arr[size/2];
    return median;
}

void display_five_Number_Summary(double median,double Q1,double Q3,double lower_whisker,double higher_whisker,vector<double> &EduNum)
{
    double mini,maxi;
    for(int i=0;i<EduNum.size();i++)
    {
        if(EduNum[i]>=lower_whisker)
        {
            mini=EduNum[i];
            break;
        }
    }

    for(int i=EduNum.size()-1;i>=0;i--)
    {
        if(EduNum[i]<=higher_whisker)
        {
            maxi=EduNum[i];
            break;
        }
    }
    cout<<endl;
    cout<< "Lower Whisker: "<<lower_whisker<<endl;
    cout<< "Minimum: " << mini << endl;
    cout<< "Q1 (First Quartile): " << Q1 << endl;
    cout<< "Median: " << median << endl;
    cout<< "Q3 (Third Quartile): " << Q3 << endl;
    cout<< "Maximum: " << maxi << endl;
    cout<< "Higher Whisker: "<<higher_whisker<<endl;
}

void boxplot(vector<double> &EduNum)
{
    sort(EduNum.begin(),EduNum.end());
    int size=EduNum.size();
    double median= find_median(EduNum);
    vector<double> lefthalf(EduNum.begin(),EduNum.begin()+size/2);
    vector<double> righthalf(size%2==0 ? (EduNum.begin()+size/2) : (EduNum.begin()+size/2 +1),EduNum.end());
    double Q1=find_median(lefthalf);
    double Q3=find_median(righthalf);
    double IQR=Q3-Q1;
    double lower_whisker=Q1-(1.5*IQR);
    double higher_whisker=Q3+(1.5*IQR);

    display_five_Number_Summary(median,Q1,Q3,lower_whisker,higher_whisker,EduNum);
}

int main()
{
    string csv_file="data.csv";
    vector<vector<string>> vec=read_file(csv_file);
    cout << "CSV Data:" << endl;
    display_csv_file_content(vec);
    vector<double> EduNum;
    for(int i=1;i<vec.size();i++)
    {
        double ednum=stod(vec[i][2]);
        EduNum.push_back(ednum);
    }
    cout<<endl;

    boxplot(EduNum);

    return 0;
}
