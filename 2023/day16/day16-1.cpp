#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>
#include <stack>

using std::cout;
using std::endl;

using std::string;
using std::vector;
using std::tuple;
using std::make_tuple;
using std::tie;
using std::get;
using std::stack;

int print( vector<vector<tuple<char,int>>> field )
{
  int cnt=0;
  
  for ( auto row : field )
  {
    for ( auto elem : row )
    {
      if ( get<1>(elem) > 0 )
      {
        cout << '#';
        cnt++;
      }
      else 
        cout << get<0>(elem);
    }
    cout << endl;
  }
  cout << endl;
  
  return cnt;
}

int count( vector<vector<tuple<char,int>>> field )
{
  int cnt=0;
  
  for ( auto row : field )
    for ( auto elem : row )
      if ( get<1>(elem) > 0 )
        cnt++;
  
  return cnt;
}

int calculate( vector<vector<tuple<char,int>>> field, stack<tuple<int,int,int>> todo )
{
  while ( !todo.empty() )
  {
    int row {};
    int col {};
    int dir {};
    tie ( row, col, dir ) = todo.top();
    todo.pop();

    // check if map was already visited with this dir
    int mdir {};
    char mact {};
    tie ( mact, mdir ) = field[row][col];

    if ( (mdir & dir) == 0)
    {
      // update map
      get<1>(field[row][col]) |= dir;
      //print(field);

      // see wat to do based on dir and act
      // right
      // dir right '.' '-'
      // dir up '-' '/'
      // dir down '-' '\'
      if ( ( ((dir & 0x1) == 0x1 ) && ( mact == '.' || mact == '-' )
        || ((dir & 0x2) == 0x2 ) && ( mact == '-' || mact == '/' )
        || ((dir & 0x8) == 0x8 ) && ( mact == '-' || mact == '\\' ) )
        && ( col < field[row].size() -1 ) )
      {
        todo.push( make_tuple(row, col+1, 0x01 ) );
        //cout << "R>" << endl; 
      }
      // up
      // dir up '.' '|'
      // dir right '/' '|'
      // dir left '\' '|' 
      if ( ( ((dir & 0x1) == 0x1 ) && ( mact == '/' || mact == '|' )
        || ((dir & 0x2) == 0x2 ) && ( mact == '.' || mact == '|' )
        || ((dir & 0x4) == 0x4 ) && ( mact == '\\' || mact == '|' ) )
        && ( row > 0 ) )
      {
        todo.push( make_tuple(row-1, col, 0x02 ) );
        //cout << "U>" << endl;
      }
      // left
      // dir left '.' '-'
      // dir up '-' '\'
      // dir down '-' '/'
      if ( ( ((dir & 0x4) == 0x4 ) && ( mact == '.' || mact == '-' )
        || ((dir & 0x2) == 0x2 ) && ( mact == '-' || mact == '\\' )
        || ((dir & 0x8) == 0x8 ) && ( mact == '-' || mact == '/' ) )
        && ( col > 0 ) )
      {
        todo.push( make_tuple(row, col-1, 0x04 ) );
        //cout << "L>" << endl; 
      }
      // down
      // dir down '.' '|'
      // dir right '\' '|'
      // dir left '/' '|' 
      if ( ( ((dir & 0x1) == 0x1 ) && ( mact == '\\' || mact == '|' )
        || ((dir & 0x8) == 0x8 ) && ( mact == '.' || mact == '|' )
        || ((dir & 0x4) == 0x4 ) && ( mact == '/' || mact == '|' ) )
        && ( row < field.size() -1 ) )
      {
        todo.push( make_tuple(row+1, col, 0x08 ) );
        //cout << "D>" << endl; 
      }
    }
  }

  return count(field);
}

int main() {
  // open the file
  std::ifstream is("day16.input");
  string str;

  vector<vector<tuple<char,int>>> field;
  stack<tuple<int,int,int>> todo;

  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    char ch;
    vector<tuple<char,int>> row;

    while ( iss.get(ch) )
    {
      auto t = make_tuple( ch, 0 );
      row.push_back( t );
      cout << ch;
    }
    field.push_back( row );
    cout << endl;
  }
  cout << endl;

  is.close();

  todo.push( make_tuple( 0,0,0x1) );
  int answer1 = calculate( field, todo );

  cout << "answer1 = " << answer1 << endl;
  //cout << "rows = " << field.size() << " cols = " << field[0].size() << endl;

  int val {};
  int mval {};

  for ( int i=0; i<110; i++ )
  {
    todo.push( make_tuple( i,0,0x1) );
    val = calculate( field, todo );
    if ( val > mval )
    {
      mval = val;
      //cout << "R:" << i << " " << mval << endl;
    }
    todo.pop();
    todo.push( make_tuple( 109,i,0x2) );
    val = calculate( field, todo );
    if ( val > mval )
    {
      mval = val;
      //cout << "U:" << i << " " << mval << endl;
    }
    todo.pop();
    todo.push( make_tuple( i,109,0x4) );
    val = calculate( field, todo );
    if ( val > mval )
    {
      mval = val;
      //cout << "L:" << i << " " << mval << endl;
    }
    todo.pop();
    todo.push( make_tuple( 0,i,0x8) );
    val = calculate( field, todo );
    if ( val > mval )
    {
      mval = val;
      //cout << "D:" << i << " " << mval << endl;
    }
    todo.pop();
  }
  cout << "answer2 = " << mval << endl;
}
