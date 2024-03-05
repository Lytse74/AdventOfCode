#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <iomanip>
#include <set>
#include <map>
#include <algorithm>

using std::cout;
using std::endl;
using std::get;
using std::make_pair;
using std::make_tuple;
using std::map;
using std::multimap;
using std::pair;
using std::set;
using std::string;
using std::tie;
using std::tuple;
using std::vector;

int main()
{
  // open the file
  std::ifstream is("day17.input");
  std::string str;

  vector<vector<int>> grid;

  while (getline(is, str))
  {
    std::istringstream iss(str);
    char ch;
    vector<int> row;

    while (iss.get(ch))
    {
      row.push_back(ch - '0');
    }
    grid.push_back(row);
  }

  cout << endl;

  is.close();

  // find cheapest path from ( 0, 0) to (n-1, n-1)
  // restrictions
  // turn 90%
  // max 3 in same dir

  // Create graph
  // nodes
  // edges -> cost
  multimap< 
      tuple<char, short, int, int>
    , pair<int,tuple<char, short, int, int>> > edge_cost;
  multimap< 
      tuple<char, short, int, int>
    , pair<int,tuple<char, short, int, int>> >::iterator edge_cost_it;
  // nodes -> costs
  map<pair<pair<char, short>, pair<int, int>>, int> path_cost;
  set<pair<pair<char, short>, pair<int, int>>> nodes_u;
  set<pair<pair<char, short>, pair<int, int>>> nodes_v;

  for (auto i = 0; i < grid.size(); i++)
  {
    for (auto j = 0; j < grid[i].size(); j++)
    {
      if (i == 0 && j == 0)
      {
        nodes_u.insert(make_pair(make_pair('-', 0), make_pair(i, j)));
        path_cost[make_pair(make_pair('-', 0), make_pair(i, j))] = 0;
        edge_cost.insert(make_pair( make_tuple('-', 0, i, j), make_pair(grid[i][j+1], make_tuple('L', 1, i, j + 1)) ));
        edge_cost.insert(make_pair( make_tuple('-', 0, i, j), make_pair(grid[i+1][j], make_tuple('D', 1, i + 1, j)) ));
      }
      if (j > 0)
      {
        nodes_u.insert(make_pair(make_pair('L', 1), make_pair(i, j)));
        for (int t = 1; t<10; t++)
        {
          if (j > t)
          {
            nodes_u.insert(make_pair(make_pair('L', t+1), make_pair(i, j)));
            edge_cost.insert(make_pair( make_tuple('L', t, i, j - 1), make_pair( grid[i][j], make_tuple('L', t+1, i, j)) ));
          }
        }
        for (int t = 3; t<10; t++)
        {
          if (i > t)
            edge_cost.insert(make_pair(make_tuple('D', t+1, i, j - 1), make_pair( grid[i][j], make_tuple('L', 1, i, j)) ));
        }
        for (int t = 3; t<10; t++)
        {
          if (i < grid.size() - (t+1) )
            edge_cost.insert(make_pair(make_tuple('U', t+1, i, j - 1), make_pair( grid[i][j], make_tuple('L', 1, i, j)) ));
        }
      }
      if (j != grid[i].size() - 1)
      {
        if (i != 0 || j != 0)
        {
          nodes_u.insert(make_pair(make_pair('R', 1), make_pair(i, j)));
          for (int t = 1; t<10; t++)
          {
            if (j < grid[i].size() - (t+1) )
            {
              nodes_u.insert(make_pair(make_pair('R', t+1), make_pair(i, j)));
              edge_cost.insert(make_pair(make_tuple('R', t, i, j + 1), make_pair( grid[i][j], make_tuple('R', t+1, i, j)) ));
            }
          }
          for (int t = 3; t<10; t++)
          {
            if (i > t)
              edge_cost.insert(make_pair(make_tuple('D', t+1, i, j + 1), make_pair( grid[i][j], make_tuple('R', 1, i, j)) ));
          }
          for (int t = 3; t<10; t++)
          {
            if (i < grid.size() - (t+1) )
              edge_cost.insert(make_pair(make_tuple('U', t+1, i, j + 1), make_pair( grid[i][j], make_tuple('R', 1, i, j)) ));
          }
        }
      }
      if (i != 0)
      {
        nodes_u.insert(make_pair(make_pair('D', 1), make_pair(i, j)));
        for (int t = 1; t<10; t++)
        {
          if (i > t)
          {
            edge_cost.insert(make_pair(make_tuple('D', t, i - 1, j), make_pair( grid[i][j], make_tuple('D', t+1, i, j)) ));
            nodes_u.insert(make_pair(make_pair('D', t+1), make_pair(i, j)));
          }
        }
        for (int t = 3; t<10; t++)
        {
          if (j > t)
            edge_cost.insert(make_pair(make_tuple('L', t+1, i - 1, j), make_pair( grid[i][j], make_tuple('D', 1, i, j)) ));
        }
        for (int t = 3; t<10; t++)
        {
          if (j < grid.size() - (t+1) )
            edge_cost.insert(make_pair(make_tuple('R', t+1, i - 1, j), make_pair( grid[i][j], make_tuple('D', 1, i, j)) ));
        }
      }
      if (i != grid.size() - 1)
      {
        if (i != 0 || j != 0)
        {
          nodes_u.insert(make_pair(make_pair('U', 1), make_pair(i, j)));
          for (int t = 1; t<10; t++)
          {
            if (i < grid[i].size() - (t+1) )
            {
              nodes_u.insert(make_pair(make_pair('U', t+1), make_pair(i, j)));
              edge_cost.insert(make_pair(make_tuple('U', t, i + 1, j), make_pair( grid[i][j], make_tuple('U', t+1, i, j)) ));
            }
          }
          for (int t = 3; t<10; t++)
          {
            if (j > t)
              edge_cost.insert(make_pair(make_tuple('L', t+1, i + 1, j), make_pair( grid[i][j], make_tuple('U', 1, i, j)) ));
          }
          for (int t = 3; t<10; t++)
          {
            if (j < grid.size() - (t+1) )
              edge_cost.insert(make_pair(make_tuple('R', t+1, i + 1, j), make_pair( grid[i][j], make_tuple('U', 1, i, j)) ));
          }
        }
      }
    }
  }

  // print nodes
  // print edges

  pair<pair<char, short>, pair<int, int>> loc = make_pair(make_pair('*', -1), make_pair(-1, -1));
  pair<int, int> fin = make_pair(grid.size() - 1, grid[0].size() - 1);

  while (loc.second != fin)
  {
    // handle
    pair<pair<char, short>, pair<int, int>> minKey;
    auto minVal = -1;

    // find node to handle new destinatuions should not create length of 4
    for (auto const &[key, val] : path_cost)
    {
      bool found = false;

      if ((minVal == -1 || val >= 0 && val < minVal))
      {
        found = (nodes_u.find(key) != nodes_u.end());
        if (found)
        {
          minVal = val;
          minKey = key;
        }
      }
    }

    // move handled node to visited
    nodes_u.erase(minKey);
    nodes_v.insert(minKey);

    cout << minKey.first.first << "|" << minKey.first.second << " (" << minKey.second.first << "," << minKey.second.second << ") visited C:"
      << path_cost[minKey] << endl;


    // updatedestinations
    auto ec_it = edge_cost.equal_range( make_tuple( minKey.first.first, minKey.first.second, minKey.second.first, minKey.second.second ) );    
    for ( edge_cost_it = ec_it.first ; edge_cost_it != ec_it.second; edge_cost_it++ )
    {
      pair<pair<char, short>, pair<int, int>> tmp;
      tmp = make_pair(make_pair(get<0>(edge_cost_it->second.second), get<1>(edge_cost_it->second.second)), make_pair(get<2>(edge_cost_it->second.second), get<3>(edge_cost_it->second.second)));
      
      loc = minKey;

      // update costs depends on prev moves
      if (path_cost[tmp] > edge_cost_it->second.first + path_cost[minKey]
        || path_cost[tmp] == 0 )
      {
          path_cost[tmp] = edge_cost_it->second.first + path_cost[minKey];
      }
      
      cout << tmp.first.first << "|" << tmp.first.second << "(" << tmp.second.first << "," << tmp.second.second << ")"
            << " C:" << path_cost[tmp] << endl;
    }
    if ( loc.second == fin )
      break;
    else
      path_cost.erase( minKey );
  }

  cout << "answer = " << path_cost[loc] << endl;
}