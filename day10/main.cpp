#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int part1(vector<string> input) {
    int res = 0, reg = 1, cycle = 1;

    for(int i = 0; i < input.size() ; i++ ) {
        if (cycle%40 == 20) {
            res += (cycle * reg);
        }   
        string curr_line = input[i];
        if (curr_line == "noop") {
            cycle += 1;
        } else {
            int addend = stoi(curr_line.substr(5, curr_line.size()-5));
            cycle += 1;
            if (cycle%40 == 20) {
                res += (cycle * reg);
            }   
            cycle += 1;
            reg += addend;
        }
    }
    return res;
}

char output(int reg, int cycle) {
    if ((cycle % 40) >= reg-1 && (cycle % 40) <= reg+1) {
        return '#';
    }
    return '.';
}

void part2(vector<string> input) {
    vector<char> res(240, '.');
    int reg = 1, cycle = 0;
    for(int i = 0; i < input.size() ; i++ ) {
        string curr_line = input[i];
        res[cycle] = output(reg, cycle);
        if (curr_line == "noop") {
            cycle += 1;
        } else {
            int addend = stoi(curr_line.substr(5, curr_line.size()-5));
            cycle += 1;
            res[cycle] = output(reg, cycle);
            cycle += 1;
            reg += addend;
        }
    }


    for (int i = 0; i < 6; i++) {
        string line;
        for(int j = 0; j < 40; j++) {
            cout << res[(i*40)+j];
        }
        cout << endl;
    } 
}

int main() {
    ifstream MyInput("input.txt");
    string line;
    vector<string> input;
    
    while(getline(MyInput, line)) {
        input.push_back(line);
    }

    cout << part1(input) << endl;
    part2(input);
}