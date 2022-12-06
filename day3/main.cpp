#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map> 
#include <set>

using namespace std;

int part1(vector<string> input) {
    int res = 0;
    for(int i = 0; i < input.size(); i++) {
        string line = input[i];
        int split_index = line.size() / 2;
        set<char> first_set;
        set<char> second_set;
        string first = line.substr(0, split_index);
        string second = line.substr(split_index, line.size()-split_index);
        const char* char_first = first.c_str();
        const char* char_second = second.c_str();
        set<char>::iterator itr;
        char special;
        for (int j = 0; j < first.size(); j++) {
            first_set.insert(char_first[j]);
            second_set.insert(char_second[j]);
        }
         for (itr = first_set.begin(); itr != first_set.end(); itr++) {
            if (second_set.count(*itr)) {
                special = *itr;
            }
         }
         int ascii = int(special);

         //lowercase
         if (ascii > 97) {
            res += ascii - 96;
         } else { //uppercase
            res += ascii - 38;
         }
    }
    return res;
}

int part2(vector<string> input) {
    int res = 0;
    set<char> first_set;
    set<char> second_set;
    set<char> third_set;
    char special;

    for(int i = 0; i < input.size(); i++) {
        string line = input[i];
        const char* char_line = line.c_str();
        if (i % 3 == 0) {
            for (int j = 0; j < line.size(); j++) {
                first_set.insert(char_line[j]);
            }
        }

        if (i % 3 == 1) {
            for (int j = 0; j < line.size(); j++) {
                second_set.insert(char_line[j]);
            }
        }

        if (i % 3 == 2) {
            for (int j = 0; j < line.size(); j++) {
                third_set.insert(char_line[j]);
            }
            set<char>::iterator itr;
            set<char> first_second_intersection;
            for (itr = first_set.begin(); itr != first_set.end(); itr++) {
                if (second_set.count(*itr)) {
                    first_second_intersection.insert(*itr);
                }
            }

            for (itr = first_second_intersection.begin(); itr != first_second_intersection.end(); itr++) {
                if (third_set.count(*itr)) {
                    special = *itr;
                }
            }
            first_set.clear();
            second_set.clear();
            third_set.clear();

            int ascii = int(special);
            //lowercase
            if (ascii > 97) {
                res += ascii - 96;
            } else { //uppercase
                res += ascii - 38;
            }

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