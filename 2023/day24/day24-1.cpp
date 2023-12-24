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


int main() {
  // open the file
  std::ifstream is("day24.input");
  std::string str;

  vector<tuple<long long, long long, long long, long long, long long, long long>> line;

  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    string sstr;
    string snum;

    cout << str << endl;

    long long px {};
    long long py {};
    long long pz {};

    long long vx {};
    long long vy {};
    long long vz {};

    int idx {}; 
    while ( getline(iss,snum, ' '))
    {
      size_t pos = snum.find_first_of(",");

      if ( pos != std::string::npos )
        snum = snum.substr(0,pos);
      
      if (idx == 0)
        px = std::stoll(snum);
      if (idx == 1)
        py = std::stoll(snum);
      if (idx == 2)
        pz = std::stoll(snum);
      if (idx == 4)
        vx = std::stoll(snum);
      if (idx == 5)
        vy = std::stoll(snum);
      if (idx == 6)
        vz = std::stoll(snum);

      idx++;
    }
    line.push_back( make_tuple( px,vx,py,vy,pz,vz));
    cout << endl;

  }
  cout << endl;

  is.close();

  //long long c2mc1;
  //long long m1mm2;
  //long long m1tc1;
  //long long c2tm2;

  long double c2mc1;
  long double m1mm2;
  long double m1tc1;
  long double c2tm2;

  //const long double minarea = static_cast<long double>( 7 );
  //const long double maxarea = static_cast<long double>( 27 );
  const long double minarea = static_cast<long double>( 200000000000000 );
  const long double maxarea = static_cast<long double>( 400000000000000 );

  long long count {};

  for ( auto i=0; i<line.size()-1; i++ )
  {
    for ( auto j=i+1; j<line.size(); j++ )
    {
      // ax + c = bx + d
      // x = (d-c) / (a-b)
      //  y = a (d-c) / (a-b) + c
      //  of
      //  y = b (d-c) / (a-b) + d
      
      long double gradient1 {};
      long double intersect1 {};
      long double gradient2 {};
      long double intersect2 {};
      long double time1 {};
      long double time2 {};
      long double x {};
      long double y {};

      cout << "A:" << get<0>(line[i]) << " " << get<1>(line[i]) << " " << get<2>(line[i]) << " " <<  get<3>(line[i]) << endl;
      gradient1 = static_cast<long double>( get<3>( line[i]) ) / static_cast<long double>( get<1>( line[i] ) );
      intersect1 = -( static_cast<long double>( get<0>( line[i] ) ) * gradient1 - static_cast<long double>(get<2>(line[i])) );
      cout << "B:" << get<0>(line[j]) << " " << get<1>(line[j]) << " " << get<2>(line[j]) << " " <<  get<3>(line[j]) << endl;
      gradient2 = static_cast<long double>( get<3>( line[j]) ) / static_cast<long double>( get<1>( line[j] ) );
      intersect2 = -( static_cast<long double>( get<0>( line[j] ) ) * gradient2 - static_cast<long double>(get<2>(line[j])) );

      //intersectionX = (c2 - c1) / (m1 - m2)
      //c2mc1 = get<0>(line[j]) - get<0>(line[i]);
      c2mc1 = intersect2 - intersect1;
      //m1mm2 = get<1>(line[i]) - get<1>(line[j]);
      m1mm2 = gradient1 - gradient2;
      if ( m1mm2 != 0 )
      {
        //cout << "X:" << c2mc1 / m1mm2 << " ->  " << endl;
        x = c2mc1 / m1mm2;
      }

      if ( m1mm2 != 0 )
      { 
        time1 = (( c2mc1 / m1mm2 ) - static_cast<long double>( get<0>(line[i])))/static_cast<long double>( get<1>( line[i]) );
        time2 = (( c2mc1 / m1mm2 ) - static_cast<long double>( get<0>(line[j])))/static_cast<long double>( get<1>( line[j]) );
      }   
      //cout << "T1: " << time1 << " T2: " << time2 << endl;

      //intersectionY = (m1*c1 - c2*m2) / m1-m2 or intersectionY = m1 * intersectionX + c1
      //m1tc1 = get<1>(line[i]) * get<0>(line[i]);
      m1tc1 = gradient1 * intersect1;
      //c2tm2 = -1*get<0>(line[j])*get<1>(line[j]);
      c2tm2 = -1 * intersect2 * gradient2;
      if ( m1mm2 != 0 )
      {
        //cout << (m1tc1 -  c2tm2) / m1mm2 << endl;
        //cout << get<0>(line[i]) + (c2mc1 / m1mm2) * get<1>(line[i]) << endl;
        //cout << "Y:" << ( m1tc1 + c2tm2 ) / m1mm2 << endl;
        //cout << "\tY1:" << gradient1 * c2mc1 / m1mm2 + intersect1 << endl;
        //cout << "\tY2:" << gradient2 * c2mc1 / m1mm2 + intersect2 << endl;
        y = gradient1 * c2mc1 / m1mm2 + intersect1;
      }

      if ( m1mm2 == 0 )
      { 
        cout << "Hailstones' paths are parallel; they never intersect." << endl;
      }
      else if ( time1 <0 || time2 <0 )
      {
        if ( time1 < 0 && time2 < 0)
        {
          cout << "Hailstones' paths crossed in the past for both hailstones." << endl;
        }
        else if ( time1 < 0 )
        {
          cout << "Hailstones' paths crossed in the past for hailstone A." << endl;
        }
        else
        {
          cout << "Hailstones' paths crossed in the past for hailstone B." << endl; 
        }
      }
      else
      {
        if ( x >= minarea && y >= minarea && x <= maxarea && y <= maxarea )
        {
          cout << "Hailstones' paths will cross inside the test area (at x=" << x << ", y=" << y << ")." << endl;
          count++;
        }
        else
        {
          cout << "Hailstones' paths will cross outside the test area (at x=" << x << ", y=" << y << ")." << endl;
        }
      }


      



    }
  }
  cout << "count = " << count << endl;
}