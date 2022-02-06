#include "SA.hpp"

using namespace std;

SA::SA()
{
}

// ctor with matrix inits
SA::SA(const vector<vector<int> >& matrix_)
{
  this->dimension = static_cast<int>(matrix_.size());
  matrix.resize(this->dimension, std::vector<int>(this->dimension));

  for(int i=0; i<this->dimension ; i++)
  {
    for(int j=0; j<this->dimension ; j++)
    {
      matrix[i][j] = matrix_[i][j];
    }
  }    
}

// sa alghoritm
int SA::alghoritm()
{
    // needed inits
    current_temperature = initial_temperature;
    current_path.resize(this->dimension);
    best_path.resize(this->dimension);

    // current path init as nearest neighbour alg.
    current_path = getNearestNeighbour();
    current_length = getTotalCost(current_path);

    // best path init as current path summary length
    for (size_t i = 0; i < dimension; i++)
      best_path[i] = current_path[i];
    best_length = current_length;

    // random seed init
    srand((unsigned int)time(NULL));

    
    // time stop criteria init
    auto internalBeginTime = std::chrono::system_clock::now();
    auto currentTimeInSeconds = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds;
    
    // main part of alg
    while (current_temperature > minimal_temperature)
    {
        // for 0..iterations do
        for (int j = 0; j < iterations; j++)
        {
            
            // stop criteria implementation
            currentTimeInSeconds = std::chrono::system_clock::now();
            elapsed_seconds = currentTimeInSeconds - internalBeginTime;
            if ( elapsed_seconds.count() > stopCriteria)
            {
                return best_length;
            }
            
            
            // make random swap
            random_swap();
            // calculate current path
            current_length = getTotalCost(current_path);
            // if current path is better than best lenth OR calculated exp probability is bigger than rand
            if (current_length < best_length or ((double)rand() / (double)RAND_MAX) < probability())
            {

                foundInTime = (double)elapsed_seconds.count();
                
                
                // update best parameters
                best_path = current_path;
                best_length = current_length;
            }
        }
        // cooling
        current_temperature *= cooling_temperature;
    }
    
    return best_length;
}

int SA::calculate(unsigned int it,int stopCriteria_,double minTemp,double coolTemp)
{
    // setters for params
    set_iterations(it);
    set_minimal_temperature(minTemp);
    set_initial_temperature(generateInitialTemperature());
    set_cooling_temperature(coolTemp);
    stopCriteria = stopCriteria_;
    
  this->startTime = std::chrono::system_clock::now();
  int path = alghoritm();
  this->endTime = std::chrono::system_clock::now();
    
    for (int k=0; k<dimension; k++) {
        cout << " " << best_path[k];
    }
    cout << " " << best_path[0] << "  " << " | Found in : " << foundInTime << " | ";
    
  return path;
}

double SA::getExecutionTime()
{
  std::chrono::duration<double> elapsed_seconds = this->endTime - this->startTime;

  return elapsed_seconds.count();
}

// getters for params
int SA::get_iterations() { return iterations; }
double SA::get_minimal_temperature() { return minimal_temperature; }
double SA::get_initial_temperature() { return initial_temperature; }
double SA::get_cooling_temperature() { return cooling_temperature; }

// setters for params
void SA::set_iterations(int i){iterations=i;};
void SA::set_minimal_temperature(double t){minimal_temperature=t;};
void SA::set_initial_temperature(double t){initial_temperature=t;};
void SA::set_cooling_temperature(double t){cooling_temperature=t;};

// random swapping
void SA::random_swap()
{
    int a = std::rand() % dimension;
    int b = std::rand() % dimension;
    while (a == b) b = std::rand() % dimension;

    current_path = best_path;
    int temporary = current_path[a];
    current_path[a] = current_path[b];
    current_path[b] = temporary;
}

// path calculating
int SA::getTotalCost(vector<int> vec)
{
    int len = 0;
    
    for(int i = 0; i< dimension-1 ;i++)
    {
        len+=matrix[ vec[i] ][ vec[i+1] ];
    }
    len+=matrix[ vec[dimension-1] ][ vec[0] ];

    return len;
    
}

// exp probability calculation
double SA::probability()
{
    double power = -((current_length - best_length) / current_temperature);
    return pow(M_E, power);
}

double SA::generateInitialTemperature()
{
    return 5 * getTotalCost(getNearestNeighbour());
}


vector<int> SA::getNearestNeighbour()
{
    vector<int> result;
    vector<bool> visited;
    result.resize(dimension, 0);
    visited.resize(dimension, false);
    
    
    result[0]=0;
    int idx=1;
    
    visited[0]=true;


    int minPath=INT_MAX;
    int minCity=-1;
    int enteredCity=0;


    while (!allVisited(visited))
    {
        for (int j = 0; j < dimension; j++)
        {
            if (matrix[enteredCity][j]<minPath && enteredCity != j && visited[j] != true)
            {
                minPath = matrix[enteredCity][j];
                minCity=j;
            }
        }
        result[idx++]=minCity;
        visited[minCity]=true;
        minPath=INT_MAX;
        enteredCity=minCity;
    }

    return result;

}

bool SA::allVisited(vector<bool> visited)
{
    for (const auto i : visited)
    {
        if(i == false)
        {
            return false;
        }
    }
    return true;
}
