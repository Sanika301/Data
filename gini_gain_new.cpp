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

double calculate_gini(map<string, int> &mp)
{
    double gini = 1.0;
    double total = 0;
    for (auto &x : mp)
    {
        total += x.second;
    }

    for (auto &x : mp)
    {
        double p = static_cast<double>(x.second) / total;
        gini -= p * p;
    }
    return gini;
}

double calculate_conditional_gini(vector<vector<string>> &vec, int feature_index, map<string, int> &target_count)
{
    map<string, map<string, int>> subsets; 

    for (int i = 1; i < vec.size(); i++) 
    {
        string feature_value = vec[i][feature_index];
        string target_value = vec[i].back(); 

        subsets[feature_value][target_value]++;
    }

    double conditional_gini = 0.0;
    double total = vec.size() - 1;

    cout << "\nConditional Gini Calculation (based on feature '" << vec[0][feature_index] << "'):" << endl;
    cout << "Feature Value\tSubset Size\tSubset Gini\tWeight\tWeighted Gini" << endl;

    for (auto &entry : subsets)
    {
        map<string, int> target_count_subset = entry.second;
        double subset_size = 0;
        for (auto &t : target_count_subset) {
            subset_size += t.second;
        }

        double weight = subset_size / total;
        double subset_gini = calculate_gini(target_count_subset);
        conditional_gini += weight * subset_gini;

        cout << entry.first << "\t\t" <<fixed<<setprecision(2)<< subset_size << "\t\t" << subset_gini << "\t\t" << weight << "\t\t" << weight * subset_gini << endl;
    }

    return conditional_gini;
}

double calculate_gini_gain(vector<vector<string>> &vec, int feature_index)
{
    map<string, int> target_count;

    for (int i = 1; i < vec.size(); i++) 
    {
        target_count[vec[i].back()]++;
    }

    double total_gini = calculate_gini(target_count);

    cout << "\nTotal Gini (based on target variable):" << endl;
    cout << "Target Variable\tGini" << endl;
    cout << "Target\t" << total_gini << endl;

    double conditional_gini = calculate_conditional_gini(vec, feature_index, target_count);

    double gini_gain = total_gini - conditional_gini;
    
    return gini_gain;
}

int main(int argc, char const *argv[])
{
    vector<vector<string>> vec = read_csv("Categ.csv");

    display_csv(vec);

    while (true) {
        string target, feature;

        // Get user input for target and feature
        cout << "\nEnter the target variable (e.g., class, outcome, etc.) or type 'exit' to quit: ";
        cin >> target;

        // Check if the user wants to exit
        if (target == "exit") {
            break;
        }

        cout << "Enter the feature for which Gini Gain is to be calculated: ";
        cin >> feature;

        // Find the feature index
        int feature_index = -1;
        for (int i = 0; i < vec[0].size(); i++) 
        {
            if (vec[0][i] == feature)
            {
                feature_index = i;
                break;
            }
        }

        if (feature_index == -1)
        {
            cout << "Feature not found!" << endl;
            continue;
        }

        double gini_gain = calculate_gini_gain(vec, feature_index);

        cout << "\nGini Gain for feature '" << feature << "' : " << gini_gain << endl;
    }

    return 0;
}
