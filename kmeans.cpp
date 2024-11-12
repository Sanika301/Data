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

double ed(double a, double b)
{
    return fabs(a-b);
}

void display_centroids(vector<double> centroids,vector<double> newcenters)
{
    cout<<"final centroids are: "<<endl;
    for(int i=0;i<centroids.size();i++)
    {
        cout<<centroids[i]<<endl;
    }
}

void display_final_clusters(vector<int> labels,vector<double> &Age){
    map<int,vector<double>> final_clusters;
    for(int i=0;i<labels.size();i++)
    {
        final_clusters[labels[i]].push_back(Age[i]);
    }

    for(auto label:final_clusters)
    {
        cout<<label.first<<" ---> ";
        for(auto age:label.second)
        {
            cout<<age<<", ";
        }
        cout<<endl;
    }
}

void kmeans(vector<double> &Age,int &k,int &iter)
{
    int n=Age.size();
    vector<double> centroids(k);
    vector<int> labels(n);

    for(int i=0;i<k;i++)
    {
        centroids[i]=Age[rand()%n];
    }

    for(int i=0;i<iter;i++)
    {
        map<int,vector<double>> label_centers;
        for(int j=0;j<n;j++)
        {
            double mini=numeric_limits<double>::max();
            int c_label=-1;
            for(int c=0;c<k;c++)
            {
                int dist=ed(Age[j],centroids[c]);
                if(dist<mini)
                {
                    mini=dist;
                    c_label=c;
                }
            }
            label_centers[c_label].push_back(Age[j]);
            labels[j]=c_label;
        }

        vector<double> newcenters;
        for(auto label:label_centers)
        {
            vector<double> age_points=label.second;
            int count=age_points.size();
            double sum=0;
            for(auto element:age_points)
            {
                sum+=element;
            }
            newcenters.push_back((sum/count));
        }

        if(newcenters==centroids)
        {
            display_centroids(centroids,newcenters);
            break;
        }

        centroids=newcenters;
    }

    display_final_clusters(labels,Age);
}


int main()
{
    string csv_file="data.csv";
    vector<vector<string>> vec=read_file(csv_file);
    cout << "CSV Data:" << endl;
    display_csv_file_content(vec);
    
    vector<double> Age;
    for (int i = 1; i < vec.size(); ++i) { 
        Age.push_back(stoi(vec[i][0])); 
    }

    int k,iter;
    cout<<"Enter the no of clusters you want to create: "<<endl;
    cin>>k;
    cout<<"Enter the max no of iterations: "<<endl;
    cin>>iter;

    kmeans(Age,k,iter);

    return 0;
}
