#pragma once

#include <chrono>
#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Tabu
{
private:
    int dimension;
    double executionTime;
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    vector<vector<int> > matrix;
    vector<vector<int> > tabuList;
    int tabuListMaxSize;
    int tabuListSize;
    std::pair <int,int> change;
    int stopCriteria;
    int maxOrderNotChanged;
    
    bool listContains(int vA, int vB);
    void listClear();
    void insertList(int vA, int vB);
    std::pair<int, int> randomSwap(vector<int> &v);
    vector<int> getNextRandomChange(vector<int> v);
    vector<int> getNearestNeighbour();
    bool allVisited(vector<bool> visited);
    int getTotalCost(vector<int> vec);
    std::pair<int, int> getRandomPair();
    void decrementTabuList();
    int alghoritm();
    
public:
  Tabu();
  Tabu(const vector<vector<int> >& matrix_);
  int calculate(int stopCriteria_,int maxOrderNotChanged_);
  double getExecutionTime();
    
};
