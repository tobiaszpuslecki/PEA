#include "Dynamic.hpp"

using namespace std;

Dynamic::Dynamic()
{
}

Dynamic::Dynamic(const vector<vector<int> >& matrix_)
{
  // inits
  this->dimension = static_cast<int>(matrix_.size());
  matrix.resize(this->dimension, std::vector<int>(this->dimension));
  visited.resize(this->dimension, 0);

  // matrix init
  for(int i=0; i<this->dimension ; i++)
  {
    for(int j=0; j<this->dimension ; j++)
    {
      matrix[i][j] = matrix_[i][j];
    }
  }

}

////    If size of S is 2, then S must be {1, i},
////     C(S, i) = dist(1, i)
////    Else if size of S is greater than 2.
////     C(S, i) = min { C(S-{i}, j) + dis(j, i)} where j belongs to S, j != i and j != 1.
void Dynamic::alghoritm(int nowVisited)
{
    visited[nowVisited]=1;
 
    cout << " " <<nowVisited;
    
    int toCity=INT_MAX;
    int calculatedMinimum=INT_MAX;
    int pathFromCalculatedMinimum=0;
 
    for(int i=0;i < dimension;i++)
    {
        if( ( not visited[i] ) && ( nowVisited != i ) )
            if( matrix[nowVisited][i] + matrix[i][nowVisited] < calculatedMinimum )
            {
                calculatedMinimum = matrix[i][0] + matrix[nowVisited][i];
                pathFromCalculatedMinimum = matrix[nowVisited][i];
                toCity = i;
            }
    }
 
    if(calculatedMinimum != INT_MAX)
        path+=pathFromCalculatedMinimum;
     
    if(toCity==INT_MAX)
    {
        toCity=0;
        cout << " " <<toCity << "  ";
        path+=matrix[nowVisited][toCity];
 
        return;
    }

    alghoritm(toCity);
}

int Dynamic::calculate()
{
  path = 0;
  this->startTime = std::chrono::system_clock::now();
  alghoritm(0);
  this->endTime = std::chrono::system_clock::now();

  return path;
}

double Dynamic::getExecutionTime()
{
  std::chrono::duration<double> elapsed_seconds = this->endTime - this->startTime;

  return elapsed_seconds.count();
}

 
