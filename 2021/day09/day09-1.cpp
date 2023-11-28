#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main() {
  // open the file
  std::ifstream is("day09.input");
  std::string str;
  int width=0;
  int height=0;
  int risk=0;
  int cnt=0;

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
        risk += ( heightmap[i][j] + 1);
        cnt++;
      }
      else
        std::cout << "*-" ;
    }
    std::cout << std::endl;
  }

  std::cout << "risk = " << risk << " count  = " << cnt << std::endl; 
}
