#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int part1(vector<string> input) {
    int res = 0;
    int curr_sum = 0;

    for(int i = 0; i < input.size() ; i++ ) {
        string curr_line = input[i];
        if (curr_line != "") {
            int num = stoi(curr_line);
            curr_sum += num;
        } else {
            if (curr_sum > res) {
                res = curr_sum;
            }
            curr_sum = 0;
        }
    }
    return res;
}

int part2(vector<string> input) {
    int curr_sum = 0;
    vector<int> sums;
    int res = 0;

    for(int i = 0; i < input.size() ; i++ ) {
        string curr_line = input[i];
        if (curr_line != "") {
            int num = stoi(curr_line);
            curr_sum += num;
        } else {
            sums.push_back(curr_sum);
            push_heap(sums.begin(), sums.end());
            curr_sum = 0;
        }
    }

    for (int i = 0; i < 3; i++) {
        res += sums.front();
        pop_heap(sums.begin(), sums.end());
        sums.pop_back();
    }

    return res;
}

int main() {
    ifstream MyInput("input.txt");
    string line;
    vector<string> input;
    
    while(getline(MyInput, line)) {
        input.push_back(line);
    }

    cout << part1(input) << endl;
    cout << part2(input) << endl;
}