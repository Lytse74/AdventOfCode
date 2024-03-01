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
using std::pair;
using std::set;
using std::string;
using std::tie;
using std::tuple;
using std::vector;

int main()
{
  // open the file
  std::ifstream is("day17.test");
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
  map<pair<tuple<char, short, int, int>, tuple<char, short, int, int>>, int> edge_cost;
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
        edge_cost[make_pair(make_tuple('-', 0, i, j), make_tuple('L', 1, i, j + 1))] = grid[i][j + 1];
        edge_cost[make_pair(make_tuple('-', 0, i, j), make_tuple('D', 1, i + 1, j))] = grid[i + 1][j];
      }
      if (j != 0)
      {
        nodes_u.insert(make_pair(make_pair('L', 1), make_pair(i, j)));
        path_cost[make_pair(make_pair('L', 1), make_pair(i, j))] = -1;
        if (j != 1)
        {
          nodes_u.insert(make_pair(make_pair('L', 2), make_pair(i, j)));
          edge_cost[make_pair(make_tuple('L', 1, i, j - 1), make_tuple('L', 2, i, j))] = grid[i][j];
          path_cost[make_pair(make_pair('L', 2), make_pair(i, j))] = -1;
          if (j != 2)
          {
            nodes_u.insert(make_pair(make_pair('L', 3), make_pair(i, j)));
            path_cost[make_pair(make_pair('L', 3), make_pair(i, j))] = -1;
            edge_cost[make_pair(make_tuple('L', 2, i, j - 1), make_tuple('L', 3, i, j))] = grid[i][j];
          }
        }
        if (i != 0)
        {
          edge_cost[make_pair(make_tuple('D', 1, i, j - 1), make_tuple('L', 1, i, j))] = grid[i][j];
          if (i != 1)
          {
            edge_cost[make_pair(make_tuple('D', 2, i, j - 1), make_tuple('L', 1, i, j))] = grid[i][j];
            if (i != 2)
            {
              edge_cost[make_pair(make_tuple('D', 3, i, j - 1), make_tuple('L', 1, i, j))] = grid[i][j];
            }
          }
        }
        if (i != grid.size() - 1)
        {
          edge_cost[make_pair(make_tuple('U', 1, i, j - 1), make_tuple('L', 1, i, j))] = grid[i][j];
          if (i != grid.size() - 2)
          {
            edge_cost[make_pair(make_tuple('U', 2, i, j - 1), make_tuple('L', 1, i, j))] = grid[i][j];
            if (i != grid.size() - 3)
            {
              edge_cost[make_pair(make_tuple('U', 3, i, j - 1), make_tuple('L', 1, i, j))] = grid[i][j];
            }
          }
        }
      }
      if (j != grid[i].size() - 1)
      {
        if (i != 0 || j != 0)
        {
          nodes_u.insert(make_pair(make_pair('R', 1), make_pair(i, j)));
          path_cost[make_pair(make_pair('R', 1), make_pair(i, j))] = -1;
          if (j != grid[i].size() - 2)
          {
            nodes_u.insert(make_pair(make_pair('R', 2), make_pair(i, j)));
            path_cost[make_pair(make_pair('R', 2), make_pair(i, j))] = -1;
            edge_cost[make_pair(make_tuple('R', 1, i, j + 1), make_tuple('R', 2, i, j))] = grid[i][j];
            if (j != grid[i].size() - 3)
            {
              nodes_u.insert(make_pair(make_pair('R', 3), make_pair(i, j)));
              path_cost[make_pair(make_pair('R', 3), make_pair(i, j))] = -1;
              edge_cost[make_pair(make_tuple('R', 2, i, j + 1), make_tuple('R', 3, i, j))] = grid[i][j];
            }
          }
          if (i != 0)
          {
            edge_cost[make_pair(make_tuple('D', 1, i, j + 1), make_tuple('R', 1, i, j))] = grid[i][j];
            if (i != 1)
            {
              edge_cost[make_pair(make_tuple('D', 2, i, j + 1), make_tuple('R', 1, i, j))] = grid[i][j];
              if (i != 2)
              {
                edge_cost[make_pair(make_tuple('D', 3, i, j + 1), make_tuple('R', 1, i, j))] = grid[i][j];
              }
            }
          }
          if (i != grid.size() - 1)
          {
            edge_cost[make_pair(make_tuple('U', 1, i, j + 1), make_tuple('R', 1, i, j))] = grid[i][j];
            if (i != grid.size() - 2)
            {
              edge_cost[make_pair(make_tuple('U', 2, i, j + 1), make_tuple('R', 1, i, j))] = grid[i][j];
              if (i != grid.size() - 3)
              {
                edge_cost[make_pair(make_tuple('U', 3, i, j + 1), make_tuple('R', 1, i, j))] = grid[i][j];
              }
            }
          }
        }
      }
      if (i != 0)
      {
        nodes_u.insert(make_pair(make_pair('D', 1), make_pair(i, j)));
        path_cost[make_pair(make_pair('D', 1), make_pair(i, j))] = -1;
        if (i != 1)
        {
          edge_cost[make_pair(make_tuple('D', 1, i - 1, j), make_tuple('D', 2, i, j))] = grid[i][j];
          nodes_u.insert(make_pair(make_pair('D', 2), make_pair(i, j)));
          path_cost[make_pair(make_pair('D', 2), make_pair(i, j))] = -1;
          if (i != 2)
          {
            nodes_u.insert(make_pair(make_pair('D', 3), make_pair(i, j)));
            path_cost[make_pair(make_pair('D', 3), make_pair(i, j))] = -1;
            edge_cost[make_pair(make_tuple('D', 2, i - 1, j), make_tuple('D', 3, i, j))] = grid[i][j];
          }
        }
        if (j != 0)
        {
          edge_cost[make_pair(make_tuple('L', 1, i - 1, j), make_tuple('D', 1, i, j))] = grid[i][j];
          if (j != 1)
          {
            edge_cost[make_pair(make_tuple('L', 2, i - 1, j), make_tuple('D', 1, i, j))] = grid[i][j];
            if (j != 2)
            {
              edge_cost[make_pair(make_tuple('L', 3, i - 1, j), make_tuple('D', 1, i, j))] = grid[i][j];
            }
          }
        }
        if (j != grid[i].size() - 1)
        {
          edge_cost[make_pair(make_tuple('R', 1, i - 1, j), make_tuple('D', 1, i, j))] = grid[i][j];
          if (j != grid[i].size() - 2)
          {
            edge_cost[make_pair(make_tuple('R', 2, i - 1, j), make_tuple('D', 1, i, j))] = grid[i][j];
            if (j != grid[i].size() - 3)
            {
              edge_cost[make_pair(make_tuple('R', 3, i - 1, j), make_tuple('D', 1, i, j))] = grid[i][j];
            }
          }
        }
      }
      if (i != grid.size() - 1)
      {
        if (i != 0 || j != 0)
        {
          nodes_u.insert(make_pair(make_pair('U', 1), make_pair(i, j)));
          path_cost[make_pair(make_pair('U', 1), make_pair(i, j))] = -1;
          if (i != grid.size() - 2)
          {
            nodes_u.insert(make_pair(make_pair('U', 2), make_pair(i, j)));
            path_cost[make_pair(make_pair('U', 2), make_pair(i, j))] = -1;
            edge_cost[make_pair(make_tuple('U', 1, i + 1, j), make_tuple('U', 2, i, j))] = grid[i][j];
            if (i != grid.size() - 2)
            {
              nodes_u.insert(make_pair(make_pair('U', 3), make_pair(i, j)));
              path_cost[make_pair(make_pair('U', 3), make_pair(i, j))] = -1;
              edge_cost[make_pair(make_tuple('U', 2, i + 1, j), make_tuple('U', 3, i, j))] = grid[i][j];
            }
          }
          if (j != 0)
          {
            edge_cost[make_pair(make_tuple('L', 1, i + 1, j), make_tuple('U', 1, i, j))] = grid[i][j];
            if (j != 1)
            {
              edge_cost[make_pair(make_tuple('L', 2, i + 1, j), make_tuple('U', 1, i, j))] = grid[i][j];
              if (j != 2)
              {
                edge_cost[make_pair(make_tuple('L', 3, i + 1, j), make_tuple('U', 1, i, j))] = grid[i][j];
              }
            }
          }
          if (j != grid[i].size() - 1)
          {
            edge_cost[make_pair(make_tuple('R', 1, i + 1, j), make_tuple('U', 1, i, j))] = grid[i][j];
            if (j != grid[i].size() - 2)
            {
              edge_cost[make_pair(make_tuple('R', 2, i + 1, j), make_tuple('U', 1, i, j))] = grid[i][j];
              if (j != grid[i].size() - 3)
              {
                edge_cost[make_pair(make_tuple('R', 3, i + 1, j), make_tuple('U', 1, i, j))] = grid[i][j];
              }
            }
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

    cout << minKey.first.first << "|" << minKey.first.second << " (" << minKey.second.first << "," << minKey.second.second << ") visited" << endl;

    // updatedestinations
    for (auto const &[key, val] : edge_cost)
    {
      if (get<0>(key.first) == minKey.first.first && get<1>(key.first) == minKey.first.second && get<2>(key.first) == minKey.second.first && get<3>(key.first) == minKey.second.second)
      {
        pair<pair<char, short>, pair<int, int>> tmp;
        pair<pair<char, short>, pair<int, int>> tmp2;
        tmp = make_pair(make_pair(get<0>(key.second), get<1>(key.second)), make_pair(get<2>(key.second), get<3>(key.second)));
        tmp2 = make_pair(make_pair(get<0>(key.first), get<1>(key.first)), make_pair(get<2>(key.first), get<3>(key.first)));
        if (path_cost[tmp] >= path_cost[tmp2])
          continue;
        cout << minKey.first.first << "|" << minKey.first.second << "(" << minKey.second.first << "," << minKey.second.second << ") "
             << "spath"
             << " C:" << path_cost[tmp2] << " : ";
        cout << tmp.first.first << "|" << tmp.first.second << "(" << tmp.second.first << "," << tmp.second.second << ")"
             << " C:" << val << endl;

        loc = minKey;

        // update costs depends on prev moves
        if (path_cost[tmp] < 0)
          path_cost[tmp] = val + path_cost[tmp2];
        else
        {
          if (path_cost[tmp2] + val < path_cost[tmp])
          {
            path_cost[tmp] = val + path_cost[tmp2];
          }
        }
      }
    }
  }

  cout << "answer = " << path_cost[loc] << endl;
}
