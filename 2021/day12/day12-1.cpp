#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

void FindPaths( std::vector<std::string> path, std::string start, std::string end, std::map<std::string,std::set<std::string>> net, int & cnt )
{
  if ( path.back() == end )
  {
    std::cout << "[ ";
    if ( !path.empty() )
    {
      for ( auto p : path )
        std::cout << p << " ";
    }
    std::cout << "]" << std::endl;
  }

  if ( path.back() == end )
  {
    cnt++;
    return;
  }

  for ( auto n : net[path.back()] )
  {
    if ( std::find(path.begin(), path.end(), n) != path.end() && n.find_first_not_of("abcdefghijklmnopqrstuvwxyz") == std::string::npos )
      continue;
    
    path.push_back(n);
    FindPaths( path, start, end, net, cnt );
    path.pop_back();
  }

  return;
}

int main() {
  // open the file
  std::ifstream is("day12.input");
  std::string str;
  
  std::map<std::string,std::set<std::string>> net;
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::string sstr;

    std::string n1,n2;

    getline( iss, n1, '-' );
    getline( iss, n2, '-' );

    net[n1].insert(n2);
    net[n2].insert(n1);
  }
  std::cout << std::endl;

  is.close();

  std::vector<std::string> path;
  path.push_back("start");
  
  int cnt = 0;
  FindPaths( path, "start", "end", net, cnt );
  std::cout << "count = " << cnt << std::endl;
}