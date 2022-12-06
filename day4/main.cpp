#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
string comma_delimiter = ",";
string dash_delimiter = "-";

struct intervalPair {
    int first_start, first_end, second_start, second_end;
};

typedef struct intervalPair Struct;

intervalPair intervalParse(string line) {
    intervalPair pair;
    int comma_index = line.find(comma_delimiter);

    string first_interval = line.substr(0, comma_index);
    string second_interval =  line.substr(comma_index+1, line.size()-comma_index);

    int first_dash_index = first_interval.find(dash_delimiter);
    pair.first_start = stoi(first_interval.substr(0, first_dash_index));
    pair.first_end = stoi(first_interval.substr(first_dash_index+1, first_interval.size()-first_dash_index));

    int second_dash_index = second_interval.find(dash_delimiter);
    pair.second_start = stoi(second_interval.substr(0, second_dash_index));
    pair.second_end = stoi(second_interval.substr(second_dash_index+1, second_interval.size()-second_dash_index));

    return pair;
}

int part1(vector<string> input) {
    int res = 0;
    for (int i = 0; i < input.size(); i++) {
        string line = input[i];
        intervalPair intervals = intervalParse(line);
        if (
            (
                (intervals.first_start <= intervals.second_start) && (intervals.first_end >= intervals.second_end)
            ) || 
            (
                (intervals.second_start <= intervals.first_start) && (intervals.second_end >= intervals.first_end)
            )) {
                res += 1;
        }
    }
    return res;
}

int part2(vector<string> input) {
    int res = 0;
    for (int i = 0; i < input.size(); i++) {
        string line = input[i];
        intervalPair intervals = intervalParse(line);
        if (
            (
                (intervals.first_start <= intervals.second_start) && (intervals.first_end >= intervals.second_start)
            ) || 
            (
                (intervals.second_start <= intervals.first_start) && (intervals.second_end >= intervals.first_start)
            )) {
                res += 1;
        }
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