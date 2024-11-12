#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

vector<vector<string>> read_file(string &csv_file)
{
    ifstream csv(csv_file);
    vector<vector<string>> vec;
    string line;
    getline(csv, line);
    while (getline(csv, line))
    {
        stringstream ss(line);
        string word;
        vector<string> row;

        while (getline(ss, word, ','))
        {
            row.push_back(word);
        }
        vec.push_back(row);
    }
    return vec;
}

void display_csv_file_content(const vector<vector<string>> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            cout << vec[i][j] << "\t";
        }
        cout << endl;
    }
}

double calculate_gini(int count_1, int count_2)
{
    int total = count_1 + count_2;
    if (total == 0) return 0.0; 

    double p1 = (double)count_1 / total;
    double p2 = (double)count_2 / total;

    double gini = 1.0 - (p1 * p1 + p2 * p2);
    return gini;
}

double calculate_overall_gini(const vector<vector<string>> &data)
{
    int count_greater = 0, count_less_equal = 0;

    for (int i = 0; i < data.size(); ++i)
    {
        string income_value = data[i][2];

        if (income_value == ">50K")
            count_greater++;
        else if (income_value == "<=50K")
            count_less_equal++;
    }

    return calculate_gini(count_greater, count_less_equal);
}

void calculate_and_print_table_with_gini_gain(const vector<vector<string>> &data, int attr_col, const string &attr_name, double overall_gini)
{
    unordered_map<string, pair<int, int>> counts; 
    int total_instances = data.size();

    for (int i = 0; i < data.size(); ++i)
    {
        string val = data[i][attr_col];
        string income_value = data[i][2]; 

        if (income_value == ">50K")
            counts[val].first++;
        else if (income_value == "<=50K")
            counts[val].second++;
    }

    double weighted_gini = 0.0;
    cout << "\nTable for " << attr_name << ":\n";
    cout << attr_name << "\t<=50K\t>50K\tGini\n";

    for (auto &pair : counts)
    {
        string category = pair.first;
        int count_greater = pair.second.first;
        int count_less_equal = pair.second.second;
        double gini = calculate_gini(count_greater, count_less_equal);
        int total_in_category = count_greater + count_less_equal;

        weighted_gini += (double)total_in_category / total_instances * gini;

        cout << category << "\t" << count_less_equal << "\t" << count_greater << "\t" << gini << endl;
    }

    double gini_gain = overall_gini - weighted_gini;
    cout << "\nGini Gain for " << attr_name << ": " << gini_gain << endl;
}

int main()
{
    string csv_file = "Categ.csv";
    vector<vector<string>> data = read_file(csv_file);

    cout << "CSV Data:" << endl;
    display_csv_file_content(data);

    cout << "\nStep 1: Calculate overall Gini impurity for the Income attribute (target)." << endl;
    double overall_gini = calculate_overall_gini(data);
    cout << "Overall Gini impurity of Income: " << overall_gini << endl;

    cout << "\nStep 2: Calculate the weighted Gini impurity and Gini gain for the 'Age' attribute." << endl;
    calculate_and_print_table_with_gini_gain(data, 0, "Age", overall_gini);

    cout << "\nStep 3: Calculate the weighted Gini impurity and Gini gain for the 'Education' attribute." << endl;
    calculate_and_print_table_with_gini_gain(data, 1, "Education", overall_gini);

    return 0;
}
