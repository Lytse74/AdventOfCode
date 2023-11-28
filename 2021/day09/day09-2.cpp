#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>

int FillBassin( const std::vector<std::vector<int>> map, int x, int y, int w, int h )
{
  std::set<std::pair<int,int>> explore;
  std::set<std::pair<int,int>> bassin;
  std::set<std::pair<int,int>>::iterator it;

  explore.insert( std::make_pair( x, y ) );

  it = explore.begin();

  while ( !explore.empty() )
  {
    if ( map[it->first][it->second] < 9 )
    {
      bassin.insert( std::make_pair( it->first, it->second ) );

      std::pair<int,int> tmp;
      if ( it->first > 0 )
      {
        tmp = std::make_pair( it->first - 1, it->second );
        if ( bassin.find( tmp ) == bassin.end() )
          explore.insert( tmp );
      }
      if ( it->first < (h - 1) )
      {
        tmp = std::make_pair( it->first + 1, it->second );
        if ( bassin.find( tmp ) == bassin.end() )
          explore.insert( tmp );
      }
      if ( it->second > 0 )
      {
        tmp = std::make_pair( it->first, it->second - 1 );
        if ( bassin.find( tmp ) == bassin.end() )
          explore.insert( tmp );
      }
      if ( it->second < ( w - 1 ) )
      {
        tmp = std::make_pair( it->first, it->second + 1 );
        if ( bassin.find( tmp ) == bassin.end() )
          explore.insert( tmp );
      }
    }
    explore.erase( it );
    it = explore.begin();
  }

  return bassin.size();
}

int main() {
  // open the file
  std::ifstream is("day09.input");
  std::string str;
  int width=0;
  int height=0;
  int risk=0;

  std::vector<std::vector<int>> heightmap;

  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    char ch;

    std::vector<int> heightline;

    while ( iss.get(ch) )
    {
      std::cout << ch << "-";
      heightline.push_back( ch - '0' );
    }
    std::cout << std::endl;
    width = heightline.size();

    heightmap.push_back( heightline );
    height++;
  }

  is.close();

  std::cout << "width = " << width << " height = " << height << std::endl;

  int max1=0, max2=0,max3=0, val=0;

  for ( int i = 0 ; i < height ; ++i )
  { 
    for ( int j = 0 ; j < width ; ++j )
    {
      bool min = true; 
      if ( j > 0 && heightmap[i][j] > heightmap[i][j-1] )
        min = false;
      if ( j < width-1 && heightmap[i][j] > heightmap[i][j+1] )
        min = false;
      if ( i > 0 && heightmap[i][j] > heightmap[i-1][j])
        min = false;
      if ( i < height-1 && heightmap[i][j] > heightmap[i+1][j] )
        min = false;
      if ( heightmap[i][j] == 9 )
        min = true;
      
      if (min)
      {
        std::cout << heightmap[i][j] << "-";
        if ( heightmap[i][j] < 9 )
        {
          risk += ( heightmap[i][j] + 1);
          val = FillBassin( heightmap, i, j, width, height );
          if ( val>=max1) { max3 = max2; max2 = max1; max1 = val; }
          else if ( val>=max2) { max3 = max2; max2 = val; }
          else if ( val>=max3) max3 = val;
        }
      }
      else
        std::cout << "*-" ;
    }
    std::cout << std::endl;
  }

  std::cout << "risk = " << risk << std::endl; 
  std::cout << "max = [ " << max1 << "," << max2 << "," << max3 << " ]" << std::endl;
  std::cout << "answer = " << max1*max2*max3 << std::endl;
}
