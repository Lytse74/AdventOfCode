#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;

void printField( std::vector<std::vector<char>> v )
{
  for ( auto line : v )
  {
    for ( auto p : line )
    {
      cout << p ;
    }
    cout << endl;
  }
  cout << endl;
}

int calcLoad ( std::vector<std::vector<char>> v )
{
  int weight = v.size();
  int val {};

  for ( auto line : v )
  {
    for ( auto p : line )
    {
      if ( p == 'O' ) 
        val += weight;
    }
    weight--;
  }

  return val;
}

void sortColUp( int n, std::vector<std::vector<char>>& field )
{
  int floor {};
  int ptr {};

  bool sorted = false;
  
  while ( !sorted )
  {
    while ( floor < field.size() && field[floor][n] == '#' )
      floor++;

    while ( floor < field.size() && field[floor][n] == 'O' )
      floor++;
    
    if ( floor == field.size() )
    {
      sorted = true;
      continue;
    }

    ptr = floor;
    while  ( ptr < field.size() && field[ptr][n] == '.' )
      ptr++;
    
    if ( ptr == field.size() )
    {
      sorted = true;
      continue;
    }

    if ( field[ptr][n] == 'O')
    {
      field[floor][n] = 'O';
      field[ptr][n] = '.';
    }
    else if ( field[ptr][n] == '#')
    {
      floor = ptr;
    } 
  }
}

void sortRowUp( int n, std::vector<std::vector<char>>& field )
{
  int floor {};
  int ptr {};

  bool sorted = false;
  
  while ( !sorted )
  {
    while ( floor < field[n].size() && field[n][floor] == '#' )
      floor++;

    while ( floor < field[n].size() && field[n][floor] == 'O' )
      floor++;
    
    if ( floor == field[n].size() )
    {
      sorted = true;
      continue;
    }

    ptr = floor;
    while  ( ptr < field[n].size() && field[n][ptr] == '.' )
      ptr++;
    
    if ( ptr == field[n].size() )
    {
      sorted = true;
      continue;
    }

    if ( field[n][ptr] == 'O')
    {
      field[n][floor] = 'O';
      field[n][ptr] = '.';
    }
    else if ( field[n][ptr] == '#')
    {
      floor = ptr;
    } 
  }
}

void sortColDown( int n, std::vector<std::vector<char>>& field )
{
  int floor = field.size() - 1;
  int ptr {};

  bool sorted = false;
  
  while ( !sorted )
  {
    while ( floor >= 0 && field[floor][n] == '#' )
      floor--;

    while ( floor >= 0 && field[floor][n] == 'O' )
      floor--;
    
    if ( floor < 0 )
    {
      sorted = true;
      continue;
    }

    ptr = floor;
    while  ( ptr >= 0 && field[ptr][n] == '.' )
      ptr--;
    
    if ( ptr < 0 )
    {
      sorted = true;
      continue;
    }

    if ( field[ptr][n] == 'O')
    {
      field[floor][n] = 'O';
      field[ptr][n] = '.';
    }
    else if ( field[ptr][n] == '#')
    {
      floor = ptr;
    } 
  }
}

void sortRowDown( int n, std::vector<std::vector<char>>& field )
{
  int floor = field[n].size() - 1;
  int ptr {};

  bool sorted = false;
  
  while ( !sorted )
  {
    while ( floor >= 0 && field[n][floor] == '#' )
      floor--;

    while ( floor >= 0 && field[n][floor] == 'O' )
      floor--;
    
    if ( floor < 0 )
    {
      sorted = true;
      continue;
    }

    ptr = floor;
    while  ( ptr >= 0 && field[n][ptr] == '.' )
      ptr--;
    
    if ( ptr < 0 )
    {
      sorted = true;
      continue;
    }

    if ( field[n][ptr] == 'O')
    {
      field[n][floor] = 'O';
      field[n][ptr] = '.';
    }
    else if ( field[n][ptr] == '#')
    {
      floor = ptr;
    } 
  }
}

int main() {
  // open the file
  std::ifstream is("day14.input");
  std::string str;
  std::vector<std::vector<char>> field;

  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::vector<char> line;
    char ch;

    while ( iss.get(ch) )
    {
      line.push_back(ch)  ;
    }
    field.push_back(line);
  }
  cout << endl;
  is.close();

  printField( field );

  // answer (1000000000-123)%26 +123

  for ( long long n=1 ; n<=142; n++ ) 
  {
    for ( auto i=0 ; i < field[0].size() ; i++ )
      sortColUp( i, field );
    if ( n==1 )
      cout << "value1  = " << calcLoad( field ) << endl;
    for ( auto i=0 ; i < field.size() ; i++ )
      sortRowUp( i, field );
    for ( auto i=0 ; i < field[0].size() ; i++ )
      sortColDown( i, field );
    for ( auto i=0 ; i < field.size() ; i++ )
      sortRowDown( i, field );
    //cout << calcLoad( field ) << " " << n << " ";
    //if ( ( n > 100 ) && ( n + 7 ) % 26 == 0 )
    //if ( ( n - 1 ) % 7 == 0 )
    //  cout <<  endl ;
  }
  cout << endl;
  printField( field );
  cout << "value2  = " << calcLoad( field ) << endl;
}