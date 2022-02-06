#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class SA
{
private:
    int dimension;
    double executionTime;
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    vector<vector<int> > matrix;

    int alghoritm();
    
    double cooling_temperature;
    double initial_temperature;
    double minimal_temperature;
    unsigned int iterations;
    double current_temperature;
    int stopCriteria;
    
    double current_length;
    double best_length;
    vector<int> current_path;
    vector<int> best_path;
    
    void random_swap();
    double probability();
    int getTotalCost(vector<int> vec);
    
    double generateInitialTemperature();
    vector<int> getNearestNeighbour();
    bool allVisited(vector<bool> visited);
    
    double foundInTime = 0.0;
    

public:
    SA();
    SA(const vector<vector<int> >& matrix_);
    int calculate(unsigned int it,int stopCriteria_,double minTemp,double coolTemp);
    double getExecutionTime();
        
    int get_iterations();
    double get_minimal_temperature();
    double get_initial_temperature();
    double get_cooling_temperature();

    void set_iterations(int i);
    void set_minimal_temperature(double t);
    void set_initial_temperature(double t);
    void set_cooling_temperature(double t);

};
