#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

class TSP
{
private:
  int dimension;
  vector<vector<int> > matrix;

public:
  TSP();
  TSP(const int dimension);
  TSP(const string& filename);
  int getDimension();
  vector<vector<int> > getMatrix();
  void printMatrix();

};
