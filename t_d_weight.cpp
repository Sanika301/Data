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

void display_t_weight(vector<vector<int>> &count_row)
{
    vector<vector<double>> t_weight;
    for(int i=0;i<count_row.size();i++)
    {
        int last=count_row[i].size()-1;
        int total=count_row[i][last];
        vector<double> t_weight_row;
        for(int j=0;j<=last;j++)
        {
            double p=((double)count_row[i][j]/total)*100.0;
            t_weight_row.push_back(p);
        }
        t_weight.push_back(t_weight_row);
    }

    map<int,string> t_mp;
    t_mp[0]="MP";
    t_mp[1]="UP";
    t_mp[2]="Goa";

    cout<<endl;
    cout<<"T-Weight"<<endl;
    for(int i=0;i<t_weight.size();i++)
    {
        cout<<t_mp[i]<<": \t";
        for(int j=0;j<t_weight[i].size();j++)
        {
            cout<<t_weight[i][j]<<"% ";
        }
        cout<<endl;
    }
}

void display_d_weight(vector<vector<int>> &count_col)
{
    vector<vector<double>> d_weight;
    for(int i=0;i<count_col.size();i++)
    {
        int last=count_col[i].size()-1;
        int total=count_col[i][last];
        vector<double> d_weight_row;
        for(int j=0;j<=last;j++)
        {
            double p=((double)count_col[i][j]/total)*100.0;
            d_weight_row.push_back(p);
        }
        d_weight.push_back(d_weight_row);
    }

    map<int,string> d_mp;
    d_mp[0]="TV";
    d_mp[1]="Mob";
    d_mp[2]="Total";

    cout<<endl;
    cout<<"D-Weight"<<endl;
    for(int i=0;i<d_weight.size();i++)
    {
        cout<<d_mp[i]<<": \t";
        for(int j=0;j<d_weight[i].size();j++)
        {
            cout<<d_weight[i][j]<<"% ";
        }
        cout<<endl;
    }
}

int main()
{
    string csv_file="data-t.csv";
    vector<vector<string>> vec=read_file(csv_file);
    cout << "CSV Data:" << endl;
    display_csv_file_content(vec);
    vector<vector<int>> count_row;
    vector<vector<int>> count_col;
    
    for(int i=1;i<vec.size();i++)
    {
        vector<int> row;
        int sum=0;
        for(int j=1;j<vec[i].size();j++)
        {
            row.push_back(stod(vec[i][j]));
            sum=sum+stod(vec[i][j]);
        }
        row.push_back(sum);
        count_row.push_back(row);
    }

    int m=vec.size();
    int n=vec[0].size();
    for(int i=1;i<n;i++)
    {
        vector<int> col;
        int sum=0;
        for(int j=1;j<m;j++)
        {
            col.push_back(stod(vec[j][i]));
            sum=sum+stod(vec[j][i]);
        }
        col.push_back(sum);
        count_col.push_back(col);
    }

    display_t_weight(count_row);
    display_d_weight(count_col);

    return 0;
}
