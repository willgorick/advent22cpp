#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

int sliding_window(string line, int goal) {
    unordered_map<char, int> unique_characters;
    int i = 0, j = 0;

    while (j - i < goal) {
        char curr_char = line[j];
        if (unique_characters.count(curr_char)) {        
            i = max(i, unique_characters[curr_char]+1);
        }
        unique_characters[curr_char] = j;
        j += 1;
    }
    return j;
}

int part1(string line) {
    return sliding_window(line, 4);
}

int part2(string line) {
    return sliding_window(line, 14);
}

int main() {
    ifstream MyInput("input.txt");
    string line;
    vector<string> input;
    
    while(getline(MyInput, line)) {
        input.push_back(line);
    }

    string lineInput = input[0];

    cout << part1(lineInput) << endl;
    cout << part2(lineInput) << endl;
}