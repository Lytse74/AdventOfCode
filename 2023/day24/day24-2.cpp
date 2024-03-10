#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <tuple>
#include <vector>
#include <set>
#include <limits>
#include <boost/multiprecision/cpp_int.hpp>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::set;
using std::tuple;
using std::make_tuple;
using std::get;

using namespace boost::multiprecision;


// Pencilpaper solution from Reddit https://www.reddit.com/r/adventofcode/comments/18pnycy/comment/kicuapd/

// points used:
// 246855340271664, 280044804035019, 302406287017222 @ 40, 21, 73
// 276006064958748, 296055609314709, 391999646036593 @ 14, 21, 24
// 293483465377495, 295344217447825, 424521127946914 @ -5, 21, -13

int main() {
  int256_t answer { -1 };
  tuple<int256_t, int256_t, int256_t> vp0 = make_tuple( -5, 21, -13 );
  tuple<int256_t, int256_t, int256_t> vp1 = make_tuple( 40, 21, 73 );
  tuple<int256_t, int256_t, int256_t> vp2 = make_tuple( 14, 21, 24 );

  tuple<int256_t, int256_t, int256_t> p0 = make_tuple( 293483465377495, 295344217447825, 424521127946914 );
  tuple<int256_t, int256_t, int256_t> p1 = make_tuple( 246855340271664, 280044804035019, 302406287017222 );
  tuple<int256_t, int256_t, int256_t> p2 = make_tuple( 276006064958748, 296055609314709, 391999646036593 );
  
  tuple<int256_t, int256_t, int256_t> vrp1 = make_tuple( get<0>(vp1) - get<0>(vp0), get<1>(vp1) - get<1>(vp0), get<2>(vp1) - get<2>(vp0) );
  tuple<int256_t, int256_t, int256_t> vrp2 = make_tuple( get<0>(vp2) - get<0>(vp0), get<1>(vp2) - get<1>(vp0), get<2>(vp2) - get<2>(vp0) );

  tuple<int256_t, int256_t, int256_t> rp1 = make_tuple( get<0>(p1) - get<0>(p0), get<1>(p1) - get<1>(p0), get<2>(p1) - get<2>(p0) );
  tuple<int256_t, int256_t, int256_t> rp2 = make_tuple( get<0>(p2) - get<0>(p0), get<1>(p2) - get<1>(p0), get<2>(p2) - get<2>(p0) );

  // Solve set of two linear equations x=x and z=z
  int256_t num1,num2;
  int256_t den1,den2;

  num2 = (get<1>(rp2)*get<0>(rp1)*get<2>(vrp1)) - (get<0>(vrp1)*get<1>(rp2)*get<2>(rp1)) + (get<1>(rp1)*get<2>(rp2)*get<0>(vrp1)) - (get<1>(rp1)*get<0>(rp2)*get<2>(vrp1) );
  den2 = get<1>(rp1)*((get<2>(vrp1)*get<0>(vrp2))-(get<0>(vrp1)*get<2>(vrp2)));
//num = (yr2*xr1*vzr1)-(vxr1*yr2*zr1)+(yr1*zr2*vxr1)-(yr1*xr2*vzr1)
//den = yr1*((vzr1*vxr2)-(vxr1*vzr2))
  
  num1 = (get<1>(rp1)*get<0>(rp2))+(get<1>(rp1)*get<0>(vrp2)*num2)/den2-(get<1>(rp2)*get<0>(rp1));
  den1 = get<1>(rp2)*get<0>(vrp1);
//num = (yr1*xr2)+(yr1*vxr2*t2)-(yr2*xr1)
//den = yr2*vxr1
  
  cout << "t1 time of first hail at collision ("<<num1<<"/"<<den1<<")=" << num1 / den1 << endl;
  cout << "t2 time of second hail at collision ("<<num2<<"/"<<den2<<")=" << num2 / den2 << endl;

  tuple<int256_t, int256_t, int256_t> cp1 = make_tuple( get<0>(p1) + num1 * get<0>(vp1)/den1, get<1>(p1) + num1 * get<1>(vp1)/den1, get<2>(p1) + num1 * get<2>(vp1)/den1 );
  tuple<int256_t, int256_t, int256_t> cp2 = make_tuple( get<0>(p2) + num2 * get<0>(vp2)/den2, get<1>(p2) + num2 * get<1>(vp2)/den2, get<2>(p2) + num2 * get<2>(vp2)/den2 );
  cout  << "collision one occurs at " << get<0>(cp1) <<  " " << get<1>(cp1) << " " << get<2>(cp1) << endl;
  cout  << "collision two occurs at " << get<0>(cp2) <<  " " << get<1>(cp2) << " " << get<2>(cp2) << endl;
 
  //#calculate the vector the rock travelled between those two collisions
  tuple<int256_t, int256_t, int256_t> m =  make_tuple( (( get<0>(cp2) - get<0>(cp1))*den1*den2)/(num2*den1-num1*den2)
                                                      ,(( get<1>(cp2) - get<1>(cp1))*den1*den2)/(num2*den1-num1*den2)
                                                      ,(( get<2>(cp2) - get<2>(cp1))*den1*den2)/(num2*den1-num1*den2) );
  cout << "vector that rocks " << get<0>(m) << " " << get<1>(m) << " " << get<2>(m) << " " << endl;

  //#calculate the initial position of the rock based on its vector
  tuple<int256_t, int256_t, int256_t> c = make_tuple( get<0>(cp1) - num1 * get<0>(m)/den1, get<1>(cp1) - num1 * get<1>(m)/den1, get<2>(cp1) - num1 * get<2>(m)/den1 );
  cout << "rock inital position " << get<0>(c) << " " << get<1>(c) << " " << get<2>(c) << endl;

  answer = get<0>(c) + get<1>(c) + get<2>(c);
  
  cout << "answer = " << answer << endl;
}