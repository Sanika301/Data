#include <bits/stdc++.h>
using namespace std;

struct DataPoint {
    string age;
    string education;
    string income;
};

vector<DataPoint> read_file(const string &csv_file) {
    ifstream csv(csv_file);
    vector<DataPoint> data;
    string line;
    
    getline(csv, line);

    while (getline(csv, line)) {
        stringstream ss(line);
        string age, education, income;
        
        getline(ss, age, ',');
        getline(ss, education, ',');
        getline(ss, income);
        
        data.push_back({age, education, income});
    }
    return data;
}

void display_csv_file_content(const vector<DataPoint> &data) {
    cout << "Age\tEducation\tIncome" << endl;
    for (const auto &dp : data) {
        cout << dp.age << "\t" << dp.education << "\t" << dp.income << endl;
    }
}

void print_count_tables(const vector<DataPoint>& data) {
    unordered_map<string, int> age_count[2];
    unordered_map<string, int> education_count[2];

    for (const auto& dp : data) {
        if (dp.income == "<=50K") {
            age_count[0][dp.age]++;
            education_count[0][dp.education]++;
        } else {
            age_count[1][dp.age]++;
            education_count[1][dp.education]++;
        }
    }

    cout << "\nAge Count Table:\n";
    cout << "Age\t<=50K\t>50K" << endl;
    for (const auto& age : age_count[0]) {
        cout << age.first << "\t" << age.second << "\t" << age_count[1][age.first] << endl;
    }

    cout << "\nEducation Count Table:\n";
    cout << "Education\t<=50K\t>50K" << endl;
    for (const auto& edu : education_count[0]) {
        cout << edu.first << "\t" << edu.second << "\t" << education_count[1][edu.first] << endl;
    }
}

void bayes_classification(const vector<DataPoint>& data, const string& age, const string& education) {
    unordered_map<string, int> class_count;
    unordered_map<string, int> age_count[2]; 
    unordered_map<string, int> education_count[2];

    for (const auto& dp : data) {
        if (dp.income == "<=50K") {
            class_count["<=50K"]++;
            age_count[0][dp.age]++;
            education_count[0][dp.education]++;
        } else {
            class_count[">50K"]++;
            age_count[1][dp.age]++;
            education_count[1][dp.education]++;
        }
    }

    int total = data.size();
    
    double prior_leq_50K = class_count["<=50K"] / (double)total; 
    double prior_gt_50K = class_count[">50K"] / (double)total;

    double likelihood_age_leq_50K = age_count[0][age] / (double)class_count["<=50K"];
    double likelihood_age_gt_50K = age_count[1][age] / (double)class_count[">50K"]; 

    double likelihood_education_leq_50K = education_count[0][education] / (double)class_count["<=50K"]; // Avoid static_cast
    double likelihood_education_gt_50K = education_count[1][education] / (double)class_count[">50K"]; // Avoid static_cast

    double posterior_leq_50K = prior_leq_50K * likelihood_age_leq_50K * likelihood_education_leq_50K;
    double posterior_gt_50K = prior_gt_50K * likelihood_age_gt_50K * likelihood_education_gt_50K;

    cout << fixed << setprecision(4);
    cout << "\nPosterior P(<=50K | Age=" << age << ", Education=" << education << ") = " << posterior_leq_50K << endl;
    cout << "Posterior P(>50K | Age=" << age << ", Education=" << education << ") = " << posterior_gt_50K << endl;

    if (posterior_leq_50K > posterior_gt_50K) {
        cout << "Predicted Income: <=50K" << endl;
    } else {
        cout << "Predicted Income: >50K" << endl;
    }
}

int main() {
    string csv_file = "Bayes.csv";
    vector<DataPoint> data = read_file(csv_file);
    
    cout << "CSV Data:" << endl;
    display_csv_file_content(data);

    print_count_tables(data);

    bayes_classification(data, "Senior", "Master");

    return 0;
}
