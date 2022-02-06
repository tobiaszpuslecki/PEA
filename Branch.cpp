#include "Branch.hpp"

using namespace std;

Branch::Branch()
{
}

Branch::Branch(const vector<vector<int> >& matrix_)
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

int Branch::alghoritm()
{

  // priority queue representing live nodes in tree
  priority_queue<Node*, std::vector<Node*>, comparator> liveNodes;

  vector<pair<int, int>> v;

  Node* root = newNode(matrix, v, 0, -1, 0); // start from 0

  // get the lower bound  at node 0
  root->cost = calculateCost(root->reducedMatrix);

  // Add root to list of live node
  liveNodes.push(root);

  while (!liveNodes.empty())
  {
      // live node with least est. cost, and then remove from list
      Node* min = liveNodes.top();
      liveNodes.pop();

      // all visited?
      if (min->depthLevel == dimension - 1)
      {
          // return to starting city
          min->path.push_back(make_pair(min->currentVertex, 0));

          int res = 0;
          for (int k = 0; k < min->path.size(); k++)
          {
              //cout << min->path[k].first << " -> " << min->path[k].second << endl;
              res += matrix[min->path[k].first][min->path[k].second];
              cout << " " << min->path[k].first;
          }
          cout << " " << min->path[0].first << "  ";
          return res;
      }

      // for every child of min(i, j) add an edge in space tree
      for (int j = 0; j < dimension; j++)
      {
          if (min->reducedMatrix[min->currentVertex][j] != INT_MAX)
          {
              // create new child node
              Node* child = newNode(min->reducedMatrix, min->path, min->depthLevel + 1, min->currentVertex, j);

              // cost is parent cost + cost of current edge + lower bound
              child->cost = min->cost + min->reducedMatrix[min->currentVertex][j] + calculateCost(child->reducedMatrix);

              // Add child
              liveNodes.push(child);
          }
      }
      delete min;
  }
  return 0;
}

Node* Branch::newNode(vector<vector<int> > parentMatrix, vector<pair<int, int>> const &path, int depthLevel, int from, int to)
{
    Node* node = new Node;
    matrix.resize(this->dimension, std::vector<int>(this->dimension));
    node->reducedMatrix.resize(this->dimension, std::vector<int>(this->dimension));

    // stores ancestors edges of state space tree
    node->path = path;

    // skip for root node
    if (depthLevel != 0)
        // add current edge to path
        node->path.push_back(make_pair(from, to));

    // copy
    for (size_t i = 0; i < this->dimension; i++)
    {
      for (size_t j = 0; j < this->dimension; j++)
      {
        node->reducedMatrix[i][j] = parentMatrix[i][j];
      }
    }

    // if depth level isnt zero, then assign INT_MAX
    if(depthLevel != 0)
    {
      for (int i = 0; i < dimension; i++)
      {
          node->reducedMatrix[from][i] = INT_MAX;
          node->reducedMatrix[i][to] = INT_MAX;
      }
    }

    // Set (j, 0) to inf
    node->reducedMatrix[to][0] = INT_MAX;

    node->depthLevel = depthLevel;

    node->currentVertex = to;

    return node;
}

// row reduction foo
void Branch::rowReduction(vector<vector<int> > reducedMatrix, vector<int> row)
{
    for (int& i : row)
        i = INT_MAX;

    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            if (reducedMatrix[i][j] < row[i])
                row[i] = reducedMatrix[i][j];

    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            if (reducedMatrix[i][j] != INT_MAX && row[i] != INT_MAX)
                reducedMatrix[i][j] -= row[i];
}

// column reduction foo
void Branch::columnReduction(vector<vector<int> > reducedMatrix, vector<int> col)
{
  for (int& i : col)
      i = INT_MAX;

    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            if (reducedMatrix[i][j] < col[j])
                col[j] = reducedMatrix[i][j];

    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            if (reducedMatrix[i][j] != INT_MAX && col[j] != INT_MAX)
                reducedMatrix[i][j] -= col[j];
}

// calc the lower bound
int Branch::calculateCost(vector<vector<int> > reducedMatrix)
{
    int cost = 0;

    vector<int> row(dimension, 0);
    rowReduction(reducedMatrix, row);

    vector<int> col(dimension, 0);
    columnReduction(reducedMatrix, col);

    for (int i = 0; i < dimension; i++)
    {
        cost += (row[i] != INT_MAX) ? row[i] : 0;
        cost += (col[i] != INT_MAX) ? col[i] : 0;
    }

    return cost;
}


int Branch::calculate()
{
  this->startTime = std::chrono::system_clock::now();
  int path = alghoritm();
  this->endTime = std::chrono::system_clock::now();
  return path;
}

double Branch::getExecutionTime()
{
  std::chrono::duration<double> elapsed_seconds = this->endTime - this->startTime;

  return elapsed_seconds.count();
}
