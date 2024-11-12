#include <bits/stdc++.h>
using namespace std;


string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos)
        return ""; 
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

vector<vector<string>> read_csv(string file)
{
    ifstream csv(file);
    string line;
    vector<vector<string>> vec;
    
    while (getline(csv, line))
    {
        stringstream ss(line);
        string word;
        vector<string> row;

        while (getline(ss, word, ','))
        {
            row.push_back(trim(word));
        }

        vec.push_back(row);
    }
    return vec;
}

void display_csv(vector<vector<string>> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            cout << vec[i][j] << '\t';
        }
        cout << endl;
    }
}

int count_target(string st,vector<vector<string>> &vec,map<string,double> &prob_target,map<string,double> &target)
{
    int m=vec.size();
    int n=vec[0].size();
    int x=-1;
    double target_total=m-1;
    for(int i=0;i<n;i++)
    {
        if(vec[0][i]==st)
        {
            for(int j=1;j<m;j++)
            {
                target[vec[j][i]]++;
            }
            x=i;
        }
    }
    for(auto x:target)
    {
        prob_target[x.first]=x.second/target_total;
    }
    return x;
}

map<pair<string,string>,double> find_like_prob(int col,int t,string attr,vector<vector<string>> &vec,map<string,double> &target)
{
    int m=vec.size();
    int n=vec[0].size();
    map<pair<string,string>,double> mp;

    for(auto x:target)
    {
        for(int j=1;j<m;j++)
        {
            if(vec[j][col]==attr && vec[j][t]==x.first)
            {
                pair<string,string> p;
                p.first=attr;
                p.second=x.first;
                mp[p]++;
            }
            
        }
        
    }

        
  

    return mp;
}

int main()
{
    vector<vector<string>> vec = read_csv("Bayes.csv");

    display_csv(vec);
    string st;
    cin>>st;
    st=trim(st);
    map<string,double> prob_target;
    map<string,double> target;
    int x=count_target(st,vec,prob_target,target);
    vector<map<pair<string,string>,double>> req_prob;
    map<string,vector<double>> p;

    for(int i=0;i<vec[0].size();i++)
    {
        if(i!=x)
        {
            string attr;
            cout<<"Enter the "<<vec[0][i]<<" required for prediction"<<endl;
            cin>>attr;
            map<pair<string,string>,double> q=find_like_prob(i,x,attr,vec,target);
            req_prob.push_back(q);
        }
    }

    for(auto x:prob_target)
    {
        vector<double> v;
        for(int i=0;i<req_prob.size();i++)
        {
            for(auto y:req_prob[i])
            {
                double d=(y.second)/target[x.first];
                v.push_back(d);
            }
        }
        p[x.first]=v;
    }

    for(auto x:p)
    {
        cout<<x.first<<": ";
        vector<double> v1=x.second;
        double pred_prob=prob_target[x.first];
        for(int i=0;i<v1.size();i++)
        {
            cout<<v1[i]<<'\t';
            pred_prob*=v1[i];
        }
        cout<<pred_prob<<endl;
    }

    return 0;
}
