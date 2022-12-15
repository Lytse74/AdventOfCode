#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
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

  const int y_chk = 2000000;
  set<int> x_sset;
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

    // beacon
    if ( yb == y_chk )
      x_bset.insert( xb );

    // sensor
    int dt = distance( xs, ys, xs, y_chk);
    cout << "dt=" << dt << endl;
    if ( d >= dt )
    {
      for ( auto i=xs-(d-dt); i<xs+(d-dt)+1; i++ )
        x_sset.insert( i );

    }
  }

  cout << "sensors:" << x_sset.size() << endl;
  cout << "beacons:" << x_bset.size() << endl;

  set_difference(x_sset.begin(), x_sset.end(), x_bset.begin(), x_bset.end(), inserter(result, result.end()));
  
  cout << "result:" << result.size() << endl;

  //close the file
  is.close();
 }
