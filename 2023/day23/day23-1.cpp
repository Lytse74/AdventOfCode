#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <tuple>
#include <vector>
#include <set>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::set;
using std::tuple;
using std::make_tuple;
using std::get;
using std::tie;
using std::tuple_cat;

void print( vector<vector<char>> & g )
{
  for ( auto i=0 ; i < g.size() ; i++ )
  {
    for ( auto j=0 ; j< g[i].size() ; j++ )
    {
      cout << g[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

bool FindStartAndEndNode( tuple<int,int> & s, tuple<int,int> & e, vector<vector<char>> & g )
{
  for ( auto j=0; j<g[0].size(); j++ )
  {
    if (g[0][j] == '.')
    {
      s = make_tuple( 0, j );
      g[0][j] = 's';
    }

    if (g[g.size()-1][j] == '.')
    {
      e = make_tuple( g.size()-1, j );
      g[g.size()-1][j] = 'e';
    }
 
  }

  return true;
}

bool FindOtherNodes( vector<vector<char>> & g, vector<tuple<int,int>> & n )
{
  for ( auto i=1; i<g.size()-1; i++ )
  {
    for ( auto j=1; j<g[i].size()-1; j++ )
    {
      if ( g[i][j]=='.' )
      if ( g[i-1][j] == 'v' && ( g[i+1][j] == 'v' || g[i][j-1] == '<' || g[i][j+1] == '>' )
        || g[i+1][j] == '^' && ( g[i-1][j] == '^' || g[i][j-1] == '<' || g[i][j+1] == '>' ) 
        || g[i][j-1] == '>' && ( g[i][j+1] == '>' || g[i-1][j] == '^' || g[i+1][j] == 'v' )
        || g[i][j+1] == '<' && ( g[i][j-1] == '<' || g[i-1][j] == '^' || g[i][j+1] == 'v' ) )
      {
        n.push_back( make_tuple( i,j ));
        g[i][j] = '*';
      }
    }
  }
  return true;
}

int FindNode( tuple<int, int> b, vector<vector<char>> & g, tuple<int,int> & e,  char dir )
{
  int i {-1 };
  int j {-1 };
  int l { -1 };

  tie( i, j ) = b;
  l = 0;
  
  while ( g[i][j] != '*' && g[i][j] != 'e' || l == 0 )
  {
    // check dir ok
    if (l==0)
    {
      if ( dir == '>' && g[i][j+1] != '>' && g[i][j+1] != '#' )
        break;
      if ( dir == '<' && g[i][j-1] != '<' && g[i][j-1] != '#' )
        break;
      if ( dir == '^' && g[i-1][j] != '^' && g[i-1][j] != '#' )
        break;
      if ( dir == 'v' && g[i+1][j] != 'v' && g[i+1][j] != '#' )
        break;
    }
    else
    {
      g[i][j] = 'x';
    }

    l++;

    if ( j<g[i].size()-1 && !( i == get<0>(b) && j+1 == get<1>(b) ) && ( g[i][j+1] == '.' || l==1 && g[i][j+1] == dir || l>1 && ( g[i][j+1] == '>' || g[i][j+1] == '<' || g[i][j+1] == '^' || g[i][j+1] == 'v' || g[i][j+1] == '*' ) ) )
      j++;
    else if ( i>0 && !( i-1 == get<0>(b) && j == get<1>(b) ) && ( g[i-1][j] == '.' || l==1 && g[i-1][j] == dir || l>1 && ( g[i-1][j] == '>' || g[i-1][j] == '<' || g[i-1][j] == '^' || g[i-1][j] == 'v' || g[i-1][j] == '*' ) ) )
      i--;
    else if ( j>0 && !( i == get<0>(b) && j-1 == get<1>(b) ) && ( g[i][j-1] == '.' || l==1 && g[i][j-1] == dir || l>1 && ( g[i][j-1] == '>' || g[i][j-1] == '<' || g[i][j-1] == '^' || g[i][j-1] == 'v' || g[i][j-1] == '*' ) ) )
      j--;
    else if ( i<g.size()-1 && !( i+1 == get<0>(b) && j == get<1>(b) ) && ( g[i+1][j] == 'e' || g[i+1][j] == '.' || l==1 && g[i+1][j] == dir || l>1 && ( g[i+1][j] == '>' || g[i+1][j] == '<' || g[i+1][j] == '^' || g[i+1][j] == 'v' || g[i+1][j] == '*' ) ) )
      i++;
    else
      break;
  } 

  e = make_tuple( i , j );

  return l;
}
  
void FindEdges( vector<tuple<int,int>> & w, vector<vector<char>> & g, vector<tuple<int,int,int,int,int>> & e )
{

  vector<tuple<int,int>>::iterator it_w = w.begin();
  tuple<int,int> end;
  
  while ( it_w != w.end() )
  {
    // check the paths to explore new nodes
    tuple<int,int> t = *it_w;
    int l = 0;
    if (get<0>(t)==0) // start node
    {
      l = FindNode( t, g, end, '*' );
      e.push_back( tuple_cat( t,end, make_tuple(l) ) );
    }
    else if ( get<0>(t) == g.size()-1 )
    {
      cout << "READY" << endl;
    }
    else
    {
      // only doe this for paths leaving the node at most 3
      if ( g[get<0>(t)][get<1>(t)+1] == '>' )
      {
        l = FindNode( t, g, end, '>' );
        e.push_back( tuple_cat( t,end, make_tuple(l) ) );
      }
      if ( g[get<0>(t)][get<1>(t)-1] == '<' )
      {
        l = FindNode( t, g, end, '<' );
        e.push_back( tuple_cat( t,end, make_tuple(l) ) );
      }
      if ( g[get<0>(t)-1][get<1>(t)] == '^' )
      {
        l = FindNode( t, g, end, '^' );
        e.push_back( tuple_cat( t,end, make_tuple(l) ) );
      }
      if ( g[get<0>(t)+1][get<1>(t)] == 'v' )
      {
        l = FindNode( t, g, end, 'v' );
        e.push_back( tuple_cat( t,end, make_tuple(l) ) );
      }
    }
    it_w = w.erase(it_w);
    print(g);
  }
}

void printEdges( vector<tuple<int,int,int,int,int>>  e )
{
  int a,b,c,d,v;

  for ( auto elem : e )
  {
    tie(a,b,c,d,v) = elem;
    cout << "P" << a << "_" << b << " -> " << "P" << c << "_" << d << "[label=" << v << "]" << endl;
  }
}

void AddBidirectionalEdges( tuple<int,int> s1, tuple<int,int> s2, vector<tuple<int,int,int,int,int>> & e )
{
  vector<tuple<int,int,int,int,int>>::iterator it_e;
  vector<tuple<int,int,int,int,int>> ne;

  for ( it_e = e.begin(); it_e != e.end(); it_e++ )
  {
    ne.push_back(*it_e);
    if ( !( get<0>(*it_e) == get<0>(s1)  && get<1>(*it_e) == get<1>(s1) ) && !( get<2>(*it_e) == get<0>(s2)-1 && get<3>(*it_e) == get<1>(s2) ) )
      ne.push_back( make_tuple( get<2>(*it_e), get<3>(*it_e), get<0>(*it_e), get<1>(*it_e), get<4>(*it_e) ) );
  }
  e = ne;
}

int FindMaxPath( tuple<int,int> s1, tuple<int,int> s2, vector<tuple<int,int,int,int,int>> e, int & curVal, vector<tuple<int,int>> & path )
{
  int val = 0;
  int maxval = -10000; // penalty for dead end

  vector<tuple<int,int,int,int,int>> s;
  vector<tuple<int,int,int,int,int>>::iterator it_e = e.begin();

  // find edges that start from s1
  for( it_e = e.begin(); it_e != e.end(); it_e++ )
  {
    if ( get<0>(*it_e) == get<0>(s1) && get<1>(*it_e) == get<1>(s1) )
    {
      s.push_back(*it_e);
      it_e = e.erase(it_e);
      it_e--;
    }
  }
  
  // eliminate edges that try to get back to s1
  for( it_e = e.begin(); it_e != e.end(); it_e++ )
  {
    if ( get<2>(*it_e) == get<0>(s1) && get<3>(*it_e) == get<1>(s1) )
    {
      it_e = e.erase(it_e);
      it_e--;
    }
  }
  
  // calculate the max
  for ( auto elem: s )
  {
    tuple<int,int> sn1 = make_tuple( get<2>(elem), get<3>(elem) ); 

    if ( sn1 != s1 && sn1 != s2 )
    {
      curVal = curVal + get<4>(elem);
      path.push_back(s1);
      val = get<4>(elem) + FindMaxPath(sn1,s2,e, curVal, path );
      path.pop_back();
      curVal = curVal - get<4>(elem);
    }
    else if ( sn1 == s2 )
    {
      val = get<4>(elem);
/*
      if ( curVal >= 6400 )
      {
        cout << curVal + val << endl;
        for ( auto pnt: path )
        {
          cout << "P(" << get<0>(pnt) << "," << get<1>(pnt) << ") ";
        }
        cout << endl;
      }
*/
    }

    if ( val > maxval )
    {
      maxval = val;
    }
  }

  return maxval;
}

int main() {
  // open the file
  std::ifstream is("day23.input");
  std::string str;
  vector<vector<char>> grid;
  vector<tuple<int,int>> nodes;
  vector<tuple<int,int,int,int,int>> edges;
  tuple<int,int> startnode;
  tuple<int,int> endnode;
  vector<tuple<int,int>> work;
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    char ch {};

    vector<char> line;
    
    while ( iss.get(ch) )
    {

      line.push_back(ch);
      cout << ch;
    }
    grid.push_back(line);
    cout << endl;
  }
  cout << endl;

  is.close();

  FindStartAndEndNode( startnode, endnode, grid );
  nodes.push_back(startnode);
  //print( grid );

  FindOtherNodes( grid, nodes );
  //print( grid );
  nodes.push_back(endnode);

  // start from startnode
  for ( auto e : nodes )
  {
    work.push_back(e);
  }

  FindEdges( work,grid, edges );
  print( grid );

  //printEdges( edges );

  int answer { 0 };
  int val { 0 };
  vector<tuple<int,int>> path;

  answer = FindMaxPath( startnode, endnode, edges, val, path );
  cout << "answer = " << answer << endl;

  AddBidirectionalEdges( startnode, endnode, edges );
  //printEdges( edges );

  int answer2 { 0 };
  answer2 = FindMaxPath( startnode, endnode, edges, val, path );
  cout << "answer2 = " << answer2 << endl;
}