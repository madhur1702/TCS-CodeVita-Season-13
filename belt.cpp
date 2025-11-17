#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;  
    cin.ignore();

    unordered_map<string, vector<string>> graph;
    unordered_map<string, string> parent;
  
    for (int i = 0; i < N; i++) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string node, x;
        ss >> node;
        while (ss >> x) {
            graph[node].push_back(x);
            parent[x] = node;
        }
    }

    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<string> products;
    string ws;
    while (ss >> ws) products.push_back(ws);

    int K;
    cin >> K;

    unordered_map<string, string> lastUsedChild;
    unordered_map<string, int> switchCount;

    long long total = 0;

    for (string prod : products) {
        string cur = prod;
        vector<pair<string, string>> path;

        while (parent.count(cur)) {
            string p = parent[cur];
            path.push_back({p, cur});
            cur = p;
        }

        reverse(path.begin(), path.end());

        int wait = 0, cool = 0, reset = 0;

        for (auto &pr : path) {
            string junction = pr.first;
            string childUsed = pr.second;
            wait += 1;

            if (!lastUsedChild.count(junction)) {
                lastUsedChild[junction] = childUsed;
                switchCount[junction] = 1;
                cool += 2;
            } else if (lastUsedChild[junction] != childUsed) {
                if (switchCount[junction] < K) {
                    switchCount[junction]++;
                    lastUsedChild[junction] = childUsed;
                    cool += 2;
                } else reset += 3;
            }
        }

        total += wait + cool + reset;
    }

    cout << total;
    return 0;
}

//tcs codevita conveyor belt
