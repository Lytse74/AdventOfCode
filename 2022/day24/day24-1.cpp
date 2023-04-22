#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

const int mod = 12; // minute repeat

char retBlizzard( vector<string> amap, int minute, int i, int j )
{
  bool be=false, bw=false, bs=false, bn=false;
  int lj = amap[i].size();
  int li = amap.size();
  char ret = 'x';

  // east
  if ( amap[i][((j-minute-1)%(lj-2)+lj-2)%(lj-2)+1] == '>' )
    be = true;
  // west
  if ( amap[i][(j+minute-1)%(lj-2)+1] == '<' )
    bw = true;
  // north
  if ( amap[(i+minute-1)%(li-2)+1][j] == '^' )
    bn = true;
  // south
  if ( amap[((i-minute-1)%(li-2)+li-2)%(li-2)+1][j] == 'v' )
    bs = true;

  if (  be && bw && bn && bs)
    ret = '4';
  else if ( be && bw && bn || be && bw && bs || be && bn && bs || bw && bn && bs )
    ret = '3';
  else if ( be && bw || be && bn || be && bs || bw && bn || bw && bs || bn && bs )
    ret = '2';
  else if ( be )
    ret = '>';
  else if ( bw )
    ret = '<';
  else if ( bn )
    ret = '^';
  else if ( bs )
    ret = 'v';
  else
    ret = '.';
  
  return ret;
}

void printBlizzards( vector<string> amap, int minute )
{
  int li = amap.size();
  for ( int i = 0; i<li; ++i )   
  {
    int lj = amap[i].length();

    for ( int j = 0; j<lj; ++j )
    {
      if (i==0 || j==0 || i == li-1 || j == lj-1 )
        cout << amap[i][j];
      else
      {
        cout << retBlizzard( amap, minute, i, j );
      }
    }
    cout << endl;
  }
}

set<vector<int>> validMoves( vector<string> amap, int minute, int i, int j )
{
  set<vector<int>> aSet;

  // Check start position
  if ( retBlizzard( amap, minute, i, j ) != '.' )
    return aSet;
  
  // entrance
  if ( i==0 && j==1 )
  {
    // stay
    aSet.insert( { minute%mod, i, j, (minute+1)%mod, i, j } );
    // south
    if ( retBlizzard( amap, minute+1, i+1, j ) == '.' )
      aSet.insert( { minute%mod, i, j, (minute+1)%mod, i+1, j } );
    return aSet;
  }

  // stay
  if ( retBlizzard( amap, minute+1, i, j ) == '.' )
    aSet.insert( { minute%mod, i, j, (minute+1)%mod, i, j } );

  // east
  if ( j < amap[i].length()-2
    && retBlizzard( amap, minute+1, i, j+1 ) == '.' )
    aSet.insert( { minute%mod, i, j, (minute+1)%mod, i, j+1 } );

  // west vvv nice
  if ( j > 2
    && retBlizzard( amap, minute+1, i, j-1 ) == '.' )
    aSet.insert( { minute%mod, i, j, (minute+1)%mod, i, j-1 } );

  // north vv twice :s
  if ( i > 2
    && retBlizzard( amap, minute+1, i-1, j ) == '.' )
    aSet.insert( { minute%mod, i, j, (minute+1)%mod, i-1, j } );

  // south
  if ( i < amap.size()-2 
    && retBlizzard( amap, minute+1, i+1, j ) == '.' )
    aSet.insert( { minute%mod, i, j, (minute+1)%mod, i+1, j } );

  // exit
  if ( i==amap.size()-2 && j==amap[i].length()-2 )
  {
    if ( retBlizzard( amap, minute+1, i+1, j ) == '.' )
      aSet.insert( { minute%mod, i, j, (minute+1)%mod, i+1, j } );
  }

  return aSet;
}

int main() {
  // open the file
  ifstream is("day24.test");
  string str;
  vector<string> mymap;

  while ( getline( is, str ) )
  {
    mymap.push_back( str );
    cout << str << endl;
  }
  cout << "^^INPUT^^" << endl;

  //close the file
  is.close();

  // indexes for tornados
  //for ( int i=0; i<18; i++ )
  //  printBlizzards( mymap, i );

  set<vector<int>> unvisited = { { 0, 0, 1, 0 } };
  set<vector<int>> visited;
  set<vector<int>> edges;

  set<vector<int>>::iterator it;

  it = unvisited.begin();
  while ( it != unvisited.end() )
  {
    // put these in unvisited
    set<vector<int>> tmp = validMoves( mymap, (*it)[0],(*it)[1],(*it)[2] );
    set<vector<int>>::iterator tit;

    tit = tmp.begin();
    while( tit != tmp.end() )
    {
      unvisited.insert( { (*tit)[3], (*tit)[4], (*tit)[5], (*it)[3]+1 } );
      edges.insert( *tit );
      ++tit;
    }
    visited.insert( *it );

    // its a mess now got to sort this out sometimeA
    if ( (*it)[1] == (mymap.size()-1) && (*it)[2] == (mymap[(*it)[1]].length()-2) )
      break;

    it = unvisited.erase( it );
    if ( it == unvisited.end() && unvisited.size() > 0 )
       it = unvisited.begin();
  }

  it = visited.begin();
  while ( it != visited.end() )
  {
    if ( ((*it)[1] == (mymap.size()-1)) && ((*it)[2] == (mymap[(*it)[1]].length()-2) ) )
    {
      cout << "result: " << (*it)[3] << endl;
    }
    ++it;
  } 
}
