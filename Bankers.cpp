#include <bits/stdc++.h>
using namespace std;

int main() {
    int process, resources;
    cout << "Enter the number of processes: ";
    cin >> process;
    cout << "Enter the number of resources: ";
    cin >> resources;

    vector<int> instance(resources);
    vector<vector<int>> allocated(process, vector<int>(resources));
    vector<vector<int>> required(process, vector<int>(resources));
    vector<int> available(resources);
    vector<int> NotFree(resources, 0);

    cout << "Enter the total instances of each resource available:" << endl;
    for (int i = 0; i < resources; i++) {
        cin >> instance[i];
    }

    cout << "Enter the maximum requirement of each resource for each process:" << endl;
    for (int i = 0; i < process; i++) {
        for (int j = 0; j < resources; j++) {
            cin >> required[i][j];
        }
    }

    cout << "Enter the instance of each resource allocated to each process:" << endl;
    for (int i = 0; i < process; i++) {
        for (int j = 0; j < resources; j++) {
            cin >> allocated[i][j];
            NotFree[j] += allocated[i][j];  
        }
    }

    // Calculate available resources
    for (int i = 0; i < resources; i++) {
        available[i] = instance[i] - NotFree[i];
    }

    vector<bool> finished(process, false);
    vector<int> ans;

    for (int k = 0; k < process; k++) {
        bool found = false;
        for (int i = 0; i < process; i++) {
            if (!finished[i]) {
                bool feasible = true;
                for (int j = 0; j < resources; j++) {
                    if (required[i][j] - allocated[i][j] > available[j]) {
                        feasible = false;
                        break;
                    }
                }
                if (feasible) {
                    // Process can finish
                    for (int j = 0; j < resources; j++) {
                        available[j] += allocated[i][j];
                    }
                    ans.push_back(i);
                    finished[i] = true;
                    found = true;
                }
            }
        }
    }
    
    if (ans.size()==0) 
    {
        cout << "The system is not in a safe state." << endl;
    }
    else
    {
        cout << "The system is in a safe state.\nSafe sequence is: ";
        for (int i = 0; i < ans.size(); i++) 
        {
            cout << "P" << ans[i] + 1;
            if (i != ans.size() - 1) cout << " -> ";
        }
    }
    cout << endl;
    return 0;
}

// INPUT

// 5 3 
// 8 6 8
// 7 6 3
// 3 2 2
// 8 0 2
// 2 1 2
// 5 2 3 
// 0 0 1
// 3 0 0
// 1 0 0
// 2 3 2
// 0 0 3