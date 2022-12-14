#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  // open the file
  ifstream is("day05.input");
   
  // read a line segment from the file
  int x1,y1,x2,y2;
  string skip;

  int grid[1000][1000];
  for ( auto i=0; i<1000; ++i)
  {
    for ( auto j=0; j<1000; ++j)
    {
      grid[i][j] = 0;
    }
  }

  while ( is >> x1 
          && getline(is,skip,',')
          && is >> y1 
          && getline(is,skip,'>')
          && is >> x2 
          && getline(is,skip,',')
          && is >> y2 )
  {
    if (x1==x2)
    {
      cout << "VERT" << endl;
      if (y1>y2)
      {
        int t=y1; y1=y2; y2=t;
      }  
      for ( auto y=y1; y<=y2; ++y)
      {
        grid[x1][y]++;
      }
    }
    if (y1==y2)
    {
      cout << "HORZ" << endl;
      if (x1>x2)
      {
        int t=x1; x1=x2; x2=t;
      }  
      for ( auto x=x1; x<=x2; ++x)
      {
        grid[x][y1]++;
      }
    }
  }

  // print grid
  // and count >1
  int cnt=0;
  for ( auto i=0; i<1000; ++i)
  {
    for ( auto j=0; j<1000; ++j)
    {
      if ( j<= 10 && i <= 10)
        cout << grid[i][j] << " ";
      if ( grid[i][j] > 1 )
        cnt++;
    }
    if ( i <= 10)
      cout << endl;
  }

  cout << "cnt: " << cnt << endl;




  //close the file
  is.close();
}
