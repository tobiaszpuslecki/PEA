#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;


struct Node
{
    // stores edges of state space tree
    vector<pair<int, int>> path;

    vector<vector<int> > reducedMatrix;

    // lower bound
    int cost;

    int currentVertex;

    // stores number of visited cities
    int depthLevel;
};


struct comparator {
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return lhs->cost > rhs->cost;
    }
};


class Branch
{
private:
  int dimension;
  double executionTime;
  std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
  vector<vector<int> > matrix;

  Node* newNode(vector<vector<int> > parentMatrix, vector<pair<int, int>> const &path, int depthLevel, int from, int to);
  void rowReduction(vector<vector<int> > reducedMatrix, vector<int> row);
  void columnReduction(vector<vector<int> > reducedMatrix, vector<int> col);
  int calculateCost(vector<vector<int> > reducedMatrix);

  int alghoritm();

public:
  Branch();
  Branch(const vector<vector<int> >& matrix_);
  int calculate();
  double getExecutionTime();
};
