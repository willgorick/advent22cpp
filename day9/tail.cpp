#include "tail.h"
using namespace std;

bool moveTail(std::vector<int> t_loc, std::vector<int> h_loc) {
  // If tail is overlapping or within 1 coord in any direction, don't move
  if (abs(h_loc[0] - t_loc[0]) <= 1 && abs(h_loc[1] - t_loc[1]) <= 1) {
    return false;
  }
  return true;
}

std::vector<int> updateTail(std::vector<int> t_loc, std::vector<int> h_loc) {
  if (!moveTail(t_loc, h_loc)) {
      return t_loc;
  }

  // Same x value
  if (t_loc[0] == h_loc[0]) {
    // Tail below head
    if (t_loc[1] < h_loc[1]) {
      t_loc[1] += 1;
    //Tail above head
    } else if (t_loc[1] > h_loc[1]) {
      t_loc[1] -= 1;
    }

  // Same y value
  } else if (t_loc[1] == h_loc[1]) {
    // Tail left of head
    if (t_loc[0] < h_loc[0]) {
      t_loc[0] += 1;
    //Tail right of head
    } else if (t_loc[0] > h_loc[0]) {
      t_loc[0] -= 1;
    }

  //Diagonals
  } else {
    // Tail is left and below
    if ((t_loc[0] < h_loc[0]) && (t_loc[1] < h_loc[1])) {
      t_loc[0] += 1;
      t_loc[1] += 1;
    
    // Tail is right and below
    } else if ((t_loc[0] > h_loc[0]) && (t_loc[1] < h_loc[1])) {
      t_loc[0] -= 1;
      t_loc[1] += 1;

    // Tail is left and above
    } else if ((t_loc[0] < h_loc[0]) && (t_loc[1] > h_loc[1])) {
      t_loc[0] += 1;
      t_loc[1] -= 1;

    // Tail is right and above
    } else if ((t_loc[0] > h_loc[0]) && (t_loc[1] > h_loc[1])) {
      t_loc[0] -= 1;
      t_loc[1] -= 1;
    }
  }

  return t_loc;
}