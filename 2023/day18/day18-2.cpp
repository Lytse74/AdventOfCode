#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::make_pair;
using std::tuple;
using std::make_tuple;
using std::set;

void count( vector<pair<int,int>> p )
{
  int pmxr {};
  int pmxc {};
  int pmnr {};
  int pmnc {};

  for ( auto pt: p )
  { 
    if ( pt.first <= pmnr ) pmnr = pt.first;
    if ( pt.first >= pmxr ) pmxr = pt.first;
    if ( pt.second <= pmnc ) pmnc = pt.second;
    if ( pt.second >= pmxc ) pmxc = pt.second;
  }

  cout << "grid = " << pmxc - pmnc +1 << " cols X " << pmxr - pmnr +1 << " rows" << endl;
  long long counter {};

  vector<pair<int,int>>::iterator p_it;
  vector<pair<int,int>>::iterator p2_it;

  for ( auto i= pmnr; i<= pmxr; i++ )
  {
    set<tuple<char,int,int,int,int>> segments;
    set<pair<int,char>> points;

    // https://stackoverflow.com/questions/1377084/unbuffered-output-with-cout
    cout << std::unitbuf;
    if ( (i % 100000) == 0)
      cout << 'z' << endl;
    else if ( (i % 1000) == 0)
      cout << '.';

    // find the line segments on this row
    p2_it = p.begin();
    for ( p_it = p2_it+1; p_it < p.end(); p_it++, p2_it++ )
    {
      if ( p_it->first == i && p2_it->first == i )
      {
        segments.insert( make_tuple( 'H', p_it->first, p_it->second,p2_it->first,p2_it->second));
        points.insert( make_pair( p_it->second,'H'));
        points.insert( make_pair( p2_it->second,'H'));
      }
      else if ( p_it->first == i && p2_it->first > i || p_it->first > i && p2_it->first == i )
      {
        segments.insert( make_tuple( 'D', p_it->first, p_it->second,p2_it->first,p2_it->second));
        points.insert( make_pair( p_it->second,'D'));
      }
      else if ( p_it->first == i && p2_it->first < i || p_it->first < i && p2_it->first == i )
      {
        segments.insert( make_tuple( 'U', p_it->first, p_it->second,p2_it->first,p2_it->second));
        points.insert( make_pair( p_it->second,'U'));
      }
      else if ( p_it->first<i && p2_it->first>i )
      {
        segments.insert( make_tuple( 'C', p_it->first, p_it->second,p2_it->first,p2_it->second));
        points.insert( make_pair( p_it->second,'C'));
      }
      else if ( p_it->first>i && p2_it->first<i )
      {
        segments.insert( make_tuple( 'K', p_it->first, p_it->second,p2_it->first,p2_it->second));
        points.insert( make_pair( p_it->second,'K'));
      }
    }

    bool out_not_in = true;
    bool up_not_down = false;
    bool down_not_up = false;
    bool hline = false;
    bool vline = false;
    int cpos {};
    int ppos {};

    set<pair<int,char>>::iterator it_pts;

    it_pts = points.begin();
    cpos = it_pts->first;

    while( it_pts != points.end() )
    {
      ppos = cpos;
      cpos = it_pts->first;

      int dpos = cpos-ppos;
      if ( vline )
      {
        vline =false;
        counter++;
      }
      
      if (dpos-1>0 && ( hline || !out_not_in))
        counter+=(dpos-1);

      if (it_pts->second == 'H')
        hline = !hline;
      else if (it_pts->second == 'U')
      {
        up_not_down = !up_not_down;
        vline = true;
      }
      else if (it_pts->second == 'D')
      {
        vline = true;
        down_not_up = !down_not_up;
      }
      else if (it_pts->second == 'K')
      {
        vline = true;
        out_not_in = !out_not_in;
      }
      else if (it_pts->second == 'C')
      {
        vline = true;
        out_not_in = !out_not_in;
      }
      if (up_not_down && down_not_up)
      {
        out_not_in = !out_not_in;
        up_not_down = false;
        down_not_up = false;
      }

      it_pts++;
    }

    if ( vline )
    {
      counter++;
    }
  }

  cout << "counter = " << counter << endl;
}

int main() {
  // open the file
  std::ifstream is("day18.input");
  std::string str;
  vector<pair<int,int>> p;
  p.push_back( make_pair(0,0) );
  int trow {};
  int tcol {};

  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::string sstr;
    std::string dir;
    std::string length;
    int len{};
    std::string color;
    
    std::string dir2;
    std::string length2;
    long long len2 {};
    
    iss >> dir;
    iss >> length;
    iss >> color;

    len = stoi(length);
    len2 = std::stoll( color.substr(2,5), 0, 16 );

    if ( color.substr(7,1) == "0") dir2= "R";
    if ( color.substr(7,1) == "1") dir2= "D";
    if ( color.substr(7,1) == "2") dir2= "L";
    if ( color.substr(7,1) == "3") dir2= "U";


    cout << color << len << dir << len2 << dir2 << endl;

    if ( dir2 == "D" ) trow += len2;
    if ( dir2 == "R" ) tcol += len2;
    if ( dir2 == "U" ) trow -= len2;
    if ( dir2 == "L" ) tcol -= len2;

    p.push_back( make_pair( trow,tcol ));

  }
  
  is.close();

  count(p);

  cout << endl;
}