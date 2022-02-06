#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <math.h>

using namespace std;

class Dynamic
{
private:
  int dimension;
  double executionTime;
  std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
  vector<vector<int> > matrix;
    vector<int> visited;
    int path;

    void alghoritm(int);
    
public:
  Dynamic();
  Dynamic(const vector<vector<int> >& matrix_);

  int calculate();
  double getExecutionTime();
};
