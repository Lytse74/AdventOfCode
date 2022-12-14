#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <cassert>
using namespace std;

int main() {
  // open the file
  ifstream is("day12.input");
  string str;

  // array to store the input
  char input[41][162];

  // array to store the steps
  int steps[41][162];

  // point start
  pair<int,int> start;

  // point end
  pair<int,int> end;

  // Initialize array
  for ( auto i=0; i<41; ++ i )
    for ( auto j=0; j<162; ++j )
    {
      input[i][j] = -1; 
      steps[i][j] = -1;
    }

  int i = 0;
  while ( getline ( is , str ) )
  {
    int j = 0;
    istringstream iss(str);
    for ( char& c: str)
    {
      if ( c == 'S')
      {
        start = make_pair( i, j );
        c = 'a';
      }
      if ( c == 'E')
      {
        end = make_pair( i, j );
        c = 'z';
      }
      input[i][j] = c;
      j++;
    }
    i++;
  }

  // print array
  for ( auto i=0; i<41; ++ i )
  {
    if ( input[i][0] == -1 ) break;
    cout << "R:" << i << " ";
    for ( auto j=0; j<162; ++j )
    {
    if ( input[i][j] == -1 ) break;
      cout << input[i][j] << " ";
    }
    cout << endl;
  }

  // print start and end
  cout << "start:" << start.first << " " << start.second << endl; 
  cout << "end:" << end.first << " " << end.second << endl; 
  
  assert("DOES NOT WORK!!"==0);
  // find shortest path
  list<pair<int,int>> todo;
  todo.push_back( end );

  while ( todo.size() > 0 )
  {
    pair<int,int> tmp = todo.front();
    todo.pop_front();

    //if ( input[tmp.first][tmp.second] == 'S' )
    if ( tmp.first == end.first && tmp.second == end.second )
    {
      steps[tmp.first][tmp.second] = 1;
    }

    // up
    if ( tmp.first > 0 )
    {
      if ( ( input[tmp.first-1][tmp.second] - input[tmp.first][tmp.second] ) >= -1 
        //&& ( input[tmp.first-1][tmp.second] - input[tmp.first][tmp.second] ) < 1 
         )
      {
        if ( steps[tmp.first-1][tmp.second] == -1 || (steps[tmp.first-1][tmp.second] -0) > steps[tmp.first][tmp.second] ) 
        {
          steps[tmp.first-1][tmp.second] = steps[tmp.first][tmp.second] + 1;
          todo.push_back( make_pair( tmp.first-1, tmp.second ) );
        }
      }
    }
    // right
    if ( tmp.second < 161 && input[tmp.first][tmp.second+1] != -1 )
    {
      if ( ( input[tmp.first][tmp.second+1] - input[tmp.first][tmp.second] ) >= -1 
        //&& ( input[tmp.first][tmp.second+1] - input[tmp.first][tmp.second] ) < 1
         )
      {
        if ( steps[tmp.first][tmp.second+1] == -1 || (steps[tmp.first][tmp.second+1] -0) > steps[tmp.first][tmp.second] ) 
        {
          steps[tmp.first][tmp.second+1] = steps[tmp.first][tmp.second] + 1;
          todo.push_back( make_pair( tmp.first, tmp.second+1 ) );
        }
      }
    }
    // down
    if ( tmp.first < 40 && input[tmp.first+1][tmp.second] != -1 )
    {
      if ( ( input[tmp.first+1][tmp.second] - input[tmp.first][tmp.second] ) >= -1 
        //&& ( input[tmp.first+1][tmp.second] - input[tmp.first][tmp.second] ) < 1
         )
      {
        if ( steps[tmp.first+1][tmp.second] == -1 || (steps[tmp.first+1][tmp.second] -0) > steps[tmp.first][tmp.second] ) 
        {
          steps[tmp.first+1][tmp.second] = steps[tmp.first][tmp.second] + 1;
          todo.push_back( make_pair( tmp.first+1, tmp.second ) );
        }
      }
    }
    // left
    if ( tmp.second > 0 )
    {
      if ( ( input[tmp.first][tmp.second-1] - input[tmp.first][tmp.second] ) >= -1 
        //&& ( input[tmp.first][tmp.second-1] - input[tmp.first][tmp.second] ) < 1
         )
      {
        if ( steps[tmp.first][tmp.second-1] == -1 || (steps[tmp.first][tmp.second-1] -0) > steps[tmp.first][tmp.second] ) 
        {
          steps[tmp.first][tmp.second-1] = steps[tmp.first][tmp.second] + 1;
          todo.push_back( make_pair( tmp.first, tmp.second-1 ) );
        }
      }
    }
  }

  int mina = 500;

  // print array and det min
  for ( auto i=0; i<41; ++ i )
  { 
    if ( steps[i][0] == -1 ) break;
    cout << "R:" << i << " ";
    for ( auto j=0; j<162; ++j )
    {
      if ( steps[i][j] == -1 ) break;
      cout << steps[i][j] << " ";
      if ( input[i][j] == 'a' && steps[i][j] <= mina )
        mina = steps[i][j];
    }
    cout << endl;
  }

  cout << "P2:" << mina -1 << endl;

  //close the file
  is.close();
 }
