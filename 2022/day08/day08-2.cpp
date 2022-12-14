#include <fstream>
#include <iostream>
#include <string>
using namespace std;


int main() {
  // open the file
  ifstream is("day08.input");

  short tree[99][99];
  int dist[99][99];
  string str;

  for ( auto i=0 ; i<99 ; ++i )
    for ( auto j=0; j<99 ; j++ )
    {
      dist[i][j] = -1;
      tree[i][j] = -1;
    }

  int i=0,j=0;

  while ( getline( is, str ) )
  {
    cout << str << endl;
    //put th trees in array
    j=0;
    for ( char& c : str )
    {
      tree[i][j] = c - '0';
      j++;
    }
    i++;
  }

  for ( auto i=0 ; i<99 ; ++i )
  {
    for ( auto j=0; j<99 ; j++ )
    {
      // make border vis
      if ( i == 0 || j == 0 || i == 98 || j == 98 )
        dist[i][j] = 0;
    }
  }
  
  for ( auto i=1 ; i<98 ; ++i )
  {
    for ( auto j=1; j<98 ; j++ )
    {
      int r=1,l=1,t=1,b=1;
      for ( auto t1=j+1; t1<98; ++t1 )
      {
        if ( tree[i][j] > tree[i][t1] && tree[i][t1]>=0 )
          r++;
        
        if ( tree[i][j] <= tree[i][t1] )
          break;
      }
      for ( auto t1=j-1; t1>0; --t1 )
      {
        if ( tree[i][j] > tree[i][t1] && tree[i][t1]>=0 )
          l++;
        
        if ( tree[i][j] <= tree[i][t1] )
          break;
      }
      for ( auto t1=i+1; t1<98; ++t1 )
      {
        if ( tree[i][j] > tree[t1][j] && tree[t1][j]>=0 )
          b++;
        
        if ( tree[i][j] <= tree[t1][j] )
          break;
      }
      for ( auto t1=i-1; t1>0; --t1 )
      {
        if ( tree[i][j] > tree[t1][j] && tree[t1][j]>=0 )
          t++;
        
        if ( tree[i][j] <= tree[t1][j] )
          break;

      }
      dist[i][j]=t*l*b*r;
//Looking up, its view is blocked at 2 trees (by another tree with a height of 5).
//Looking left, its view is not blocked; it can see 2 trees.
//Looking down, its view is also not blocked; it can see 1 tree.
//Looking right, its view is blocked at 2 trees (by a massive tree of height 9).
    }
  }
  
  int max = 0;

  for ( auto i=0 ; i<99 ; ++i )
  {
    for ( auto j=0; j<99 ; j++ )
    {
      //cout << tree[i][j];
      cout << dist[i][j];
      if ( dist[i][j]>=max && tree[i][j] >= 0 ) max=dist[i][j];  
    }
    cout << endl;
  }

  cout << "max: " << max << endl;

  //close the file
  is.close();
}
