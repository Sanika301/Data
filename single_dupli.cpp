#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> load_csv(string filename) {
    ifstream file(filename);
    string row;
    vector<vector<string>> data;
    
    while (getline(file, row)) {
        stringstream stream(row);
        string cell;
        vector<string> record;
        
        while (getline(stream, cell, ',')) {
            record.push_back(cell);
        }
        
        data.push_back(record);
    }
    
    return data;
}

void print_csv(const vector<vector<string>>& data) {
    for (const auto& row : data) {
        for (const auto& cell : row) {
            cout << cell << '\t';
        }
        cout << endl;
    }
}

vector<pair<double, double>> generate_pairs(int col_count, const vector<vector<string>>& data, const vector<int>& columns) {
    int row_count = data.size();
    vector<pair<double, double>> points;
    
    for (int i = 1; i < row_count; i++) {
        pair<double, double> point;
        point.first = stod(data[i][0]);
        point.second = stod(data[i][2]);
        points.push_back(point);
    }
    
    return points;
}

double compute_distance(const pair<double, double>& point1, const pair<double, double>& point2) {
    double x_diff = pow(abs(point1.first - point2.first), 2);
    double y_diff = pow(abs(point1.second - point2.second), 2);
    return sqrt(x_diff + y_diff);
}

void calculate_distance_matrix(vector<vector<double>>& matrix, const vector<pair<double, double>>& points) {
    for (int i = 0; i < points.size(); i++) {
        for (int j = i; j < points.size(); j++) {
            matrix[j][i] = matrix[i][j] = compute_distance(points[i], points[j]);
        }
    }

    for (const auto& row : matrix) {
        for (const auto& value : row) {
            cout << fixed << setprecision(2) << value << '\t';
        }
        cout << endl;
    }
}

pair<int, int> get_closest_pair(const vector<vector<double>>& matrix) {
    int idx1 = 0, idx2 = 0;
    double min_dist = numeric_limits<double>::max();
    
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = i + 1; j < matrix[i].size(); j++) {
            if (matrix[i][j] < min_dist) {
                min_dist = matrix[i][j];
                idx1 = i;
                idx2 = j;
            }
        }
    }
    
    return make_pair(idx1, idx2);
}

void perform_clustering(vector<vector<double>>& matrix) {
    int remaining_clusters = matrix.size();
    
    while (remaining_clusters > 1) {
        cout << endl;
        
        pair<int, int> closest_pair = get_closest_pair(matrix);
        cout << closest_pair.first << " " << closest_pair.second << endl;
        
        for (int i = 0; i < matrix.size(); i++) {
            if (i != closest_pair.first && i != closest_pair.second) {
                matrix[i][closest_pair.first] = matrix[closest_pair.first][i] = min(matrix[closest_pair.first][i], matrix[closest_pair.second][i]);
            }
        }
        
        matrix.erase(matrix.begin() + closest_pair.second);
        for (int i = 0; i < matrix.size(); i++) {
            matrix[i].erase(matrix[i].begin() + closest_pair.second);
        }

        for (int i = 0; i < matrix.size(); i++) {
            cout << i << "-->";
            for (int j = 0; j < matrix[i].size(); j++) {
                cout << fixed << setprecision(2) << matrix[i][j] << '\t';
            }
            cout << endl;
        }
        
        remaining_clusters--;
        cout << endl;
    }
}

int main() {
    vector<vector<string>> data = load_csv("data.csv");
    print_csv(data);
    
    int column_count;
    cout << "Enter the number of columns to apply single linkage on: ";
    cin >> column_count;
    
    cout << "Enter the column indices: ";
    vector<int> columns(column_count);
    
    for (int i = 0; i < column_count; i++) {
        cin >> columns[i];
    }
    
    vector<pair<double, double>> points = generate_pairs(column_count, data, columns);
    vector<vector<double>> distance_matrix(points.size(), vector<double>(points.size(), -1));
    
    calculate_distance_matrix(distance_matrix, points);
    perform_clustering(distance_matrix);

    return 0;
}
