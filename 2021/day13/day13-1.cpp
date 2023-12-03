#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <utility>

void PrintPaper( std::set<std::pair<int,int>> paper, int lx, int ux, int ly, int uy )
{
  std::set<std::pair<int,int>>::iterator it;
  it = paper.begin();
  for ( int j = ly; j<=uy; j++ )
  {
    for ( int i = lx; i<=ux; i++ )
    {
      if ( paper.find( std::make_pair(i,j) ) != paper.end() ) //( it->first == i && it->second == j )
      {
        std::cout << "#";
        it++;
      }
      else
        std::cout << ".";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  return;
}

void FoldPaper( std::set<std::pair<int,int>> & paper, char axis, int val, int& minx, int& maxx, int& miny, int& maxy )
{
  std::set<std::pair<int,int>>::iterator it;
  std::set<std::pair<int,int>>::iterator itb;
  std::set<std::pair<int,int>> scratch;
  it = paper.begin();
  
  if ( axis == 'x' )
  {
    if ( val - (maxx - val) < minx ) 
      minx = val - (maxx - val);
    maxx = val-1;

    while ( it != paper.end() )
    {
      if ( it->first > val )
      {
        scratch.insert( std::make_pair( val - ( it->first - val ), it->second ) );
        it = paper.erase(it);
      }
      else 
        it++;
    }
  }

  if ( axis == 'y' )
  {
    if ( val - (maxy - val) < miny )
      miny = val - (maxy - val);
    maxy = val-1;
    
    while ( it != paper.end() )
    {
      if ( it->second > val )
      {
        scratch.insert( std::make_pair( it->first, val - ( it->second - val ) ) );
        it = paper.erase(it);
      }
      else 
        it++;
    }
  }

  // join scratch in paper
  paper.insert(scratch.begin(), scratch.end());
  return;
}

int main() {
    // open the file
    std::ifstream is("day13.input");
    std::string str;
    
    int minx=1000, miny=1000, maxx=0, maxy=0;

    std::set<std::pair<int,int>> points;
    std::set<std::pair<int,int>>::iterator it;


    while ( getline( is, str ) && str != "" )
    {
      std::istringstream iss(str);
      std::string sstr;
    int x=0; int y=0;
    int idx =0;

    while ( getline( iss, sstr, ',' ) )
    {
      if ( idx == 0) x = std::stoi( sstr );
      if ( idx == 1) 
      {
        y = std::stoi( sstr );
        if ( x < minx ) minx = x;
        if ( x > maxx ) maxx = x;
        if ( y < miny ) miny = y;
        if ( y > maxy ) maxy = y;
      }
      idx++;
    }
    points.insert( std::make_pair( x,y ) );
    std::cout << "x = " << x << " y = " << y << std::endl;
  }
  std::cout << "minx = " << minx << " miny = " << miny << std::endl;
  std::cout << "maxx = " << maxx << " maxy = " << maxy << std::endl;

  PrintPaper( points, minx, maxx, miny, maxy );
  while ( getline( is, str ) && str != "" )
  {
    std::istringstream iss(str);
    std::string sstr;
    int idx=0;
    char axis;
    int axisval=-1;

    while ( getline( iss, sstr, '=' ) )
    {
      if ( idx == 0 ) axis = sstr.back();
      if ( idx == 1 ) axisval = std::stoi( sstr );
      idx++;
    }
    std::cout << "axis = " << axis << ":" << axisval << std::endl;
    std::cout << "str = " << str << std::endl;

    FoldPaper( points, axis, axisval, minx, maxx, miny, maxy );
    PrintPaper( points, minx, maxx, miny, maxy );

  }

  std::cout << "points = " << points.size() << std::endl;


  is.close();
}