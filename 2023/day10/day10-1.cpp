#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>

using std::cout;
using std::endl;

void print( const std::vector<std::vector<char>> pipes )
{
  for ( auto row : pipes )
  {
    for ( auto col : row )
    {
      cout << col;
    }
    cout << endl;
  }
  cout << endl;
}

std::set<std::pair<int,int>>  Update( std::vector<std::vector<char>> & pipes, std::set<std::pair<int,int>> work )
{
  std::set<std::pair<int,int>> tmp;

  for ( auto w : work ) 
  {
    char ch = pipes[w.first][w.second];

    //if ( ch != '*' )
    //   cout << pipes[w.first][w.second] << "(" << w.first << "," << w.second << ")";

    // up
    if ( ( w.first > 0) && ( ch == '|' || ch == 'J' || ch == 'L' ) ) 
      tmp.insert( std::make_pair( w.first -1, w.second ) );
    // down
    if ( ( w.first < pipes.size() - 1 ) && ( ch == '|' || ch == 'F' || ch == '7' )) 
      tmp.insert( std::make_pair( w.first +1, w.second ) );
    // left
    if ( ( w.second > 0 ) && (  ch ==  '-' || ch == 'J' || ch == '7' ) ) 
      tmp.insert( std::make_pair( w.first, w.second -1 ) );
    // right
    if ( ( w.second < pipes[0].size() - 1 ) && ( ch  == '-' || ch == 'L' || ch == 'F' ) ) 
      tmp.insert( std::make_pair( w.first, w.second +1 ) );

    pipes[w.first][w.second] = '*';
  }

  return tmp;
}

int main() {
  // open the file
  std::ifstream is("day10.input");
  std::string str;
  std::pair<int,int> start;
  std::vector<std::vector<char>> pipes;
  std::vector<std::vector<char>> pipes2;
  int width {};
  int height {};
  int row {};
  std::set<std::pair<int,int>> work;
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::vector<char> arow;
    char ch;

    pipes.push_back( arow );

    while ( iss.get(ch) )
    {
      pipes[row].push_back(ch);
      if ( ch  == 'S' )
        start = std::make_pair( row, pipes[row].size()-1);
    }
    width = pipes[row].size();
    row++;
  }
  height = pipes.size();
  is.close();

  // calculate the start symbol
  char chl, chu, chr,chd;
  bool bl=false, bu=false, br=false, bd=false;

  if ( start.first > 0 )
    chu = pipes[start.first-1][start.second];
  if ( start.first < height -1 )
    chd = pipes[start.first+1][start.second];
  if ( start.second > 0 )
    chl = pipes[start.first][start.second-1];
  if ( start.second < width -1 )
    chr = pipes[start.first][start.second+1];

  if ( chl == '-' || chl == 'L' || chl == 'F' )
    bl = true;
  if ( chr == '-' || chr == 'J' || chr == '7' )
    br = true;
  if ( chu == '|' || chu == 'F' || chu == '7' )
    bu = true;
  if ( chd == '|' || chd == 'L' || chd == 'J' )
    bd = true;

  if ( bu && bd )
    pipes[start.first][start.second] = '|';
  if ( bl && br )
    pipes[start.first][start.second] = '-';
  if ( bl && bd )
    pipes[start.first][start.second] = '7';
  if ( bl && bu )
    pipes[start.first][start.second] = 'J';
  if ( bu && br )
    pipes[start.first][start.second] = 'L';
  if ( bd && br )
    pipes[start.first][start.second] = 'F';

  //print( pipes );
  pipes2 = pipes;

  // update pipes
  int steps {};

  // start with two pipes that connect to start
  work.insert( start );
  work = Update( pipes, work ); 

  while ( !work.empty() )
  {
    steps++;
    work = Update( pipes, work ); 
    //print( pipes );
  }
  steps--;
  
  print( pipes );
  cout << "steps = " << steps << endl;
  
  for ( auto i=0; i<height; i++ )
  {
    for ( auto j=0; j<width; j++ )
    {
      if ( pipes[i][j] != '*' )
        pipes2[i][j] = '.';
    }
  }

  int cnt {};
  int irow {};
  for ( auto row : pipes2 )
  {
    int icol {};
    int toggle {};
    bool up = false;
    bool down = false;
    for ( auto col : row )
    {
      if ( col == 'F' )
        down = true;
      if ( col == 'L' )
        up = true;
      if ( col == '|' )
        toggle++;
      if ( col == 'J' && down )
      {
        toggle++;
        down = false;
      }
      if ( col == 'J' && up )
        up = false;
      if ( col == '7' && down )
        down = false;
      if ( col == '7' && up )
      {
        toggle++;
        up = false;
      }
      if ( col == '.' && ( toggle & 0x1 ) )
      {
        pipes2[irow][icol] = 'I';
        cnt++;
      }

      icol++; 
    }
    irow++;
  }

  print( pipes2 );
  cout << "count = " << cnt << endl;
}