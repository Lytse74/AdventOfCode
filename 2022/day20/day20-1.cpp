#include <fstream>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;



int main() {
  // open the file
  ifstream is("day20.input");
  int i;

  list<pair<int,bool>> my_list;
  list<pair<int,bool>>::iterator it;

  while ( is >> i )
  {
    my_list.push_back( make_pair( i, true ) );
  }

  //close the file
  is.close();

  int s = my_list.size()-1;

  for (it = my_list.begin(); it != my_list.end(); it++)
  {
    cout << it->first << endl;
  }

  it = my_list.begin(); 
  while ( it != my_list.end() )
  {
    if ( it->second )
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
      cout << j << ',' << de << ',' << rit->first << endl;

      my_list.insert( rit, make_pair( it->first, false ) );
      it = my_list.erase( it );
    }
    else
    {
      it++;
    }
  }

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
