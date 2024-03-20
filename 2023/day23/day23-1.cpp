#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <tuple>
#include <vector>
#include <set>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::set;
using std::tuple;
using std::make_tuple;
using std::get;

bool FindStartAndEndNode( tuple<int,int> & s, tuple<int,int> & e, vector<vector<char>> g )
{
  for ( auto j=0; j<g[0].size(); j++ )
  {
    if (g[0][j] == '.')
      s = make_tuple( 0, j );

    if (g[g.size()-1][j] == '.')
      e = make_tuple( g.size()-1, j );
 
  }

  return true;
}

bool FindNode( );

  
void FindEdges( vector<tuple<int,int>> & w, vector<vector<char>> & g, tuple<int,int> e )
{
  while ( !w.empty() )
  {
    // check the paths to explore new nodes
    tuple<int,int> t = w.front();
    if (get<0>(t)==0) // start node
      FindNode( );
    else
    {
             
    }
  }
}


int main() {
  // open the file
  std::ifstream is("day23.test");
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

  // start from startnode
  work.push_back(startnode);
  nodes.push_back(startnode);

  FindEdges( work,grid, )

}