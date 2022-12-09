#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include "tail.h"
#include <tuple>

using namespace std;

struct hashFunction
{
  size_t operator()(const tuple<int , 
                    int >&x) const
  {
    return get<0>(x) ^ get<1>(x);
  }
};

int part1(vector<string> input) {
    tuple<int, int> initial{0, 0}; 
    unordered_set<tuple<int, int>, hashFunction > t_visited;
    t_visited.insert(initial);
    std::vector<int> h_loc{0, 0};
    std::vector<int> t_loc{0, 0};

    for (int i = 0; i < input.size(); i++) {
        string line = input[i];
        char dir = line[0];
        int count = stoi(line.substr(2, line.size()-2));
        for (int j = 0; j < count; j++) {
            switch(dir) {
                case 'U':
                    h_loc[1] += 1;
                    break;
                case 'D':
                    h_loc[1] -= 1;
                    break;
                case 'L':
                    h_loc[0] -= 1;
                    break;
                case 'R':
                    h_loc[0] += 1;
                    break;
            }
            t_loc = updateTail(t_loc, h_loc);
            tuple<int, int> t_tuple = make_tuple(t_loc[0], t_loc[1]);
            t_visited.insert(t_tuple);
        }
    }
    return t_visited.size();
}

int part2(vector<string> input) {
    tuple<int, int> initial{0, 0}; 
    unordered_set<tuple<int, int>, hashFunction > t_visited;
    t_visited.insert(initial);
    vector<vector<int> > coordList;
    for(int i = 0; i < 10; i++) {
        coordList.push_back(vector<int>{0, 0});
    }

    for (int i = 0; i < input.size(); i++) {
        string line = input[i];
        char dir = line[0];
        int count = stoi(line.substr(2, line.size()-2));
        for (int j = 0; j < count; j++) {
            switch(dir) {
                case 'U':
                    coordList[0][1] += 1;
                    break;
                case 'D':
                    coordList[0][1] -= 1;
                    break;
                case 'L':
                    coordList[0][0] -= 1;
                    break;
                case 'R':
                    coordList[0][0] += 1;
                    break;
            }
            for (int x = 1; x < 10; x++) {
                coordList[x] = updateTail(coordList[x], coordList[x-1]);
            }
            tuple<int, int> t_tuple = make_tuple(coordList[9][0], coordList[9][1]);
            t_visited.insert(t_tuple);
        }
    }

    return t_visited.size();
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