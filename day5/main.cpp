#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <functional>
#include <string>
#include <cctype> 

using namespace std;

vector<string> delimiters = {" from ", " to "};
vector<int> delimiter_lengths = {6, 4};

void print_queue(deque<string> queue) {
    for (int i = 0; i < queue.size(); i++) {
        cout << queue[i];
        if (i < queue.size()-1) {
             cout << " -> ";
        }
    }
    cout << endl;
}

void print_all_queus_from_stack(unordered_map<int, deque<string> > stack_map) {
    for (int i = 1; i < stack_map.size()+1; i++) {
        print_queue(stack_map[i]);
    }
}

bool isAllSpaces(string check) {
    string strippedCheck;
    for (int i = 0; i < check.size(); i++) {
        if (check[i] != ' ') {
            strippedCheck.append(&check[i]);
        }
    }
    return !strippedCheck.size();
}

unordered_map<int, deque<string> > parseStacksAndIncrementPointer(vector<string> input, int* i) {
    unordered_map<int, deque<string> > stack_map;
    while(input[*i] != "") {
        string line = input[*i];
        try {
            stoi(line);
            *i += 1;
            break;
        }
        catch(exception &err) {
            for(int j = 0; j < line.size(); j += 4) {
                int ind = (j / 4) + 1;
                string curr = line.substr(j+1, 1);
                
                if (!isAllSpaces(curr)) {
                    if (stack_map.count(ind)) {
                        stack_map[ind].push_back(curr);
                    } else {
                        deque<string> temp;
                        temp.clear();
                        temp.push_back(curr);
                        stack_map[ind] = temp;
                    }
                }
            }
            *i += 1;
        }
    }
    *i += 1;
    return stack_map;
}

void moveCrates9000(unordered_map<int, deque<string> >* stack_map, int i, vector<string> input) {
    while (i < input.size()) {
        deque<string> temp_queue;
        string line = input[i];
        string relevant = line.substr(5, line.size()-5);
        int fromIndex = relevant.find(delimiters[0]);
        int count = stoi(relevant.substr(0, line.size()-fromIndex));
        string stacks = relevant.substr(fromIndex+delimiter_lengths[0], relevant.size()-fromIndex+1);
        int toIndex = stacks.find(delimiters[1]);
        int source = stoi(stacks.substr(0, stacks.size()-toIndex));
        int destination = stoi(stacks.substr(toIndex+delimiter_lengths[1], stacks.size()-toIndex-delimiter_lengths[1]));
        for (int i = 0; i < count; i++) {
            (*stack_map)[destination].push_front((*stack_map)[source].front());
            (*stack_map)[source].pop_front();
        }
        
        i += 1;
    }
}

void moveCrates9001(unordered_map<int, deque<string> >* stack_map, int i, vector<string> input) {
    while (i < input.size()) {
        deque<string> temp_queue;
        string line = input[i];
        string relevant = line.substr(5, line.size()-5);
        int fromIndex = relevant.find(delimiters[0]);
        int count = stoi(relevant.substr(0, line.size()-fromIndex));
        string stacks = relevant.substr(fromIndex+delimiter_lengths[0], relevant.size()-fromIndex+1);
        int toIndex = stacks.find(delimiters[1]);
        int source = stoi(stacks.substr(0, stacks.size()-toIndex));
        int destination = stoi(stacks.substr(toIndex+delimiter_lengths[1], stacks.size()-toIndex-delimiter_lengths[1]));
        for (int i = 0; i < count; i++) {
            temp_queue.push_front((*stack_map)[source].front());
            (*stack_map)[source].pop_front();
        }
        for (int i = 0; i < count; i++) {
            (*stack_map)[destination].push_front(temp_queue.front());
            temp_queue.pop_front();
        }
        
        i += 1;
    }
}

string part1(vector<string> input) {
    string res;
    int i = 0;
    unordered_map<int, deque<string> > stack_map = parseStacksAndIncrementPointer(input, &i);
    moveCrates9000(&stack_map, i, input);

    for (int i = 1; i < stack_map.size()+1; i++) {
        res.append(stack_map[i].front());
    }
    return res;
}

string part2(vector<string> input) {
    string res;
    int i = 0;
    unordered_map<int, deque<string> > stack_map = parseStacksAndIncrementPointer(input, &i);
    moveCrates9001(&stack_map, i, input);

    for (int i = 1; i < stack_map.size()+1; i++) {
        res.append(stack_map[i].front());
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