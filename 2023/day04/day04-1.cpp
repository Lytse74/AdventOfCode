#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <map>

using std::istringstream;
using std::cout;
using std::endl;
using std::set;
using std::set_intersection;
using std::map;

int main() {
  // open the file
  std::ifstream is("day04.input");
  std::string str;
  int sum {};
  map<int,int> cards;
  int total {};
  
  while ( getline( is, str ) )
  {
    istringstream iss(str);
    std::string sstr;
    set<int> draw;
    set<int> wins;
    set<int> intersect;
    int points {};
    int size {};
    int card {};

    getline( iss, sstr, ':' );
    {
      istringstream isss(sstr);
      std::string ssstr;
      getline( isss, ssstr, ' ');
      cout << ssstr << endl;
      while ( getline( isss, ssstr, ' '));
      card = std::stoi( ssstr );
      cout << card << endl;
      cards[card] += 1;
    }
    getline( iss, sstr, '|' );
    {
      istringstream isss(sstr);
      int tmp {};
 
      while ( isss >> tmp )
      {
        draw.insert( tmp );
        cout << tmp << " ";
      }
      cout << endl;
    }
    getline( iss, sstr );
    {
      istringstream isss(sstr);
      int tmp {};
 
      while ( isss >> tmp )
      {
        wins.insert( tmp );
        cout << tmp << " ";
      }
      cout << endl;
    }
    set_intersection( draw.begin(), draw.end(), wins.begin(), wins.end(), std::inserter(intersect, intersect.begin()));
    size = intersect.size();

    if ( size > 0 )
      points = 0x1 << (size-1);
    cout << "points = " << points << endl;
    sum += points;

    for ( int i=0; i<size; ++i )
    { 
      cards[card+i+1] += cards[card];
    }

    cout << "cards = " << cards[card] << endl;
  }

  for ( int i=0; i<cards.size(); ++i )
  {
    total += cards[i+1];
  }

  cout << "sum = " << sum << endl;
  cout << "total = " << total << endl;

  is.close();
}
