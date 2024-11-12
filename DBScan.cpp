#include <bits/stdc++.h>
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

double ed(double a,double b)
{
    return fabs(a-b);
}

vector<double> get_neighbours(int point,vector<double> &Age, double epsilon)
{
    vector<double> neighbours;
    for(int i=0;i<Age.size();i++)
    {
        if(ed(Age[i],point)<=epsilon)
        {
            neighbours.push_back(Age[i]);
        }
    }
    return neighbours;
}

map<double,vector<double>> neighbourhood;

void display_neighbours()
{
    cout<<"Neighbours of each point: "<<endl;
    for(auto x:neighbourhood)
    {
        cout<<x.first<<": ";
        for(auto point : x.second)
        {
            cout<<point<<" ";
        }
        cout<<endl;
    }
}

void display_clusters(set<vector<double>> &st)
{
    int j=0;
    for(auto x:st)
    {
        cout<<"cluster"<<j<<" : ";
        for(int i=0;i<x.size();i++)
        {
            cout<<x[i]<<" ";
        }
        cout<<endl;
        j++;
    }
}

void create_cluster(vector<double> &core_points, vector<double> border_points)
{
    map<int,vector<double>> clusters;
    int cluster_no=0;
    set<vector<double>> st;
    for(auto x:neighbourhood)
    {
        vector<double> vec=x.second;
        sort(vec.begin(),vec.end());
        st.insert(vec);
    }

    display_clusters(st);
    
}

void DBSCAN(vector<double> &Age,double &epsilon,double &minimum_points)
{
    vector<double> core_points;
    vector<double> border_points;
    vector<double> noise_points;
    int cluster_no=0;
    for(int i=0;i<Age.size();i++)
    {
        vector<double> neigh=get_neighbours(Age[i],Age,epsilon);
        neighbourhood[i]=neigh;
        if(neigh.size()>0 && neigh.size()<minimum_points)
        {
            border_points.push_back(Age[i]);
        }
        else if(neigh.size()==0)
        {
            noise_points.push_back(Age[i]);
        }
        else
        {
            core_points.push_back(Age[i]);
        }
    }

    display_neighbours();
    create_cluster(core_points,border_points);
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

    double epsilon;
    double min_points;
    cout<<"Enter Epsilon (radius): ";
    cin>>epsilon;
    cout<<"Enter minimum no of points to be a core point: ";
    cin>>min_points;
    DBSCAN(Age,epsilon,min_points);


    return 0;
}
