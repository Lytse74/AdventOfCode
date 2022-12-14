#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

//const int xs=12;
//const int ys=11;
//const int x_off = 493;

const int xs=63;
const int ys=163;
const int x_off = 443;

char grid[xs][ys]; // global config

void draw_line( int x1, int y1, int x2, int y2 )
{
  grid[x1 - x_off][y1] = '#'; 
  grid[x2 - x_off][y2] = '#';

  if ( x1 == x2 )
  {
    // vertical line
    int ty;
    if ( y1>y2 ) 
    {
      ty=y1; y1=y2; y2=ty;
    }
    for ( auto i=y1+1; i<y2; ++i)
      grid[x1 - x_off][i] = '#';
  }
  
  if ( y1 == y2 )
  {
    // horizontal line
    int tx;
    if ( x1>x2 ) 
    {
      tx=x1; x1=x2; x2=tx;
    }
    for ( auto i=x1+1; i<x2; ++i)
      grid[i-x_off][y1] = '#';
  }
}

void empty_grid()
{
  for ( auto i=0; i<xs; ++i )
  {
    for ( auto j=0; j<ys-1; ++j )
    {
      grid[i][j] = '.';
    }
    grid[i][ys-1] = '=';
  }
}

void print_grid()
{
  for ( auto i=0; i<ys; ++i )
  {
    for ( auto j=0; j<xs; ++j )
    {
      cout << grid[j][i];
    }
    cout << endl;
  }
   
}

void draw_sand(int x, int y, bool moves)
{
  if ( grid[x][y]=='.' && !moves)
  {
    grid[x][y]='o';
  }
  else if ( grid[x][y]=='.' && moves) 
  {
    grid[x][y]='~';
  }
  else
  {
    grid[x][y]='0';
  }
}

void set_sand_source()
{
  grid[500-x_off][0] = '+';
}

int main() {
  // open the file
  ifstream is("day14.input");
  string str;
  int miny=0,maxy=0,minx=500,maxx=500;

  empty_grid();

  while ( getline( is, str ) )
  {
    istringstream iss( str );
    char ch=' ';
    int x1,y1;
    int x2,y2;

    iss >> x1 >> ch >> y1;

    if ( x1 < minx ) minx=x1;
    if ( x1 > maxx ) maxx=x1;
    if ( y1 < miny ) miny=y1;
    if ( y1 > maxy ) maxy=y1;

    if ( iss.peek() == ' ')
      iss >> ch >> ch;
    ch = iss.peek();

    //cout << str << endl;
    while ( ch != EOF )
    {
      iss >> x2 >> ch >> y2;

      if ( iss.peek() == ' ')
        iss >> ch >> ch;
      ch = iss.peek();

      if ( x2 < minx ) minx=x2;
      if ( x2 > maxx ) maxx=x2;
      if ( y2 < miny ) miny=y2;
      if ( y2 > maxy ) maxy=y2;

      draw_line( x1,y1,x2,y2);

      x1=x2;
      y1=y2;
    }
  }
  
  set_sand_source();

  list<pair<int,int>> my_sand;
  list<pair<int,int>>::iterator sand_it;

  bool cont = true;

  int cnt = 0;
  int ti = 0;

  for ( auto i=0; i<968 && cont; i++)
  {
    ti=i;
    my_sand.push_back( make_pair( 500-x_off,0 ) );
    sand_it = my_sand.begin(); 
    while ( sand_it != my_sand.end() )
    {
      if ( grid[sand_it->first][sand_it->second+1]=='=')
      {  
        cont = false; 
        break;
      }
      else if ( grid[sand_it->first][sand_it->second+1]=='.')
      {
        sand_it->second++;
      }
      else if ( grid[sand_it->first-1][sand_it->second+1]=='.')
      {
        sand_it->first--;
        sand_it->second++;
      }
      else if ( grid[sand_it->first+1][sand_it->second+1]=='.')
      {
        sand_it->first++;
        sand_it->second++;
      }
      else
      {
        draw_sand( sand_it->first, sand_it->second, false );
        sand_it = my_sand.erase(sand_it);
        cnt++;
        continue;
        //my_sand.pop_front();
      
      }

      sand_it++;
      
    }
  }

  // draw_sands
  for (sand_it = my_sand.begin(); sand_it != my_sand.end(); ++sand_it)
  {
    draw_sand( sand_it->first, sand_it->second, true );
  }

  
  print_grid();

  cout << "x in [" << minx << "," << maxx << "]" << endl;
  cout << "y in [" << miny << "," << maxy << "]" << endl;

  cout << "cnt:" << cnt << endl;
  cout << "ti:" << ti << endl;

  //close the file
  is.close();
 }
