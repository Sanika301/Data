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

pair<int,int> find_min_dist(vector<vector<double>> &dist_matrix,vector<int> &total_clusters)
{
    pair<int,int> min_dist_points;
    int c1=-1;
    int c2=-1;

    double mini=numeric_limits<double>::max();
    for(int i=0;i<total_clusters.size();i++)
    {
        for(int j=0;j<total_clusters.size();j++)
        {
            int l=total_clusters[i];
            int m=total_clusters[j];
            if(l!=m && dist_matrix[l][m]<mini)
            {
                mini=dist_matrix[l][m];
                c1=l;
                c2=m;
            }
        }
    }
    min_dist_points.first=c1;
    min_dist_points.second=c2;
    return min_dist_points;
}


void display_distance_matrix(vector<vector<double>> &dist_matrix,vector<int> &total_clusters)
{
    cout<<endl;
    cout<<"Distance Matrix: "<<endl;
    for(int i=0;i<total_clusters.size();i++)
    {
        for(int j=0;j<total_clusters.size();j++)
        {
            if (i == j) {
                cout << setw(8) << "zero"; 
            } else {
                cout << setw(8) << fixed << setprecision(2) << dist_matrix[i][j];
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

void average_linkage(vector<double> &Age)
{
    vector<vector<double>> dist_matrix(Age.size(), vector<double>(Age.size()));
    for(int i=0;i<Age.size();i++)
    {
        for(int j=0;j<Age.size();j++)
        {
            if(i==j)
            {
                dist_matrix[i][j]=numeric_limits<double>::max();
            }
            else
            {
                dist_matrix[i][j]=ed(Age[i],Age[j]);
            }
        }
    }

    vector<int> total_clusters(Age.size());
    vector<int> cluster_labels(Age.size());
    for(int i=0;i<Age.size();i++)
    {
       total_clusters[i]=i;
       cluster_labels[i]=i;
    }

    display_distance_matrix(dist_matrix,total_clusters);

    while(total_clusters.size()>1)
    {
        pair<int,int> p=find_min_dist(dist_matrix,total_clusters);
        int c1 = p.first;
        int c2 = p.second;
        cout << endl;
        cout << "Merging clusters: " << c1 << " and " << c2 << " with distance: " 
             << dist_matrix[c1][c2] << endl;
        cout << endl;

        for (int i : total_clusters) {
            if (i != c1 && i != c2) {
                dist_matrix[c1][i] = dist_matrix[i][c1] = 
                    (dist_matrix[c1][i]+dist_matrix[c2][i])/2;
            }
        }

        for (int i = 0; i < Age.size(); ++i) {
            if (cluster_labels[i] == c2) {
                cluster_labels[i] = c1; 
            }
        }

        total_clusters.erase(remove(total_clusters.begin(), total_clusters.end(), c2), total_clusters.end());
        display_distance_matrix(dist_matrix, total_clusters);
    }

    cout << "Final Cluster:" << endl;
    for (int i = 0; i < cluster_labels.size(); ++i) {
        cout << "Data point " << i << " is in cluster " << cluster_labels[i] << endl;
    }
    
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

    average_linkage(Age);


    return 0;
}
