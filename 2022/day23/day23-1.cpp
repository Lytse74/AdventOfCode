#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void print( const vector<string> maps )
{
  for ( int i=1; i<maps.size()-1; ++i )
  {
    for ( int j=1; j<maps[i].length()-1; ++j )
    {
        cout << maps[i][j];
    }
    cout << endl;
  }
}

void proposal( const vector<string> maps, const vector<vector<short>> dir, vector<pair<pair<int,int>,pair<int,int>>> & moves, map<pair<int,int>,int> & count )
{
  for ( int i=1; i<maps.size()-1; ++i )
  {
    for ( int j=1; j<maps[i].length()-1; ++j )
    {
      if ( maps[i][j] == '#' )
      {
        bool proposal =  false;

        if ( maps[i-1][j-1] == '.' 
          && maps[i-1][j] == '.' 
          && maps[i-1][j+1] == '.' 
          && maps[i][j-1] == '.' 
          && maps[i][j+1] == '.' 
          && maps[i+1][j-1] == '.' 
          && maps[i+1][j] == '.' 
          && maps[i+1][j+1] == '.' 
        )
        {
          ;
        }
        else   
          for ( int d=0; d<dir.size(); ++d)
          {
            if ( maps[i+dir[d][0]][j+dir[d][1]] == '.' 
              && maps[i+dir[d][2]][j+dir[d][3]] == '.' 
              && maps[i+dir[d][4]][j+dir[d][5]] == '.' 
            )
            {
  //            cout <<  d;
              moves.push_back( make_pair( make_pair( i+dir[d][2], j+dir[d][3]), make_pair( i, j ) ));
              count[ make_pair( i +dir[d][2], j+dir[d][3])]++;
              proposal = true;
              break;
            }
          }
          
  //        if ( !proposal ) 
  //          cout << maps[i][j];
        }
  //      else
  //        cout << maps[i][j];
      }
  //    cout << endl;
    }
  }

void prune( vector<pair<pair<int,int>,pair<int,int>>> & moves, map<pair<int,int>,int> count )
{
  vector<pair<pair<int,int>,pair<int,int>>>::iterator it;

  it = moves.begin();

  while ( it != moves.end() )
  {
    if ( count[it->first] > 1 )
    {
      it = moves.erase(it);
    }
    else
      ++it;
  }
}

void clear( vector<pair<pair<int,int>,pair<int,int>>> & moves, map<pair<int,int>,int> & count )
{
  moves.clear();
  count.clear();
}

void rotate( vector<vector<short>> & dir )
{
  rotate( dir.begin(), dir.begin()+1, dir.end());
}

void execute( vector<string> & maps, vector<pair<pair<int,int>,pair<int,int>>> moves )
{
  vector<pair<pair<int,int>,pair<int,int>>>::iterator it;

  it = moves.begin();

  while ( it != moves.end() )
  {
    maps[(it->first).first][(it->first).second] = '#';
    maps[(it->second).first][(it->second).second] = '.';
    ++it;
  }
}

int result_p1( const vector<string> maps )
{
  int min_i = maps.size();
  int min_j = maps[0].length();
  int max_i = 0;
  int max_j = 0;
  int cnt = 0;

  for ( int i=0; i<maps.size()-1; ++i )
  {
    for ( int j=0; j<maps[i].length()-1; ++j )
    {
      if ( maps[i][j] == '#' )
      {
        cnt++;
        if ( i < min_i ) min_i = i;
        if ( j < min_j ) min_j = j;
        if ( i > max_i ) max_i = i;
        if ( j > max_j ) max_j = j;
      }
    } 
  }
  cout << "count: " << cnt << " rows: " << (max_i - min_i +1) << " cols:" << (max_j - min_j +1) << endl;

  return ((max_i - min_i +1)*(max_j - min_j +1) - cnt);
}

int main() {
  // open the file
  ifstream is("day23.input");
  string str;
  vector<string> maps;
  vector<string>::iterator maps_it;

  const int border = 10;
  int strlen=0;

  getline(is,str);
  strlen = str.length();
  
  string tmp = "";
  tmp.append(strlen - tmp.length(), '.');
  tmp.insert(tmp.begin(), border, '.');
  tmp.append(border, '.');

  for ( int  i=0; i<border; ++i)
    maps.push_back( tmp );

  str.insert(str.begin(), border, '.');
  str.append(border, '.');
  maps.push_back( str );

  while ( getline( is, str ) )
  {
    str.insert(str.begin(), border, '.');
    str.append(border, '.');
    maps.push_back( str );
  }

  for ( int  i=0; i<border; ++i)
    maps.push_back( tmp );

  for ( maps_it = maps.begin() ; maps_it != maps.end() ; ++maps_it )
  {
    cout << *maps_it << endl;
  }

  //close the file
  is.close();

  vector<vector<short>> dir = {{ -1, -1 , -1, 0, -1, 1 } // north
                                ,{ 1, -1, 1, 0, 1, 1 } // south
                                ,{ -1, -1, 0, -1 , 1, -1 } // west
                                ,{ -1,1,0,1,1,1 }}; // east

  vector<pair<pair<int,int>,pair<int,int>>> moves;
  
  map<pair<int,int>,int> count;

  for ( int i=0; i<10; i++ )
  {
    clear( moves, count );
    result_p1(maps);
    proposal( maps, dir, moves, count );
    prune( moves, count );
    execute( maps, moves );
    cout << "After round " << i+1 << endl;
    print( maps );
    rotate( dir );
  }

  cout << "result: " << result_p1( maps ) << endl;
}
