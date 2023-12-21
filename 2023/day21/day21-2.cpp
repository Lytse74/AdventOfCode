#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <tuple>
#include <vector>
#include <set>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::set;
using std::tuple;
using std::make_tuple;
using std::get;
using std::tie;

set<tuple<int,int>> FloodIt( vector<vector<int>> & grid, set<tuple<int,int>> checkPt,  int color = 0 )
{
  set<tuple<int,int>> ret;

  for ( auto it = checkPt.begin(); it != checkPt.end(); it++ )
  {
    int r {}; int c {};
    tie(r,c) = *it;

    grid[r][c] = color;

    if ((r>0) && grid[r-1][c] == -1 )
      ret.insert( make_tuple( r-1, c ) );
    if ((c>0) && grid[r][c-1] == -1 )
      ret.insert( make_tuple( r, c-1 ) );
    if (( r < grid.size()-1) && grid[r+1][c] == -1 )
      ret.insert( make_tuple( r+1, c ) );
    if (( c < grid[0].size()-1) && grid[r][c+1] == -1 )
      ret.insert( make_tuple( r, c+1 ) );
  }

  return ret;
}

int print( vector<vector<int>> grid, bool p )
{
  int count {};
  for ( auto line: grid )
  {
    for ( auto pt: line )
    {
      if ( pt == -1 )
      {
        if(p) {cout << ".";}
      }
      else if ( pt == -2 )
      {
        if(p) {cout << "#";}
      }
      else
      {
        //if ( ( pt & 0x1 ) == 0x0 )
          count++;
        if(p) {cout << (char)('0' + (pt % 11));}
      }
    }
    if(p) {cout << endl;}
  }
  cout << "count = " << count << endl;

  return 0;
}

int main() {
  // open the file
  std::ifstream is("day21.test2");
  std::string str;

  vector<vector<int>> grid;
  tuple<int,int> start = make_tuple(-1,-1);
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    char ch {};

    vector<int> line;
   
    while ( iss.get(ch) )
    {
      int val {};
      if ( ch == '.' )
        val = -1;
      if ( ch == '#' )
        val = -2;
      if ( ch == 'S' )
      {
        val = -1;
        get<0>(start) = grid.size();
        get<1>(start) = line.size();
      }
      line.push_back(val);
      cout << ch;
    }
    grid.push_back(line);
    cout << endl;
  }
  cout << endl;

  is.close();

  set<tuple<int,int>> checkPt;
  checkPt.insert( start );

  print( grid, true );

  int color {};
  
  //while( !checkPt.empty() )
  for ( auto i=0; i<=55; i++)
  { 
    checkPt = FloodIt( grid, checkPt, color );
    print( grid, true );
    cout <<  "color = " << color << endl;
    color++;
  }
}