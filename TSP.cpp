#include "TSP.hpp"

using namespace std;

TSP::TSP()
{
}

// ctor with dimension as arg. Generates random NxN matrix
TSP::TSP(const int dimension)
{

  //std::default_random_engine generator;
  //std::uniform_int_distribution<int> distribution(1,100);
  //auto getRandomInt = std::bind ( distribution, generator );

    srand ((unsigned int)time(NULL));
    
    this->dimension = dimension;
    
  matrix.resize(dimension, std::vector<int>(dimension));

  for(int i=0; i<dimension ; i++)
  {
    for(int j=0; j<dimension ; j++)
    {
      if(i==j)
        matrix[i][j]=-1;
      else
        matrix[i][j] = rand() % 100 + 1; //getRandomInt();
    }
  }
}

//ctor with filename as arg
TSP::TSP(const string& filename)
{
    size_t found = filename.find(".atsp");
    if (found != string::npos)
    {
        ifstream myfile (filename);
        if (myfile.is_open())
        {
            string sbuffer;
            int iBuffer;
            
            while(sbuffer != "DIMENSION:")
                myfile >> sbuffer;
          myfile >> iBuffer;
          this->dimension = iBuffer;
          matrix.resize(dimension, std::vector<int>(dimension));

            while(sbuffer != "EDGE_WEIGHT_SECTION")
                myfile >> sbuffer;
            
//            myfile >> iBuffer;
//            cout << "ibuffer: " << iBuffer << " $ ";
//
          for(int i=0; i<dimension ; i++)
          {
            for(int j=0; j<dimension ; j++)
            {
              myfile >> matrix[i][j];
            }
          }
          myfile.close();
          cout << endl << filename << " loaded." << endl;
        }

        else
        {
          cout << "Unable to open file";
          terminate();
        }
    }
    else
    {
          int iBuffer;
          ifstream myfile (filename);
          if (myfile.is_open())
          {
            myfile >> iBuffer;
            this->dimension = iBuffer;
            matrix.resize(dimension, std::vector<int>(dimension));

            for(int i=0; i<dimension ; i++)
            {
              for(int j=0; j<dimension ; j++)
              {
                myfile >> matrix[i][j];
              }
            }
            myfile.close();
            cout << filename << " loaded." << endl;
          }

          else
          {
            cout << "Unable to open file";
            terminate();
          }
        
    }
}

// dimension getter
int TSP::getDimension()
{
	return this->dimension;
}

// matrix getter
vector<vector<int> > TSP::getMatrix()
{
  int rows = this->dimension;
  int cols = this->dimension;


  std::vector<std::vector<int> > retValue(rows);
  std::vector<std::vector<int> >::iterator i;
  for(i = retValue.begin(); i != retValue.end(); ++i)
  {
    i->resize(cols);
  }

  for(int i=0; i<dimension ; i++)
  {
    for(int j=0; j<dimension ; j++)
    {
      retValue[i][j] = matrix[i][j];
    }
  }

  return retValue;
}


void TSP::printMatrix()
{
    for(int i=0; i<dimension ; i++)
    {
      for(int j=0; j<dimension ; j++)
      {
          cout << " " << matrix[i][j];
      }
        cout << endl;
    }
}


//
