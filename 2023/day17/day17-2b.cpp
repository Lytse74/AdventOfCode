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
#include <bits/stdc++.h>

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
using std::priority_queue;
using std::greater;

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

  // seen set
  set<tuple<int,int,int,int,int>> seen;

  // priority queue
  priority_queue< 
    tuple< int, int, int, int, int, int > 
  , vector< tuple< int, int, int, int, int, int > > 
  , greater< tuple< int, int, int, int, int, int > > > 
          pQueue; 
  
  // variables
  int heatloss;
  int row;
  int col;
  int drow;
  int dcol;
  int steps;
  
  // push initial state on the Queue
  pQueue.push( make_tuple( 0, 0, 0, 0, 0, 0 ) );

  while ( !pQueue.empty() )
  {
    tie( heatloss, row, col, drow, dcol, steps ) = pQueue.top();
    pQueue.pop();

    // skip record outside the grid
    if ( row  < 0 || col < 0 || row >= grid.size() || col >= grid[row].size() )
      continue;
    
    // print an answer
    if ( row == grid.size()-1 && col == grid[row].size()-1 && steps >= 4) // added steps >= 4
    {
      cout << "answer = " << heatloss << endl;
      break;
    }

    // skip record we have seen before
    if ( seen.find( make_tuple( row, col, drow, dcol, steps ) ) != seen.end() )
      continue;
    
    // mark record seen
    seen.insert( make_tuple( row, col, drow, dcol, steps ) );

    // continue in direction when less than 3 or 10 steps
    if ( steps < 10 && !( drow == 0 && dcol == 0) ) // changed 3 to 10
    {
      int nrow = row + drow;
      int ncol = col + dcol;
      if ( nrow >= 0 && nrow < grid.size() && ncol >=0 && ncol < grid[nrow].size() )
      {
        pQueue.push( make_tuple( heatloss + grid[nrow][ncol], nrow, ncol, drow, dcol, steps +1 ) );
      }
    }

    // try the other directions
    if ( steps >= 4 || drow == 0 && dcol == 0 ) // added this to allow turning
    {
      set<tuple<int,int>> dirs = {{0,1},{1,0},{-1,0},{0,-1}};
      for ( auto dir : dirs )
      {
        if ( dir != make_tuple(drow,dcol) && dir != make_tuple( -drow, -dcol ) )
        {
          int ndrow, ndcol;
          tie( ndrow, ndcol ) = dir;
          int nrow = row + ndrow;
          int ncol = col + ndcol;
          if ( nrow >= 0 && nrow < grid.size() && ncol >=0 && ncol < grid[nrow].size() )
          {
            pQueue.push( make_tuple( heatloss + grid[nrow][ncol], nrow, ncol, ndrow, ndcol, 1 ) );
          }
        }
      }
    }
  }
}
