#include "Brutal.hpp"

using namespace std;

Brutal::Brutal()
{
}

// brutal force alg
Brutal::Brutal(const vector<vector<int> >& matrix_)
{
  // inits
  this->dimension = static_cast<int>(matrix_.size());
  matrix.resize(this->dimension, std::vector<int>(this->dimension));
  best.resize(this->dimension);
    

  // matrix init
  for(int i=0; i<this->dimension ; i++)
  {
    for(int j=0; j<this->dimension ; j++)
    {
      matrix[i][j] = matrix_[i][j];
    }
  }
}

int Brutal::alghoritm()
{
  // init permutation array
  int* permutation = new int[this->dimension];
  for (auto i = 0; i < this->dimension; i++)
    permutation[i]=i;
  //std::sort (permutation,permutation+this->dimension);

  int temp_path = 0;
  int best_path=INT_MAX;

  do
  {
      temp_path=0;

      // calculate temporary path for current permutation
      for(int i = 0; i<this->dimension-1;i++)
      {
          temp_path+=matrix[ permutation[i] ][ permutation[i+1] ];
      }
      temp_path+=matrix[ permutation[this->dimension-1] ][ permutation[0] ];

      // update if better solution found
      if(temp_path<best_path)
      {
            best_path = temp_path;
          for (int k=0; k<dimension; k++) {
              best[k] = permutation[k];
          }
      }
      
  // find next permutations
  } while ( std::next_permutation(permutation,permutation+this->dimension) );
    
    for (int k=0; k<dimension; k++) {
        cout << " " << best[k];
    }
    cout << " " << best[0] << "   ";
    
  return best_path;
}


int Brutal::calculate()
{
  this->startTime = std::chrono::system_clock::now();
  int path = alghoritm();
  this->endTime = std::chrono::system_clock::now();
  return path;
}

double Brutal::getExecutionTime()
{
  std::chrono::duration<double> elapsed_seconds = this->endTime - this->startTime;

  return elapsed_seconds.count();
}
