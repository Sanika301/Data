#include <bits/stdc++.h>
using namespace std;


vector<vector<string>> read_csv(string file)
{
    ifstream csv(file);
    string line;
    vector<vector<string>> vec;
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

void display_csv(vector<vector<string>> &vec)
{
    for(int i=0;i<vec.size();i++)
    {
        for(int j=0;j<vec[i].size();j++)
        {
            cout<<vec[i][j]<<'\t';
        }
        cout<<endl;
    }
}

vector<pair<double,double>> create_pair(int n,vector<vector<string>> &vec,vector<int> &ni)
{
    int m=vec.size();

    vector<pair<double,double>> v;

    for(int i=1;i<m;i++)
    {
        pair<double,double> p;
        p.first=stod(vec[i][0]);
        p.second=stod(vec[i][2]);

        v.push_back(p);
    }
    return v;
}

double ed(pair<double,double> &p1,pair<double,double> &p2)
{
    double x=pow(abs(p1.first-p2.first),2)+pow(abs(p1.second-p2.second),2);
    return sqrt(x);
}

void create_dist_mat(vector<vector<double>> &dist,vector<pair<double,double>> &v)
{
    for(int i=0;i<v.size();i++)
    {
        for(int j=i;j<v.size();j++)
        {
            dist[j][i]=dist[i][j]=ed(v[i],v[j]);
        }
    }

    for(int i=0;i<v.size();i++)
    {
        for(int j=0;j<v.size();j++)
        {
            cout<<fixed<<setprecision(2)<<dist[i][j]<<'\t';
        }
        cout<<endl;
    }
}

pair<int,int> find_min(vector<vector<double>> &dist)
{
    int c1=0;
    int c2=0;
    double mini=numeric_limits<double>::max();
    for(int i=0;i<dist.size();i++)
    {
        for(int j=i+1;j<dist[i].size();j++)
        {
            if(dist[i][j]<mini)
            {
                mini=dist[i][j];
                c1=i;
                c2=j;
            }
        }
    }
    
    return make_pair(c1,c2);
}

void single_multi(vector<vector<double>> &dist)
{
    int total_clusters=dist.size();
    while(total_clusters>1)
    {
        cout<<endl;
        pair<int,int> p=find_min(dist);
        cout<<p.first<<" "<<p.second<<endl;
        for(int i=0;i<dist.size();i++)
        {
            if(i!=p.first && i!=p.second)
            {
                dist[i][p.first]=dist[p.first][i]=min(dist[p.first][i],dist[p.second][i]);
            }
        }
        dist.erase(dist.begin()+p.second);

        for(int i=0;i<dist.size();i++)
        {
            dist[i].erase(dist[i].begin()+p.second);
        }

        for(int i=0;i<dist.size();i++)
        {
            cout<<i<<"-->";
            for(int j=0;j<dist[i].size();j++)
            {
                cout<<fixed<<setprecision(2)<<dist[i][j]<<'\t';
            }
            cout<<endl;
        }
        total_clusters--;
        cout<<endl;
    }
    

}

int main(int argc, char const *argv[])
{
    vector<vector<string>> vec=read_csv("data.csv");
    display_csv(vec);
    int n;
    cout<<"Enter the no of columns you want to apply single linkage on: ";
    cin>>n;
    cout<<"Enter the column nos: ";
    vector<int> ni(n);
    for(int i=0;i<n;i++)
    {
        cin>>ni[i];
    }
    vector<pair<double,double>>v=create_pair(n,vec,ni);
    vector<vector<double>> dist(v.size(),vector<double> (v.size(),-1));
    create_dist_mat(dist,v);
    single_multi(dist);

    return 0;
}

