#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <list>
using namespace std;

int distance( int x1, int y1, int x2, int y2 )
{
  int d1,d2;

  d1 = x1 - x2;
  d2 = y1 - y2;

  if (d1<0) d1 = -d1;
  if (d2<0) d2 = -d2;

  return (d1+d2);
}

int main() {
  // open the file
  ifstream is("day15.input");
  string str;

  int y_chk;
  list<pair<int,int>> x_sset;
  list<pair<int,int>>::iterator x_sset_it;
  list<pair<pair<int,int>,int>> sensors;
  list<pair<pair<int,int>,int>>::iterator ss_it;
  set<int> x_bset;
  set<int> result;

  while ( getline( is, str ) )
  {
    istringstream iss(str);
    string str2;
    int cnt=0;
    int xs,ys,xb,yb;

    while ( iss >> str2 )
    {
      if ( cnt==2
        || cnt==3
        || cnt==8
        || cnt==9 )
      {
        istringstream iss2(str2);
        char ch;
        int n;
        iss2 >> ch >> ch;
        iss2 >> n;

        if ( cnt==2 ) xs=n;
        if ( cnt==3 ) ys=n;
        if ( cnt==8 ) xb=n;
        if ( cnt==9 ) yb=n;

        cout << str2 << ",";
      }
      cnt++;
    }
    cout << endl;
    cout << "S(" << xs << "," << ys << ") B(" << xb << "," << yb << ")" << endl;
    int d = distance( xs, ys, xb, yb );
    cout << "distance=" << d << endl;

    sensors.push_back(make_pair(make_pair(xs,ys),d));

  }

  for ( y_chk=0; y_chk<=4000000; y_chk++)
  {
    x_sset.clear();

    for (ss_it = sensors.begin(); ss_it != sensors.end(); ++ss_it)
    {
      // sensor
      int xs = ss_it->first.first;
      int ys = ss_it->first.second;
      int d = ss_it->second;
      int dt = distance( xs, ys, xs, y_chk);

      if ( d >= dt )
      {
        x_sset.push_back( make_pair( xs-(d-dt),xs+(d-dt) ) );
      }
    }

    x_sset.sort();

    int start=0; //x_sset.begin()->first;
    int ends=start;

    for (x_sset_it = x_sset.begin(); x_sset_it != x_sset.end(); ++x_sset_it)
    {
      if ( x_sset_it->first <= ends+1 && x_sset_it->second > ends )
        ends = x_sset_it->second;
    }
     
    if ( ends < 4000000 )
    {
      cout << "ends:" << ends << "y_chk:" <<  y_chk << endl;
      long res = ((long) ends+1)*4000000+ (long) y_chk;
      cout << "P2:" << res << endl;
    }
  }


  //close the file
  is.close();
 }
