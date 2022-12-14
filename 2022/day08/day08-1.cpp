#include <fstream>
#include <iostream>
#include <string>
using namespace std;


int main() {
  // open the file
  ifstream is("day08.input");

  bool vis[99][99];
  short tree[99][99];
  string str;

  for ( auto i=0 ; i<99 ; ++i )
    for ( auto j=0; j<99 ; j++ )
    {
      vis[i][j] = true;
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
      vis[i][j] = false;
      j++;
    }
    i++;
  }

  for ( auto i=0 ; i<99 ; ++i )
  {
    int mt = tree[i][0];
    for ( auto j=0; j<99 ; j++ )
    {
      // make border vis
      if ( i == 0 || j == 0 || i == 98 || j == 98 )
        vis[i][j] = true;
      
      // left -> right
      if ( tree[i][j] > mt )
      {
        vis[i][j] = true;
        mt = tree[i][j];
      }
    }
  }
  
  for ( auto i=0 ; i<99 ; ++i )
  {
    int mt = tree[i][98];
    for ( auto j=0; j<99 ; j++ )
    {
      // right -> left
      if ( tree[i][98-j] > mt )
      {
        vis[i][98-j] = true;
        mt = tree[i][98-j];
      }
    }
  }
  
  for ( auto i=0 ; i<99 ; ++i )
  {
    int mt = tree[0][i];
    for ( auto j=0; j<99 ; j++ )
    {
      // top -> bottom
      if ( tree[j][i] > mt )
      {
        vis[j][i] = true;
        mt = tree[j][i];
      }
    }
  }

  for ( auto i=0 ; i<99 ; ++i )
  {
    int mt = tree[98][i];
    for ( auto j=0; j<99 ; j++ )
    {
      // bottom -> top
      if ( tree[98-j][i] > mt )
      {
        vis[98-j][i] = true;
        mt = tree[98-j][i];
      }
    }
  }

  int cnt = 0;

  for ( auto i=0 ; i<99; ++i )
  {
    for ( auto j=0; j<99 ; j++ )
    {
      //cout << tree[i][j];
      cout << vis[i][j] ? 1 : 0 ;
      if ( vis[i][j] && tree[i][j] >= 0 ) cnt++;  
    }
    cout << endl;
  }

  cout << "cnt: " << cnt << endl;

  //close the file
  is.close();
}
