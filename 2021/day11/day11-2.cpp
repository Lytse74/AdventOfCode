#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

void PrintField( std::vector<std::vector<int>> field )
{
  for ( auto v: field )
  {
    for ( auto i: v )
      std::cout << i << '-';
    std::cout << std::endl;
  }
  std::cout << std::endl;
}


int MakeStep( std::vector<std::vector<int>> & field, int d, int w )
{
  int flashes = 0;
  std::vector<std::pair<int,int>> spikes;
  std::vector<std::pair<int,int>>::iterator it;

  // init  
  for ( int i=0; i<d; ++i )
  {
    for ( int j=0; j<w; ++j )
    {
      ++field[i][j];
    }
  }
  PrintField( field );

  while( true ) {
    // find spikes
    for ( int i=0; i<d; ++i )
    {
      for ( int j=0; j<w; ++j )
      {
        if ( field[i][j] > 9)
          spikes.push_back( std::make_pair(i,j) );
      }
    }

    if ( spikes.empty() ) break;

    // flash it
    while ( !spikes.empty() )
    {
      it = spikes.begin();
      int x=it->first,y=it->second;
      
      field[x][y] = 0;
      if (x>0 && y>0 && field[x-1][y-1]>0) ++field[x-1][y-1];
      if (x>0 && field[x-1][y]>0) ++field[x-1][y];
      if (x>0 && y<(w-1) && field[x-1][y+1]>0) ++field[x-1][y+1];
      if (y<(w-1) && field[x][y+1]>0) ++field[x][y+1];
      if (x<(d-1) && y<(w-1) && field[x+1][y+1]>0) ++field[x+1][y+1];
      if (x<(d-1) && field[x+1][y]>0) ++field[x+1][y];
      if (x<(d-1) && y>0 && field[x+1][y-1]>0) ++field[x+1][y-1];
      if (y>0 && field[x][y-1]>0) ++field[x][y-1];
      flashes++;
        
      spikes.erase(it);
      it = spikes.begin();
      }
      PrintField( field );
    }

  return flashes;
}

int main() {
  // open the file
  std::ifstream is("day11.input");
  std::string str;
  std::vector<std::vector<int>> field;
  int width=0;
  int depth=0;
  int cnt=1;
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    char ch;
    std::vector<int> line;

    while ( iss.get(ch) )
    {
      std::cout << ch << "-";
      line.push_back( ch - '0' );
    }
    std::cout << std::endl;
    width = line.size();

    field.push_back( line );
    depth++;
  }
  std::cout << std::endl;

  is.close();

   while ( MakeStep( field, width, depth ) != 100 )
     cnt++;
  std::cout << "count = " << cnt << std::endl;
}
