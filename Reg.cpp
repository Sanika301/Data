#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

vector<vector<string>> read_file(const string &csv_file) {
    ifstream csv(csv_file);
    vector<vector<string>> vec;
    string line;
    
    while (getline(csv, line)) {
        stringstream ss(line);
        string word;
        vector<string> row;
        while (getline(ss, word, ',')) {
            row.push_back(word);
        }
        vec.push_back(row);
    }
    return vec;
}

void display_csv_file_content(const vector<vector<string>> &vec) {
    for (const auto &row : vec) {
        for (const auto &item : row) {
            cout << item << "\t";
        }
        cout << endl;
    }
}

void reg_coef(const vector<vector<string>> &vec) {
    int n = vec.size() - 1; 
    vector<long double> age_vals, salary_vals;

    for (int i = 1; i < vec.size(); ++i) { 
        age_vals.push_back(stold(vec[i][0])); 
        salary_vals.push_back(stold(vec[i][1])); 
    }

    long double sum_age = 0, sum_salary = 0;
    for (int i = 0; i < n; ++i) {
        sum_age += age_vals[i];
        sum_salary += salary_vals[i];
    }
    long double mean_age = sum_age / n;
    long double mean_salary = sum_salary / n;

    long double numerator = 0, denominator = 0;

    for (int i = 0; i < n; ++i) {
        numerator += (age_vals[i] - mean_age) * (salary_vals[i] - mean_salary);
        denominator += (age_vals[i] - mean_age) * (age_vals[i] - mean_age);
    }

    long double m = numerator / denominator; 
    long double c = mean_salary - (m * mean_age);

    cout << "Slope= " << m << endl;
    cout << "Intercept= " << c << endl;

    cout << "The linear regression equation is: salary = " << m << "age + " << c << endl;
}

int main() {
    string csv_file = "Reg.csv"; 
    vector<vector<string>> vec = read_file(csv_file);
    cout << "CSV Data:" << endl;
    
    display_csv_file_content(vec);

    reg_coef(vec);

    return 0;
}
