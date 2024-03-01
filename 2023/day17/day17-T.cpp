#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <iomanip>
#include <set>

using std::cout;
using std::endl;
using std::vector;
using std::tuple;
using std::tie;
using std::get;
using std::make_tuple;
using std::string;
using std::pair;
using std::make_pair;
using std::set;

set<tuple<int,int,string>> InitSteps( set<tuple<int,int,string>> v, vector<vector<pair<int,char>>> & c )
{
  int row {-1};
  int col {-1};
  string moves;
  set<tuple<int,int,string>> w;
  set<tuple<int,int,string>>::iterator v_it;

  for ( v_it = v.begin(); v_it != v.end(); v_it++ )
  {
    tuple<int,int,string> t = (*v_it);
    tie( row, col, moves ) = t;
    c[row][col].first = 0;

    if ( row > 0)
      w.insert( make_tuple( row-1,col, moves + 'U' ));
    if ( col > 0)
      w.insert( make_tuple( row,col-1, moves + 'L' ));
    if ( row < c.size()-1 )
      w.insert( make_tuple( row+1,col, moves + 'D' ));
    if ( col < c[0].size()-1 )
      w.insert( make_tuple( row,col+1, moves + 'R' ));
  }

  return w;
}

set<tuple<int,int,string>> NextSteps( set<tuple<int,int,string>> v, vector<vector<pair<int,char>>> & c, vector<vector<int>> g )
{
  int row {-1};
  int col {-1};
  string moves;
  set<tuple<int,int,string>> w;
  set<tuple<int,int,string>>::reverse_iterator v_it;

  for ( v_it = v.rbegin(); v_it != v.rend(); v_it++ )
  {
    tuple<int,int,string> t = (*v_it);
    tie( row, col, moves ) = t;

    char ch = moves.back();

    bool upd = false;

    switch ( ch )
    {
      case 'U': if ( ( c[row+1][col].first + g[row][col] ) <= c[row][col].first )
        { c[row][col].first = (c[row+1][col].first + g[row][col]); upd = true;
        c[row][col].second = '^'; }
        break;
      case 'D': if ( ( c[row-1][col].first + g[row][col] ) <= c[row][col].first )
        { c[row][col].first = (c[row-1][col].first + g[row][col]); upd = true;
        c[row][col].second = 'v'; }
        break;
      case 'L': if ( ( c[row][col+1].first + g[row][col] ) <= c[row][col].first )
        { c[row][col].first = (c[row][col+1].first + g[row][col]); upd = true;
        c[row][col].second = '<'; }
        break;
      case 'R': if ( ( c[row][col-1].first + g[row][col] ) <= c[row][col].first )
        { c[row][col].first = (c[row][col-1].first + g[row][col]); upd = true;
        c[row][col].second = '>'; }
        break;
    }

    if ( !upd ) continue;

    if ( row > 0 && ch != 'D' && moves != "UUU")
    {
      if ( ch == 'U' ) 
        w.insert( make_tuple( row-1,col, moves + 'U' ));
      else w.insert( make_tuple( row-1,col, "U" ));
    }
    if ( col > 0 && ch != 'R' && moves != "LLL")
    {
      if ( ch == 'L' ) 
        w.insert( make_tuple( row,col-1, moves + 'L' ));
      else w.insert( make_tuple( row,col-1, "L" ));
    }
    if ( row < c.size()-1  && ch != 'U' && moves != "DDD")
    {
      if ( ch == 'D' ) 
        w.insert( make_tuple( row+1,col, moves + 'D' ));
      else w.insert( make_tuple( row+1,col, "D" ));
    }
    if ( col < c[0].size()-1  && ch != 'L' && moves != "RRR")
    {
      if ( ch == 'R' ) 
        w.insert( make_tuple( row,col+1, moves + 'R' ));
      else w.insert( make_tuple( row,col+1, "R" ));
    }
  }

  return w;
}

void print( vector<vector<pair<int,char>>> c )
{
  for ( auto row : c )
  {
    for ( auto e: row )
    {
      cout << e.second << std::setw(4) << e.first;
    }
    cout <<  endl;
  }
  cout << endl;
}

void print_ex( vector<vector<pair<int,char>>> c, int ro , int co )
{
  if ( co < 5) co  += (5 - co);
  if ( ro < 5) ro  += (5 - ro);
  if ( co > c[0].size() -6 ) co -= 6 - (c[0].size() - co); 
  if ( ro > c.size() -6 ) ro -= 6 - (c.size() - ro);
   
  for ( auto i = ro - 5; i<= ro + 5; i++ )
  {
    for ( auto j = co - 5; j<=co + 5; j++ )
    {
      cout << c[i][j].second << std::setw(5) << c[i][j].first;
    }
    cout <<  endl;
  }
  cout << endl;
}

int main() {
  // open the file
  std::ifstream is("day17.test");
  std::string str;

  vector<vector<int>> grid;
  vector<vector<pair<int,char>>> costs;
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    char ch;
    vector<int> row;

    while ( iss.get(ch) )
    {
      row.push_back( ch - '0');
    }
    grid.push_back(row);
  }

  cout << endl;

  is.close();

  // find cheapest path from ( 0, 0) to (n-1, n-1)
  // turn 90%
  // max 3 in same dir

  // start with 0,0
  // find edges
  // calculate loss

  for ( auto i=0; i< grid.size(); i++)
  {
    vector<pair<int,char>> t;
    for ( auto j=0; j< grid[i].size(); j++)
    {
      t.push_back( make_pair(99999,'-'));
    }
    costs.push_back(t);
  }
  
  // each node has a function that calculates the los to the next node base on direction an previous steps
  //bool nextstep( grid, steps );

  set<tuple<int,int,string>> steps;

  //steps.push_back( make_tuple( 140, 140, ""));
  //steps.push_back( make_tuple( 0, 0, ""));
  steps.insert( make_tuple( 0, 0, ""));
   
  steps = InitSteps( steps, costs );
  
  while ( !steps.empty() )
  {
    //print_ex( costs, get<0>(steps[0]), get<1>(steps[0]) );
    steps = NextSteps( steps, costs, grid );
  }
  steps.insert( make_tuple( 0, 0, ""));
   
  steps = InitSteps( steps, costs );
  
  while ( !steps.empty() )
  {
    //print_ex( costs, get<0>(steps[0]), get<1>(steps[0]) );
    steps = NextSteps( steps, costs, grid );
  }
  print( costs );
}