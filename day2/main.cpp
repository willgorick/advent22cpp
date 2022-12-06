#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map> 

using namespace std;

int part1(vector<string> input) {
    int res = 0;
    unordered_map<string, unordered_map<string, int> > hash_map = {
        {"A", unordered_map<string, int>()},
        {"B", unordered_map<string, int>()},
        {"C", unordered_map<string, int>()}
    };
    // X -> 1, Y -> 2, Z -> 3
    // Lose -> 0, Tie -> 3, Win -> 6
    hash_map["A"]["X"] = 4;
    hash_map["A"]["Y"] = 8; 
    hash_map["A"]["Z"] = 3;
    hash_map["B"]["X"] = 1;
    hash_map["B"]["Y"] = 5;
    hash_map["B"]["Z"] = 9;
    hash_map["C"]["X"] = 7;
    hash_map["C"]["Y"] = 2;
    hash_map["C"]["Z"] = 6;

    string delimiter = " ";
    int delimiter_size = delimiter.size();
    for(int i = 0; i < input.size(); i++) {
        string line = input[i];
        int delimiter_index = line.find(delimiter);
        string opponent = line.substr(0, delimiter_index);
        string me = line.substr(delimiter_index+delimiter_size, line.size()-delimiter_index);
        res += hash_map[opponent][me];
    }
    
    return res;
}

int part2(vector<string> input) {
    int res = 0;
    unordered_map<string, unordered_map<string, int> > hash_map = {
        {"A", unordered_map<string, int>()},
        {"B", unordered_map<string, int>()},
        {"C", unordered_map<string, int>()}
    };
    // X -> Lose, Y -> Draw, Z -> Win
    // Lose -> 0, Tie -> 3, Win -> 6
    hash_map["A"]["X"] = 3;
    hash_map["A"]["Y"] = 4; 
    hash_map["A"]["Z"] = 8;
    hash_map["B"]["X"] = 1;
    hash_map["B"]["Y"] = 5;
    hash_map["B"]["Z"] = 9;
    hash_map["C"]["X"] = 2;
    hash_map["C"]["Y"] = 6;
    hash_map["C"]["Z"] = 7;

    string delimiter = " ";
    int delimiter_size = delimiter.size();
    for(int i = 0; i < input.size(); i++) {
        string line = input[i];
        int delimiter_index = line.find(delimiter);
        string opponent = line.substr(0, delimiter_index);
        string me = line.substr(delimiter_index+delimiter_size, line.size()-delimiter_index);
        res += hash_map[opponent][me];
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