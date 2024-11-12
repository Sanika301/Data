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

double calculate_entropy(map<string, int> &mp)
{
    double entropy = 0.0;
    double total = 0;
    for (auto x : mp)
    {
        total += x.second;
    }

    for (auto &x : mp)
    {
        double p = static_cast<double>(x.second) / total;
        if (p > 0) 
        {
            entropy += -p * log2(p);
        }
    }
    return entropy;
}

double calculate_conditional_entropy(vector<vector<string>> &vec, int feature_index, map<string, int> &target_count)
{
    map<string, map<string, int>> subsets; 

    for (int i = 1; i < vec.size(); i++) 
    {
        string feature_value = vec[i][feature_index];
        string target_value = vec[i].back(); 

        subsets[feature_value][target_value]++;
    }

    double conditional_entropy = 0.0;
    double total = vec.size() - 1;

    cout << "\nConditional Entropy Calculation (based on feature '" << vec[0][feature_index] << "'):" << endl;
    cout << "Feature Value\tSubset Size\tSubset Entropy\tWeight\tWeighted Entropy" << endl;

    for (auto &entry : subsets)
    {
        map<string, int> target_count_subset = entry.second;
        double subset_size = 0;
        for (auto &t : target_count_subset) {
            subset_size += t.second;
        }

        double weight = subset_size / total;
        double subset_entropy = calculate_entropy(target_count_subset);
        conditional_entropy += weight * subset_entropy;

        cout << entry.first << "\t\t" <<fixed<<setprecision(2)<< subset_size << "\t\t" << subset_entropy << "\t\t" << weight << "\t\t" << weight * subset_entropy << endl;
    }

    return conditional_entropy;
}

double calculate_information_gain(vector<vector<string>> &vec, int feature_index)
{
    map<string, int> target_count;

    for (int i = 1; i < vec.size(); i++) 
    {
        target_count[vec[i].back()]++;
    }

    double total_entropy = calculate_entropy(target_count);

    cout << "\nTotal Entropy (based on target variable):" << endl;
    cout << "Target Variable\tEntropy" << endl;
    cout << "Target\t" << total_entropy << endl;

    double conditional_entropy = calculate_conditional_entropy(vec, feature_index, target_count);

    double info_gain = total_entropy - conditional_entropy;
    
    return info_gain;
}

int main(int argc, char const *argv[])
{
    vector<vector<string>> vec = read_csv("Categ.csv");

    display_csv(vec);

    while (true) {
        string target, feature;

        cout << "\nEnter the target variable or type 'exit' to quit: ";
        cin >> target;

        if (target == "exit") {
            break;
        }

        // Find the index of the target variable in the first row (header row)
        int target_index = -1;
        for (int i = 0; i < vec[0].size(); i++) 
        {
            if (vec[0][i] == target)
            {
                target_index = i;
                break;
            }
        }

        if (target_index == -1)
        {
            cout << "Target variable not found!" << endl;
            continue;
        }

        cout << "Enter the feature for which information gain is to be calculated: ";
        cin >> feature;

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

        double info_gain = calculate_information_gain(vec, feature_index);

        cout << "\nInformation Gain for feature '" << feature << "' : " << info_gain << endl;
    }

    return 0;
}
