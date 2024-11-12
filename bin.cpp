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


void display_csv_file_content(vector<vector<string>> &vec)
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

vector<vector<double>> equal_width_binning(vector<double> &Age, int num_bins)
{
    double min_age = *min_element(Age.begin(), Age.end());
    double max_age = *max_element(Age.begin(), Age.end());

    double bin_width = (max_age - min_age) / num_bins;

    vector<vector<double>> bins(num_bins);

    for (double age : Age)
    {
        int bin_index = (age - min_age) / bin_width;
        if (bin_index == num_bins)
            bin_index--;
        bins[bin_index].push_back(age);
    }

    return bins;
}

vector<vector<double>> equal_frequency_binning(vector<double> &Age, int num_bins)
{
    sort(Age.begin(), Age.end());
    vector<vector<double>> bins;
    int bin_size = Age.size() / num_bins;

    for (int i = 0; i < num_bins; ++i)
    {
        vector<double> bin(Age.begin() + i * bin_size, Age.begin() + min((i + 1) * bin_size, (int)Age.size()));
        bins.push_back(bin);
    }

    return bins;
}

void smooth_by_mean(vector<vector<double>> &bins)
{
    for (auto &bin : bins)
    {
        if (bin.empty()) continue;
        double mean = accumulate(bin.begin(), bin.end(), 0.0) / bin.size();
        for (auto &value : bin)
        {
            value = mean;
        }
    }
}

void smooth_by_median(vector<vector<double>> &bins)
{
    for (auto &bin : bins)
    {
        if (bin.empty()) continue;
        sort(bin.begin(), bin.end());
        double median = bin[bin.size() / 2];
        for (auto &value : bin)
        {
            value = median;
        }
    }
}

void smooth_by_boundary(vector<vector<double>> &bins)
{
    for (auto &bin : bins)
    {
        if (bin.empty()) continue;
        double min_val = *min_element(bin.begin(), bin.end());
        double max_val = *max_element(bin.begin(), bin.end());
        for (auto &value : bin)
        {
            value = (value - min_val <= max_val - value) ? min_val : max_val;
        }
    }
}

void display_bins(const vector<vector<double>> &bins, const string &title)
{
    cout << "\n" << title << ":\n";
    for (int i = 0; i < bins.size(); ++i)
    {
        cout << "Bin " << i + 1 << ": ";
        for (double value : bins[i])
        {
            cout << value << " ";
        }
        cout << endl;
    }
}

int main()
{
    string csv_file = "data.csv";
    vector<vector<string>> vec = read_file(csv_file);
    cout << "CSV Data:" << endl;
    display_csv_file_content(vec);

    vector<double> Age;
    for (int i = 1; i < vec.size(); ++i)
    {
        Age.push_back(stoi(vec[i][0]));
    }

    sort(Age.begin(),Age.end());
    int num_bins; 
    cout<<"Enter the no of bins: ";
    cin>>num_bins;

    vector<vector<double>> width_bins = equal_width_binning(Age, num_bins);
    display_bins(width_bins, "Equal Width Bins");

    vector<vector<double>> width_bins_mean = width_bins, width_bins_median = width_bins, width_bins_boundary = width_bins;
    smooth_by_mean(width_bins_mean);
    smooth_by_median(width_bins_median);
    smooth_by_boundary(width_bins_boundary);
    display_bins(width_bins_mean, "Equal Width Bins (Mean Smoothing)");
    display_bins(width_bins_median, "Equal Width Bins (Median Smoothing)");
    display_bins(width_bins_boundary, "Equal Width Bins (Boundary Smoothing)");

    vector<vector<double>> frequency_bins = equal_frequency_binning(Age, num_bins);
    display_bins(frequency_bins, "Equal Frequency Bins");

    vector<vector<double>> freq_bins_mean = frequency_bins, freq_bins_median = frequency_bins, freq_bins_boundary = frequency_bins;
    smooth_by_mean(freq_bins_mean);
    smooth_by_median(freq_bins_median);
    smooth_by_boundary(freq_bins_boundary);
    display_bins(freq_bins_mean, "Equal Frequency Bins (Mean Smoothing)");
    display_bins(freq_bins_median, "Equal Frequency Bins (Median Smoothing)");
    display_bins(freq_bins_boundary, "Equal Frequency Bins (Boundary Smoothing)");

    return 0;
}
