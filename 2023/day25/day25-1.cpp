#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <tuple>
#include <vector>
#include <set>
#include <algorithm>
#include <bits/stdc++.h>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::set;
using std::tuple;
using std::make_tuple;
using std::get;
using std::pair;


// https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm
// Adjacency matrix implementation of Stoer–Wagner min cut algorithm.
//
// Running time:
//     O(|V|^3)
pair<int, vector<int>> globalMinCut(vector<vector<int>> mat) {
    pair<int, vector<int>> best = {INT_MAX, {}};
    int n = mat.size();
    vector<vector<int>> co(n);

    for (int i = 0; i < n; i++)
        co[i] = {i};

    for (int ph = 1; ph < n; ph++) {
        vector<int> w = mat[0];
        size_t s = 0, t = 0;
        for (int it = 0; it < n - ph; it++) { // O(V^2) -> O(E log V) with prio. queue
            w[t] = INT_MIN;
            s = t, t = max_element(w.begin(), w.end()) - w.begin();
            for (int i = 0; i < n; i++) w[i] += mat[t][i];
        }
        best = min(best, {w[t] - mat[t][t], co[t]});
        co[s].insert(co[s].end(), co[t].begin(), co[t].end());
        for (int i = 0; i < n; i++) mat[s][i] += mat[t][i];
        for (int i = 0; i < n; i++) mat[i][s] = mat[s][i];
        mat[0][t] = INT_MIN;
    }

    return best;
}

int main() {
  // open the file
  std::ifstream is("day25.input");
  std::string str;

  // nodes 
  set<string> nodes;
  // edges
  set<tuple<string,string>> edges;

  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    string node;
    string node2;
    
    getline(iss,node,':');
    nodes.insert(node);
    
    while ( getline(iss,node2,' '))
    {
      if ( node2 == "" )
        continue;

      nodes.insert(node2);
      if (node<node2)
        edges.insert( make_tuple( node, node2 ));
      else
        edges.insert( make_tuple( node2, node ));
 
      cout << node << "<>" << node2 << endl;
    }

  }
  cout << endl;

  is.close();

  for ( auto n: nodes )
  {
    int res = count_if(edges.begin(), edges.end(), 
                       [n](tuple<string,string> e) { return ( get<0>(e) == n || get<1>(e) == n ); } );
    cout << "node " << n << " has a degree of " << res << endl;
  }

  vector<vector<int>> mat;

  for ( auto n: nodes )
  {
    vector<int> row;
    for ( auto m: nodes)
    {
      if ( n == m )
        row.push_back(0);
      else if ( edges.find( make_tuple(n,m) ) != edges.end() 
              || edges.find( make_tuple(m,n) ) != edges.end() )
        row.push_back(1);
      else
        row.push_back(0);
    }
    mat.push_back(row);
  }

  pair<int,vector<int>> res = globalMinCut( mat );

  cout << "answer1 = " << ( nodes.size() - res.second.size() ) * res.second.size() << endl;

}