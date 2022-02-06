#include "Tabu.hpp"

using namespace std;

Tabu::Tabu()
{
}

// ctor with matrix inits
Tabu::Tabu(const vector<vector<int> >& matrix_)
{
    
    this->dimension = static_cast<int>(matrix_.size());
    matrix.resize(this->dimension, std::vector<int>(this->dimension));
    tabuList.resize(this->dimension, std::vector<int>(this->dimension));


    for(int i=0; i<this->dimension ; i++)
        for(int j=0; j<this->dimension ; j++)
          matrix[i][j] = matrix_[i][j];
}

// tabu search alg.
int Tabu::alghoritm()
{
    // needed inits
    int orderNotChanged = 0;

    // current path init as nearest neighbour alg.
    vector<int> currentPath = getNearestNeighbour();
    vector <int> bestPath = currentPath;

    // best path init as current path summary length
    int bestLength = getTotalCost(bestPath);
    
    // random seed init
    srand((unsigned int)time(NULL));
    
    // time stop criteria init
    double foundInTime = 0.0;
    auto internalBeginTime = std::chrono::system_clock::now();
    auto currentTimeInSeconds = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds;
    
    while (true)
    {
        // stop criteria implementation
        currentTimeInSeconds = std::chrono::system_clock::now();
        elapsed_seconds = currentTimeInSeconds - internalBeginTime;

        if ( elapsed_seconds.count() > stopCriteria)
        {
            break;
        }
        
        // generate random change
        currentPath = getNextRandomChange(currentPath);
        int currentOrderDistance = getTotalCost(currentPath);

        // update if better than current
        if (currentOrderDistance < bestLength)
        {
            foundInTime = (double)elapsed_seconds.count();
            bestPath = currentPath;
            bestLength = getTotalCost(bestPath);
            orderNotChanged = 0;
        }
        else
        {
            orderNotChanged++;
            insertList(change.first, change.second);
        }

        // if not changed in maxOrderNotChanged -> make swaps and clear
        if (orderNotChanged >= maxOrderNotChanged)
        {
            for (int i = 0; i < 1000; i++)
                randomSwap(currentPath);

            orderNotChanged = 0;
            listClear();
        }
        // decrement all possible edges
        decrementTabuList();
    }

    for (const auto i : bestPath) {
        cout << " " << i;
    }
    cout << " " << bestPath[0] << "  " << " | Found in : " << foundInTime << " | ";

    return bestLength;
}

int Tabu::calculate(int stopCriteria_,int maxOrderNotChanged_)
{
    stopCriteria = stopCriteria_;
    maxOrderNotChanged = maxOrderNotChanged_;
    tabuListMaxSize = static_cast<int>(dimension/10);
    tabuListSize = 0;
    
  this->startTime = std::chrono::system_clock::now();
  int path = alghoritm();
  this->endTime = std::chrono::system_clock::now();
  return path;
}

double Tabu::getExecutionTime()
{
  std::chrono::duration<double> elapsed_seconds = this->endTime - this->startTime;

  return elapsed_seconds.count();
}

bool Tabu::listContains(int vA, int vB)
{
    return tabuList[vA][vB] >= 1;
}

void Tabu::listClear()
{
    tabuListSize = 0;
    
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            tabuList[i][j] = 0;
}


void Tabu::insertList(int vA, int vB)
{
    if (tabuListSize < tabuListMaxSize)
    {
        tabuList[vA][vB] = 5;
        tabuListSize++;
    }
}

int Tabu::getTotalCost(vector<int> vec)
{
    int len = 0;
    
    for(int i = 0; i< dimension-1 ;i++)
    {
        len+=matrix[ vec[i] ][ vec[i+1] ];
    }
    len+=matrix[ vec[dimension-1] ][ vec[0] ];

    return len;
    
}

vector<int> Tabu::getNearestNeighbour()
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

bool Tabu::allVisited(vector<bool> visited)
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

std::pair<int, int> Tabu::randomSwap(vector<int> &v)
{
    std::pair<int, int> pair = getRandomPair();

    swap(v[pair.first], v[pair.second]);
    
    return pair;
}

std::pair<int, int> Tabu::getRandomPair()
{
    std::pair<int, int> result;
    
    //srand((unsigned int)time(NULL));
    
    result.first = rand() % (dimension - 1) + 1;
    result.second = rand() % (dimension - 1) + 1;
    while (result.first == result.second)
        result.second = rand() % (dimension - 1) + 1;
    
    return result;
}

vector<int> Tabu::getNextRandomChange(vector<int> v)
{
    vector<int> nextRandomPath(v);

    for (int i = 0; i < sqrt(dimension); i++)
    {
        vector<int> newRandomPath(nextRandomPath);

        std::pair<int, int> pair = randomSwap(newRandomPath);
        

        
        bool lc = listContains(pair.first, pair.second);
        auto gtc1 = getTotalCost(newRandomPath);
        auto gtc2 = getTotalCost(nextRandomPath);
        //if (not listContains(pair.first, pair.second)
        if (not lc
            && gtc1 < gtc2)
        {
            nextRandomPath = newRandomPath;
            change = pair;
        }
    }
    return nextRandomPath;
}

void Tabu::decrementTabuList()
{
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            if (tabuList[i][j] > 0)
                tabuList[i][j]--;
}
