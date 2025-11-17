#include <bits/stdc++.h>
using namespace std;

long long factorial(int n) {
    if (n > 20) return 1e18;
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

void solve(vector<string>& arr, long long k) {
    int n = arr.size();
    k--;
    
    for (int i = 0; i < n; i++) {
        long long fact = factorial(n - i - 1);
        int index = k / fact;
        k = k % fact;
        
        string temp = arr[i + index];
        for (int j = i + index; j > i; j--) {
            arr[j] = arr[j - 1];
        }
        arr[i] = temp;
    }
}

int main() {
    int n;
    cin >> n;
    
    vector<pair<string, int>> goodies(n);
    map<string, int> ship_wgts;
    
    for (int i = 0; i < n; i++) {
        cin >> goodies[i].first >> goodies[i].second;
        ship_wgts[goodies[i].first] += goodies[i].second;
    }
    
    long long k;
    cin >> k;
    
    map<int, vector<string>> wgt_groups;
    for (auto& p : ship_wgts) {
        wgt_groups[p.second].push_back(p.first);
    }
    
    vector<int> swgts;
    vector<long long> cumulative_perms;
    long long total_perms = 1;
    
    for (auto& p : wgt_groups) {
        swgts.push_back(p.first);
        sort(wgt_groups[p.first].begin(), wgt_groups[p.first].end());
    }
    sort(swgts.rbegin(), swgts.rend());
    
    for (int wgt : swgts) {
        int group_size = wgt_groups[wgt].size();
        total_perms *= factorial(group_size);
    }
    
    vector<string> opt_arr;
    long long rem = k - 1;
    
    for (int wgt : swgts) {
        vector<string> group = wgt_groups[wgt];
        sort(group.begin(), group.end());
        
        int group_size = group.size();
        long long perms_group = factorial(group_size);
        
        long long perms_after = 1;
        bool found = false;
        for (int i = 0; i < (int)swgts.size(); i++) {
            if (swgts[i] == wgt) {
                found = true;
                continue;
            }
            if (found) {
                perms_after *= factorial(wgt_groups[swgts[i]].size());
            }
        }
        
        long long idx = rem / perms_after;
        rem = rem % perms_after;
        
        solve(group, idx + 1);
        
        for (auto& ship : group) {
            opt_arr.push_back(ship);
        }
    }
    
    map<string, int> ship_pos;
    for (int i = 0; i < (int)opt_arr.size(); i++) {
        ship_pos[opt_arr[i]] = i + 1;
    }
    
    long long total_cost = 0;
    for (int i = 0; i < n; i++) {
        int goodie_pos = i + 1;
        int ship_pos1 = ship_pos[goodies[i].first];
        int dist = goodie_pos + ship_pos1;
        total_cost += (long long)goodies[i].second * dist;
    }
    
    cout << total_cost << "\n";
    for (int i = 0; i < (int)opt_arr.size(); i++) {
        cout << opt_arr[i];
        if (i < (int)opt_arr.size() - 1) cout << " ";
    }
    
    return 0;
}


//TCS CodeVita 2025 - Optimal Arrangement of Ships