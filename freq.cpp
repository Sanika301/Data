#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

map<int, set<string>> readTransactions(string tr_file) {
    ifstream t(tr_file);
    string line;
    getline(t, line); 
    map<int, set<string>> ts;

    while (getline(t, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        stringstream ss(line);
        string tid, item;
        getline(ss, tid, ',');
        while (getline(ss, item, ',')) { 
            ts[stoi(tid)].insert(item);
        }
    }

    return ts;
}

void display_ts(map<int,set<string>> &ts) {
    for(auto t:ts) {
        cout << t.first << "---->  ";
        for(auto item: t.second) {
            cout << item << ", ";
        }
        cout << endl;
    }
}

void get_itemset(vector<string> &items, int combination_size, int start, vector<string> &current, vector<vector<string>> &itemset) {
    if (current.size() == combination_size) {
        itemset.push_back(current);
        return;
    }

    for (int i = start; i < items.size(); ++i) {
        current.push_back(items[i]);
        get_itemset(items, combination_size, i + 1, current, itemset);
        current.pop_back();
    }
}

void display_items_minSupport(map<string,float> &support,float minsupport) {
    cout << endl;
    cout << "Items with minimum entered support: " << endl;
    for(auto x:support) {
        if(x.second >= minsupport) {
            cout << x.first << " --> " << x.second << endl;
        }
    }
}

void display_frequency(map<string,int> &items) {
    cout << endl;
    cout << "Frequency of all items:" << endl;
    for(auto x: items) {
        cout << x.first << ": --> " << x.second << endl;
    }
    cout << endl;
}

map<string,int> count_items(map<int,set<string>> &ts, int max_combination_size) {
    map<string,int> items;

    for(auto t:ts) {
        vector<string> item_vector(t.second.begin(), t.second.end());

        for(auto item: t.second) {
            items[item]++;
        }

        for (int size = 2; size <= max_combination_size; ++size) {
            vector<vector<string>> itemset;
            vector<string> current;
            get_itemset(item_vector, size, 0, current, itemset);
            
            for (auto &combo : itemset) {
                stringstream combo_key;
                for (int i = 0; i < combo.size(); ++i) {
                    combo_key << combo[i];
                    if (i < combo.size() - 1) combo_key << ",";
                }
                items[combo_key.str()]++;
            }
        }
    }

    return items;
}

void display_support(map<string,float> &support) {
    cout << endl;
    cout << "Support of all items:" << endl;
    for(auto x:support) {
        cout << x.first << " --> " << x.second << endl;
    }
}

void calculate_support(map<int,set<string>> &ts, float minSupport, int max_combination_size) {
    map<string,int> items = count_items(ts, max_combination_size);
    display_frequency(items);
    int totalts = ts.size();
    map<string,float> support;

    for(auto item:items) {
        float sup = ((float)item.second / totalts);
        support[item.first] = sup;
    }

    display_support(support);
    display_items_minSupport(support, minSupport);
}

int main() {
    string tr_file = "transactions.csv";
    map<int,set<string>> ts = readTransactions(tr_file);
    display_ts(ts);

    float min_sup = 0.4;
    int max_combination_size = 2; 
    cout << "Enter Min Support: ";
    cin >> min_sup;
    cout << "Enter maximum combination size: ";
    cin >> max_combination_size;

    calculate_support(ts, min_sup, max_combination_size);

    return 0;
}
