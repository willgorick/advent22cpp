#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int> > input2d;

int part1(vector<vector<int> > input) {
    int res = 0;
    vector<vector<bool> > visible(input.size(), vector<bool> (input[0].size(), false));

    // l -> r
    for(int i = 0; i < input.size(); i++) {
        int local_max = -1;
        for(int j = 0; j < input[i].size(); j++) {
            int curr = input[i][j];
            if (curr > local_max) {
                visible[i][j] = true;
                local_max = curr;
            }
        }
    }

    // r -> l
    for(int i = 0; i < input.size(); i++) {
        int local_max = -1;
        for(int j = input[i].size()-1; j >= 0; j--) {
            int curr = input[i][j];
            if (curr > local_max) {
                visible[i][j] = true;;
                local_max = curr;
            }
        }
    }

    // u -> d
    for(int j = 0; j < input[0].size(); j++) {
        int local_max = -1;
        for(int i = 0; i < input.size(); i++) {
            int curr = input[i][j];
            if (curr > local_max) {
                visible[i][j] = true;;
                local_max = curr;
            }
        }
    }

    // d -> u
    for(int j = 0; j < input[0].size(); j++) {
        int local_max = -1;
        for(int i = input.size()-1; i >= 0; i--) {
            int curr = input[i][j];
            if (curr > local_max) {
                visible[i][j] = true;;
                local_max = curr;
            }
        }
    }
    for(int i = 0; i < visible.size(); i++) {
        for(int j = 0; j < visible[i].size(); j++) {
            if (visible[i][j]) {
                res += 1;
            }
        }
    }

    return res;
}

int scenicScore(int i, int j) {
    int l_score = 0, r_score = 0, u_score = 0, d_score = 0;
    int house = input2d[i][j];
    int i_u = i-1, i_d = i+1, j_l = j-1, j_r = j+1;

    // up_score
    while(i_u >= 0) {
        u_score += 1;
        if (input2d[i_u][j] >= house) {
            break;
        }
        i_u -= 1;
    }

    // down_score
    while(i_d < input2d.size()) {
        d_score += 1;
        if (input2d[i_d][j] >= house) {
            break;
        }
        i_d += 1;
    }

    // left_score
    while (j_l >= 0) {
        l_score += 1;
        if (input2d[i][j_l] >= house) {
            break;
        }
        j_l -= 1;
    }

    // right_score
    while (j_r < input2d[i].size()) {
        r_score += 1;
        if (input2d[i][j_r] >= house) {
            break;
        }
        j_r += 1;
    }


    int res = l_score * r_score * u_score * d_score;
    return res;
}

int part2(vector<vector<int> > input) {
    int res = 0;
    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[i].size(); j++) {
            res = max(res, scenicScore(i, j));
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


    for(int i = 0; i < input.size(); i++) {
        vector<int> line;
        for(int j = 0; j < input[i].size(); j++) {
            int s = int(input[i][j]) - 48;
            line.push_back(s);
        }
        input2d.push_back(line);
    }

    cout << part1(input2d) << endl;
    cout << part2(input2d) << endl;
}