#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::make_pair;

void floodit( std::set<pair<int,int>> & f, vector<vector<char>> & grid )
{
  std::set<pair<int,int>>::iterator it_f;

  it_f = f.begin();

  while ( it_f != f.end() )
  {
    int r = it_f->first;
    int c = it_f->second;

    if ( r > 0 && c > 0 && r<grid.size()-1 && c<grid[0].size()-1 )
    {
      if ( grid[r-1][c-1] == '.' )
        f.insert( make_pair( r-1,c-1) );
      if ( grid[r-1][c] == '.' )
        f.insert( make_pair( r-1,c) );
      if ( grid[r-1][c+1] == '.' )
        f.insert( make_pair( r-1,c+1) );
      if ( grid[r][c-1] == '.' )
        f.insert( make_pair( r,c-1) );
      if ( grid[r][c+1] == '.' )
        f.insert( make_pair( r,c+1) );
      if ( grid[r+1][c-1] == '.' )
        f.insert( make_pair( r+1,c-1) );
      if ( grid[r+1][c] == '.' )
        f.insert( make_pair( r+1,c) );
      if ( grid[r+1][c+1] == '.' )
        f.insert( make_pair( r+1,c+1) );
    }
    if ( r == 0 && c > 0 && c<grid[0].size()-1 )
    {
      if ( grid[r][c-1] == '.' )
        f.insert( make_pair( r,c-1) );
      if ( grid[r][c+1] == '.' )
        f.insert( make_pair( r,c+1) );
      if ( grid[r+1][c-1] == '.' )
        f.insert( make_pair( r+1,c-1) );
      if ( grid[r+1][c] == '.' )
        f.insert( make_pair( r+1,c) );
      if ( grid[r+1][c+1] == '.' )
        f.insert( make_pair( r+1,c+1) );
    }
    if ( r == grid.size()-1 && c > 0 && c<grid[0].size()-1 )
    {
      if ( grid[r][c-1] == '.' )
        f.insert( make_pair( r,c-1) );
      if ( grid[r][c+1] == '.' )
        f.insert( make_pair( r,c+1) );
      if ( grid[r-1][c-1] == '.' )
        f.insert( make_pair( r-1,c-1) );
      if ( grid[r-1][c] == '.' )
        f.insert( make_pair( r-1,c) );
      if ( grid[r-1][c+1] == '.' )
        f.insert( make_pair( r-1,c+1) );
    }
    if ( r > 0 && c == 0 && r<grid.size()-1 )
    {
      if ( grid[r-1][c] == '.' )
        f.insert( make_pair( r-1,c) );
      if ( grid[r-1][c+1] == '.' )
        f.insert( make_pair( r-1,c+1) );
      if ( grid[r][c+1] == '.' )
        f.insert( make_pair( r,c+1) );
      if ( grid[r+1][c] == '.' )
        f.insert( make_pair( r+1,c) );
      if ( grid[r+1][c+1] == '.' )
        f.insert( make_pair( r+1,c+1) );
    }
    if ( r > 0 && c == grid[0].size()-1 && r<grid.size()-1 )
    {
      if ( grid[r-1][c] == '.' )
        f.insert( make_pair( r-1,c) );
      if ( grid[r-1][c-1] == '.' )
        f.insert( make_pair( r-1,c-1) );
      if ( grid[r][c-1] == '.' )
        f.insert( make_pair( r,c-1) );
      if ( grid[r+1][c] == '.' )
        f.insert( make_pair( r+1,c) );
      if ( grid[r+1][c-1] == '.' )
        f.insert( make_pair( r+1,c-1) );
    }
    grid[r][c] = 'o';

    it_f = f.erase(it_f);
    it_f = f.begin();
  }
}

void print( vector<pair<int,int>> p )
{
  int pmxr {};
  int pmxc {};
  int pmnr {};
  int pmnc {};

  for ( auto pt: p )
  { 
    if ( pt.first <= pmnr ) pmnr = pt.first;
    if ( pt.first >= pmxr ) pmxr = pt.first;
    if ( pt.second <= pmnc ) pmnc = pt.second;
    if ( pt.second >= pmxc ) pmxc = pt.second;
  }

  vector<vector<char>> grid;

  for ( auto i=pmnr; i<=pmxr; i++)
  {
    vector<char> row;
    for  ( auto j=pmnc; j<=pmxc; j++ )
    {
      row.push_back('.');
    }
    grid.push_back(row);
  }

  vector<pair<int,int>>::iterator p_it;
  p_it = p.begin();
  int rw = p_it->first;
  int cl = p_it->second;
  p_it++;
  
  while ( p_it != p.end() )
  {
    if ( rw == p_it->first )
    {
      if ( cl < p_it->second )
        for ( auto j=cl; j<= p_it->second; j++ )
          grid[rw-pmnr][j-pmnc] = '#';
      else
        for ( auto j=cl; j>= p_it->second; j-- )
          grid[rw-pmnr][j-pmnc] = '#';
    }
    else if ( cl == p_it->second )
    {
      if ( rw < p_it->first )
        for ( auto i=rw; i<= p_it->first; i++ )
          grid[i-pmnr][cl-pmnc] = '#';
      else
        for ( auto i=rw; i>= p_it->first; i-- )
          grid[i-pmnr][cl-pmnc] = '#';
    }
    rw = p_it->first;
    cl = p_it->second;
    p_it++;
  }

  int rc {};
  int cc {};

  std::set<pair<int,int>> flood;

  for ( auto row : grid )
  {
    for ( auto po : row)
    {
      if (rc==0 && po == '.' )
      {
        flood.insert(make_pair(rc,cc));
        grid[rc][cc] = 'o';
        po = 'o'; 
      }
      else if (cc==0 && po == '.')
      {
        flood.insert(make_pair(rc,cc));
        grid[rc][cc] = 'o';
        po = 'o'; 
      }
      else if (rc==grid.size()-1 && po == '.' )
      {
        flood.insert(make_pair(rc,cc));
        grid[rc][cc] = 'o';
        po = 'o'; 
      }
      else if (cc==row.size()-1 && po == '.' )
      {
        flood.insert(make_pair(rc,cc));
        grid[rc][cc] = 'o';
        po = 'o'; 
      }
      cc++;
    }
    cc=0;
    rc++;
  }

  floodit( flood, grid );

  int dotcount {};
  for ( auto row : grid )
  {
    for ( auto po : row)
    {
      if ( po == '.' || po == '#' )
      {
        dotcount++;
      }
      cout << po;
    }
    cout << endl;
  }

  cout <<  endl;
  cout << "ANSWER1 = " << dotcount << endl;
}

int main() {
  // open the file
  std::ifstream is("day18.input");
  std::string str;
  vector<pair<int,int>> p;
  p.push_back( make_pair(0,0) );
  int trow {};
  int tcol {};

  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::string sstr;
    std::string dir;
    std::string length;
    int len{};
    std::string color;
    
    iss >> dir;
    iss >> length;
    iss >> color;

    cout << color << stoi( length ) << dir << endl;

    if ( dir == "D" ) trow += stoi(length);
    if ( dir == "R" ) tcol += stoi(length);
    if ( dir == "U" ) trow -= stoi(length);
    if ( dir == "L" ) tcol -= stoi(length);
    p.push_back( make_pair( trow,tcol ));

  }
  
  is.close();

  print(p);

  cout << endl;
}