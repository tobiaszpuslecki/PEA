#pragma once

#include <limits>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Brutal
{
private:
  int dimension;
  double executionTime;
  std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
  vector<vector<int> > matrix;
  vector<int> best;

  int alghoritm();

public:
  Brutal();
  Brutal(const vector<vector<int> >& matrix_);

  int calculate();
  double getExecutionTime();
};
