#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct File {
    int size;
    string name, type;
};

struct Directory {
    string name, type;
    int res;
    vector<File> files;
    Directory *parent, *root;
    vector<Directory> directories;
    vector<int> size_list;
};

void parse_input(vector<string> input, Directory *curr_dir) {
    for(int i = 0; i < input.size(); i++) {
        string line = input[i];
        if (line[0] == '$') { //Command is being issued
            if (line == "$ cd ..") { // Go up one directory level
                curr_dir = curr_dir->parent;
            } else if(line == "$ cd /") { // Go up to root
                curr_dir = curr_dir->root;
            } else if(line.substr(0, 4) == "$ cd") { // Go down into specific folder
                string targetDir = line.substr(5, line.size()-5);
                for (int i = 0; i < curr_dir->directories.size(); i++) {
                    if (curr_dir->directories[i].name == targetDir) {
                        curr_dir = &(curr_dir->directories[i]);
                        break;
                    }
                }
            } //The only other option is an ls command, which we don't need to handle
        } else { // Not a command so we're in the middle of an ls output
            int spaceIndex = line.find(" ");
            string dirOrNumber = line.substr(0, spaceIndex);
            string name = line.substr(spaceIndex+1, line.size()-spaceIndex-1);
            if (isdigit(dirOrNumber[0])) { // We're looking at a file
                int size = stoi(dirOrNumber);
                File file = {
                    size,
                    name,
                    "file"
                };
                curr_dir->files.push_back(file);
            } else { // We're looking at a dir
                vector<File> files;
                vector<Directory> dirs;
                Directory dir = {
                    name,
                    "dir",
                    0,
                    files,
                    curr_dir,
                    curr_dir->root,
                    dirs
                };
                curr_dir->directories.push_back(dir);
            }
        }
    }
}

int dfsSolve(Directory *curr_dir) {
    int curr_res = 0;
    for (int i = 0; i < curr_dir->files.size(); i++) {
        curr_res += curr_dir->files[i].size;
    }
    for (int i = 0; i < curr_dir->directories.size(); i++) {
        curr_res += dfsSolve(&(curr_dir->directories[i]));
    }
    if (curr_res <= 100000) {
        curr_dir->root->res += curr_res;
    }
    curr_dir->root->size_list.push_back(curr_res);

    return curr_res;
}

int main() {
    ifstream MyInput("input.txt");
    string line;
    vector<string> input;
    
    while(getline(MyInput, line)) {
        input.push_back(line);
    }

    vector<File> files;
    vector<Directory> dirs;
    vector<int> size_list;

    Directory root = {
        "/",
        "dir",
        0,
        files,
        NULL,
        NULL,
        dirs,
        size_list
    };
    root.root = &root;
    root.parent = NULL;
    root.directories = dirs;

    parse_input(input, &root);
    int totalCap = 70000000;
    int totalUsed = dfsSolve(&root);

    cout << "Part 1: " << root.res << endl;
    int unused = totalCap - totalUsed;
    int min_goal = 30000000 - unused;
    int best_to_delete = totalUsed;

    for (int i = 0; i < root.size_list.size(); i++) {
        int curr_size = root.size_list[i];
        if (curr_size > min_goal && curr_size < best_to_delete) {
            best_to_delete = curr_size;
        }
    }
    cout << "Part 2: " << best_to_delete << endl;
}