#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <deque>

using namespace std;

struct Monkey {
    int name;
    deque<long long> items;
    string operation;
    int test;
    int ifTrue;
    int ifFalse;
    long long inspections;
};  

int executeOperation(long long curr, string operation) {
    if (operation == "old * old") {
        return curr * curr;
    } else if (operation.substr(4, 1) == "*") {
        return curr * stoi(operation.substr(6, operation.size()-6));
    } else if (operation.substr(4, 1) == "+") {
        return curr + stoi(operation.substr(6, operation.size()-6));
    }
    return curr;
}

int part1(vector<string> input) {
    vector<Monkey> monkeyList;
    for(int i = 0; i < input.size(); i+=7) {
        int monkey_name = stoi(input[i+0].substr(7, 1));
        deque<long long> items;
        string itemString = input[i+1].substr(18, input[i+1].size()-18);
        stringstream s_stream(itemString);
        while(s_stream.good()) {
            string substr;
            getline(s_stream, substr, ',');
            items.push_back(stoi(substr));
        }

        string operation = input[i+2].substr(19, input[i+2].size()-19);
        int test = stoi(input[i+3].substr(21, input[i+3].size()-21));
        int ifTrue = stoi(input[i+4].substr(29, input[i+4].size()-29));
        int ifFalse = stoi(input[i+5].substr(30, input[i+5].size()-30));

        Monkey monkey = {
            monkey_name,
            items,
            operation,
            test,
            ifTrue,
            ifFalse
        };
        monkeyList.push_back(monkey);
    }

    for (int j = 0; j < 20; j++) {
        for(int i = 0; i < monkeyList.size(); i++) {
            while(monkeyList[i].items.size() > 0) {
                monkeyList[i].inspections += 1;
                long long curr = monkeyList[i].items.front();
                monkeyList[i].items.pop_front();
                curr = executeOperation(curr, monkeyList[i].operation);
                curr /= 3;
                bool check = curr % monkeyList[i].test == 0;
                if (check) {
                    monkeyList[monkeyList[i].ifTrue].items.push_back(curr);
                } else {
                    monkeyList[monkeyList[i].ifFalse].items.push_back(curr);
                }
            };
        }
    }

    int max = 0, secondMax = 0;
    for (int i = 0; i < monkeyList.size(); i++) {
        if (monkeyList[i].inspections > max) {
            secondMax = max;
            max = monkeyList[i].inspections;
        } else if (monkeyList[i].inspections > secondMax) {
            secondMax = monkeyList[i].inspections;
        }
    }
    return max * secondMax;
}

long long part2(vector<string> input) {
    vector<Monkey> monkeyList;
    int lcm = 1;
    int totalItems = 0;
    for(int i = 0; i < input.size(); i+=7) {
        int monkey_name = stoi(input[i+0].substr(7, 1));
        deque<long long> items;
        string itemString = input[i+1].substr(18, input[i+1].size()-18);
        stringstream s_stream(itemString);
        while(s_stream.good()) {
            totalItems += 1;
            string substr;
            getline(s_stream, substr, ',');
            items.push_back(stoi(substr));
        }

        string operation = input[i+2].substr(19, input[i+2].size()-19);
        int test = stoi(input[i+3].substr(21, input[i+3].size()-21));
        lcm *= test;
        int ifTrue = stoi(input[i+4].substr(29, input[i+4].size()-29));
        int ifFalse = stoi(input[i+5].substr(30, input[i+5].size()-30));

        Monkey monkey = {
            monkey_name,
            items,
            operation,
            test,
            ifTrue,
            ifFalse,
            0
        };
        monkeyList.push_back(monkey);
    }

    for (int j = 0; j < 10000; j++) { 
        for(int i = 0; i < monkeyList.size(); i++) {
            while(monkeyList[i].items.size() > 0) {
                monkeyList[i].inspections += 1;
                long long curr = monkeyList[i].items.front();
                monkeyList[i].items.pop_front();
                curr = executeOperation(curr, monkeyList[i].operation);
                curr %= lcm;
                int idx = monkeyList[i].ifFalse;
                if (curr % monkeyList[i].test == 0) {
                    idx = monkeyList[i].ifTrue;
                }
                monkeyList[idx].items.push_back(curr % lcm);
            };
        }
    }
    long long max = 0, secondMax = 0;

    for (int i = 0; i < monkeyList.size(); i++) {
        if (monkeyList[i].inspections > max) {
            secondMax = max;
            max = monkeyList[i].inspections;
        } else if (monkeyList[i].inspections > secondMax) {
            secondMax = monkeyList[i].inspections;
        }
    }
    long long monkeyBusiness = max * secondMax;
    return monkeyBusiness;
}

int main() {
    ifstream MyInput("input.txt");
    string line;
    vector<string> input;
    
    while(getline(MyInput, line)) {
        input.push_back(line);
    }

    cout << part1(input) << endl << endl;
    cout << part2(input) << endl;
}