#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;



int main() {
  // open the file
  ifstream is("day20.input");
  long long i;
  long long dkey = 811589153;

  list<pair<long long,int>> my_list;
  list<pair<long long,int>> my_orglist;
  list<pair<long long,int>>::iterator it;
  list<pair<long long,int>>::iterator oit;

  int count = 0;

  while ( is >> i )
  {
    my_list.push_back( make_pair( i*dkey, ++count ) );
    my_orglist.push_back( make_pair( i*dkey, count ) );
  }

  //close the file
  is.close();

  int s = my_list.size()-1;
  for (it = my_list.begin(); it != my_list.end(); it++)
  {
    cout << it->first << endl;
  }


  for ( int r=0; r<10; r++)
  {
  for (oit = my_orglist.begin(); oit != my_orglist.end(); oit++)
  {
    for (it = my_list.begin(); it != my_list.end(); it++)
    {
       if ( it->first == oit->first && it->second == oit->second )
         break;
    }
    
    if ( it != my_list.end() )
    {
      auto de = distance( it, my_list.end() );
      auto j = it->first % s;
      if (j<0) { j+=s; }
      if ( j<de )
      { 
        j += 1;
      }
      else
      {
        j += 2;
      }
      auto rit = next( it, j );
      //cout << j << ',' << de << ',' << rit->first << endl;

      my_list.insert( rit, make_pair( it->first, it->second ) );
      it = my_list.erase( it );
    }
  }
  for (it = my_list.begin(); it != my_list.end(); it++)
  {
    cout << it->first << endl;
  }
  }


/*
Initial arrangement:
811589153, 1623178306, -2434767459, 2434767459, -1623178306, 0, 3246356612
After 1 round of mixing:
0, -2434767459, 3246356612, -1623178306, 2434767459, 1623178306, 811589153
After 2 rounds of mixing:
0, 2434767459, 1623178306, 3246356612, -2434767459, -1623178306, 811589153
After 3 rounds of mixing:
0, 811589153, 2434767459, 3246356612, 1623178306, -1623178306, -2434767459
After 4 rounds of mixing:
0, 1623178306, -2434767459, 811589153, 2434767459, 3246356612, -1623178306
After 5 rounds of mixing:
0, 811589153, -1623178306, 1623178306, -2434767459, 3246356612, 2434767459
After 6 rounds of mixing:
0, 811589153, -1623178306, 3246356612, -2434767459, 1623178306, 2434767459
After 7 rounds of mixing:
0, -2434767459, 2434767459, 1623178306, -1623178306, 811589153, 3246356612
After 8 rounds of mixing:
0, 1623178306, 3246356612, 811589153, -2434767459, 2434767459, -1623178306
After 9 rounds of mixing:
0, 811589153, 1623178306, -2434767459, 3246356612, 2434767459, -1623178306
After 10 rounds of mixing:
0, -2434767459, 1623178306, 3246356612, -1623178306, 2434767459, 811589153
*/



  // find zero
  for (it = my_list.begin(); it != my_list.end(); it++)
  {
    if ( it->first == 0 )
      break;

  }

  cout << it->first << endl;
  auto de = distance( it, my_list.end() );

  auto n1000 = 1000 % ( s+1 );
  if ( n1000 >= de )
    ++n1000;
  auto n2000 = 2000 % ( s+1 );
  if ( n2000 >= de )
    ++n2000;
  auto n3000 = 3000 % ( s+1 );
  if ( n3000 >= de )
    ++n3000;

  auto nit1 = next( it, n1000 );
  auto nit2 = next( it, n2000 );
  auto nit3 = next( it, n3000 );

  cout << nit1->first << endl;
  cout << nit2->first << endl;
  cout << nit3->first << endl;


  cout << "result: " << nit1->first + nit2->first + nit3->first << endl;
}
